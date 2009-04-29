#include "SoLongSucker.h"
#include "Player.h"
#include "PlayersMsg.h"
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sstream>
using namespace std;
using namespace IOMgmt;
using namespace SimMgmt;

#include "JacobJerk.h"
#include "NancyNice.h"
#include "RandyRandom.h"

Player* allocatePlayerFromString(const std::string& name,int handsize,int chipno)
{
	if(name=="JacobJerk{")
		return new AI::JacobJerk(handsize,chipno);
	else if(name=="NancyNice{")
		return new AI::NancyNice(handsize,chipno);
	else if(name=="RandyRandom{")
		return new AI::RandyRandom(handsize,chipno);
	else
		return NULL;
}


SoLongSucker::SoLongSucker()
{
	ifstream& fin = simInMgr.getStream();

	string token;
	// Parse opening token
	fin >> token;
	if ( token != "SoLongSucker{" )
		throw AppError(string("Incorrect Token '" + token + "', excpected token 'SoLongSucker{' !"),
		               string("SoLongSucker::SoLongSucker()"));

	// parse data member # of players
	fin >> token;
	if ( token != "numPlayers:" )
		throw AppError(string("Incorrect Token '" + token + "', excpected token 'numPlayers:' !"),
		               string("SoLongSucker::SoLongSucker()"));
	fin >> token;
	numPlayers = atoi(token.c_str());
	if ( numPlayers <= 0 )
		throw AppError(string("Number of Players is not positive!"),
		               string("SoLongSucker::SoLongSucker()"));

	fin >> token;
	if ( token != "numChipsPerPlayer:" )
		throw AppError(string("Incorrect Token '" + token + "', excpected token 'numChipsPerPlayer:' !"),
		               string("SoLongSucker::SoLongSucker()"));
	fin >> token;
	numChipsPerPlayer = atoi(token.c_str());
	if ( numChipsPerPlayer <= 0 )
		throw AppError(string("Number of Chips per Player is not positive!"),
		               string("SoLongSucker::SoLongSucker()"));	


	players    = new AGENTPTR[numPlayers];
	// Construct Student instances
	for (int i = 0; i < numPlayers; i++)
	{
		simInMgr.setFilePos();
		std::string playertag;
		fin >> playertag;
		players[i] = allocatePlayerFromString(playertag,numChipsPerPlayer,i);
		simInMgr.resetFilePos();		
		players[i]->Extract();
	}

	// Parse closing token
	fin >> token;
	if ( token != "}SoLongSucker" )
		throw AppError(string("Incorrect Token '" + token + "', excpected token '}SoLongSucker' !"),
		               string("SoLongSucker::SoLongSucker()"));

	numEvents = 0;

}



SoLongSucker::~SoLongSucker()
{
	for ( int i = 0 ; i < numPlayers ; i++ ) 
		delete players[i];
	delete [] players;
}


void SoLongSucker::Initialize()
{
	ostream& simlog = simOutMgr.getStream();

	// Construct new Players object
	PlayersMsg *playersm = new PlayersMsg(numPlayers);
	int i;

	// Set players
	for ( i=0; i < numPlayers; i++ )
	{
		std::ostringstream oss;
		oss << i;
		playersm->setAgent( oss.str() , players[i] );
	}

	// Initialize players
	for ( i=0; i < numPlayers; i++ )
		players[i]->Initialize( playersm );

	simOutMgr.newLine();
	simlog << *playersm;
	simOutMgr.newLine();

	srand(time(NULL));
	int playerselect=rand() % numPlayers;
	for ( i=0;i < numPlayers; i++)
		players[i]->Dispatch(dynamic_cast<Player*>(players[i])->AcceptChipMsgGiveTurn(playerselect));

	delete playersm;
}

void SoLongSucker::Simulate()
{
	Event    e;
	Message *msg;
	string   token;
	ostream& simlog = simOutMgr.getStream();


	while ( theEventMgr.moreEvents() )
	{
		//retrive next event and message
		e   = theEventMgr.getNextEvent();
		msg = e.getMsg();

		// Output to simlog
		simOutMgr.newLine();
		simlog << e;
		simOutMgr.newLine();

		// Dispatch
		e.getRecvr()->Dispatch( msg );

		// destruct message
		delete msg;

		// Update statistical data
		lastEvent = e.getTime();
		numEvents++;
	}
	//code to terminate all players
	for ( int i = 0; i < numPlayers; i++)
	{
		players[i]->Dispatch(dynamic_cast<Player*>(players[i])->AcceptTerminate());
	}
}//Simulate

void SoLongSucker::Insert()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simlog << "SoLongSucker{ ";
	simOutMgr.pushMargin();

	simlog << "numPlayers: " << numPlayers << endl;
	simlog << "numChipsPerPlayer: " << numChipsPerPlayer; 
	simOutMgr.advToMargin();

	for (int i = 0 ; i < numPlayers ; i++ )
	{
		simlog << *(dynamic_cast<Player*>(players[i]));
		simOutMgr.advToMargin();
	}
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
	simlog << "}SoLongSucker ";
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
}

void SoLongSucker::WrapUp()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.newLine();
	simOutMgr.pushMargin();

	simlog << "Simulation Statistics:";

	simOutMgr.advToMargin();
	simlog << "Number of events : " << numEvents;

	simOutMgr.advToMargin();
	simlog << "Time of Last event : " <<  lastEvent;

	simOutMgr.advToMargin();
	simlog << "Total simulation time : " << theEventMgr.clock();

	simOutMgr.advToMargin();
	simOutMgr.popMargin();
	simOutMgr.newLine();

}

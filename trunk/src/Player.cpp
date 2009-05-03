#include "Player.h"
#include "IOMacros.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "PlayersMsg.h"
using namespace SimMgmt;

Player::Player()
{
}

Player::Player(const unsigned sizeOfHand, const Chip Id, Board* inboard) :
		id(Id), hand(sizeOfHand, Id), board(inboard),dead(false)
{
}

Player::~Player()
{
}
Message  *Player::AcceptTerminate()
{
	std::ostringstream oss;
	oss <<  "player " << id;
	return new Message(4,"Terminate: " + oss.str());
}

void Player::Initialize(SimMgmt::Message* players)
{
	PlayersMsg* pm=dynamic_cast<PlayersMsg*>(players);
	otherplayers.insert(otherplayers.begin(),(Player**)(pm->getPlayers()),(Player**)(pm->getPlayers())+pm->getNumAgents());
}

void Player::doTerminate()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simlog << "At time: " << theEventMgr.clock();
	simlog << ", Student: " << id <<  " is terminating!";
	simOutMgr.advToMargin();
	simlog << *this;
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
}

void Player::TakePile(std::list<Pile>::iterator i)
{
	std::vector<Chip> pilep(i->begin(),i->end());
	int ignorev=this->PickUpPile(pilep);
	
	hand.insert(pilep.begin(),pilep.begin()+ignorev);
	hand.insert(pilep.begin()+ignorev+1,pilep.end());
	
	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simOutMgr.getStream() << "Player " << id << " picked up pile " << *i << endl;
	simOutMgr.getStream() << "Player discarded a Chip of type " << pilep[ignorev] << " from the pile." << endl;
	simOutMgr.getStream() << "Player hand now looks like " << hand << endl;
	board->takePile(i);
}

void Player::TakeTurn()
{
	ostream& simlog = simOutMgr.getStream();
	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simOutMgr.advToMargin();	
	simlog << "It is now Player " << id << "'s turn.";
	simOutMgr.popMargin();
	
	std::vector<Player*> playerchoices=otherplayers;
	MoveProposal mp=PerformMove(playerchoices);
	executeMove(mp,playerchoices);
}

void Player::doGiveTurn(const Chip Id)
{
	currentturn=Id;
	
	if(hand.size()==0)
	{	
		if(dead==false)
		{
			simOutMgr.newLine();
			simOutMgr.getStream() << "Player " << Id << " has been eliminated." << endl;
			dead=true;
		}
		throw 23;
	}
	if(Id==id)
		TakeTurn();
	otherplayers[Id]->Dispatch(otherplayers[Id]->AcceptBargainOffer(CreateBargain()));
}

void Player::doBargainOffer(Bargain* b)
{
	bool accepted=AcceptOrRejectBargain(b);
	if(accepted)
	{	
		//3
		SimMgmt::simOutMgr.getStream() << "Player " << getId() << " accepted a bargain!" << endl;
		SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,otherplayers[rand()%otherplayers.size()], AcceptBargainAccept(*b)));
	}
	else
	{
		SimMgmt::simOutMgr.getStream() << "Player " << getId() << " rejected a bargain!" << endl;
		SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,otherplayers[rand()%otherplayers.size()], AcceptBargainReject(*b)));
		//5

	}
}

void Player::doBargainAccept(Bargain* b)
{
	bargains.push_back(*b);
}

void Player::doBargainReject(Bargain* b)
{
}

void Player::Dispatch(SimMgmt::Message* msg)
{
	int h          = msg->getHandler();
	switch ( h )
	{
		case 1:
		{
			try
			{
				doGiveTurn(dynamic_cast<ChipMsg*>(msg)->getChip());
			}
			catch(int)
			{
				Chip externalchip;
				for(int i=0;i<otherplayers.size();i++)
				{
					if(!otherplayers[i]->Dead() && getId()!=i)
					{
						externalchip=i;
						simOutMgr.newLine();
						simOutMgr.pushMargin();
						simOutMgr.advToMargin();	
						simOutMgr.getStream() << "Attempted to give player " << id << " the turn, but player is dead.  Re-Giving turn to " << i <<".";
						simOutMgr.popMargin();
						SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,otherplayers[externalchip], AcceptChipMsgGiveTurn(externalchip)));
						break;
					}
				}
			}
			break;
		}
		case 2:
		{
			doBargainOffer(&dynamic_cast<BargainMsg*>(msg)->getBargain());
			break;
		}
		case 3:
		{
			doBargainAccept(&dynamic_cast<BargainMsg*>(msg)->getBargain());
			break;
		}
		case 4: doTerminate(); break;
		case 5:
		{
			doBargainReject(&dynamic_cast<BargainMsg*>(msg)->getBargain());
			break;
		}
		default: throw AppError("Undefined handler ID!", "Student::Dispatch()");
	}
}

BargainMsg* Player::AcceptBargainOffer(const Bargain& b)
{
	return new BargainMsg(2,"There was a bargain offered",b);
}

BargainMsg* Player::AcceptBargainAccept(const Bargain& b)
{
	return new BargainMsg(3,"There was a bargain accepted",b);
}

BargainMsg* Player::AcceptBargainReject(const Bargain& b)
{
	return new BargainMsg(5,"There was a bargain rejected",b);
}

ChipMsg* Player::AcceptChipMsgGiveTurn(Chip c)
{	
	ostringstream oss;
	oss << "The turn has been given to " << c;	
	return new ChipMsg(1,oss.str(),c);
}

template<class InputIterator, class T>
  InputIterator myfind ( InputIterator first, InputIterator last, const T& value )
  {
    for ( ;first!=last; first++) if ( *first==value ) break;
    return first;
  }

void Player::executeMove(const MoveProposal& move,std::vector<Player*>& playerchoices)
{
	hand.erase(hand.find(move.getChip()));	
	if(board->addChipToPile(move))
	{
		if(!otherplayers[(move.getChip())]->Dead())
		{
			otherplayers[(move.getChip())]->TakePile(move.getPile());
			SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this, otherplayers[(move.getChip())], AcceptChipMsgGiveTurn(move.getChip())));
		}	
	}
	else
	{
		if(board->isPile(move.getPile()))
		{	
			Pile& mypile=*move.getPile();
			for(int i=0;i<playerchoices.size();++i)
			{
			//	std::cout << i << "Y:" << playerchoices[i]->getId() << ':' << mypile.size() << std::endl;
				bool found=false;
				for(int j=0;j<mypile.size();j++)
				{
					if(mypile[j]==playerchoices[i]->getId())
					{
						found=true;
						break;
					}
				}			
				if(!found && !playerchoices[i]->Dead())
				{
					SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,playerchoices[i], AcceptChipMsgGiveTurn(playerchoices[i]->getId())));
					break;
				}
			}
			if(!playerchoices[0]->Dead())
				SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,otherplayers[mypile[0]], AcceptChipMsgGiveTurn(otherplayers[mypile[0]]->getId())));
		}
		else
		{
			if(!playerchoices[0]->Dead())
				SimMgmt::theEventMgr.postEvent(Event(theEventMgr.clock()+1, this,playerchoices[0], AcceptChipMsgGiveTurn(playerchoices[0]->getId())));
			
		}
	}
}

INSERT(Player)

void Player::Put()
{
	std::ostream& fout = simOutMgr.getStream();
	fout << TAG(hand) << " " << hand << " ";
	fout << TAG(id) << " " << id << " ";
	for(std::list<Bargain>::iterator i = bargains.begin(); i != bargains.end(); i++)
		fout << TAG(*i) << " " << *i << " ";
}

EXTRACT(Player)

void Player::Get() throw(IOMgmt::TokenError)
{
/*
	Note that this implementation does not read in any inital bargains to the Player
	std::ifstream& fin = simInMgr.getStream();

	for(int i = 0; i < 2; i++)
	{
		std::string token = "";
		fin >> token;
		if(token == TAG(id))
			fin >> id;
		else if(token == TAG(hand))
			fin >> hand;
		else
			throw IOMgmt::TokenError(std::string("Unexpected token '" + token + "', '" + TAG(id) + "' or '" + TAG(hand) + "' expected!"), std::string("Player::Get()"));
	}
*/
}

OUT_OPERATOR(Player)

IN_OPERATOR(Player)


/*
Student::Student():Agent()
{
}


Student::~Student()
{
}


void Student::Extract() throw(TokenError)
{
	string token;
	ifstream& fin = simInMgr.getStream();


	// Parse opening token
	fin >> token;
	if ( token != "Student{" )
		throw TokenError(string("Incorrect Token, '" + token + "', excpected 'Student{' !"),
		                 string("Student::Extract()"));

	// Parse data members
	Get();

	// Parse closing token
	fin >> token;
	if ( token != "}Student" )
		throw TokenError(string("Incorrect Token '" + token + "', excpected token '}Student' !"),
		                 string("Student::Get()"));
}

void Student::Get() throw(TokenError)
{
	string token;
	ifstream& fin = simInMgr.getStream();

	// parse inherited members
	Agent::Get();

	// parse token "QuestDelay"
	fin >> token;
	if ( token != "questdelay:" )
		throw TokenError(string("Incorrect Token '" + token + "', excpected 'questdelay:' !"),
		                 string("Student::Get(@1)"));

	// Parse question delay
	fin >> token;
	questDelay = atoi(token.c_str());

	// parse token "AnsrDelay"
	fin >> token;
	if ( token != "ansrdelay:" )
		throw TokenError(string("Incorrect Token '" + token + "', excpected 'ansrdelay:' !"),
		                 string("Student::Get(@2)"));

	// Parse answer delay
	fin >> token;
	ansrDelay = atoi(token.c_str());

	// parse token "scandelay"
	fin >> token;
	if ( token != "scandelay:" )
		throw TokenError(string("Incorrect Token '" + token + "', excpected 'scandelay:' !"),
		                 string("Student::Get(@3)"));

	// Parse scandelay
	fin >> token;
	scanDelay = atoi(token.c_str());

	// parse token "interest"
	fin >> token;
	if ( token != "interest:" )
		throw TokenError(string("Incorrect Token '" + token + "', excpected 'interest:' !"),
		                 string("Student::Get(@4)"));

	// Parse interest
	fin >> token;
	interest = atoi(token.c_str());
}

void Student::Insert()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	simlog << "Student{ ";
	Put();
	simOutMgr.advToMargin();
	simlog << "}Student ";
	simOutMgr.popMargin();
}

void Student::Put()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	Agent::Put();
	simOutMgr.advToMargin();
	simlog << " questdelay: " << questDelay;
	simOutMgr.advToMargin();
	simlog << " ansrdelay: "  << ansrDelay;
	simOutMgr.advToMargin();
	simlog << " scandelay: "  << scanDelay;
	simOutMgr.advToMargin();
	simlog << " interest: "   << interest;
	simOutMgr.popMargin();
}


void Student::Initialize(MSGPTR players)
{
	// Obtaining player's handle
	me  = (Student *)((Players *)players)->getAgent(NameOf());
	// Pick and Agent at random to send a question to.
	you = ((Players *)players)->getOthers(interest);

	// Construct new message
	Message *scanMsg = ((Student *)me)->AcceptScanComplete();

	// Construct new Event
	Event e( scanDelay , me , me, scanMsg );

	// Post Event
	theEventMgr.postEvent(e);

}

void Student::Dispatch  (MSGPTR msg)
{
	int h          = msg->getHandler();
	switch ( h )
	{
		case 1:
		{
			string content = ((SpeakMsg *)msg)->getContent();
			doQuestions(content);
			break;
		}
		case 2:
		{
			string content = ((SpeakMsg *)msg)->getContent();
			doAnswers(content);
			break;
		}
		case 3: doScanComplete(); break;
		case 4: doTerminate(); break;
		default: throw AppError("Undefined handler ID!", "Student::Dispatch()");
	}

}//Dispatch

SpeakMsg *Student::AcceptQuestion(string aquestion)
{
	return new SpeakMsg(1,"question",aquestion);
}

SpeakMsg *Student::AcceptAnswer(string response)
{
	return new SpeakMsg(2,"answer",response);
}


Message  *Student::AcceptScanComplete()
{
	return new Message(3,"Scan is complete for " + NameOf());
}

Message  *Student::AcceptTerminate()
{
	return new Message(4,"Terminate: " + NameOf());
}


void Student::doScanComplete()
{
	int time = theEventMgr.clock() + questDelay;
	lastyou = 0;
	// Construct new message
	SpeakMsg *strMsg = ((Student *)you[lastyou])->AcceptQuestion("What is your name?");

	// Construct new Event
	Event e( time , me , you[lastyou] , strMsg );

	// Post Event
	theEventMgr.postEvent(e);
}

void Student::doQuestions(string question)
{
	int time = theEventMgr.clock() + ansrDelay ;
	SpeakMsg *strMsg = AcceptAnswer("My name is:" + NameOf() + "!" );

	Event e( time , me , theEventMgr.getSendr() , strMsg );

	theEventMgr.postEvent(e);
}

void Student::doAnswers(string response)
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simlog << "At time: " << theEventMgr.clock();
	simlog << ", Student: " + NameOf() + " received the following response from: " + theEventMgr.getSendr()->NameOf();
	simOutMgr.advToMargin();
	simlog << response;
	simOutMgr.popMargin();
	simOutMgr.advToMargin();

	if ( lastyou < interest-1 )
	{
		int time = theEventMgr.clock() + questDelay;
		SpeakMsg *strMsg = ((Student *)you[++lastyou])->AcceptQuestion("What is your name?");

		// Construct new Event
		Event e( time , me , you[lastyou] , strMsg );

		// Post Event
		theEventMgr.postEvent(e);
	}//if

}


void Student::doTerminate()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.newLine();
	simOutMgr.pushMargin();
	simlog << "At time: " << theEventMgr.clock();
	simlog << ", Student: " + NameOf() + " is terminating!";
	simOutMgr.advToMargin();
	simlog << *me;
	simOutMgr.popMargin();
	simOutMgr.advToMargin();
}


*/

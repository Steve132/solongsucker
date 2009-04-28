#include "Player.h"
#include "IOMacros.h"
#include <sstream>
using namespace SimMgmt;

Player::Player()
{
}

Player::Player(const unsigned sizeOfHand, const Chip Id) :
		id(Id), hand(sizeOfHand, Id)
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
}

void Player::Dispatch(SimMgmt::Message* msg)
{
}

Bargain* Player::AcceptBargainOffer()
{
}

Bargain* Player::AcceptBargainAccept()
{
}

Bargain* Player::AcceptBargainReject()
{
}

void Player::TakeTurn()
{
}

ChipMsg* Player::AcceptChipMsgGiveTurn(std::list<Player> validPlayers)
{
}

INSERT(Player)

PUT(Player)

EXTRACT(Player)

GET(Player)

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

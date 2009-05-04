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


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


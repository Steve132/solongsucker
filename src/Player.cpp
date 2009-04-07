#include "Player.h"

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

void Player::AcceptTurn()
{
}

SimMgmt::Message* Player::GiveTurn(std::list<Player> validPlayers)
{
}

INSERT(Player)

PUT(Player)

EXTRACT(Player)

GET(Player)

OUT_OPERATOR(Player)

IN_OPERATOR(Player)


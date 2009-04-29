#include "RandyRandom.h"
#include "IOMacros.h"
using namespace AI;

RandyRandom::RandyRandom(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

Bargain RandyRandom::CreateBargain()
{
	return Bargain();
}

EXTRACT(RandyRandom)

INSERT(RandyRandom)

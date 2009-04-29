#include "RandyRandom.h"
#include "IOMacros.h"
using namespace AI;

RandyRandom::RandyRandom(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

EXTRACT(RandyRandom)

INSERT(RandyRandom)

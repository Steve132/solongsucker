#include "RandyRandom.h"
#include "IOMacros.h"
using namespace AI;

RandyRandom::RandyRandom(const unsigned sizeOfHand, const Chip Id):Player(sizeOfHand,Id)
{
}

EXTRACT(RandyRandom)

INSERT(RandyRandom)

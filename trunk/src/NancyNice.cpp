#include "NancyNice.h"
#include "IOMacros.h"
using namespace AI;

NancyNice::NancyNice(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

EXTRACT(NancyNice)

INSERT(NancyNice)

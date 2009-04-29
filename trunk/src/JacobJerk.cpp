#include "JacobJerk.h"
#include "IOMacros.h"
using namespace AI;

JacobJerk::JacobJerk(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

EXTRACT(JacobJerk)

INSERT(JacobJerk)

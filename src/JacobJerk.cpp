#include "JacobJerk.h"
#include "IOMacros.h"
using namespace AI;

JacobJerk::JacobJerk(const unsigned sizeOfHand, const Chip Id):Player(sizeOfHand,Id)
{
}

EXTRACT(JacobJerk)

INSERT(JacobJerk)

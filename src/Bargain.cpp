#include "Bargain.h"
#include "IOMacros.h"

Bargain::Bargain(const MoveProposal currentMoveProposal, const std::multiset<Chip> Chips, const Chip NextTurn) :
	move(currentMoveProposal), chips(Chips), nextTurn(NextTurn)
{
}

Bargain::~Bargain()
{
}

INSERT(Bargain)

PUT(Bargain)

EXTRACT(Bargain)

GET(Bargain)

OUT_OPERATOR(Bargain)

IN_OPERATOR(Bargain)


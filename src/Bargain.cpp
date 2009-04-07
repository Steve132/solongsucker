#include "Bargain.h"

Bargain::Bargain(const int Handler, const std::string Description) : SimMgmt::Message(Handler, Description)
{
}

Bargain::Bargain(const int Handler, const std::string Description, const Move currentMove, const std::multiset<Chip> Chips, const Chip NextTurn) :
	SimMgmt::Message(Handler, Description), move(currentMove), chips(Chips), nextTurn(NextTurn)
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


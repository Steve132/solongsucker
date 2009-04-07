#include "Bargain.h"

Bargain::Bargain(int Handler, std::string Description) : SimMgmt::Message(Handler, Description)
{
}

Bargain::Bargain(int Handler, std::string Description, Move currentMove, std::multiset<Chip> Chips, Chip NextTurn) :
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


#include "Bargain.h"
#include "IOMacros.h"

Bargain::Bargain()
{
}

Bargain::Bargain(const MoveProposal currentMoveProposal, const std::multiset<Chip> Chips, const Chip NextTurn) :
		move(currentMoveProposal), chips(Chips), nextTurn(NextTurn)
{
}

Bargain::~Bargain()
{
}

INSERT(Bargain)

void Bargain::Put()
{
	std::ostream& fout = SimMgmt::simOutMgr.getStream();
	fout << TAG(move) << " " << move << " ";
	fout << TAG(nextTurn) << " " << nextTurn << " ";
	fout << TAG(numChips) << " " << chips.size() << " ";
	if(chips.size() > 0)
	{
		fout << TAG(chips) << " ";
		for(std::multiset<Chip>::iterator i = chips.begin(); i != chips.end(); i++)
			fout << *i << " ";
	}
}

EXTRACT(Bargain)

GET(Bargain)

OUT_OPERATOR(Bargain)

IN_OPERATOR(Bargain)


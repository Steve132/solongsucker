#include "Board.h"
#include "IOMacros.h"

Board::Board()
{
}

Board::~Board()
{
}

bool Board::addChipToPile(const MoveProposal& move)
{
	unsigned count = 0;
	std::list<Pile>::iterator pile = move.getPile();
	for(std::list<Pile>::iterator i = stacks.begin(); i != stacks.end(); i++)
	{
		if(pile == i)
			return (addChipToPile(move.getChip(), count));
		count++;
	}
	createNewPile(move.getChip());
	return true;
}

bool Board::addChipToPile(const Chip c, const unsigned index)
{
	// If index beyond number of Piles, create new Pile
	unsigned count = 0;
	if(index > stacks.size())
		createNewPile(c);

	// Add chip to Pile at index
	std::list<Pile>::iterator i = stacks.begin();
	while(count < index)
	{
		i++;
		count++;
	}
	Chip prev = (*i).back();
	(*i).push_back(c);

	// Check to see if two identical Chips are at top of pile
	return (prev == c);
}

void Board::createNewPile(const Chip c)
{
	Pile p;
	stacks.push_back(p);
	(*(stacks.end())).push_back(c);
}

void Board::takePile(std::list<Pile>::iterator i)
{
	stacks.erase(i);
}

void Board::discardChips(const std::multiset<Chip> chips)
{
	deadbox.insert(chips.begin(), chips.end());
}

INSERT(Board)

PUT(Board)

EXTRACT(Board)

GET(Board)

OUT_OPERATOR(Board)

IN_OPERATOR(Board)


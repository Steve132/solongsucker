#include "RandyRandom.h"
#include "IOMacros.h"
using namespace AI;

RandyRandom::RandyRandom(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

void RandyRandom::PerformMove()
{
	// Examine bargains in list
	std::list<Bargain>::iterator i;
	for(i = bargains.begin(); i != bargains.end(); i++)
	{
		;
	}

	// Add chip to first pile as default if no bargains desired to be performed?
//	if(i == bargains.end())
//		board->addChipToPile(id, 0);
}


Bargain RandyRandom::CreateBargain()
{
	return Bargain();
}

void RandyRandom::AcceptOrRejectBargain(Bargain* b)
{
}

EXTRACT(RandyRandom)

INSERT(RandyRandom)

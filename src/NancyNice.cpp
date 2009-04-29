#include "NancyNice.h"
#include "IOMacros.h"
using namespace AI;

NancyNice::NancyNice(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

void NancyNice::PerformMove()
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


Bargain NancyNice::CreateBargain()
{
	return Bargain();
}

void NancyNice::AcceptOrRejectBargain(Bargain* b)
{
}

EXTRACT(NancyNice)

INSERT(NancyNice)

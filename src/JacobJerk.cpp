#include "JacobJerk.h"
#include "IOMacros.h"
using namespace AI;

JacobJerk::JacobJerk(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

int JacobJerk::PickUpPile(std::vector<Chip>&)
{
	return 0;
}

MoveProposal JacobJerk::PerformMove(std::vector<Player*>&)
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

Bargain JacobJerk::CreateBargain()
{
	return Bargain();
}

bool JacobJerk::AcceptOrRejectBargain(Bargain* b)
{
}

EXTRACT(JacobJerk)

INSERT(JacobJerk)

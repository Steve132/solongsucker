#include "NancyNice.h"
#include "IOMacros.h"
using namespace AI;

NancyNice::NancyNice(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}

Bargain NancyNice::CreateBargain()
{
	return Bargain();
}

EXTRACT(NancyNice)

INSERT(NancyNice)

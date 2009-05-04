#include "NancyNice.h"
#include "IOMacros.h"
#include "Pile.h"
#include <cstdlib>
#include <algorithm>
using namespace AI;

NancyNice::NancyNice(const unsigned sizeOfHand, const Chip Id, Board* board):Player(sizeOfHand,Id,board)
{
}
int NancyNice::PickUpPile(std::vector<Chip>& v)
{
	std::vector<Chip>::iterator ip=find(v.begin(),v.end(),getId());
	return ip == v.end() ? 0 : static_cast<int>(v.end()-ip);
}
MoveProposal NancyNice::PerformMove(std::vector<Player*>& p)
{
	// Examine bargains in list
	/*std::list<Bargain>::iterator i;
	for(i = bargains.begin(); i != bargains.end(); i++)
	{
		;
	}*/
	
	std::list<Pile>::iterator it=board->getIterator();
	if(board->getNumPiles()!=0)
	{
		int rnum=rand() % (board->getNumPiles());	
		for(int i=0;i<rnum;++i)
		{
			it++;
		}
	}
	
	int rnum1=rand() % hand.size();
	std::multiset<Chip>::iterator ci=hand.begin();
	
	for(int i=0;i<rnum1;++i)
	{
		ci++;
	}
	Chip c=*ci;

	struct shuffunctorwrap
	{
		static ptrdiff_t myrandom (ptrdiff_t i) { return rand() % i;}
	};

	std::random_shuffle(p.begin(),p.end(),shuffunctorwrap::myrandom);
	return MoveProposal(it,c);

	// Add chip to first pile as default if no bargains desired to be performed?
//	if(i == bargains.end() )
//		board->addChipToPile(id, 0);
}



Bargain NancyNice::CreateBargain()
{
	return Bargain();
}

bool NancyNice::AcceptOrRejectBargain(Bargain* b)
{
	return true;
}

EXTRACT(NancyNice)

INSERT(NancyNice)

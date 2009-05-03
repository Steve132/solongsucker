#ifndef NANCYNICE_H
#define NANCYNICE_H

#include "Player.h"

namespace AI{

class NancyNice: public Player
{
public:
	NancyNice(const unsigned sizeOfHand, const Chip Id, Board* board);
	MoveProposal PerformMove(std::vector<Player*>&);
	Bargain CreateBargain();
	void AcceptOrRejectBargain(Bargain* b);
	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
};

}

#endif

#ifndef RANDYRANDOM_H
#define RANDYRANDOM_H

#include "Player.h"

namespace AI{

class RandyRandom: public Player
{
public:
	RandyRandom(const unsigned sizeOfHand, const Chip Id, Board* board);
	virtual int PickUpPile(std::vector<Chip>&);
	MoveProposal PerformMove(std::vector<Player*>&);
	Bargain CreateBargain();
	bool AcceptOrRejectBargain(Bargain* b);
	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
};
}

#endif

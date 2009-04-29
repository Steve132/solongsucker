#ifndef RANDYRANDOM_H
#define RANDYRANDOM_H

#include "Player.h"

namespace AI{

class RandyRandom: public Player
{
public:
	RandyRandom(const unsigned sizeOfHand, const Chip Id, Board* board);
	Bargain CreateBargain();
	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
};
}

#endif

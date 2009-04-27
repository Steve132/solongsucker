#ifndef NANCYNICE_H
#define NANCYNICE_H

#include "Player.h"

namespace AI{

class NancyNice: public Player
{
public:
	NancyNice(const unsigned sizeOfHand, const Chip Id);
	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
};

}

#endif

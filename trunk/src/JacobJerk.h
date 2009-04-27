#ifndef JACOBJERK_H
#define JACOBJERK_H

#include "Player.h"

namespace AI{

class JacobJerk: public Player
{
public:
	JacobJerk(const unsigned sizeOfHand, const Chip Id);
	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
};

}

#endif

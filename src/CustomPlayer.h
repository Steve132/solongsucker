#ifndef _CUSTOMPLAYER
#define _CUSTOMPLAYER

#include "Bargain.h"
#include "Chip.h"
#include "Player.h"

class CustomPlayer : public Player
{
public:
	enum property
	{
		AGGRESSIVENESS,
		ACCEPTIVENESS,
		IGNORANCE,		// etc.
		NUM_PROPERTIES
	};

	CustomPlayer();
	CustomPlayer(unsigned sizeOfHand, Chip id, property* properties = NULL);
	~CustomPlayer();

	virtual Bargain* AcceptBargainAccept();
	virtual Bargain* AcceptBargainReject();

	// To fulfill OODataDesign.doc
	friend std::ostream&  operator<<(std::ostream& fout, Pile& stack);
	friend std::ifstream& operator>>(std::ifstream& fin, Pile& stack);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();

protected:
	// To fulfill OODataDesign.doc
	virtual void Get() throw(IOMgmt::TokenError);
	virtual void Put();

private:
	property properties[NUM_PROPERTIES];
};

#endif


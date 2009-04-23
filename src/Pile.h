#ifndef _PILE
#define _PILE

#include "Chip.h"
#include "IOMgmt.h"
#include <deque>
#include <iostream>

class Pile : private std::deque<Chip>
{
public:
	Pile();
	~Pile();

	// Permit access to deque functions

	// To fulfill OODataDesign.doc
	friend std::ostream&  operator<<(std::ostream& fout, Pile& stack);
	friend std::ifstream& operator>>(std::ifstream& fin, Pile& stack);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();

protected:
	// To fulfill OODataDesign.doc
	virtual void Get() throw(IOMgmt::TokenError);
	virtual void Put();
};

#endif


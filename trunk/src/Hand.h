#ifndef _HAND
#define _HAND

#include "Chip.h"
#include "IOMgmt.h"
#include <iostream>
#include <set>

class Hand: private std::multiset<Chip>
{
public:
	using std::multiset<Chip>::erase;
	using std::multiset<Chip>::size;
	using std::multiset<Chip>::begin;
	using std::multiset<Chip>::find;
	Hand();
	Hand(const unsigned Size, const Chip chipId);
	~Hand();

	// To fulfill OODataDesign.doc
	friend std::ostream&  operator<<(std::ostream& fout, Hand& hand);
	friend std::ifstream& operator>>(std::ifstream& fin, Hand& hand);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();

protected:
	// To fulfill OODataDesign.doc
	virtual void Put();
	virtual void Get() throw(IOMgmt::TokenError);
};

#endif


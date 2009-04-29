#ifndef _MOVEPROPOSAL
#define _MOVEPROPOSAL

#include "Chip.h"
#include "IOMgmt.h"
#include "Pile.h"
#include <iostream>
#include <list>

class MoveProposal
{
public:
	MoveProposal();
	MoveProposal(const std::list<Pile>::iterator pileIterator, const Chip chipId);
	~MoveProposal();

	Chip getChip() const { return chip; }
	std::list<Pile>::iterator getPile() const { return pile; }

	// To fulfill OODataDesign.doc
	friend std::ostream&  operator<<(std::ostream& fout, MoveProposal& MoveProposal);
	friend std::ifstream& operator>>(std::ifstream& fin, MoveProposal& MoveProposal);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();

protected:
	// To fulfill OODataDesign.doc
	virtual void Get() throw(IOMgmt::TokenError);
	virtual void Put();

private:
	std::list<Pile>::iterator pile;
	Chip chip;
};

#endif


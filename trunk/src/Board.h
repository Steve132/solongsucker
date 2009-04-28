#ifndef _BOARD
#define _BOARD

#include "Bargain.h"
#include "Chip.h"
#include "SimMgmt.h"
#include "Pile.h"
#include <set>

class Board
{
public:
	Board();
	~Board();

	void discardChips(const std::multiset<Chip> chips);
	bool addChipToPile(const Chip c, const unsigned index);
	void createNewPile(const Chip c);
	std::list<Pile>::iterator getIterator() { std::list<Pile>::iterator i = stacks.begin(); return i; }
	std::multiset<Chip> getDeadbox() const { return deadbox; }

	// To fulfill OODataDesign.doc
	friend ostream&  operator<<(ostream& fout, Bargain& bargain);
	friend ifstream& operator>>(ifstream& fin, Bargain& bargain);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();

protected:
	// To fulfill OODataDesign.doc
	virtual void Put();
	virtual void Get() throw(IOMgmt::TokenError);

private:
	std::list<Pile> stacks;
	std::multiset<Chip> deadbox;
};

#endif


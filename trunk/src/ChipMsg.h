#ifndef _CHIPMSG
#define _CHIPMSG

#include "Chip.h"
#include "SimMgmt.h"

class ChipMsg : public SimMgmt::Message
{
public:
	ChipMsg(const int Handler, const std::string Description);
	ChipMsg(const int Handler, const std::string Description, const Chip chipIn);
	~ChipMsg();

	// To fulfill OODataDesign.doc
	friend ostream&  operator<<(ostream& fout, ChipMsg& chipMsg);
	friend ifstream& operator>>(ifstream& fin, ChipMsg& chipMsg);

	virtual void Extract()  throw(IOMgmt::TokenError);
	virtual void Insert();

	Chip& getChip() { return chip; }

protected:
	// To fulfill OODataDesign.doc
	virtual void Put();
	virtual void Get() throw(IOMgmt::TokenError);

private:
	Chip chip;
};

#endif


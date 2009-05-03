#include "Hand.h"
#include "IOMacros.h"

Hand::Hand()
{
}

Hand::Hand(const unsigned Size, const Chip chipId)
{
	for (unsigned i = 0; i < Size; i++)
		insert(chipId);
}

Hand::~Hand()
{
}

INSERT(Hand)

void Hand::Put()
{
	std::ostream& fout = SimMgmt::simOutMgr.getStream();
	SimMgmt::simOutMgr.pushMargin();
	for(iterator i = begin(); i != end(); i++)
	{
		fout << *i << " ";
		//SimMgmt::simOutMgr.advToMargin();
	}
	SimMgmt::simOutMgr.popMargin();
}
EXTRACT(Hand)

GET(Hand)

OUT_OPERATOR(Hand)

IN_OPERATOR(Hand)


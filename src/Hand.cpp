#include "Hand.h"
#include "IOMacros.h"

Hand::Hand()
{
}

Hand::Hand(const unsigned Size, const Chip chipId)
{
	for(unsigned i = 0; i < Size; i++)
		insert(chipId);
}

Hand::~Hand()
{
}

INSERT(Hand)

PUT(Hand)

EXTRACT(Hand)

GET(Hand)

OUT_OPERATOR(Hand)

IN_OPERATOR(Hand)


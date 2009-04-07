#include "Hand.h"
#include "IOMacros.h"

Hand::Hand()
{
}

Hand::Hand(const unsigned Size, const Chip chipId) :
	size(Size), chip(chipId)
{
	for(unsigned i = 0; i < size; i++)
		insert(chip);
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


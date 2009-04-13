#include "Move.h"
#include "IOMacros.h"

Move::Move()
{
}

Move::Move(const std::list<Pile>::iterator pileIterator, const Chip chipId)	:
	pile(pileIterator), chip(chipId)
{
}

Move::~Move()
{
}

INSERT(Move)

PUT(Move)

EXTRACT(Move)

GET(Move)

OUT_OPERATOR(Move)

IN_OPERATOR(Move)


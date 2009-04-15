#include "MoveProposal.h"
#include "IOMacros.h"

MoveProposal::MoveProposal()
{
}

MoveProposal::MoveProposal(const std::list<Pile>::iterator pileIterator, const Chip chipId)	:
	pile(pileIterator), chip(chipId)
{
}

MoveProposal::~MoveProposal()
{
}

INSERT(MoveProposal)

PUT(MoveProposal)

EXTRACT(MoveProposal)

GET(MoveProposal)

OUT_OPERATOR(MoveProposal)

IN_OPERATOR(MoveProposal)


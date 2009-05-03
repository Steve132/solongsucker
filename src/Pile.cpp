#include "Pile.h"
#include "IOMacros.h"

Pile::Pile()
{
}

Pile::~Pile()
{
}

INSERT(Pile)

void Pile::Put()
{
	std::ostream& fout = SimMgmt::simOutMgr.getStream();
	SimMgmt::simOutMgr.pushMargin();
	for(iterator i = begin(); i != end(); i++)
	{
		fout << *i << " ";
		SimMgmt::simOutMgr.advToMargin();
	}
	SimMgmt::simOutMgr.popMargin();
}

EXTRACT(Pile)

GET(Pile)

OUT_OPERATOR(Pile)

IN_OPERATOR(Pile)


#include "ChipMsg.h"
#include "IOMacros.h"

ChipMsg::ChipMsg(const int Handler, const std::string Description) :
		SimMgmt::Message(Handler, Description)
{
}

ChipMsg::ChipMsg(const int Handler, const std::string Description, const Chip chipIn) :
		SimMgmt::Message(Handler, Description), chip(chipIn)
{
}

ChipMsg::~ChipMsg()
{
}

INSERT(ChipMsg)

void ChipMsg::Put()
{
	std::ostream& fout = SimMgmt::simOutMgr.getStream();
	Message::Put();
	SimMgmt::simOutMgr.advToMargin();
	fout << TAG(chip) << " " << chip;
}

EXTRACT(ChipMsg)

GET(ChipMsg)

OUT_OPERATOR(ChipMsg)

IN_OPERATOR(ChipMsg)


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

PUT(ChipMsg)

EXTRACT(ChipMsg)

GET(ChipMsg)

OUT_OPERATOR(ChipMsg)

IN_OPERATOR(ChipMsg)


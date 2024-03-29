#include "BargainMsg.h"
#include "IOMacros.h"

BargainMsg::BargainMsg(const int Handler, const std::string Description) :
		SimMgmt::Message(Handler, Description)
{
}

BargainMsg::BargainMsg(const int Handler, const std::string Description, const Bargain& bargainIn) :
		SimMgmt::Message(Handler, Description), bargain(bargainIn)
{
}

BargainMsg::~BargainMsg()
{
}

INSERT(BargainMsg)

void BargainMsg::Put()
{
	std::ostream& fout = SimMgmt::simOutMgr.getStream();
	fout << TAG(bargain) << " " << bargain << " ";
}

EXTRACT(BargainMsg)

GET(BargainMsg)

OUT_OPERATOR(BargainMsg)

IN_OPERATOR(BargainMsg)


#include "CustomPlayer.h"

CustomPlayer::CustomPlayer()
{
}

CustomPlayer::CustomPlayer(unsigned SizeOfHand, Chip Id, property* Properties) :
	Player(SizeOfHand, Id)
{
	for(unsigned i = 0; i < (sizeof(Properties)/sizeof(property)); i++)
		properties[i] = Properties[i];
}

CustomPlayer::~CustomPlayer()
{
}

Bargain* CustomPlayer::AcceptBargainAccept()
{
}

Bargain* CustomPlayer::AcceptBargainReject()
{
}

INSERT(CustomPlayer)

PUT(CustomPlayer)

EXTRACT(CustomPlayer)

GET(CustomPlayer)

OUT_OPERATOR(CustomPlayer)

IN_OPERATOR(CustomPlayer)




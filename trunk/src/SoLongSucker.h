#ifndef SOLONGSUCKER_H
#define SOLONGSUCKER_H

#include "SimMgmt.h"
#include "Board.h"

class SoLongSucker
{  //Virtual World
public:
	SoLongSucker();
	~SoLongSucker();
	void Initialize();
	void Simulate();
	void WrapUp(); //Writes to the default program output stream
	void Insert();    //Writes to the default program output stream

private:
	Board board;

	int numPlayers;
	int numChipsPerPlayer;
	int numEvents;
	int winningPlayer;
	int lastEvent;
	SimMgmt::Agent  **players; //dynamic array of Agent*
};//Conversation

#endif

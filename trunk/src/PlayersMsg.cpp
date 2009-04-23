#include "PlayersMsg.h"
#include <cstdlib>
using namespace SimMgmt;
using namespace std;


PlayersMsg::PlayersMsg(int MaxAgents) throw(AppError):Message(0,"PlayersMsg")
{
	if ( MaxAgents < 1 )throw AppError("MaxAgents must be >= 1! ","PlayersMsg::PlayersMsg()");
	agents     = new AGENTPTR[MaxAgents];
	agentNames = new string[MaxAgents];
	numAgents  = MaxAgents;
	lastAgent  = -1;
}

PlayersMsg::~PlayersMsg()
{
	delete[] agents;
	delete[] agentNames;
}

int PlayersMsg::getNumAgents()
{
	return numAgents;
}

AGENTPTR PlayersMsg::getAgent(string playerid) throw(AppError)
{
	if ( lastAgent != numAgents-1 )
		throw AppError("Protocol violation!  Agents have not been defined!",
		               "PlayersMsg::getAgent(@1)");
	int i = 0;
	for (; i <= numAgents ; i++)
	{
		if ( agentNames[i] == playerid ) break;
	}

	if ( i > numAgents )
		throw AppError("Cannot identify Agent !",
		               "PlayersMsg::getAgent(" + playerid + ")");
	else return agents[i];
}

AGENTPTR *PlayersMsg::getOthers(int Num) throw(AppError)
{
	if ( lastAgent != numAgents-1 )
		throw AppError("Protocol violation!  Agents have not been defined!",
		               "PlayersMsg::getOthers(@1)");

	// Selects a random subset of distinct Agents of size (Num).
	if ( Num > numAgents )
		throw AppError("Number of random Agents requested exceeds number defined!",
		               "PlayersMsg::getOthers(@2)");

	AGENTPTR *randomAgents = new AGENTPTR[Num];
	int n, j, k = 0;

	n = rand() % numAgents;
	randomAgents[k] = agents[n];
	while ( k < Num-1 )
	{
		n = rand() % numAgents;
		for (j = 0; j <= k; j++)
		{
			if ( agents[n] == randomAgents[j] ) break;
		}//for
		if ( j > k )
		{
			randomAgents[++k] = agents[n];
		}//if
	}//while
	return randomAgents;
}

void PlayersMsg::setAgent(string playerid, AGENTPTR agent) throw(AppError)
{
	lastAgent++;
	if ( lastAgent >= numAgents )
		throw AppError("Agent overflow attempted!",
		               "PlayersMsg::setAgent(@1)");
	for (int i=0; i < lastAgent; i++)
	{
		if ( playerid == agentNames[i] || agent == agents[i] )
			throw AppError("Duplicate definition of Agent attempted!",
			               "PlayersMsg::setAgent(@2)");
	}//for
	agentNames[lastAgent] = playerid;
	agents[lastAgent]     = agent;
}

void PlayersMsg::Insert()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	simlog << "PlayersMsg{ ";
	Put();
	simOutMgr.advToMargin();
	simlog << "}PlayersMsg ";
	simOutMgr.popMargin();
}//Insert

void PlayersMsg::Put()
{
	ostream& simlog = simOutMgr.getStream();

	simOutMgr.pushMargin();
	for (int i = 0; i < numAgents; i++ )
	{
		simlog << " agent[ " << i << " ] = " << agentNames[i];
		simOutMgr.advToMargin();
	}//for
	simOutMgr.popMargin();
}//Put



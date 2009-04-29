#ifndef PLAYERSMSG_H
#define PLAYERSMSG_H
#include "IOMgmt.h"
#include "SimMgmt.h"

class PlayersMsg : public SimMgmt::Message
{  // Inherits from Message
public:
	PlayersMsg(int MaxAgents) throw(AppError);
	~PlayersMsg();
	int       getNumAgents();
	SimMgmt::Agent* getAgent(string playerid) throw(AppError);
	SimMgmt::Agent** getOthers(int Num) throw(AppError);
	void      setAgent(string playerid, SimMgmt::Agent* agent) throw(AppError);
	SimMgmt::Agent**	  getPlayers(){return agents;}
protected:
	//Inherited as virtual and must be redefined:
	virtual void Insert();//Must write to the default program output stream
	virtual void Put();   //Must write to the default program output stream
private:
	int      numAgents;
	int      lastAgent;
	SimMgmt::Agent* *agents;
	string   *agentNames;
}; //Players

#endif

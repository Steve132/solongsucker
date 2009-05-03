#ifndef _PLAYER
#define _PLAYER

#include "BargainMsg.h"
#include "Board.h"
#include "Chip.h"
#include "ChipMsg.h"
#include "Hand.h"
#include "SimMgmt.h"
#include "MoveProposal.h"
#include <list>
#include <vector>
class Player : public SimMgmt::Agent
{
public:
	Player();
	Player(const unsigned sizeOfHand, const Chip Id, Board* inboard);
	virtual ~Player();

	// Required by Agent definition
	void Initialize(SimMgmt::Message* players);
	void Dispatch(SimMgmt::Message* msg);

	// Styled after Workman's message passing system
	virtual BargainMsg* AcceptBargainOffer(const Bargain&);
	virtual BargainMsg* AcceptBargainAccept(const Bargain&);
	virtual BargainMsg* AcceptBargainReject(const Bargain&);
	virtual SimMgmt::Message  *AcceptTerminate();

	// Pure virtual functions for game functionality to be decided by AIs
	virtual MoveProposal PerformMove(std::vector<Player*>&) = 0;
	virtual Bargain CreateBargain() = 0;
	virtual bool AcceptOrRejectBargain(Bargain* b) = 0;
	virtual int PickUpPile(std::vector<Chip>&)=0;

	void TakeTurn();
	void TakePile(std::list<Pile>::iterator pile);
	ChipMsg* AcceptChipMsgGiveTurn(Chip);

	// To fulfill OODataDesign.doc
	friend std::ostream&  operator<<(std::ostream& fout, Pile& stack);
	friend std::ifstream& operator>>(std::ifstream& fin, Pile& stack);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
	

	void doGiveTurn(const Chip Id);
	void doBargainOffer(Bargain* b);
	void doBargainAccept(Bargain* b);
	void doBargainReject(Bargain* b);
	void doTerminate();
	
	Chip getId() const {return id;}
	bool& Dead() { return dead;}

protected:
	void executeMove(const MoveProposal& move,std::vector<Player*> &);

	// To fulfill OODataDesign.doc
	virtual void Get() throw(IOMgmt::TokenError);
	virtual void Put();

	std::list<Bargain> bargains;

	Board* board;
	bool dead;
	Hand hand;
	Chip id;
	Chip currentturn;
	std::vector<Player*> otherplayers;
};

#endif


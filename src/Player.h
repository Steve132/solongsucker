#ifndef _PLAYER
#define _PLAYER

#include "Bargain.h"
#include "Chip.h"
#include "Hand.h"
#include "SimMgmt.h"
#include <list>

class Player : public SimMgmt::Agent
{
	public:
		Player();
		Player(const unsigned sizeOfHand, const Chip Id);
		virtual ~Player();
	
		// Required by Agent definition
		void Initialize(SimMgmt::Message* players);
		void Dispatch(SimMgmt::Message* msg);

		// Styled after Workman's message passing system
		Bargain* AcceptBargainOffer();
		virtual Bargain* AcceptBargainAccept();
		virtual Bargain* AcceptBargainReject();

		void AcceptTurn();
		SimMgmt::Message* GiveTurn(std::list<Player> validPlayers);

		// To fulfill OODataDesign.doc
		friend std::ostream&  operator<<(std::ostream& fout, Stack& stack);
		friend std::ifstream& operator>>(std::ifstream& fin, Stack& stack);
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Get(std::ifstream& fin);
		virtual void Put(std::ostream& fout);

	private:
		Hand hand;
		Chip id;
};

#endif


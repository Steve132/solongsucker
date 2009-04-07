#ifndef _BARGAIN
#define _BARGAIN

#include "Chip.h"
#include "Move.h"
#include "SimMgmt.h"
#include <set>

class Bargain : public SimMgmt::Message
{
	public:
		Bargain(int Handler, std::string Description);
		Bargain(int Handler, std::string Description, Move currentMove, std::multiset<Chip> Chips, Chip NextTurn);
		~Bargain();

		// To fulfill OODataDesign.doc
		friend ostream&  operator<<(ostream& fout, Bargain& bargain);
		friend ifstream& operator>>(ifstream& fin, Bargain& bargain);
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Put(std::ostream& fout);
		virtual void Get(std::ifstream& fin);

	private:
	// "If _Move{(Player id)_ lays on _(Stack iterator)_}, give turn to _(Player id)_, and I'll offer _(chips)_.", if the Player suggesting Bargain is out of turn.
	// "I'll _Move_, and give turn to _(Player id)_, and I want you to give me _(chips)_.", if the Player suggesting the Bargain is in turn.
	// Thus nextTurn varies on whether the Player suggesting the Bargain is in or out of turn.
		Move move;
		std::multiset<Chip> chips;
		Chip nextTurn;
};

#endif


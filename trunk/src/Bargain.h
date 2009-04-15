#ifndef _BARGAIN
#define _BARGAIN

#include "Chip.h"
#include "MoveProposal.h"
#include <set>

class Bargain
{
	public:
		Bargain(const MoveProposal currentMoveProposal, const std::multiset<Chip> Chips, const Chip NextTurn);
		~Bargain();

		// To fulfill OODataDesign.doc
		friend ostream&  operator<<(ostream& fout, Bargain& bargain);
		friend ifstream& operator>>(ifstream& fin, Bargain& bargain);
	
		virtual void Extract() throw(IOMgmt::TokenError);
		virtual void Insert();

	protected:
		// To fulfill OODataDesign.doc
		virtual void Put();
		virtual void Get() throw(IOMgmt::TokenError);

	private:
	// "If _MoveProposal{(Player id)_ lays on _(Pile iterator)_}, give turn to _(Player id)_, and I'll offer _(chips)_.", if the Player suggesting Bargain is out of turn.
	// "I'll _MoveProposal_, and give turn to _(Player id)_, and I want you to give me _(chips)_.", if the Player suggesting the Bargain is in turn.
	// Thus nextTurn varies on whether the Player suggesting the Bargain is in or out of turn.
		MoveProposal move;
		std::multiset<Chip> chips;
		Chip nextTurn;
};

#endif


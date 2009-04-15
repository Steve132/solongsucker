#ifndef _BOARD
#define _BOARD

#include "Chip.h"
#include "Player.h"
#include "SimMgmt.h"
#include "Pile.h"
#include <set>

class Board
{
	public:
		Board();
		~Board();
	
		// Styled after Workman's Conversation class
		void Initialize();
		void Simulate();	// Performs rule checking
		void WrapUp();

		SimMgmt::Message* AcceptChipsDiscard(std::multiset<Chip> chips);

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
		std::set<Player> players;
		std::list<Pile> stacks;
};

#endif


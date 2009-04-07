#ifndef _BOARD
#define _BOARD

#include "Chip.h"
#include "Player.h"
#include "SimMgmt.h"
#include "Stack.h"
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
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Put(std::ostream& fout);
		virtual void Get(std::ifstream& fin);

	private:
		std::set<Player> players;
		std::list<Stack> stacks;
};

#endif


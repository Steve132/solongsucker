#ifndef _CUSTOMPLAYER
#define _CUSTOMPLAYER

#include "Bargain.h"
#include "Chip.h"
#include "Player.h"

class CustomPlayer : public Player
{
	public:
		enum property
		{
			AGGRESSIVENESS,
			ACCEPTIVENESS,
			IGNORANCE,		// etc.
			NUM_PROPERTIES
		};

		CustomPlayer();
		CustomPlayer(unsigned sizeOfHand, Chip id, property* properties = NULL);
		~CustomPlayer();

		virtual Bargain* AcceptBargainAccept();
		virtual Bargain* AcceptBargainReject();

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
		property properties[NUM_PROPERTIES];
};

#endif


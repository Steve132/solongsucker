#ifndef _MOVE
#define _MOVE

#include "Chip.h"
#include "IOMacros.h"
#include "Stack.h"
#include <iostream>
#include <list>

class Move
{
	public:
		Move();
		Move(const std::list<Stack>::iterator pileIterator, const Chip chipId);
		~Move();

		// To fulfill OODataDesign.doc
		friend std::ostream&  operator<<(std::ostream& fout, Move& move);
		friend std::ifstream& operator>>(std::ifstream& fin, Move& move);

		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Get(std::ifstream& fin);		
		virtual void Put(std::ostream& fout);
	
	private:
		std::list<Stack>::iterator pile;
		Chip chip;
};

#endif


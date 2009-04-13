#ifndef _PILE
#define _PILE

#include "Chip.h"
#include <deque>
#include <iostream>

class Pile : public std::deque<Chip>
{
	public:
		Pile();
		~Pile();

		// To fulfill OODataDesign.doc
		friend std::ostream&  operator<<(std::ostream& fout, Pile& stack);
		friend std::ifstream& operator>>(std::ifstream& fin, Pile& stack);
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Get(std::ifstream& fin);
		virtual void Put(std::ostream& fout);
};

#endif


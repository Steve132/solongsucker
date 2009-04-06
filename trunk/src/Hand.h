#ifndef _HAND
#define _HAND

#include "Chip.h"
#include <iostream>
#include <set>

class Hand : public std::multiset<Chip>
{
	public:
		Hand();
		~Hand();

		// To fulfill OODataDesign.doc
		friend std::ostream&  operator<<(std::ostream& fout, Hand& hand);
		friend std::ifstream& operator>>(std::ifstream& fin, Hand& hand);

		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Put(std::ostream& fout);
		virtual void Get(std::ifstream& fin);
};

#endif


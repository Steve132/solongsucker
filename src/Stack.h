#ifndef _STACK
#define _STACK

#include "Chip.h"
#include <deque>
#include <iostream>

class Stack : public std::deque<Chip>
{
	public:
		Stack();
		~Stack();

		// To fulfill OODataDesign.doc
		friend std::ostream&  operator<<(std::ostream& fout, Stack& stack);
		friend std::ifstream& operator>>(std::ifstream& fin, Stack& stack);
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Get(std::ifstream& fin);
		virtual void Put(std::ostream& fout);
};

#endif


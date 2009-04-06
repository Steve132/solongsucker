#ifndef _IOMACROS
#define _IOMACROS

#include "IOMgmt.h"
#include <stdarg.h>

#define TAG(word) #word ":"

#define OPENTKN(classname) #classname "{"
#define CLOSETKN(classname) "}" #classname

#define INSERT(classname)							\
void classname::Insert(std::ostream& fout)				\
{												\
	fout << OPENTKN(classname) << " ";					\
	Put(fout);									\
	fout << CLOSETKN(classname) << " ";				\
}

#define EXTRACT(classname)							\
void classname::Extract(std::ifstream& fin)				\
{												\
	std::string token;								\
	fin >> token;									\
	if(token != OPENTKN(classname)) 					\
		throw IOMgmt::TokenError(std::string("Unrecognized open token, " + token + ", '" + OPENTKN(classname) + "' expected!"), std::string(std::string(#classname) + "::Extract()"));	\
	Get(fin);										\
	fin >> token;									\
	if(token != CLOSETKN(classname))					\
		throw IOMgmt::TokenError(std::string("Unrecognized close token, " + token + ", '" + CLOSETKN(classname) + "' expected!"), std::string(std::string(#classname) + "::Extract()"));	\
}

#define GET(classname)								\
void classname::Get(std::ifstream& fin)					\
{												\
}

#define PUT(classname)								\
void classname::Put(std::ostream& fout)					\
{												\
}

#define OUT_OPERATOR(classname)						\
std::ostream& operator<<(std::ostream &fout, classname &c)	\
{												\
	c.Insert(fout);								\
	return fout;									\
}

#define IN_OPERATOR(classname)						\
std::ifstream& operator>>(std::ifstream &fin, classname &c)	\
{												\
	c.Extract(fin);								\
	return fin;									\
}

#endif


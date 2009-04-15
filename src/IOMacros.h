#ifndef _IOMACROS
#define _IOMACROS

#include "IOMgmt.h"
#include "SimMgmt.h"
#include <stdarg.h>

#define TAG(word) #word ":"

#define OPENTKN(classname) #classname "{"
#define CLOSETKN(classname) "}" #classname

#define INSERT(classname)							\
void classname::Insert()								\
{												\
	std::ostream& fout = SimMgmt::simOutMgr.getStream();	\
	fout << OPENTKN(classname) << " ";					\
	Put();										\
	fout << CLOSETKN(classname) << " ";				\
}

#define EXTRACT(classname)							\
void classname::Extract() throw(IOMgmt::TokenError)		\
{												\
	std::ifstream& fin = SimMgmt::simInMgr.getStream();	\
	std::string token;								\
	fin >> token;									\
	if(token != OPENTKN(classname)) 					\
		throw IOMgmt::TokenError(std::string("Unrecognized open token, " + token + ", '" + OPENTKN(classname) + "' expected!"), std::string(std::string(#classname) + "::Extract()"));	\
	Get();										\
	fin >> token;									\
	if(token != CLOSETKN(classname))					\
		throw IOMgmt::TokenError(std::string("Unrecognized close token, " + token + ", '" + CLOSETKN(classname) + "' expected!"), std::string(std::string(#classname) + "::Extract()"));	\
}

#define GET(classname)								\
void classname::Get()	throw(IOMgmt::TokenError)		\
{												\
}

#define PUT(classname)								\
void classname::Put()								\
{												\
}

#define OUT_OPERATOR(classname)						\
std::ostream& operator<<(std::ostream &fout, classname &c)	\
{												\
	c.Insert();									\
	return fout;									\
}

#define IN_OPERATOR(classname)						\
std::ifstream& operator>>(std::ifstream &fin, classname &c)	\
{												\
	c.Extract();									\
	return fin;									\
}

#endif


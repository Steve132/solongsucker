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

#define GETVAR(classname, n, members...)				\
void classname::Get()	throw(IOMgmt::TokenError)		\
{												\
	std::ifstream& fin = SimMgmt::simInMgr.getStream();	\
												\
	std::string alltokentags = "";					\
	for(unsigned i = 0; i < (n-1); i++)				\
		alltokentags += ", " + TAG(members[i]);			\
	alltokentags += TAG(members[i]);					\
												\
	for(unsigned i = 0; i < n; i++)					\
	{											\
		std::string token;							\
		fin >> token;								\
		for(unsigned j = 0; j < n; j++)				\
		{										\
			if(token == TAG(members[j])				\
				fin >> members[j];					\
		}										\
		if(j == n)								\
			throw IOMgmt::TokenError(std::string("Unrecognized open token, " + token + ", '" + alltokentags + "' expected!"), std::string(std::string(#classname)) + "::Get()"));		\
	}											\
}

#define PUT(classname)								\
void classname::Put()								\
{												\
}

#define PUTVAR(classname, n, members...)				\
void classname::Put()								\
{												\
	std::ostream& fout = SimMgmt::simOutMgr.getStream();	\
												\
	for(unsigned i = 0; i < n; i++)					\
		fout << TAG(members[i]) << " " << members[i] " ";	\
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


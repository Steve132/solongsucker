#ifndef _CHIPMSG
#define _CHIPMSG

#include "Chip.h"
#include "SimMgmt.h"

class ChipMsg : public SimMgmt::Message
{
	public:
		ChipMsg(const int Handler, const std::string Description);
		ChipMsg(const int Handler, const std::string Description, const Chip chipIn);
		~ChipMsg();
	
		// To fulfill OODataDesign.doc
		friend ostream&  operator<<(ostream& fout, ChipMsg& chipMsg);
		friend ifstream& operator>>(ifstream& fin, ChipMsg& chipMsg);
	
		virtual void Extract(std::ifstream& fin);
		virtual void Insert(std::ostream& fout);

	protected:
		// To fulfill OODataDesign.doc
		virtual void Put(std::ostream& fout);
		virtual void Get(std::ifstream& fin);
	
	private:
		Chip chip;
};

#endif


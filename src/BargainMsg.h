#ifndef _BARGAINMSG
#define _BARGAINMSG

#include "Bargain.h"
#include "SimMgmt.h"

class BargainMsg : public SimMgmt::Message
{
public:
	BargainMsg(int Handler, std::string Description);
	BargainMsg(int Handler, std::string Description, const Bargain& bargainIn);
	~BargainMsg();

	// To fulfill OODataDesign.doc
	friend ostream&  operator<<(ostream& fout, Bargain& bargain);
	friend ifstream& operator>>(ifstream& fin, Bargain& bargain);

	virtual void Extract() throw(IOMgmt::TokenError);
	virtual void Insert();
	Bargain& getBargain() {return bargain;}

protected:
	// To fulfill OODataDesign.doc
	virtual void Put();
	virtual void Get() throw(IOMgmt::TokenError);

private:
	Bargain bargain;
};

#endif


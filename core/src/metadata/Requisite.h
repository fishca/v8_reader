//---------------------------------------------------------------------------

#ifndef RequisiteH
#define RequisiteH

#include "MDO.h"

//---------------------------------------------------------------------------
class TRequisite : public TMDO
{
public:
	TRequisite();
	TRequisite(String _name, String _guid);
	~TRequisite();
};

class TAccountingFlag : public TMDO
{
public:
	TAccountingFlag();
	TAccountingFlag(String _name, String _guid);
	~TAccountingFlag();
};

class TDimensionAccountingFlag : public TMDO
{
public:
	TDimensionAccountingFlag();
	TDimensionAccountingFlag(String _name, String _guid);
	~TDimensionAccountingFlag();
};


#endif


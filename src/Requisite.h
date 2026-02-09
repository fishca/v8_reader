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
	__fastcall ~TRequisite();
};

class TAccountingFlag : public TMDO
{
public:
	__fastcall TAccountingFlag();
	__fastcall TAccountingFlag(String _name, String _guid);
	__fastcall ~TAccountingFlag();
};

class TDimensionAccountingFlag : public TMDO
{
public:
	__fastcall TDimensionAccountingFlag();
	__fastcall TDimensionAccountingFlag(String _name, String _guid);
	__fastcall ~TDimensionAccountingFlag();
};


#endif

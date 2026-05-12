//---------------------------------------------------------------------------

#pragma hdrstop

#include "Requisite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


 TRequisite::TRequisite(String _name, String _guid)
{
	name = _name;
	guid = _guid;
}

 TRequisite::TRequisite()
{
	name = "";
    guid = "";
}

__fastcall TRequisite::~TRequisite()
{

}



__fastcall TAccountingFlag::TAccountingFlag()
{
	name = "";
	guid = "";
}

__fastcall TAccountingFlag::TAccountingFlag(String _name, String _guid)
{
	name = _name;
	guid = _guid;
}

__fastcall TAccountingFlag::~TAccountingFlag()
{

}

__fastcall TDimensionAccountingFlag::TDimensionAccountingFlag()
{
	name = "";
	guid = "";
}

__fastcall TDimensionAccountingFlag::TDimensionAccountingFlag(String _name, String _guid)
{
	name = _name;
	guid = _guid;
}

__fastcall TDimensionAccountingFlag::~TDimensionAccountingFlag()
{

}


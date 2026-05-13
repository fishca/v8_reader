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

TRequisite::~TRequisite()
{

}



TAccountingFlag::TAccountingFlag()
{
	name = "";
	guid = "";
}

TAccountingFlag::TAccountingFlag(String _name, String _guid)
{
	name = _name;
	guid = _guid;
}

TAccountingFlag::~TAccountingFlag()
{

}

TDimensionAccountingFlag::TDimensionAccountingFlag()
{
	name = "";
	guid = "";
}

TDimensionAccountingFlag::TDimensionAccountingFlag(String _name, String _guid)
{
	name = _name;
	guid = _guid;
}

TDimensionAccountingFlag::~TDimensionAccountingFlag()
{

}



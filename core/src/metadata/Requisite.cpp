//---------------------------------------------------------------------------


#include "Requisite.h"
//---------------------------------------------------------------------------


 TRequisite::TRequisite(const Utf16String& _name, const Utf16String& _guid)
{
	name = _name;
	guid = _guid;
}

 TRequisite::TRequisite()
{
	name = u"";
    guid = u"";
}

TRequisite::~TRequisite()
{

}



TAccountingFlag::TAccountingFlag()
{
	name = u"";
	guid = u"";
}

TAccountingFlag::TAccountingFlag(const Utf16String& _name, const Utf16String& _guid)
{
	name = _name;
	guid = _guid;
}

TAccountingFlag::~TAccountingFlag()
{

}

TDimensionAccountingFlag::TDimensionAccountingFlag()
{
	name = u"";
	guid = u"";
}

TDimensionAccountingFlag::TDimensionAccountingFlag(const Utf16String& _name, const Utf16String& _guid)
{
	name = _name;
	guid = _guid;
}

TDimensionAccountingFlag::~TDimensionAccountingFlag()
{

}



//---------------------------------------------------------------------------


#include "MDO.h"
//---------------------------------------------------------------------------

TMDO::TMDO() : name(u""), guid(u"")
{
}

TMDO::~TMDO()
{

}

void TMDO::SetName(const Utf16String& _name)
{
	name = _name;
}

void TMDO::SetGUID(const Utf16String& _guid)
{
	guid = _guid;
}

Utf16String TMDO::GetName()
{
	return name;
}

Utf16String TMDO::GetGUID()
{
	return guid;
}


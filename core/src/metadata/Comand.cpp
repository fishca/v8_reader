//---------------------------------------------------------------------------


#include "Comand.h"
//---------------------------------------------------------------------------


TComand::TComand()
{

}

TComand::TComand(const Utf16String& _name, const Utf16String& _guid)
{
	name = _name;
    guid = _guid;
}

TComand::~TComand()
{

}


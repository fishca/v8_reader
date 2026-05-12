//---------------------------------------------------------------------------

#pragma hdrstop

#include "MDO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TMDO::TMDO() : name(""), guid("")
{
//	name = "";
//	guid = "";
}

__fastcall TMDO::~TMDO()
{

}

void __fastcall TMDO::SetName(String _name)
{
	name = _name;
}

void __fastcall TMDO::SetGUID(String _guid)
{
	guid = _guid;
}

System::String TMDO::GetName()
{
	return name;
}

System::String TMDO::GetGUID()
{
	return guid;
}

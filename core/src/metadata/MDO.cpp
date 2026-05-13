//---------------------------------------------------------------------------

#pragma hdrstop

#include "MDO.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TMDO::TMDO() : name(""), guid("")
{
//	name = "";
//	guid = "";
}

TMDO::~TMDO()
{

}

void TMDO::SetName(String _name)
{
	name = _name;
}

void TMDO::SetGUID(String _guid)
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


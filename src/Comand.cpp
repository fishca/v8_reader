//---------------------------------------------------------------------------

#pragma hdrstop

#include "Comand.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TComand::TComand()
{

}

__fastcall TComand::TComand(String _name, String _guid)
{
	name = _name;
    guid = _guid;
}

__fastcall TComand::~TComand()
{

}

//---------------------------------------------------------------------------

#pragma hdrstop

#include "Comand.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TComand::TComand()
{

}

TComand::TComand(String _name, String _guid)
{
	name = _name;
    guid = _guid;
}

TComand::~TComand()
{

}


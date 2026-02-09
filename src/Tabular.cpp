//---------------------------------------------------------------------------

#pragma hdrstop

#include "Tabular.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TTabular::TTabular()
{

}

__fastcall TTabular::TTabular(String _name, String _guid)
{
	name = _name;
    guid = _guid;
}

__fastcall TTabular::~TTabular()
{

}

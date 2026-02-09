//---------------------------------------------------------------------------

#pragma hdrstop

#include "Moxel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TMoxel::TMoxel()
{

}

__fastcall TMoxel::TMoxel(String _name, String _guid)
{
	name = _name;
    guid = _guid;
}

__fastcall TMoxel::~TMoxel()
{

}

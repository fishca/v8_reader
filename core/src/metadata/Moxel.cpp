//---------------------------------------------------------------------------


#include "Moxel.h"
//---------------------------------------------------------------------------


TMoxel::TMoxel()
{

}

TMoxel::TMoxel(const Utf16String& _name, const Utf16String& _guid)
{
	name = _name;
    guid = _guid;
}

TMoxel::~TMoxel()
{

}


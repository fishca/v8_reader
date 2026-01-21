//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Numerators.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TNumerators::TNumerators()
{
	guid   = "";
	name   = "";
	parent = NULL;
}

__fastcall TNumerators::TNumerators(v8catalog *_parent, const String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));
}

__fastcall TNumerators::TNumerators(v8catalog *_parent, const String& _guid, const String& _name)
{
	name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));
}

__fastcall TNumerators::~TNumerators()
{

}

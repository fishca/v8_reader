//---------------------------------------------------------------------------


#include "Common.h"
#include "Numerators.h"
//---------------------------------------------------------------------------


TNumerators::TNumerators()
{
	guid   = "";
	name   = "";
	parent = NULL;
}

TNumerators::TNumerators(v8catalog *_parent, const String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));
}

TNumerators::TNumerators(v8catalog *_parent, const String& _guid, const String& _name)
{
	name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));
}

TNumerators::~TNumerators()
{

}


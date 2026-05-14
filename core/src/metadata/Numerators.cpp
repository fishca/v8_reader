//---------------------------------------------------------------------------


#include "Common.h"
#include "Numerators.h"
//---------------------------------------------------------------------------


TNumerators::TNumerators()
{
	guid   = u"";
	name   = u"";
	parent = NULL;
}

TNumerators::TNumerators(v8catalog *_parent, const Utf16String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(_guid)));
}

TNumerators::TNumerators(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
{
	name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(_guid)));
}

TNumerators::~TNumerators()
{

}


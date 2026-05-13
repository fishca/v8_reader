//---------------------------------------------------------------------------


#include "Common.h"
#include "Sequences.h"
//---------------------------------------------------------------------------


TSequences::TSequences()
{
	guid   = "";
	name   = "";
	parent = NULL;
}

TSequences::TSequences(v8catalog *_parent, const String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));
}

TSequences::TSequences(v8catalog *_parent, const String& _guid, const String& _name)
{
    name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(V8Utf16FromString(_guid))));

}

TSequences::~TSequences()
{

}


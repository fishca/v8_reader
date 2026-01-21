//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "Sequences.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSequences::TSequences()
{
	guid   = "";
	name   = "";
	parent = NULL;
}

__fastcall TSequences::TSequences(v8catalog *_parent, const String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));
}

__fastcall TSequences::TSequences(v8catalog *_parent, const String& _guid, const String& _name)
{
    name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));

}

__fastcall TSequences::~TSequences()
{

}

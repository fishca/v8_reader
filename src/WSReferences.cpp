//---------------------------------------------------------------------------

#pragma hdrstop

#include "WSReferences.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TWSReferences::TWSReferences() : EmptyMetadataObject<TWSReferences>()
{
	referenceName = "";
	root_data.reset();
}

__fastcall TWSReferences::TWSReferences(v8catalog* _parent, const String& _guid)
	: EmptyMetadataObject<TWSReferences>(_parent, _guid)
{
	referenceName = "";
	root_data.reset();
}

__fastcall TWSReferences::TWSReferences(v8catalog* _parent, const String& _guid, const String& _name)
	: EmptyMetadataObject<TWSReferences>(_parent, _guid, _name)
{
	referenceName = _name;
	root_data.reset();
}

String __fastcall TWSReferences::GetReferenceName()
{
	return referenceName;
}

void __fastcall TWSReferences::SetReferenceName(String _name)
{
	referenceName = _name;
	name = _name;
}

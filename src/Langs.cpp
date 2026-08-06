//---------------------------------------------------------------------------

#pragma hdrstop

#include "Langs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TLangs::TLangs() : EmptyMetadataObject<TLangs>()
{
	name = "";
	root_data.reset();
}

__fastcall TLangs::TLangs(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TLangs>(_parent, _guid)
{
	name = "";
	root_data.reset();
}

__fastcall TLangs::TLangs(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TLangs>(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

String __fastcall TLangs::GetLangName()
{
	return name;
}

void __fastcall TLangs::SetLangName(String _name)
{
	name = _name;
}

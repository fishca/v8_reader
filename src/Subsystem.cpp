//---------------------------------------------------------------------------

#pragma hdrstop

#include "Subsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSubsystem::TSubsystem() : EmptyMetadataObject<TSubsystem>()
{
	name = "";
	root_data.reset();
}

__fastcall TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TSubsystem>(_parent, _guid)
{
	name = "";
	root_data.reset();
}

__fastcall TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TSubsystem>(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

String __fastcall TSubsystem::GetSubsystemName()
{
	return name;
}

void __fastcall TSubsystem::SetSubsystemName(String _name)
{
	name = _name;
}

//---------------------------------------------------------------------------

#pragma hdrstop

#include "SettingsStorages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSettingsStorages::TSettingsStorages() : EmptyMetadataObject<TSettingsStorages>()
{
    storageName = "";
    root_data.reset();
}

__fastcall TSettingsStorages::TSettingsStorages(v8catalog* _parent, const String& _guid) : EmptyMetadataObject<TSettingsStorages>(_parent, _guid)
{
    storageName = "";
    root_data.reset();
}

__fastcall TSettingsStorages::TSettingsStorages(v8catalog* _parent, const String& _guid, const String& _name) : EmptyMetadataObject<TSettingsStorages>(_parent, _guid, _name)
{
    storageName = _name;
    root_data.reset();
}

String __fastcall TSettingsStorages::GetStorageName()
{
    return storageName;
}

void __fastcall TSettingsStorages::SetStorageName(String _name)
{
    storageName = _name;
    name = _name;
}

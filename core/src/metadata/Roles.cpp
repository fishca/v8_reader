//---------------------------------------------------------------------------

#pragma hdrstop

#include "Roles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TRoles::TRoles() : BaseMetadataObject()
{
    roleName = "";
    root_data.reset();
}

TRoles::TRoles(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    roleName = "";
    root_data.reset();
}

TRoles::TRoles(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    roleName = _name;
    root_data.reset();
}

TRoles::~TRoles()
{
}

String TRoles::GetRoleName()
{
    return roleName;
}

void TRoles::SetRoleName(String _name)
{
    roleName = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TRoles::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TRoles::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TRoles::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TRoles::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TRoles::getForms()
{
    return forms;
}

void TRoles::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ СЂРѕР»Рё РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ СЂРѕР»Рё СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


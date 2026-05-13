//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommandGroups.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TCommandGroups::TCommandGroups() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommandGroups::~TCommandGroups()
{
}

String TCommandGroups::GetCommandName()
{
    return name;
}

void TCommandGroups::SetCommandName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommandGroups::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommandGroups::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommandGroups::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommandGroups::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommandGroups::getForms()
{
    return forms;
}

void TCommandGroups::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РіСЂСѓРїРїС‹ РєРѕРјР°РЅРґ РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РіСЂСѓРїРїС‹ РєРѕРјР°РЅРґ СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


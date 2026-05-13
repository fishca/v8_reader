//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonCommands.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TCommonCommands::TCommonCommands() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonCommands::~TCommonCommands()
{
}

String TCommonCommands::GetCommandName()
{
    return name;
}

void TCommonCommands::SetCommandName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonCommands::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonCommands::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonCommands::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonCommands::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonCommands::getForms()
{
    return forms;
}

void TCommonCommands::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РѕР±С‰РµР№ РєРѕРјР°РЅРґС‹ РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РѕР±С‰РµР№ РєРѕРјР°РЅРґС‹ СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


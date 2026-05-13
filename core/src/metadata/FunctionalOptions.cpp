//---------------------------------------------------------------------------

#pragma hdrstop

#include "FunctionalOptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TFunctionalOptions::TFunctionalOptions() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TFunctionalOptions::~TFunctionalOptions()
{
}

String TFunctionalOptions::GetOptionName()
{
    return name;
}

void TFunctionalOptions::SetOptionName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFunctionalOptions::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFunctionalOptions::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFunctionalOptions::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFunctionalOptions::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFunctionalOptions::getForms()
{
    return forms;
}

void TFunctionalOptions::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


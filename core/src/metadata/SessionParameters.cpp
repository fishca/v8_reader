//---------------------------------------------------------------------------

#pragma hdrstop

#include "SessionParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TSessionParameters::TSessionParameters() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TSessionParameters::~TSessionParameters()
{
}

String TSessionParameters::GetParameterName()
{
    return name;
}

void TSessionParameters::SetParameterName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TSessionParameters::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TSessionParameters::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TSessionParameters::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TSessionParameters::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TSessionParameters::getForms()
{
    return forms;
}

void TSessionParameters::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РїР°СЂР°РјРµС‚СЂР° СЃРµР°РЅСЃР° РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РїР°СЂР°РјРµС‚СЂР° СЃРµР°РЅСЃР° СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


//---------------------------------------------------------------------------

#pragma hdrstop

#include "FunctionalOptionsParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TFunctionalOptionsParameters::TFunctionalOptionsParameters() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TFunctionalOptionsParameters::~TFunctionalOptionsParameters()
{
}

String TFunctionalOptionsParameters::GetParameterName()
{
    return name;
}

void TFunctionalOptionsParameters::SetParameterName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFunctionalOptionsParameters::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFunctionalOptionsParameters::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFunctionalOptionsParameters::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFunctionalOptionsParameters::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFunctionalOptionsParameters::getForms()
{
    return forms;
}

void TFunctionalOptionsParameters::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РїР°СЂР°РјРµС‚СЂР° С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РїР°СЂР°РјРµС‚СЂР° С„СѓРЅРєС†РёРѕРЅР°Р»СЊРЅРѕР№ РѕРїС†РёРё СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


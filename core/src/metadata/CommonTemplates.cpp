//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonTemplates.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TCommonTemplates::TCommonTemplates() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonTemplates::~TCommonTemplates()
{
}

String TCommonTemplates::GetTemplateName()
{
    return name;
}

void TCommonTemplates::SetTemplateName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonTemplates::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonTemplates::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonTemplates::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonTemplates::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonTemplates::getForms()
{
    return forms;
}

void TCommonTemplates::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РѕР±С‰РµРіРѕ РјР°РєРµС‚Р° РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РѕР±С‰РµРіРѕ РјР°РєРµС‚Р° СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}

//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonAttributes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TCommonAttributes::TCommonAttributes() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonAttributes::~TCommonAttributes()
{
}

String TCommonAttributes::GetAttributeName()
{
    return name;
}

void TCommonAttributes::SetAttributeName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonAttributes::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonAttributes::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonAttributes::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonAttributes::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonAttributes::getForms()
{
    return forms;
}

void TCommonAttributes::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РѕР±С‰РµРіРѕ СЂРµРєРІРёР·РёС‚Р° РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РѕР±С‰РµРіРѕ СЂРµРєРІРёР·РёС‚Р° СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


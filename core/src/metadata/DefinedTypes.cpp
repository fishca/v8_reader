//---------------------------------------------------------------------------

#pragma hdrstop

#include "DefinedTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TDefinedTypes::TDefinedTypes() : BaseMetadataObject()
{
    typeName = "";
    root_data.reset();
}

TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    typeName = "";
    root_data.reset();
}

TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    typeName = _name;
    root_data.reset();
}

TDefinedTypes::~TDefinedTypes()
{
}

String TDefinedTypes::GetTypeName()
{
    return typeName;
}

void TDefinedTypes::SetTypeName(String _name)
{
    typeName = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TDefinedTypes::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TDefinedTypes::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TDefinedTypes::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TDefinedTypes::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TDefinedTypes::getForms()
{
    return forms;
}

void TDefinedTypes::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РѕРїСЂРµРґРµР»СЏРµРјРѕРіРѕ С‚РёРїР° РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ С‚РёРїР° СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


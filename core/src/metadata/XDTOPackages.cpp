//---------------------------------------------------------------------------
#pragma hdrstop

#include "XDTOPackages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TXDTOPackages::TXDTOPackages() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    parent = _parent;
    root_data.reset();
}

TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

TXDTOPackages::~TXDTOPackages()
{
    // root_data Р±СѓРґРµС‚ РѕСЃРІРѕР±РѕР¶РґРµРЅ РІ Р±Р°Р·РѕРІРѕРј РєР»Р°СЃСЃРµ
}

String TXDTOPackages::GetXDTOPackageName()
{
    return name;
}

// Р РµР°Р»РёР·Р°С†РёСЏ РІРёСЂС‚СѓР°Р»СЊРЅС‹С… РјРµС‚РѕРґРѕРІ BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& TXDTOPackages::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TXDTOPackages::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TXDTOPackages::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TXDTOPackages::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TXDTOPackages::getForms()
{
    return forms;
}

void TXDTOPackages::initializeFromTree()
{
    // XDTO-РїР°РєРµС‚С‹ РјРѕРіСѓС‚ РЅРµ РёРјРµС‚СЊ СЃС‚Р°РЅРґР°СЂС‚РЅРѕР№ СЃС‚СЂСѓРєС‚СѓСЂС‹ СЂРµРєРІРёР·РёС‚РѕРІ/РєРѕРјР°РЅРґ
    // РћСЃС‚Р°РІР»СЏРµРј РїСѓСЃС‚С‹РјРё vectors - СЌС‚Рѕ РЅРѕСЂРјР°Р»СЊРЅРѕ РґР»СЏ РґР°РЅРЅРѕРіРѕ С‚РёРїР° РјРµС‚Р°РґР°РЅРЅС‹С…
}
//---------------------------------------------------------------------------


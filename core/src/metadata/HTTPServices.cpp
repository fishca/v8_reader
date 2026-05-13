//---------------------------------------------------------------------------
#pragma hdrstop

#include "HTTPServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

THTTPServices::THTTPServices() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    parent = _parent;
    root_data.reset();
}

THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

THTTPServices::~THTTPServices()
{
    // root_data Р±СѓРґРµС‚ РѕСЃРІРѕР±РѕР¶РґРµРЅ РІ Р±Р°Р·РѕРІРѕРј РєР»Р°СЃСЃРµ
}

String THTTPServices::GetHTTPServicesName()
{
    return name;
}

void THTTPServices::SetHTTPServicesName(String _name)
{
    name = _name;
}

// Р РµР°Р»РёР·Р°С†РёСЏ РІРёСЂС‚СѓР°Р»СЊРЅС‹С… РјРµС‚РѕРґРѕРІ BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& THTTPServices::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& THTTPServices::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& THTTPServices::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& THTTPServices::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& THTTPServices::getForms()
{
    return forms;
}

void THTTPServices::initializeFromTree()
{
    // HTTP-СЃРµСЂРІРёСЃС‹ РјРѕРіСѓС‚ РЅРµ РёРјРµС‚СЊ СЃС‚Р°РЅРґР°СЂС‚РЅРѕР№ СЃС‚СЂСѓРєС‚СѓСЂС‹ СЂРµРєРІРёР·РёС‚РѕРІ/РєРѕРјР°РЅРґ
    // РћСЃС‚Р°РІР»СЏРµРј РїСѓСЃС‚С‹РјРё vectors - СЌС‚Рѕ РЅРѕСЂРјР°Р»СЊРЅРѕ РґР»СЏ РґР°РЅРЅРѕРіРѕ С‚РёРїР° РјРµС‚Р°РґР°РЅРЅС‹С…
}
//---------------------------------------------------------------------------


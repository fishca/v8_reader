//---------------------------------------------------------------------------
#pragma hdrstop

#include "WebServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TWebServices::TWebServices() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

TWebServices::TWebServices(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    parent = _parent;
    root_data.reset();
}

TWebServices::TWebServices(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

TWebServices::~TWebServices()
{
    // root_data Р±СѓРґРµС‚ РѕСЃРІРѕР±РѕР¶РґРµРЅ РІ Р±Р°Р·РѕРІРѕРј РєР»Р°СЃСЃРµ
}

String TWebServices::GetWebServiceName()
{
    return name;
}

void TWebServices::SetWebServiceName(String _name)
{
    name = _name;
}

// Р РµР°Р»РёР·Р°С†РёСЏ РІРёСЂС‚СѓР°Р»СЊРЅС‹С… РјРµС‚РѕРґРѕРІ BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& TWebServices::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TWebServices::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TWebServices::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TWebServices::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TWebServices::getForms()
{
    return forms;
}

void TWebServices::initializeFromTree()
{
    // Р’РµР±-СЃРµСЂРІРёСЃС‹ РјРѕРіСѓС‚ РЅРµ РёРјРµС‚СЊ СЃС‚Р°РЅРґР°СЂС‚РЅРѕР№ СЃС‚СЂСѓРєС‚СѓСЂС‹ СЂРµРєРІРёР·РёС‚РѕРІ/РєРѕРјР°РЅРґ
    // РћСЃС‚Р°РІР»СЏРµРј РїСѓСЃС‚С‹РјРё vectors - СЌС‚Рѕ РЅРѕСЂРјР°Р»СЊРЅРѕ РґР»СЏ РґР°РЅРЅРѕРіРѕ С‚РёРїР° РјРµС‚Р°РґР°РЅРЅС‹С…
}
//---------------------------------------------------------------------------


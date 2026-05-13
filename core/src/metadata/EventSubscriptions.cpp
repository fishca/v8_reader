//---------------------------------------------------------------------------

#pragma hdrstop

#include "EventSubscriptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TEventSubscriptions::TEventSubscriptions() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TEventSubscriptions::~TEventSubscriptions()
{
}

String TEventSubscriptions::GetEventSubscriptionName()
{
    return name;
}

void TEventSubscriptions::SetEventSubscriptionName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TEventSubscriptions::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TEventSubscriptions::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TEventSubscriptions::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TEventSubscriptions::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TEventSubscriptions::getForms()
{
    return forms;
}

void TEventSubscriptions::initializeFromTree()
{
    // РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РїРѕРґРїРёСЃРєРё РЅР° СЃРѕР±С‹С‚РёРµ РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
    // РРјСЏ РїРѕРґРїРёСЃРєРё РЅР° СЃРѕР±С‹С‚РёРµ СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}


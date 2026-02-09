//---------------------------------------------------------------------------

#pragma hdrstop

#include "EventSubscriptions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TEventSubscriptions::TEventSubscriptions() : BaseMetadataObject()
{
    name = "";
}

__fastcall TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
}

__fastcall TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
}

__fastcall TEventSubscriptions::~TEventSubscriptions()
{
}

String __fastcall TEventSubscriptions::GetEventSubscriptionName()
{
    return name;
}

void __fastcall TEventSubscriptions::SetEventSubscriptionName(String _name)
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

void __fastcall TEventSubscriptions::initializeFromTree()
{
    // Инициализация подписки на событие из дерева метаданных
    // Имя подписки на событие уже установлено в конструкторе
}

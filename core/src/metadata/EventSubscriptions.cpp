//---------------------------------------------------------------------------


#include "EventSubscriptions.h"
//---------------------------------------------------------------------------


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
    // Инициализация подписки на событие из дерева метаданных
    // Имя подписки на событие уже установлено в конструкторе
}


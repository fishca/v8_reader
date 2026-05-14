//---------------------------------------------------------------------------


#include "EventSubscriptions.h"
//---------------------------------------------------------------------------


TEventSubscriptions::TEventSubscriptions() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TEventSubscriptions::TEventSubscriptions(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TEventSubscriptions::~TEventSubscriptions()
{
}

Utf16String TEventSubscriptions::GetEventSubscriptionName() const
{
    return name;
}

void TEventSubscriptions::SetEventSubscriptionName(const Utf16String& _name)
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


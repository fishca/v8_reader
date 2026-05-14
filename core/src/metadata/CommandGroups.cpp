//---------------------------------------------------------------------------


#include "CommandGroups.h"
//---------------------------------------------------------------------------


TCommandGroups::TCommandGroups() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommandGroups::~TCommandGroups()
{
}

Utf16String TCommandGroups::GetCommandName() const
{
    return name;
}

void TCommandGroups::SetCommandName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommandGroups::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommandGroups::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommandGroups::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommandGroups::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommandGroups::getForms()
{
    return forms;
}

void TCommandGroups::initializeFromTree()
{
    // Инициализация группы команд из дерева метаданных
    // Имя группы команд уже установлено в конструкторе
}


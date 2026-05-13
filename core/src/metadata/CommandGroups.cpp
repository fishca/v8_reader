//---------------------------------------------------------------------------


#include "CommandGroups.h"
//---------------------------------------------------------------------------


TCommandGroups::TCommandGroups() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TCommandGroups::TCommandGroups(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommandGroups::~TCommandGroups()
{
}

String TCommandGroups::GetCommandName()
{
    return name;
}

void TCommandGroups::SetCommandName(String _name)
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


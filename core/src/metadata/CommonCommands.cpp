//---------------------------------------------------------------------------


#include "CommonCommands.h"
//---------------------------------------------------------------------------


TCommonCommands::TCommonCommands() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TCommonCommands::TCommonCommands(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TCommonCommands::TCommonCommands(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TCommonCommands::~TCommonCommands()
{
}

Utf16String TCommonCommands::GetCommandName() const
{
    return name;
}

void TCommonCommands::SetCommandName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonCommands::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonCommands::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonCommands::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonCommands::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonCommands::getForms()
{
    return forms;
}

void TCommonCommands::initializeFromTree()
{
    // Инициализация общей команды из дерева метаданных
    // Имя общей команды уже установлено в конструкторе
}


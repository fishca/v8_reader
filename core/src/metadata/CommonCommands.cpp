//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonCommands.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonCommands::TCommonCommands() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TCommonCommands::TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TCommonCommands::~TCommonCommands()
{
}

String __fastcall TCommonCommands::GetCommandName()
{
    return name;
}

void __fastcall TCommonCommands::SetCommandName(String _name)
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

void __fastcall TCommonCommands::initializeFromTree()
{
    // Инициализация общей команды из дерева метаданных
    // Имя общей команды уже установлено в конструкторе
}

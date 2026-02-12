//---------------------------------------------------------------------------

#pragma hdrstop

#include "TConstants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TConstants::TConstants() : BaseMetadataObject()
{
    name = "";
}

__fastcall TConstants::TConstants(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
}

__fastcall TConstants::TConstants(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
}

__fastcall TConstants::~TConstants()
{
}

String __fastcall TConstants::GetConstantsName()
{
    return name;
}

void __fastcall TConstants::SetConstantsName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TConstants::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TConstants::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TConstants::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TConstants::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TConstants::getForms()
{
    return forms;
}

void __fastcall TConstants::initializeFromTree()
{
    // Инициализация константы из дерева метаданных
    // Имя константы уже установлено в конструкторе
}
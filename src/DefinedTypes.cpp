//---------------------------------------------------------------------------

#pragma hdrstop

#include "DefinedTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TDefinedTypes::TDefinedTypes() : BaseMetadataObject()
{
    typeName = "";
    root_data.reset();
}

__fastcall TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    typeName = "";
    root_data.reset();
}

__fastcall TDefinedTypes::TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    typeName = _name;
    root_data.reset();
}

__fastcall TDefinedTypes::~TDefinedTypes()
{
}

String __fastcall TDefinedTypes::GetTypeName()
{
    return typeName;
}

void __fastcall TDefinedTypes::SetTypeName(String _name)
{
    typeName = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TDefinedTypes::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TDefinedTypes::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TDefinedTypes::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TDefinedTypes::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TDefinedTypes::getForms()
{
    return forms;
}

void __fastcall TDefinedTypes::initializeFromTree()
{
    // Инициализация определяемого типа из дерева метаданных
    // Имя типа уже установлено в конструкторе
}

//---------------------------------------------------------------------------


#include "DefinedTypes.h"
//---------------------------------------------------------------------------


TDefinedTypes::TDefinedTypes() : BaseMetadataObject()
{
    name.clear();
    root_data.reset();
}

TDefinedTypes::TDefinedTypes(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name.clear();
    root_data.reset();
}

TDefinedTypes::TDefinedTypes(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TDefinedTypes::~TDefinedTypes()
{
}

Utf16String TDefinedTypes::GetTypeName() const
{
    return name;
}

void TDefinedTypes::SetTypeName(const Utf16String& _name)
{
    name = _name;
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

void TDefinedTypes::initializeFromTree()
{
    // Инициализация определяемого типа из дерева метаданных
    // Имя типа уже установлено в конструкторе
}


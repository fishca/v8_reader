//---------------------------------------------------------------------------


#include "Roles.h"
//---------------------------------------------------------------------------


TRoles::TRoles() : BaseMetadataObject()
{
    name.clear();
    root_data.reset();
}

TRoles::TRoles(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name.clear();
    root_data.reset();
}

TRoles::TRoles(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TRoles::~TRoles()
{
}

Utf16String TRoles::GetRoleName() const
{
    return name;
}

void TRoles::SetRoleName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TRoles::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TRoles::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TRoles::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TRoles::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TRoles::getForms()
{
    return forms;
}

void TRoles::initializeFromTree()
{
    // Инициализация роли из дерева метаданных
    // Имя роли уже установлено в конструкторе
}


//---------------------------------------------------------------------------

#pragma hdrstop

#include "Roles.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TRoles::TRoles() : BaseMetadataObject()
{
    roleName = "";
    root_data.reset();
}

__fastcall TRoles::TRoles(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    roleName = "";
    root_data.reset();
}

__fastcall TRoles::TRoles(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    roleName = _name;
    root_data.reset();
}

__fastcall TRoles::~TRoles()
{
}

String __fastcall TRoles::GetRoleName()
{
    return roleName;
}

void __fastcall TRoles::SetRoleName(String _name)
{
    roleName = _name;
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

void __fastcall TRoles::initializeFromTree()
{
    // Инициализация роли из дерева метаданных
    // Имя роли уже установлено в конструкторе
}

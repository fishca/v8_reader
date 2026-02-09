//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonForms.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonForms::TCommonForms() : BaseMetadataObject()
{
    name = "";
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
}

__fastcall TCommonForms::TCommonForms(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
}

__fastcall TCommonForms::~TCommonForms()
{
}

String __fastcall TCommonForms::GetFormName()
{
    return name;
}

void __fastcall TCommonForms::SetFormName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonForms::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonForms::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonForms::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonForms::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonForms::getForms()
{
    return forms;
}

void __fastcall TCommonForms::initializeFromTree()
{
    // Инициализация общей формы из дерева метаданных
    // Имя общей формы уже установлено в конструкторе
}

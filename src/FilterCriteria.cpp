//---------------------------------------------------------------------------

#pragma hdrstop

#include "FilterCriteria.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TFilterCriteria::TFilterCriteria() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TFilterCriteria::TFilterCriteria(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TFilterCriteria::TFilterCriteria(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TFilterCriteria::~TFilterCriteria()
{
}

String __fastcall TFilterCriteria::GetFilterCriteriaName()
{
    return name;
}

void __fastcall TFilterCriteria::SetFilterCriteriaName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFilterCriteria::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFilterCriteria::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFilterCriteria::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFilterCriteria::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFilterCriteria::getForms()
{
    return forms;
}

void __fastcall TFilterCriteria::initializeFromTree()
{
    // Инициализация критерия отбора из дерева метаданных
    // Имя критерия отбора уже установлено в конструкторе
}

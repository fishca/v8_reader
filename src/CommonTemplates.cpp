//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonTemplates.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonTemplates::TCommonTemplates() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TCommonTemplates::TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TCommonTemplates::~TCommonTemplates()
{
}

String __fastcall TCommonTemplates::GetTemplateName()
{
    return name;
}

void __fastcall TCommonTemplates::SetTemplateName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonTemplates::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonTemplates::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonTemplates::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonTemplates::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonTemplates::getForms()
{
    return forms;
}

void __fastcall TCommonTemplates::initializeFromTree()
{
    // Инициализация общего макета из дерева метаданных
    // Имя общего макета уже установлено в конструкторе
}
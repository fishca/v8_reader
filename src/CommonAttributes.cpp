//---------------------------------------------------------------------------

#pragma hdrstop

#include "CommonAttributes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TCommonAttributes::TCommonAttributes() : BaseMetadataObject()
{
    name = "";
}

__fastcall TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
}

__fastcall TCommonAttributes::TCommonAttributes(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
}

__fastcall TCommonAttributes::~TCommonAttributes()
{
}

String __fastcall TCommonAttributes::GetAttributeName()
{
    return name;
}

void __fastcall TCommonAttributes::SetAttributeName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TCommonAttributes::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TCommonAttributes::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TCommonAttributes::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TCommonAttributes::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TCommonAttributes::getForms()
{
    return forms;
}

void __fastcall TCommonAttributes::initializeFromTree()
{
    // Инициализация общего реквизита из дерева метаданных
    // Имя общего реквизита уже установлено в конструкторе
}

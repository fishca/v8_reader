//---------------------------------------------------------------------------
#pragma hdrstop

#include "XDTOPackages.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TXDTOPackages::TXDTOPackages() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

__fastcall TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data = nullptr;
    parent = _parent;
}

__fastcall TXDTOPackages::TXDTOPackages(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data = nullptr;
    parent = _parent;
}

__fastcall TXDTOPackages::~TXDTOPackages()
{
    // root_data будет освобожден в базовом классе
}

String __fastcall TXDTOPackages::GetXDTOPackageName()
{
    return name;
}

// Реализация виртуальных методов BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& TXDTOPackages::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TXDTOPackages::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TXDTOPackages::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TXDTOPackages::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TXDTOPackages::getForms()
{
    return forms;
}

void __fastcall TXDTOPackages::initializeFromTree()
{
    // XDTO-пакеты могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------

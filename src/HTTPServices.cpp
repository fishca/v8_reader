//---------------------------------------------------------------------------
#pragma hdrstop

#include "HTTPServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall THTTPServices::THTTPServices() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

__fastcall THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    parent = _parent;
    root_data.reset();
}

__fastcall THTTPServices::THTTPServices(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

__fastcall THTTPServices::~THTTPServices()
{
    // root_data будет освобожден в базовом классе
}

String __fastcall THTTPServices::GetHTTPServicesName()
{
    return name;
}

void __fastcall THTTPServices::SetHTTPServicesName(String _name)
{
    name = _name;
}

// Реализация виртуальных методов BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& THTTPServices::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& THTTPServices::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& THTTPServices::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& THTTPServices::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& THTTPServices::getForms()
{
    return forms;
}

void __fastcall THTTPServices::initializeFromTree()
{
    // HTTP-сервисы могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------

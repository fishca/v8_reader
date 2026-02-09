//---------------------------------------------------------------------------
#pragma hdrstop

#include "WebServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TWebServices::TWebServices() : BaseMetadataObject()
{
    name = "";
    root_data = nullptr;
    parent = nullptr;
}

__fastcall TWebServices::TWebServices(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data = nullptr;
    parent = _parent;
}

__fastcall TWebServices::TWebServices(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data = nullptr;
    parent = _parent;
}

__fastcall TWebServices::~TWebServices()
{
    // root_data будет освобожден в базовом классе
}

String __fastcall TWebServices::GetWebServiceName()
{
    return name;
}

void __fastcall TWebServices::SetWebServiceName(String _name)
{
    name = _name;
}

// Реализация виртуальных методов BaseMetadataObject

std::vector<std::unique_ptr<TRequisite>>& TWebServices::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TWebServices::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TWebServices::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TWebServices::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TWebServices::getForms()
{
    return forms;
}

void __fastcall TWebServices::initializeFromTree()
{
    // Веб-сервисы могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

#include "HTTPServices.h"
//---------------------------------------------------------------------------

THTTPServices::THTTPServices() : BaseMetadataObject()
{
    name = u"";
    root_data = nullptr;
    parent = nullptr;
}

THTTPServices::THTTPServices(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    parent = _parent;
    root_data.reset();
}

THTTPServices::THTTPServices(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

THTTPServices::~THTTPServices()
{
    // root_data будет освобожден в базовом классе
}

Utf16String THTTPServices::GetHTTPServicesName() const
{
    return name;
}

void THTTPServices::SetHTTPServicesName(const Utf16String& _name)
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

void THTTPServices::initializeFromTree()
{
    // HTTP-сервисы могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------


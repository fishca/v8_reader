//---------------------------------------------------------------------------

#include "WebServices.h"
//---------------------------------------------------------------------------

TWebServices::TWebServices() : BaseMetadataObject()
{
    name = u"";
    root_data = nullptr;
    parent = nullptr;
}

TWebServices::TWebServices(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    parent = _parent;
    root_data.reset();
}

TWebServices::TWebServices(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

TWebServices::~TWebServices()
{
    // root_data будет освобожден в базовом классе
}

Utf16String TWebServices::GetWebServiceName() const
{
    return name;
}

void TWebServices::SetWebServiceName(const Utf16String& _name)
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

void TWebServices::initializeFromTree()
{
    // Веб-сервисы могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------


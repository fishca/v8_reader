//---------------------------------------------------------------------------

#include "XDTOPackages.h"
//---------------------------------------------------------------------------

TXDTOPackages::TXDTOPackages() : BaseMetadataObject()
{
    name = u"";
    root_data = nullptr;
    parent = nullptr;
}

TXDTOPackages::TXDTOPackages(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    parent = _parent;
    root_data.reset();
}

TXDTOPackages::TXDTOPackages(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    parent = _parent;
    root_data.reset();
}

TXDTOPackages::~TXDTOPackages()
{
    // root_data будет освобожден в базовом классе
}

Utf16String TXDTOPackages::GetXDTOPackageName() const
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

void TXDTOPackages::initializeFromTree()
{
    // XDTO-пакеты могут не иметь стандартной структуры реквизитов/команд
    // Оставляем пустыми vectors - это нормально для данного типа метаданных
}
//---------------------------------------------------------------------------


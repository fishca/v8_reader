//---------------------------------------------------------------------------


#include "SettingsStorages.h"
//---------------------------------------------------------------------------


TSettingsStorages::TSettingsStorages() : BaseMetadataObject()
{
    name.clear();
    root_data.reset();
}

TSettingsStorages::TSettingsStorages(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name.clear();
    root_data.reset();
}

TSettingsStorages::TSettingsStorages(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TSettingsStorages::~TSettingsStorages()
{
}

Utf16String TSettingsStorages::GetStorageName() const
{
    return name;
}

void TSettingsStorages::SetStorageName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TSettingsStorages::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TSettingsStorages::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TSettingsStorages::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TSettingsStorages::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TSettingsStorages::getForms()
{
    return forms;
}

void TSettingsStorages::initializeFromTree()
{
    // Инициализация хранилища настроек из дерева метаданных
    // Имя хранилища настроек уже установлено в конструкторе
}


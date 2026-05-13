//---------------------------------------------------------------------------


#include "SettingsStorages.h"
//---------------------------------------------------------------------------


TSettingsStorages::TSettingsStorages() : BaseMetadataObject()
{
    storageName = "";
    root_data.reset();
}

TSettingsStorages::TSettingsStorages(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    storageName = "";
    root_data.reset();
}

TSettingsStorages::TSettingsStorages(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    storageName = _name;
    root_data.reset();
}

TSettingsStorages::~TSettingsStorages()
{
}

String TSettingsStorages::GetStorageName()
{
    return storageName;
}

void TSettingsStorages::SetStorageName(String _name)
{
    storageName = _name;
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


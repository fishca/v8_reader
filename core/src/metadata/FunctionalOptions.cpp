//---------------------------------------------------------------------------


#include "FunctionalOptions.h"
//---------------------------------------------------------------------------


TFunctionalOptions::TFunctionalOptions() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TFunctionalOptions::TFunctionalOptions(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TFunctionalOptions::~TFunctionalOptions()
{
}

String TFunctionalOptions::GetOptionName()
{
    return name;
}

void TFunctionalOptions::SetOptionName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFunctionalOptions::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFunctionalOptions::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFunctionalOptions::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFunctionalOptions::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFunctionalOptions::getForms()
{
    return forms;
}

void TFunctionalOptions::initializeFromTree()
{
    // Инициализация функциональной опции из дерева метаданных
    // Имя функциональной опции уже установлено в конструкторе
}


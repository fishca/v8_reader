//---------------------------------------------------------------------------


#include "SessionParameters.h"
//---------------------------------------------------------------------------


TSessionParameters::TSessionParameters() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TSessionParameters::~TSessionParameters()
{
}

String TSessionParameters::GetParameterName()
{
    return name;
}

void TSessionParameters::SetParameterName(String _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TSessionParameters::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TSessionParameters::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TSessionParameters::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TSessionParameters::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TSessionParameters::getForms()
{
    return forms;
}

void TSessionParameters::initializeFromTree()
{
    // Инициализация параметра сеанса из дерева метаданных
    // Имя параметра сеанса уже установлено в конструкторе
}


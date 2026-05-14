//---------------------------------------------------------------------------


#include "SessionParameters.h"
//---------------------------------------------------------------------------


TSessionParameters::TSessionParameters() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TSessionParameters::TSessionParameters(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TSessionParameters::~TSessionParameters()
{
}

Utf16String TSessionParameters::GetParameterName()
{
    return name;
}

void TSessionParameters::SetParameterName(const Utf16String& _name)
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


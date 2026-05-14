//---------------------------------------------------------------------------


#include "FunctionalOptionsParameters.h"
//---------------------------------------------------------------------------


TFunctionalOptionsParameters::TFunctionalOptionsParameters() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    root_data.reset();
}

TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

TFunctionalOptionsParameters::~TFunctionalOptionsParameters()
{
}

Utf16String TFunctionalOptionsParameters::GetParameterName() const
{
    return name;
}

void TFunctionalOptionsParameters::SetParameterName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFunctionalOptionsParameters::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFunctionalOptionsParameters::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFunctionalOptionsParameters::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFunctionalOptionsParameters::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFunctionalOptionsParameters::getForms()
{
    return forms;
}

void TFunctionalOptionsParameters::initializeFromTree()
{
    // Инициализация параметра функциональной опции из дерева метаданных
    // Имя параметра функциональной опции уже установлено в конструкторе
}


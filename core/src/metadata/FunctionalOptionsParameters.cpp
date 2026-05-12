//---------------------------------------------------------------------------

#pragma hdrstop

#include "FunctionalOptionsParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TFunctionalOptionsParameters::TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TFunctionalOptionsParameters::~TFunctionalOptionsParameters()
{
}

String __fastcall TFunctionalOptionsParameters::GetParameterName()
{
    return name;
}

void __fastcall TFunctionalOptionsParameters::SetParameterName(String _name)
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

void __fastcall TFunctionalOptionsParameters::initializeFromTree()
{
    // Инициализация параметра функциональной опции из дерева метаданных
    // Имя параметра функциональной опции уже установлено в конструкторе
}

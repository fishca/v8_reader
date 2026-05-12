//---------------------------------------------------------------------------

#pragma hdrstop

#include "SessionParameters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TSessionParameters::TSessionParameters() : BaseMetadataObject()
{
    name = "";
    root_data.reset();
}

__fastcall TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = "";
    root_data.reset();
}

__fastcall TSessionParameters::TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    root_data.reset();
}

__fastcall TSessionParameters::~TSessionParameters()
{
}

String __fastcall TSessionParameters::GetParameterName()
{
    return name;
}

void __fastcall TSessionParameters::SetParameterName(String _name)
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

void __fastcall TSessionParameters::initializeFromTree()
{
    // Инициализация параметра сеанса из дерева метаданных
    // Имя параметра сеанса уже установлено в конструкторе
}

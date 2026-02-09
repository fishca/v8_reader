//---------------------------------------------------------------------------

#pragma hdrstop

#include "ExchangePlans.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TExchangePlans::TExchangePlans() : BaseMetadataObject()
{
    exchangePlanName = "";
}

__fastcall TExchangePlans::TExchangePlans(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    exchangePlanName = "";
}

__fastcall TExchangePlans::TExchangePlans(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    exchangePlanName = _name;
}

__fastcall TExchangePlans::~TExchangePlans()
{
}

String __fastcall TExchangePlans::GetExchangePlanName()
{
    return exchangePlanName;
}

void __fastcall TExchangePlans::SetExchangePlanName(String _name)
{
    exchangePlanName = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TExchangePlans::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TExchangePlans::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TExchangePlans::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TExchangePlans::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TExchangePlans::getForms()
{
    return forms;
}

void __fastcall TExchangePlans::initializeFromTree()
{
    // Инициализация плана обмена из дерева метаданных
    // Имя плана обмена уже установлено в конструкторе
}

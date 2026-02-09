//---------------------------------------------------------------------------

#pragma hdrstop

#include "Bots.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall TBots::TBots() : BaseMetadataObject()
{
    botName = "";
}

__fastcall TBots::TBots(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    botName = "";
}

__fastcall TBots::TBots(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    botName = _name;
}

__fastcall TBots::~TBots()
{
}

String __fastcall TBots::GetBotName()
{
    return botName;
}

void __fastcall TBots::SetBotName(String _name)
{
    botName = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TBots::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TBots::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TBots::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TBots::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TBots::getForms()
{
    return forms;
}

void __fastcall TBots::initializeFromTree()
{
    // Инициализация бота из дерева метаданных
    // Имя бота уже установлено в конструкторе
}

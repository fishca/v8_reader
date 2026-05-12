//---------------------------------------------------------------------------

#pragma hdrstop

#include "Subsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TSubsystem::TSubsystem() : BaseMetadataObject()
{
	name = "";
	root_data.reset();
}

__fastcall TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	name = "";
	root_data.reset();
}

__fastcall TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

__fastcall TSubsystem::~TSubsystem()
{
}

String __fastcall TSubsystem::GetSubsystemName()
{
	return name;
}

void __fastcall TSubsystem::SetSubsystemName(String _name)
{
	name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TSubsystem::getAttributes()
{
	return attributes;
}

std::vector<std::unique_ptr<TComand>>& TSubsystem::getCommands()
{
	return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TSubsystem::getLayouts()
{
	return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TSubsystem::getTabularSections()
{
	return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TSubsystem::getForms()
{
	return forms;
}

void __fastcall TSubsystem::initializeFromTree()
{
	// Инициализация подсистемы из дерева метаданных
	// Имя подсистемы уже установлено в конструкторе
}
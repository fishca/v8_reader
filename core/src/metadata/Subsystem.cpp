//---------------------------------------------------------------------------


#include "Subsystem.h"
//---------------------------------------------------------------------------

TSubsystem::TSubsystem() : BaseMetadataObject()
{
	name = u"";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	name = u"";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	name = V8Utf16FromString(_name);
	root_data.reset();
}

TSubsystem::~TSubsystem()
{
}

String TSubsystem::GetSubsystemName()
{
	return String(reinterpret_cast<const wchar_t*>(name.c_str()));
}

void TSubsystem::SetSubsystemName(String _name)
{
	name = V8Utf16FromString(_name);
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

void TSubsystem::initializeFromTree()
{
	// Инициализация подсистемы из дерева метаданных
	// Имя подсистемы уже установлено в конструкторе
}

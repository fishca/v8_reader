//---------------------------------------------------------------------------


#include "Subsystem.h"
//---------------------------------------------------------------------------

TSubsystem::TSubsystem() : BaseMetadataObject()
{
	name = u"";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
	name = u"";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

TSubsystem::~TSubsystem()
{
}

Utf16String TSubsystem::GetSubsystemName()
{
	return name;
}

void TSubsystem::SetSubsystemName(const Utf16String& _name)
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

void TSubsystem::initializeFromTree()
{
	// Инициализация подсистемы из дерева метаданных
	// Имя подсистемы уже установлено в конструкторе
}

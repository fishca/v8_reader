//---------------------------------------------------------------------------

#pragma hdrstop

#include "Langs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TLangs::TLangs() : BaseMetadataObject()
{
	name = "";
	root_data.reset();
}

TLangs::TLangs(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	name = "";
	root_data.reset();
}

TLangs::TLangs(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

TLangs::~TLangs()
{
}

String TLangs::GetLangName()
{
	return name;
}

void TLangs::SetLangName(String _name)
{
	name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TLangs::getAttributes()
{
	return attributes;
}

std::vector<std::unique_ptr<TComand>>& TLangs::getCommands()
{
	return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TLangs::getLayouts()
{
	return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TLangs::getTabularSections()
{
	return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TLangs::getForms()
{
	return forms;
}

void TLangs::initializeFromTree()
{
	// Инициализация интерфейса из дерева метаданных
	// Имя интерфейса уже установлено в конструкторе
}


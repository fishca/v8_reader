//---------------------------------------------------------------------------

#pragma hdrstop

#include "Subsystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TSubsystem::TSubsystem() : BaseMetadataObject()
{
	name = "";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
	name = "";
	root_data.reset();
}

TSubsystem::TSubsystem(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
	name = _name;
	root_data.reset();
}

TSubsystem::~TSubsystem()
{
}

String TSubsystem::GetSubsystemName()
{
	return name;
}

void TSubsystem::SetSubsystemName(String _name)
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
	// РРЅРёС†РёР°Р»РёР·Р°С†РёСЏ РїРѕРґСЃРёСЃС‚РµРјС‹ РёР· РґРµСЂРµРІР° РјРµС‚Р°РґР°РЅРЅС‹С…
	// РРјСЏ РїРѕРґСЃРёСЃС‚РµРјС‹ СѓР¶Рµ СѓСЃС‚Р°РЅРѕРІР»РµРЅРѕ РІ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂРµ
}

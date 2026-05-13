//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "InformationRegisters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static InfoRegisterTreePaths GetInformationRegistersPaths()
{
	InfoRegisterTreePaths paths;
	// TODO: РїСѓС‚Рё СЃРєРѕРїРёСЂРѕРІР°РЅС‹ РїРѕ Р°РЅР°Р»РѕРіРёРё СЃ Catalogs - РЅРµРѕР±С…РѕРґРёРјРѕ РїСЂРѕРІРµСЂРёС‚СЊ Рё РёСЃРїСЂР°РІРёС‚СЊ РґР»СЏ СЂРµРіРёСЃС‚СЂРѕРІ СЃРІРµРґРµРЅРёР№
	paths.attIdx = 7;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.dimIdx = 4;   // РёР·РјРµСЂРµРЅРёСЏ
	paths.dimItemPath = {0, 1, 1, 1, 2};
	paths.resIdx = 3;   // СЂРµСЃСѓСЂСЃС‹
	paths.resItemPath = {0, 1, 1, 1, 2};
	paths.formsIdx = 5;
	paths.cmdIdx = 8;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 6;
	paths.getFormNameFunc = GetNameFormCatalogs;
	return paths;
}

TInformationRegisters::TInformationRegisters()
	: MetadataObjectInformationRegister()
{
}

TInformationRegisters::TInformationRegisters(v8catalog *_parent, const String& _guid)
	: MetadataObjectInformationRegister(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TInformationRegisters::TInformationRegisters(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectInformationRegister(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TInformationRegisters::~TInformationRegisters()
{
}

void TInformationRegisters::initializeFromTree()
{
	MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetInformationRegistersPaths());
}


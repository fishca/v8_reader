//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "InformationRegisters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

static InfoRegisterTreePaths GetInformationRegistersPaths()
{
	InfoRegisterTreePaths paths;
	// TODO: пути скопированы по аналогии с Catalogs - необходимо проверить и исправить для регистров сведений
	paths.attIdx = 7;
	paths.attItemPath = {0, 1, 1, 1, 2};
	paths.dimIdx = 4;   // измерения
	paths.dimItemPath = {0, 1, 1, 1, 2};
	paths.resIdx = 3;   // ресурсы
	paths.resItemPath = {0, 1, 1, 1, 2};
	paths.formsIdx = 5;
	paths.cmdIdx = 8;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	paths.moxIdx = 6;
	paths.getFormNameFunc = GetNameFormCatalogs;
	return paths;
}

__fastcall TInformationRegisters::TInformationRegisters()
	: MetadataObjectInformationRegister()
{
}

__fastcall TInformationRegisters::TInformationRegisters(v8catalog *_parent, const String& _guid)
	: MetadataObjectInformationRegister(_parent, _guid)
{
	initializeFromTree();
}

__fastcall TInformationRegisters::TInformationRegisters(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectInformationRegister(_parent, _guid, _name)
{
	initializeFromTree();
}

__fastcall TInformationRegisters::~TInformationRegisters()
{
}

void __fastcall TInformationRegisters::initializeFromTree()
{
	MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetInformationRegistersPaths());
}

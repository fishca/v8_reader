//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "AccumulationRegisters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Убрать static для CRTP-шаблона
InfoRegisterTreePaths GetAccumulationRegistersPaths()
{
	InfoRegisterTreePaths paths;
	// Пути для регистров накопления - аналогично регистрам сведений
	paths.attIdx = 6;
	paths.attItemPath = {0, 1, 1, 1, 2};
	
    paths.dimIdx = 7;   // измерения
	paths.dimItemPath = {0, 1, 1, 1, 2};
	
    paths.resIdx = 5;   // ресурсы
	paths.resItemPath = {0, 1, 1, 1, 2};
	
    paths.formsIdx = 8;
	
    paths.cmdIdx = 4;
	paths.cmdItemPath = {0, 1, 2, 9, 2};
	
    paths.moxIdx = 3;
	
    paths.getFormNameFunc = GetNameFormCatalogs;
	return paths;
}

__fastcall TAccumulationRegisters::TAccumulationRegisters()
	: MetadataObjectInformationRegisterT<TAccumulationRegisters, GetAccumulationRegistersPaths>()
{
}

__fastcall TAccumulationRegisters::TAccumulationRegisters(v8catalog *_parent, const String& _guid)
	: MetadataObjectInformationRegisterT<TAccumulationRegisters, GetAccumulationRegistersPaths>(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TAccumulationRegisters::TAccumulationRegisters(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectInformationRegisterT<TAccumulationRegisters, GetAccumulationRegistersPaths>(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TAccumulationRegisters::~TAccumulationRegisters()
{
}

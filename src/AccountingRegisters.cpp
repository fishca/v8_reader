//---------------------------------------------------------------------------
#pragma hdrstop

#include "Common.h"
#include "AccountingRegisters.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// Конфигурация путей в дереве парсинга для регистров бухгалтерии
// Убрать static для CRTP-шаблона
InfoRegisterTreePaths GetAccountingRegistersPaths()
{
    InfoRegisterTreePaths paths;
    
	// Пути для регистров бухгалтерии
    paths.attIdx = 7;
    paths.attItemPath = {0, 1, 1, 1, 2};

    paths.dimIdx = 3;   // измерения
    paths.dimItemPath = {0, 1, 1, 1, 2};

    paths.resIdx = 5;   // ресурсы
    paths.resItemPath = {0, 1, 1, 1, 2};

    paths.formsIdx = 8;

    paths.cmdIdx = 6;
    paths.cmdItemPath = {0, 1, 2, 9, 2};

    paths.moxIdx = 4;

    paths.getFormNameFunc = GetNameFormPVH;
    return paths;
}

__fastcall TAccountingRegisters::TAccountingRegisters()
    : MetadataObjectInformationRegisterT<TAccountingRegisters, GetAccountingRegistersPaths>()
{
}

__fastcall TAccountingRegisters::TAccountingRegisters(v8catalog *_parent, const String& _guid)
    : MetadataObjectInformationRegisterT<TAccountingRegisters, GetAccountingRegistersPaths>(_parent, _guid)
{
    initializeFromTree();
	root_data.reset();
}

__fastcall TAccountingRegisters::TAccountingRegisters(v8catalog *_parent, const String& _guid, const String& _name)
    : MetadataObjectInformationRegisterT<TAccountingRegisters, GetAccountingRegistersPaths>(_parent, _guid, _name)
{
    initializeFromTree();
	root_data.reset();
}

__fastcall TAccountingRegisters::~TAccountingRegisters()
{
}

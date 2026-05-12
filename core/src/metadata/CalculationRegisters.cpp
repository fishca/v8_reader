//---------------------------------------------------------------------------

#pragma hdrstop

#include "CalculationRegisters.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

// Конфигурация путей в дереве парсинга для регистров расчета
static InfoRegisterTreePaths GetCalculationRegistersPaths()
{
    InfoRegisterTreePaths paths;
    // Пути для регистров расчета
    paths.attIdx = 3;
    paths.attItemPath = {0, 1, 1, 1, 2};

    paths.dimIdx = 9;   // измерения
    paths.dimItemPath = {0, 1, 1, 1, 2};

    paths.resIdx = 6;   // ресурсы
    paths.resItemPath = {0, 1, 1, 1, 2};

    paths.formsIdx = 7;

    paths.cmdIdx = 8;
    paths.cmdItemPath = {0, 1, 2, 9, 2};

    paths.moxIdx = 5;

    paths.getFormNameFunc = GetNameFormCatalogs;
    return paths;
}

//---------------------------------------------------------------------------
__fastcall TCalculationRegisters::TCalculationRegisters()
	: MetadataObjectInformationRegister()
{
}

//---------------------------------------------------------------------------
__fastcall TCalculationRegisters::TCalculationRegisters(v8catalog *_parent, const String& _guid)
	: MetadataObjectInformationRegister(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

//---------------------------------------------------------------------------
__fastcall TCalculationRegisters::TCalculationRegisters(v8catalog *_parent, const String& _guid, const String& _name)
	: MetadataObjectInformationRegister(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

//---------------------------------------------------------------------------
__fastcall TCalculationRegisters::~TCalculationRegisters()
{
}

//---------------------------------------------------------------------------
void __fastcall TCalculationRegisters::initializeFromTree()
{
	// Инициализируем стандартные поля (реквизиты, измерения, ресурсы, формы, команды, макеты)
	MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetCalculationRegistersPaths());
}

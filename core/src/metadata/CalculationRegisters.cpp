//---------------------------------------------------------------------------


#include "CalculationRegisters.h"

//---------------------------------------------------------------------------


//  онфигураци€ путей в дереве парсинга дл€ регистров расчета
static InfoRegisterTreePaths GetCalculationRegistersPaths()
{
    InfoRegisterTreePaths paths;
    // ѕути дл€ регистров расчета
    paths.attIdx = 3;
    paths.attItemPath = {0, 1, 1, 1, 2};

    paths.dimIdx = 9;   // измерени€
    paths.dimItemPath = {0, 1, 1, 1, 2};

    paths.resIdx = 6;   // ресурсы
    paths.resItemPath = {0, 1, 1, 1, 2};

    paths.formsIdx = 7;

    paths.cmdIdx = 8;
    paths.cmdItemPath = {0, 1, 2, 9, 2};

    paths.moxIdx = 5;

    paths.getFormNameFunc = GetNameFormCatalogs16;
    return paths;
}

//---------------------------------------------------------------------------
TCalculationRegisters::TCalculationRegisters()
	: MetadataObjectInformationRegister()
{
}

//---------------------------------------------------------------------------
TCalculationRegisters::TCalculationRegisters(v8catalog *_parent, const Utf16String& _guid)
	: MetadataObjectInformationRegister(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

//---------------------------------------------------------------------------
TCalculationRegisters::TCalculationRegisters(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: MetadataObjectInformationRegister(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

//---------------------------------------------------------------------------
TCalculationRegisters::~TCalculationRegisters()
{
}

//---------------------------------------------------------------------------
void TCalculationRegisters::initializeFromTree()
{
	// »нициализируем стандартные пол€ (реквизиты, измерени€, ресурсы, формы, команды, макеты)
	MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetCalculationRegistersPaths());
}


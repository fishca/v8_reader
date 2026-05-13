//---------------------------------------------------------------------------

#include "Common.h"
#include "AccountingRegisters.h"
//---------------------------------------------------------------------------

// Конфигурация путей в дереве парсинга для регистров бухгалтерии
static InfoRegisterTreePaths GetAccountingRegistersPaths()
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

TAccountingRegisters::TAccountingRegisters()
    : MetadataObjectInformationRegister()
{
}

TAccountingRegisters::TAccountingRegisters(v8catalog *_parent, const String& _guid)
    : MetadataObjectInformationRegister(_parent, _guid)
{
    initializeFromTree();
	root_data.reset();
}

TAccountingRegisters::TAccountingRegisters(v8catalog *_parent, const String& _guid, const String& _name)
    : MetadataObjectInformationRegister(_parent, _guid, _name)
{
    initializeFromTree();
	root_data.reset();
}

TAccountingRegisters::~TAccountingRegisters()
{
}

void TAccountingRegisters::initializeFromTree()
{
    // Инициализируем стандартные поля (реквизиты, измерения, ресурсы, формы, команды, макеты)
    // AccountingFlags и DimensionAccountingFlags будут загружены отдельно
    MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetAccountingRegistersPaths());

    // TODO: Загрузка AccountingFlags и DimensionAccountingFlags
    // При необходимости добавить дополнительную логику загрузки
}


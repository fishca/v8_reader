//---------------------------------------------------------------------------
#ifndef MetadataTreeBuilderH
#define MetadataTreeBuilderH
//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <memory>
#include <unordered_set>

#include "VirtualTrees.hpp"
#include "MainUnit.h"
#include "BaseMetadataObject.h"
#include "MetadataObjectInformationRegister.h"
#include "AccountingRegisters.h"
#include "ChartOfAccounts.h"
#include "Enums.h"
#include "ExternalDataSources.h"
#include "Subsystem.h"
#include "APIcfBase.h"

//---------------------------------------------------------------------------
// Индексы иконок дерева метаданных
namespace TreeImage
{
	constexpr int Root             = 72;
	constexpr int Attributes       = 83;
	constexpr int TabularSections  = 82;
	constexpr int Forms            = 86;
	constexpr int Commands         = 98;
	constexpr int Layouts          = 79;
	constexpr int Dimensions       = 10;
	constexpr int Resources        = 11;
	constexpr int AccountingFlags  = 118;
	constexpr int SubcontoFlags    = 119;
	constexpr int JournalColumns   = 6;
}

constexpr int DefaultTreeNodeAge = 30;

//---------------------------------------------------------------------------
// Базовые операции с узлами дерева

void initNode(VirtualTreeData* data, const String& name, int imageIndex, int age = DefaultTreeNodeAge);

PVirtualNode addChildNode(TVirtualStringTree* tree, PVirtualNode parent, const String& name, int imageIndex, int age = DefaultTreeNodeAge);

template <typename Collection, typename NameGetter>
void addSection(TVirtualStringTree* tree, PVirtualNode parent, const String& sectionName, int sectionImageIndex, int itemImageIndex, const Collection& items, NameGetter getName, int age = DefaultTreeNodeAge)
{
	PVirtualNode sectionNode = addChildNode(tree, parent, sectionName, sectionImageIndex, age);
	for (const auto& item : items)
		addChildNode(tree, sectionNode, getName(item), itemImageIndex, age);
}

void addTabularSections(TVirtualStringTree* tree, PVirtualNode parent, const std::vector<std::unique_ptr<TTabular>>& items, int age = DefaultTreeNodeAge);

//---------------------------------------------------------------------------
// Секции для стандартных объектов и регистров

void fillStandardMetadataSections(TVirtualStringTree* tree, PVirtualNode childNode, BaseMetadataObject* metadataObject);

void fillInformationRegisterSections(TVirtualStringTree* tree, PVirtualNode childNode, MetadataObjectInformationRegister* metadataObject);

//---------------------------------------------------------------------------
// fill*Tree — заполнение узла конкретного типа метаданных

void fillCatalogsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject);

void fillFormsCommandsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject);

void fillAccumulationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject);

void fillCalculationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject);

void fillInformationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject);

void fillAccountingRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TAccountingRegisters* metadataObject);

void fillChartAccTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TChartOfAccounts* metadataObject);

void fillJournalTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject);

void fillEnumTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TEnums* curEnum);

void fillExternalDataSourceTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TExternalDataSources* metadataObject);

//---------------------------------------------------------------------------
// Вспомогательные функции для подсистем

String normalizeGuid(const String& guid);

String GetNameSubsystem(v8catalog* cf, String& guid_md);
String GetSubsystemInnerGuid(v8catalog* cf, String& guid_md);
void GetListChildrenSubsystem(v8catalog* cf, String& guid_md, std::vector<String>& child);

TSubsystem* findSubsystemByAnyGuid(v8catalog* cf, const MetadataVector<TObject>& subsystems, const String& guid);

String getSubsystemDisplayNameByGuid(v8catalog* cf, const MetadataVector<TObject>& subsystems, const String& guid);

void addSubsystemChildrenToTree(TVirtualStringTree* tree, PVirtualNode parentNode, v8catalog* cf, const MetadataVector<TObject>& subsystems, TSubsystem* parentSubsystem, int imgIndex);

void addSubsystemChildrenToTreeByGuid(TVirtualStringTree* tree, PVirtualNode parentNode, v8catalog* cf, const MetadataVector<TObject>& subsystems, const String& parentGuid, int imgIndex);

std::unordered_set<String> collectChildSubsystemGuids(v8catalog* cf, const MetadataVector<TObject>& subsystems);

//---------------------------------------------------------------------------
#endif

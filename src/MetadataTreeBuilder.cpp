//---------------------------------------------------------------------------
#pragma hdrstop

#include "MetadataTreeBuilder.h"
#include "Parse_tree_vcl_adapter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


namespace
{
	String ToVcl(const Utf16String& value)
	{
		return v8reader::vcl_bridge::Utf16ToString(value);
	}
}


void initNode(VirtualTreeData* data, const String& name, int imageIndex, int age)
{
	data->Name = name;
	data->Age = age;
	data->ImgIndex = imageIndex;
	data->text_module = L"";
	data->moduleItemGuid = L"";
	data->MetadataObject = nullptr;
	data->moduleLocation = ModuleTextLocation();
	data->moduleEditable = false;
	data->moduleDirty = false;
}

void initNode(VirtualTreeData* data, const Utf16String& name, int imageIndex, int age = DefaultTreeNodeAge)
{
	initNode(data, ToVcl(name), imageIndex, age);
}

PVirtualNode addChildNode(TVirtualStringTree* tree, PVirtualNode parent, const String& name, int imageIndex, int age)
{
	PVirtualNode childNode = tree->AddChild(parent);
	VirtualTreeData* childData = static_cast<VirtualTreeData*>(tree->GetNodeData(childNode));
	initNode(childData, name, imageIndex, age);
	return childNode;
}

PVirtualNode addChildNode(TVirtualStringTree* tree, PVirtualNode parent, const Utf16String& name, int imageIndex, int age = DefaultTreeNodeAge)
{
	return addChildNode(tree, parent, ToVcl(name), imageIndex, age);
}

void addTabularSections(TVirtualStringTree* tree, PVirtualNode parent, const std::vector<std::unique_ptr<TTabular>>& items, int age)
{
	PVirtualNode sectionNode = addChildNode(tree, parent, L"Табличные части", TreeImage::TabularSections, age);
	tree->Expanded[sectionNode] = true;

	for (const auto& item : items)
	{
		PVirtualNode tabularNode = addChildNode(tree, sectionNode, item->name, TreeImage::TabularSections, age);
		if (!item->attributes.empty())
		{
			for (const auto& attribute : item->attributes)
				addChildNode(tree, tabularNode, attribute->name, TreeImage::Attributes, age);

			tree->Expanded[tabularNode] = true;
		}
	}
}

static void addModuleTextNode(TVirtualStringTree* tree, PVirtualNode parent, BaseMetadataObject* metadataObject, const String& name, ModuleTextKind kind, int imageIndex)
{
	if (!tree || !metadataObject)
		return;

	PVirtualNode moduleNode = addChildNode(tree, parent, name, imageIndex);
	VirtualTreeData* moduleData = static_cast<VirtualTreeData*>(tree->GetNodeData(moduleNode));
	moduleData->MetadataObject = metadataObject;
	moduleData->moduleLocation.kind = kind;
	moduleData->moduleEditable = false;
}

static void addNestedModuleTextNode(TVirtualStringTree* tree, PVirtualNode parent, BaseMetadataObject* metadataObject, const String& itemGuid, const String& name, ModuleTextKind kind, int imageIndex)
{
	if (!tree || !metadataObject || itemGuid.IsEmpty())
		return;

	PVirtualNode moduleNode = addChildNode(tree, parent, name, imageIndex);
	VirtualTreeData* moduleData = static_cast<VirtualTreeData*>(tree->GetNodeData(moduleNode));
	moduleData->MetadataObject = metadataObject;
	moduleData->moduleItemGuid = itemGuid;
	moduleData->moduleLocation.kind = kind;
	moduleData->moduleEditable = false;
}

template <typename Collection>
static void addMetadataItemSection(TVirtualStringTree* tree, PVirtualNode parent, const String& sectionName, int sectionImageIndex, int itemImageIndex, const Collection& items, BaseMetadataObject* metadataObject, ModuleTextKind moduleKind, const String& moduleNodeName)
{
	PVirtualNode sectionNode = addChildNode(tree, parent, sectionName, sectionImageIndex);
	for (const auto& item : items)
	{
		PVirtualNode itemNode = addChildNode(tree, sectionNode, item->name, itemImageIndex);
		addNestedModuleTextNode(tree, itemNode, metadataObject, item->guid, moduleNodeName, moduleKind, itemImageIndex);
	}
}

//---------------------------------------------------------------------------
// Секции для стандартных объектов и регистров

void fillStandardMetadataSections(TVirtualStringTree* tree, PVirtualNode childNode, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;

	addModuleTextNode(tree, childNode, metadataObject, L"Модуль объекта", ModuleTextKind::ObjectModule, TreeImage::Forms);
	addModuleTextNode(tree, childNode, metadataObject, L"Модуль менеджера", ModuleTextKind::ManagerModule, TreeImage::Forms);

	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes, metadataObject->getAttributes(), [](const auto& item) { return item->name; });

	addTabularSections(tree, childNode, metadataObject->getTabularSections(), 0);
	addMetadataItemSection(tree, childNode, L"Формы", TreeImage::Forms, TreeImage::Forms, metadataObject->getForms(), metadataObject, ModuleTextKind::FormModule, L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");
	addSection(tree, childNode, L"Макеты",   TreeImage::Layouts,  TreeImage::Layouts, metadataObject->getLayouts(), [](const auto& item) { return item->name; });
}

void fillInformationRegisterSections(TVirtualStringTree* tree, PVirtualNode childNode, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;

	addModuleTextNode(tree, childNode, metadataObject, L"Модуль объекта", ModuleTextKind::ObjectModule, TreeImage::Forms);
	addModuleTextNode(tree, childNode, metadataObject, L"Модуль менеджера", ModuleTextKind::ManagerModule, TreeImage::Forms);

	addSection(tree, childNode, L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions, metadataObject->getDimensions(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Ресурсы",   TreeImage::Resources,  TreeImage::Resources, metadataObject->getResources(),  [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes, metadataObject->getAttributes(), [](const auto& item) { return item->name; });

	addMetadataItemSection(tree, childNode, L"Формы", TreeImage::Forms, TreeImage::Forms, metadataObject->getForms(), metadataObject, ModuleTextKind::FormModule, L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");

	addSection(tree, childNode, L"Макеты",    TreeImage::Layouts,    TreeImage::Layouts, metadataObject->getLayouts(),    [](const auto& item) { return item->name; });
}

//---------------------------------------------------------------------------
// fill*Tree

void fillCatalogsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	childData->MetadataObject = metadataObject;
	fillStandardMetadataSections(tree, childNode, metadataObject);
}

void fillFormsCommandsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	addMetadataItemSection(tree, childNode, L"Формы", TreeImage::Forms, TreeImage::Forms, metadataObject->getForms(), metadataObject, ModuleTextKind::FormModule, L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");
}

void fillAccumulationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillCalculationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillInformationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillAccountingRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TAccountingRegisters* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	addSection(tree, childNode, L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions, metadataObject->getDimensions(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Ресурсы",   TreeImage::Resources,  TreeImage::Resources, 	metadataObject->getResources(),  [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes, metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета", TreeImage::AccountingFlags, TreeImage::AccountingFlags, metadataObject->getAccountingFlags(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета субконто", TreeImage::SubcontoFlags, TreeImage::SubcontoFlags, metadataObject->getDimensionAccountingFlags(), [](const auto& item) { return item->name; });

	addMetadataItemSection(tree, childNode, L"Формы", TreeImage::Forms, TreeImage::Forms, metadataObject->getForms(), metadataObject, ModuleTextKind::FormModule, L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");

	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts, metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillChartAccTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TChartOfAccounts* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	addSection(tree, childNode, L"Реквизиты",               TreeImage::Attributes,      TreeImage::Attributes,      metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета",          TreeImage::AccountingFlags, TreeImage::AccountingFlags, metadataObject->accflags,        [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета субконто", TreeImage::SubcontoFlags,   TreeImage::SubcontoFlags,   metadataObject->dimaccflags,     [](const auto& item) { return item->name; });

	addTabularSections(tree, childNode, metadataObject->getTabularSections(), 0);

	addMetadataItemSection(tree, childNode, L"Формы",   TreeImage::Forms,    TreeImage::Forms,    metadataObject->getForms(),    metadataObject, ModuleTextKind::FormModule,    L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");

	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts, metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillJournalTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	childData->MetadataObject = metadataObject;

	addModuleTextNode(tree, childNode, metadataObject, L"Модуль менеджера", ModuleTextKind::ManagerModule, TreeImage::Forms);

	addSection(tree, childNode, L"Графы",   TreeImage::JournalColumns, TreeImage::JournalColumns, metadataObject->getAttributes(), [](const auto& item) { return item->name; });

	addTabularSections(tree, childNode, metadataObject->getTabularSections());

	addMetadataItemSection(tree, childNode, L"Формы", TreeImage::Forms, TreeImage::Forms, metadataObject->getForms(), metadataObject, ModuleTextKind::FormModule, L"Модуль формы");
	addMetadataItemSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands, metadataObject->getCommands(), metadataObject, ModuleTextKind::CommandModule, L"Модуль команды");
	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts, metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillEnumTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TEnums* curEnum)
{
	initNode(childData, curEnum->name, imgIndex);

	childData->MetadataObject = curEnum;

	PVirtualNode managerModuleNode = addChildNode(tree, childNode, L"Модуль менеджера", TreeImage::Forms);
	VirtualTreeData* managerModuleData = static_cast<VirtualTreeData*>(tree->GetNodeData(managerModuleNode));
	managerModuleData->MetadataObject = curEnum;
	managerModuleData->moduleLocation.kind = ModuleTextKind::ManagerModule;
	managerModuleData->moduleEditable = false;

	addSection(tree, childNode, L"Значения", TreeImage::Attributes, TreeImage::Attributes, curEnum->attributes, [](const auto& item) { return item; });
	addSection(tree, childNode, L"Формы",    TreeImage::Forms,      TreeImage::Forms,      curEnum->forms,      [](const auto& item) { return item; });
	addSection(tree, childNode, L"Команды",  TreeImage::Commands,   TreeImage::Commands,   curEnum->comands,    [](const auto& item) { return item; });
	addSection(tree, childNode, L"Макеты",   TreeImage::Layouts,    TreeImage::Layouts,    curEnum->moxels,     [](const auto& item) { return item; });
}

namespace
{
	void addStringSection(TVirtualStringTree* tree, PVirtualNode parent, const String& sectionName, int sectionImageIndex, int itemImageIndex, const std::vector<String>& items)
	{
		PVirtualNode sectionNode = nullptr;
		for (const auto& item : items)
		{
			if (!item.IsEmpty())
			{

				if (!sectionNode)
					sectionNode = addChildNode(tree, parent, sectionName, sectionImageIndex);

				addChildNode(tree, sectionNode, item, itemImageIndex);

			}
		}
	}

	void fillExternalTableTree(TVirtualStringTree* tree, PVirtualNode parent, const TExternalDataSourceTable& tableData, int imgIndex)
	{
		PVirtualNode tableNode = addChildNode(tree, parent, tableData.name, imgIndex);

		addStringSection(tree, tableNode, L"Поля",    TreeImage::Attributes, TreeImage::Attributes, tableData.fields);
		addStringSection(tree, tableNode, L"Формы",   TreeImage::Forms,      TreeImage::Forms,      tableData.forms);
		addStringSection(tree, tableNode, L"Команды", TreeImage::Commands,   TreeImage::Commands,   tableData.commands);
		addStringSection(tree, tableNode, L"Макеты",  TreeImage::Layouts,    TreeImage::Layouts,    tableData.layouts);

		tree->Expanded[tableNode] = true;
	}

	void fillExternalCubeTree(TVirtualStringTree* tree, PVirtualNode parent, const TExternalDataSourceCube& cubeData, int imgIndex)
	{
		PVirtualNode cubeNode = addChildNode(tree, parent, cubeData.name, imgIndex);

		if (!cubeData.dimensionTables.empty())
		{
			PVirtualNode dimensionTablesNode = addChildNode(tree, cubeNode, L"Таблицы измерений", TreeImage::TabularSections);
			for (const auto& tableData : cubeData.dimensionTables)
				fillExternalTableTree(tree, dimensionTablesNode, tableData, TreeImage::TabularSections);
			tree->Expanded[dimensionTablesNode] = true;
		}

		addStringSection(tree, cubeNode, L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions, cubeData.dimensions);
		addStringSection(tree, cubeNode, L"Ресурсы",   TreeImage::Resources,  TreeImage::Resources,  cubeData.resources);
		addStringSection(tree, cubeNode, L"Формы",     TreeImage::Forms,      TreeImage::Forms,      cubeData.forms);
		addStringSection(tree, cubeNode, L"Команды",   TreeImage::Commands,   TreeImage::Commands,   cubeData.commands);
		addStringSection(tree, cubeNode, L"Макеты",    TreeImage::Layouts,    TreeImage::Layouts,    cubeData.layouts);
		tree->Expanded[cubeNode] = true;
	}
}

void fillExternalDataSourceTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData, int imgIndex, TExternalDataSources* metadataObject)
{
	if (!metadataObject)
		return;

	initNode(childData, metadataObject->name, imgIndex);

	if (!metadataObject->tables.empty())
	{
		PVirtualNode tablesNode = addChildNode(tree, childNode, L"Таблицы", TreeImage::TabularSections);
		for (const auto& tableData : metadataObject->tables)
			fillExternalTableTree(tree, tablesNode, tableData, TreeImage::TabularSections);
		tree->Expanded[tablesNode] = true;
	}

	if (!metadataObject->cubes.empty())
	{
		PVirtualNode cubesNode = addChildNode(tree, childNode, L"Кубы", TreeImage::TabularSections);
		for (const auto& cubeData : metadataObject->cubes)
			fillExternalCubeTree(tree, cubesNode, cubeData, TreeImage::TabularSections);
		tree->Expanded[cubesNode] = true;
	}

	addStringSection(tree, childNode, L"Функции", TreeImage::Commands, TreeImage::Commands, metadataObject->functions);
	tree->Expanded[childNode] = true;
}

//---------------------------------------------------------------------------
// Вспомогательные функции для подсистем

String normalizeGuid(const String& guid)
{
	return Trim(guid).LowerCase();
}

String normalizeGuid(const Utf16String& guid)
{
	return normalizeGuid(ToVcl(guid));
}

String GetNameSubsystem(v8catalog* cf, String& guid_md)
{
	String Result = "";
	v8file* filedata = cf->GetFile16(V8Utf16FromString(guid_md));
	if (!filedata)
		return Result;
	tree* tree_md = get_treeFromV8file(filedata);
	if (!tree_md)
		return Result;
	tree* node = tree_md;
	node = &(*node)[0][1][1][2];
	Result = node->get_value();
	delete tree_md;
	return Result;
}

String GetSubsystemInnerGuid(v8catalog* cf, String& guid_md)
{
	String Result = "";
	v8file* filedata = cf->GetFile16(V8Utf16FromString(guid_md));
	if (!filedata)
		return Result;
	tree* tree_md = get_treeFromV8file(filedata);
	if (!tree_md)
		return Result;
	tree* node = tree_md;
	node = &(*node)[0][1][1][1];
	Result = node->get_value();
	delete tree_md;
	return Result;
}

void GetListChildrenSubsystem(v8catalog* cf, String& guid_md, std::vector<String>& child)
{
	v8file* filedata = cf->GetFile16(V8Utf16FromString(guid_md));
	if (!filedata)
		return;
	tree* tree_md = get_treeFromV8file(filedata);
	if (!tree_md)
		return;
	tree* node = tree_md;
	node = &(*node)[0][3][0];

	tree* curNodeChild = node->get_next();
	while (curNodeChild)
	{
		curNodeChild = curNodeChild->get_next();
		if (curNodeChild)
			child.push_back(curNodeChild->get_value());
	}
}

TSubsystem* findSubsystemByAnyGuid(v8catalog* cf, const MetadataVector<MetadataEntity>& subsystems, const String& guid)
{
	String targetGuid = normalizeGuid(guid);
	if (targetGuid.IsEmpty())
		return nullptr;

	for (const auto& item : subsystems)
	{
		TSubsystem* subsystem = dynamic_cast<TSubsystem*>(item.get());
		if (!subsystem)
			continue;

		if (normalizeGuid(subsystem->guid) == targetGuid)
			return subsystem;

		String originalGuid = ToVcl(subsystem->guid);
		if (normalizeGuid(GetSubsystemInnerGuid(cf, originalGuid)) == targetGuid)
			return subsystem;
	}
	return nullptr;
}

String getSubsystemDisplayNameByGuid(v8catalog* cf, const MetadataVector<MetadataEntity>& subsystems, const String& guid)
{
	String guidCopy = guid;
	String name = GetNameSubsystem(cf, guidCopy);
	if (!name.IsEmpty())
		return name;

	TSubsystem* subsystem = findSubsystemByAnyGuid(cf, subsystems, guid);
	if (subsystem)
		return ToVcl(subsystem->name);

	return guid;
}

void addSubsystemChildrenToTreeByGuid(TVirtualStringTree* tree, PVirtualNode parentNode, v8catalog* cf, const MetadataVector<MetadataEntity>& subsystems, const String& parentGuid, int imgIndex)
{
	if (!tree || !cf)
		return;

	tree->Expanded[parentNode] = true;

	String subsystemGuid = parentGuid;
	std::vector<String> childrenGuids;
	GetListChildrenSubsystem(cf, subsystemGuid, childrenGuids);
	if (childrenGuids.empty())
	{
		String subsystemInnerGuid = GetSubsystemInnerGuid(cf, subsystemGuid);
		if (!subsystemInnerGuid.IsEmpty())
			GetListChildrenSubsystem(cf, subsystemInnerGuid, childrenGuids);
	}

	for (const auto& childGuid : childrenGuids)
	{
		TSubsystem* childSubsystem = findSubsystemByAnyGuid(cf, subsystems, childGuid);

		PVirtualNode childNode = tree->AddChild(parentNode);
		VirtualTreeData* childData = static_cast<VirtualTreeData*>(tree->GetNodeData(childNode));
		childData->Name = childSubsystem
			? ToVcl(childSubsystem->name)
			: getSubsystemDisplayNameByGuid(cf, subsystems, childGuid);
		childData->Age = 99;
		childData->ImgIndex = imgIndex;
		childData->text_module = L"";
		childData->MetadataObject = childSubsystem;
		tree->Expanded[childNode] = true;

		String nextGuid = childSubsystem ? ToVcl(childSubsystem->guid) : childGuid;
		addSubsystemChildrenToTreeByGuid(tree, childNode, cf, subsystems, nextGuid, imgIndex);
	}
}

void addSubsystemChildrenToTree(TVirtualStringTree* tree, PVirtualNode parentNode, v8catalog* cf, const MetadataVector<MetadataEntity>& subsystems, TSubsystem* parentSubsystem, int imgIndex)
{
	if (!tree || !cf || !parentSubsystem)
		return;
	addSubsystemChildrenToTreeByGuid(tree, parentNode, cf, subsystems, ToVcl(parentSubsystem->guid), imgIndex);
}

std::unordered_set<String> collectChildSubsystemGuids(v8catalog* cf, const MetadataVector<MetadataEntity>& subsystems)
{
	std::unordered_set<String> childSubsystemGuids;
	if (!cf)
		return childSubsystemGuids;

	for (const auto& item : subsystems)
	{
		TSubsystem* subsystem = dynamic_cast<TSubsystem*>(item.get());
		if (!subsystem)
			continue;

		String subsystemGuid = ToVcl(subsystem->guid);
		std::vector<String> childrenGuids;
		GetListChildrenSubsystem(cf, subsystemGuid, childrenGuids);
		if (childrenGuids.empty())
		{
			String subsystemInnerGuid = GetSubsystemInnerGuid(cf, subsystemGuid);
			if (!subsystemInnerGuid.IsEmpty())
				GetListChildrenSubsystem(cf, subsystemInnerGuid, childrenGuids);
		}

		for (const auto& childGuid : childrenGuids)
		{
			TSubsystem* childSubsystem = findSubsystemByAnyGuid(cf, subsystems, childGuid);
			if (childSubsystem)
			{
				String childFileGuid = normalizeGuid(ToVcl(childSubsystem->guid));
				if (!childFileGuid.IsEmpty())
					childSubsystemGuids.insert(childFileGuid);

				String originalChildGuid = ToVcl(childSubsystem->guid);
				String childInnerGuid = normalizeGuid(GetSubsystemInnerGuid(cf, originalChildGuid));
				if (!childInnerGuid.IsEmpty())
					childSubsystemGuids.insert(childInnerGuid);
			}
			else
			{
				childSubsystemGuids.insert(normalizeGuid(childGuid));
			}
		}
	}
	return childSubsystemGuids;
}


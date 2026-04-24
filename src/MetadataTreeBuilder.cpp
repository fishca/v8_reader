//---------------------------------------------------------------------------
#pragma hdrstop

#include "MetadataTreeBuilder.h"
#include "Parse_tree.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Базовые операции с узлами дерева

void initNode(VirtualTreeData* data, const String& name, int imageIndex, int age)
{
	data->Name = name;
	data->Age = age;
	data->ImgIndex = imageIndex;
}

PVirtualNode addChildNode(TVirtualStringTree* tree, PVirtualNode parent, const String& name, int imageIndex, int age)
{
	PVirtualNode childNode = tree->AddChild(parent);
	VirtualTreeData* childData = static_cast<VirtualTreeData*>(tree->GetNodeData(childNode));
	initNode(childData, name, imageIndex, age);
	return childNode;
}

void addTabularSections(TVirtualStringTree* tree, PVirtualNode parent,
	const std::vector<std::unique_ptr<TTabular>>& items, int age)
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

//---------------------------------------------------------------------------
// Секции для стандартных объектов и регистров

void fillStandardMetadataSections(TVirtualStringTree* tree, PVirtualNode childNode,
	BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;

	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes,
		metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addTabularSections(tree, childNode, metadataObject->getTabularSections(), 0);
	addSection(tree, childNode, L"Формы",    TreeImage::Forms,    TreeImage::Forms,
		metadataObject->getForms(),      [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды",  TreeImage::Commands, TreeImage::Commands,
		metadataObject->getCommands(),   [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Макеты",   TreeImage::Layouts,  TreeImage::Layouts,
		metadataObject->getLayouts(),    [](const auto& item) { return item->name; });
}

void fillInformationRegisterSections(TVirtualStringTree* tree, PVirtualNode childNode,
	MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;

	addSection(tree, childNode, L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions,
		metadataObject->getDimensions(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Ресурсы",   TreeImage::Resources,  TreeImage::Resources,
		metadataObject->getResources(),  [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes,
		metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Формы",     TreeImage::Forms,      TreeImage::Forms,
		metadataObject->getForms(),      [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды",   TreeImage::Commands,   TreeImage::Commands,
		metadataObject->getCommands(),   [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Макеты",    TreeImage::Layouts,    TreeImage::Layouts,
		metadataObject->getLayouts(),    [](const auto& item) { return item->name; });
}

//---------------------------------------------------------------------------
// fill*Tree

void fillCatalogsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	fillStandardMetadataSections(tree, childNode, metadataObject);
}

void fillFormsCommandsTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	addSection(tree, childNode, L"Формы",   TreeImage::Forms,    TreeImage::Forms,
		metadataObject->getForms(),    [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands,
		metadataObject->getCommands(), [](const auto& item) { return item->name; });
}

void fillAccumulationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillCalculationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillInformationRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, MetadataObjectInformationRegister* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);
	fillInformationRegisterSections(tree, childNode, metadataObject);
}

void fillAccountingRegisterTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, TAccountingRegisters* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);

	addSection(tree, childNode, L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions,
		metadataObject->getDimensions(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Ресурсы",   TreeImage::Resources,  TreeImage::Resources,
		metadataObject->getResources(),  [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes,
		metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета",          TreeImage::AccountingFlags, TreeImage::AccountingFlags,
		metadataObject->getAccountingFlags(),          [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета субконто", TreeImage::SubcontoFlags,   TreeImage::SubcontoFlags,
		metadataObject->getDimensionAccountingFlags(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Формы",   TreeImage::Forms,    TreeImage::Forms,
		metadataObject->getForms(),    [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands,
		metadataObject->getCommands(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts,
		metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillChartAccTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, TChartOfAccounts* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);

	addSection(tree, childNode, L"Реквизиты",               TreeImage::Attributes,      TreeImage::Attributes,
		metadataObject->getAttributes(),  [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета",          TreeImage::AccountingFlags, TreeImage::AccountingFlags,
		metadataObject->accflags,         [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Признаки учета субконто", TreeImage::SubcontoFlags,   TreeImage::SubcontoFlags,
		metadataObject->dimaccflags,      [](const auto& item) { return item->name; });
	addTabularSections(tree, childNode, metadataObject->getTabularSections(), 0);
	addSection(tree, childNode, L"Формы",   TreeImage::Forms,    TreeImage::Forms,
		metadataObject->getForms(),    [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands,
		metadataObject->getCommands(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts,
		metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillJournalTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, BaseMetadataObject* metadataObject)
{
	if (!metadataObject)
		return;
	initNode(childData, metadataObject->name, imgIndex);

	addSection(tree, childNode, L"Графы",   TreeImage::JournalColumns, TreeImage::JournalColumns,
		metadataObject->getAttributes(), [](const auto& item) { return item->name; });
	addTabularSections(tree, childNode, metadataObject->getTabularSections());
	addSection(tree, childNode, L"Формы",   TreeImage::Forms,    TreeImage::Forms,
		metadataObject->getForms(),    [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Команды", TreeImage::Commands, TreeImage::Commands,
		metadataObject->getCommands(), [](const auto& item) { return item->name; });
	addSection(tree, childNode, L"Макеты",  TreeImage::Layouts,  TreeImage::Layouts,
		metadataObject->getLayouts(),  [](const auto& item) { return item->name; });
}

void fillEnumTree(TVirtualStringTree* tree, PVirtualNode childNode, VirtualTreeData* childData,
	int imgIndex, TEnums* curEnum)
{
	initNode(childData, curEnum->name, imgIndex);

	addSection(tree, childNode, L"Значения", TreeImage::Attributes, TreeImage::Attributes,
		curEnum->attributes, [](const auto& item) { return item; });
	addSection(tree, childNode, L"Формы",    TreeImage::Forms,      TreeImage::Forms,
		curEnum->forms,      [](const auto& item) { return item; });
	addSection(tree, childNode, L"Команды",  TreeImage::Commands,   TreeImage::Commands,
		curEnum->comands,    [](const auto& item) { return item; });
	addSection(tree, childNode, L"Макеты",   TreeImage::Layouts,    TreeImage::Layouts,
		curEnum->moxels,     [](const auto& item) { return item; });
}

//---------------------------------------------------------------------------
// Вспомогательные функции для подсистем

String normalizeGuid(const String& guid)
{
	return Trim(guid).LowerCase();
}

String GetNameSubsystem(v8catalog* cf, String& guid_md)
{
	String Result = "";
	v8file* filedata = cf->GetFile(guid_md);
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
	v8file* filedata = cf->GetFile(guid_md);
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
	v8file* filedata = cf->GetFile(guid_md);
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

TSubsystem* findSubsystemByAnyGuid(v8catalog* cf, const MetadataVector<TObject>& subsystems, const String& guid)
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

		String originalGuid = subsystem->guid;
		if (normalizeGuid(GetSubsystemInnerGuid(cf, originalGuid)) == targetGuid)
			return subsystem;
	}
	return nullptr;
}

String getSubsystemDisplayNameByGuid(v8catalog* cf, const MetadataVector<TObject>& subsystems, const String& guid)
{
	String guidCopy = guid;
	String name = GetNameSubsystem(cf, guidCopy);
	if (!name.IsEmpty())
		return name;

	TSubsystem* subsystem = findSubsystemByAnyGuid(cf, subsystems, guid);
	if (subsystem)
		return subsystem->name;

	return guid;
}

void addSubsystemChildrenToTreeByGuid(TVirtualStringTree* tree, PVirtualNode parentNode,
	v8catalog* cf, const MetadataVector<TObject>& subsystems,
	const String& parentGuid, int imgIndex)
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
			? childSubsystem->name
			: getSubsystemDisplayNameByGuid(cf, subsystems, childGuid);
		childData->Age = 99;
		childData->ImgIndex = imgIndex;
		childData->text_module = L"";
		childData->MetadataObject = childSubsystem;
		tree->Expanded[childNode] = true;

		String nextGuid = childSubsystem ? childSubsystem->guid : childGuid;
		addSubsystemChildrenToTreeByGuid(tree, childNode, cf, subsystems, nextGuid, imgIndex);
	}
}

void addSubsystemChildrenToTree(TVirtualStringTree* tree, PVirtualNode parentNode,
	v8catalog* cf, const MetadataVector<TObject>& subsystems,
	TSubsystem* parentSubsystem, int imgIndex)
{
	if (!tree || !cf || !parentSubsystem)
		return;
	addSubsystemChildrenToTreeByGuid(tree, parentNode, cf, subsystems, parentSubsystem->guid, imgIndex);
}

std::unordered_set<String> collectChildSubsystemGuids(v8catalog* cf,
	const MetadataVector<TObject>& subsystems)
{
	std::unordered_set<String> childSubsystemGuids;
	if (!cf)
		return childSubsystemGuids;

	for (const auto& item : subsystems)
	{
		TSubsystem* subsystem = dynamic_cast<TSubsystem*>(item.get());
		if (!subsystem)
			continue;

		String subsystemGuid = subsystem->guid;
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
				String childFileGuid = normalizeGuid(childSubsystem->guid);
				if (!childFileGuid.IsEmpty())
					childSubsystemGuids.insert(childFileGuid);

				String originalChildGuid = childSubsystem->guid;
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

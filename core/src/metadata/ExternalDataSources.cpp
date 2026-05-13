//---------------------------------------------------------------------------


#include "ExternalDataSources.h"
//---------------------------------------------------------------------------

namespace
{
	tree* GetNodeByPath(tree* root, std::initializer_list<int> indexes)
	{
		tree* current = root;
		if (!current)
			return nullptr;

		for (int index : indexes)
		{
			if (!current || index < 0 || index >= current->get_num_subnode())
				return nullptr;

			current = current->get_subnode(index);
		}

		return current;
	}

	String GetValueByPath(tree* root, std::initializer_list<int> indexes)
	{
		tree* node = GetNodeByPath(root, indexes);
		return node ? node->get_value() : String();
	}

	String GetFirstValueByPath(tree* root, std::initializer_list<std::initializer_list<int>> paths)
	{
		for (const auto& path : paths)
		{
			String value = GetValueByPath(root, path);
			if (!value.IsEmpty())
				return value;
		}

		return String();
	}

	tree* GetPayloadRoot(tree* root)
	{
		if (!root)
			return nullptr;
		if (root->get_num_subnode() == 1)
			return root->get_subnode(0);
		return root;
	}

	tree* GetSection(tree* root, int index)
	{
		return GetNodeByPath(root, {index});
	}

	int GetSectionCount(tree* root, int index)
	{
		tree* section = GetSection(root, index);
		if (!section || section->get_num_subnode() < 2)
			return 0;

		return section->get_subnode(1)->get_value().ToIntDef(0);
	}

	String GetFileNameByPath(v8catalog* parent, const String& guid, std::initializer_list<int> indexes)
	{
		if (!parent || guid.IsEmpty())
			return String();

		v8file* file = parent->GetFile16(V8Utf16FromString(guid));
		if (!file)
			return String();

		try
		{
			std::unique_ptr<tree> fileTree(get_treeFromV8file(file));
			return GetValueByPath(GetPayloadRoot(fileTree.get()), indexes);
		}
		catch (...)
		{
			return String();
		}
	}

	void ReadFileList(tree* root, int sectionIndex, v8catalog* parent,
		std::initializer_list<int> namePath, std::vector<String>& target)
	{
		tree* section = GetSection(root, sectionIndex);
		int count = GetSectionCount(root, sectionIndex);
		if (!section)
			return;

		for (int i = 0; i < count; ++i)
		{
			tree* guidNode = section->get_subnode(i + 2);
			if (!guidNode)
				continue;

			String itemName = GetFileNameByPath(parent, guidNode->get_value(), namePath);
			if (!itemName.IsEmpty())
				target.push_back(itemName);
		}
	}

	void ReadInlineList(tree* root, int sectionIndex, std::initializer_list<int> namePath,
		std::vector<String>& target)
	{
		tree* section = GetSection(root, sectionIndex);
		int count = GetSectionCount(root, sectionIndex);
		if (!section)
			return;

		for (int i = 0; i < count; ++i)
		{
			tree* itemNode = section->get_subnode(i + 2);
			String itemName = GetValueByPath(itemNode, namePath);
			if (!itemName.IsEmpty())
				target.push_back(itemName);
		}
	}

	TExternalDataSourceTable ReadTable(v8catalog* parent, const String& guid)
	{
		TExternalDataSourceTable tableData;
		if (!parent || guid.IsEmpty())
			return tableData;

		v8file* file = parent->GetFile16(V8Utf16FromString(guid));
		if (!file)
			return tableData;

		std::unique_ptr<tree> tableTree;
		try
		{
			tableTree.reset(get_treeFromV8file(file));
		}
		catch (...)
		{
			tableData.name = guid;
			return tableData;
		}
		tree* root = GetPayloadRoot(tableTree.get());

		tableData.name = GetFirstValueByPath(root, {
			{1, 1, 1, 2},
			{0, 1, 1, 2},
			{1, 0, 1, 2}
		});
		if (tableData.name.IsEmpty())
			tableData.name = guid;
		ReadFileList(root, 3, parent, {1, 1, 2}, tableData.forms);
		ReadFileList(root, 4, parent, {1, 2, 2}, tableData.layouts);
		ReadInlineList(root, 5, {0, 1, 3, 2, 9, 2}, tableData.commands);
		ReadInlineList(root, 6, {0, 1, 1, 1, 2}, tableData.fields);

		return tableData;
	}

	TExternalDataSourceCube ReadCube(v8catalog* parent, const String& guid)
	{
		TExternalDataSourceCube cubeData;
		if (!parent || guid.IsEmpty())
			return cubeData;

		v8file* file = parent->GetFile16(V8Utf16FromString(guid));
		if (!file)
			return cubeData;

		std::unique_ptr<tree> cubeTree;
		try
		{
			cubeTree.reset(get_treeFromV8file(file));
		}
		catch (...)
		{
			cubeData.name = guid;
			return cubeData;
		}
		tree* root = GetPayloadRoot(cubeTree.get());

		cubeData.name = GetFirstValueByPath(root, {
			{1, 1, 1, 2},
			{0, 1, 1, 2},
			{1, 0, 1, 2}
		});
		if (cubeData.name.IsEmpty())
			cubeData.name = guid;
		ReadFileList(root, 3, parent, {1, 1, 2}, cubeData.forms);
		ReadFileList(root, 4, parent, {1, 2, 2}, cubeData.layouts);
		ReadInlineList(root, 5, {0, 1, 3, 2, 9, 2}, cubeData.commands);
		ReadInlineList(root, 7, {0, 1, 1, 1, 2}, cubeData.dimensions);
		ReadInlineList(root, 8, {0, 1, 1, 1, 2}, cubeData.resources);

		tree* tablesSection = GetSection(root, 6);
		int tableCount = GetSectionCount(root, 6);
		if (tablesSection)
		{
			for (int i = 0; i < tableCount; ++i)
			{
				tree* guidNode = tablesSection->get_subnode(i + 2);
				if (guidNode)
					cubeData.dimensionTables.push_back(ReadTable(parent, guidNode->get_value()));
			}
		}

		return cubeData;
	}
}

TExternalDataSources::TExternalDataSources()
	: BaseMetadataObject()
{
	root_data.reset();
}

TExternalDataSources::TExternalDataSources(v8catalog* _parent, const String& _guid)
	: BaseMetadataObject()
{
	name = _guid;
	guid = _guid;
	parent = _parent;
	if (parent)
	{
		try
		{
			v8file* file = parent->GetFile16(V8Utf16FromString(guid));
			if (file)
				root_data.reset(get_treeFromV8file(file));
		}
		catch (...)
		{
			root_data.reset();
		}
	}
	if (root_data)
		initializeFromTree();
	root_data.reset();
}

TExternalDataSources::TExternalDataSources(v8catalog* _parent, const String& _guid, const String& _name)
	: BaseMetadataObject()
{
	name = _name;
	guid = _guid;
	parent = _parent;
	if (parent)
	{
		try
		{
			v8file* file = parent->GetFile16(V8Utf16FromString(guid));
			if (file)
				root_data.reset(get_treeFromV8file(file));
		}
		catch (...)
		{
			root_data.reset();
		}
	}
	if (root_data)
		initializeFromTree();
	root_data.reset();
}

TExternalDataSources::~TExternalDataSources()
{
}

std::vector<std::unique_ptr<TRequisite>>& TExternalDataSources::getAttributes()
{
	return attributes;
}

std::vector<std::unique_ptr<TComand>>& TExternalDataSources::getCommands()
{
	return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TExternalDataSources::getLayouts()
{
	return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TExternalDataSources::getTabularSections()
{
	return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TExternalDataSources::getForms()
{
	return forms;
}

void TExternalDataSources::initializeFromTree()
{
	tree* root = GetPayloadRoot(root_data.get());
	String sourceName = GetFirstValueByPath(root, {
		{1, 1, 1, 2},
		{0, 1, 1, 2},
		{1, 0, 1, 2}
	});
	if (!sourceName.IsEmpty())
		name = sourceName;

	tables.clear();
	cubes.clear();
	functions.clear();

	tree* cubesSection = GetSection(root, 3);
	int cubeCount = GetSectionCount(root, 3);
	if (cubesSection)
	{
		for (int i = 0; i < cubeCount; ++i)
		{
			tree* guidNode = cubesSection->get_subnode(i + 2);
			if (guidNode)
				cubes.push_back(ReadCube(parent, guidNode->get_value()));
		}
	}

	ReadInlineList(root, 4, {0, 1, 1, 1, 2}, functions);

	tree* tablesSection = GetSection(root, 5);
	int tableCount = GetSectionCount(root, 5);
	if (tablesSection)
	{
		for (int i = 0; i < tableCount; ++i)
		{
			tree* guidNode = tablesSection->get_subnode(i + 2);
			if (guidNode)
				tables.push_back(ReadTable(parent, guidNode->get_value()));
		}
	}
}


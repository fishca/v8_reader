//---------------------------------------------------------------------------


#include "Tabular.h"
#include "guids.h"
//---------------------------------------------------------------------------

namespace
{
	bool IsServiceTabularAttributeName(const String& value)
	{
		String trimmed = Trim(value);
		return trimmed == L"Реквизиты" || trimmed == L"Реквизит";
	}

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

	tree* GetNodeByPath(tree* root, const std::vector<int>& indexes)
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

	bool IsGuidLikeValue(const String& value)
	{
		String trimmed = Trim(value);
		if (trimmed.Length() != 36)
			return false;

		for (int i = 1; i <= trimmed.Length(); i++)
		{
			wchar_t ch = trimmed[i];
			bool isHex = (ch >= L'0' && ch <= L'9') || (ch >= L'a' && ch <= L'f') || (ch >= L'A' && ch <= L'F');
			bool isDash = (ch == L'-');
			if (!isHex && !isDash)
				return false;
		}

		return true;
	}

	bool IsNumericLikeValue(const String& value)
	{
		String trimmed = Trim(value);
		if (trimmed.IsEmpty())
			return false;

		for (int i = 1; i <= trimmed.Length(); i++)
		{
			wchar_t ch = trimmed[i];
			if (!((ch >= L'0' && ch <= L'9') || ch == L'.' || ch == L',' || ch == L'-'))
				return false;
		}

		return true;
	}

	String FindFirstMeaningfulString(tree* node)
	{
		if (!node)
			return L"";

		String value = Trim(node->get_value());
		if (!value.IsEmpty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.SubString(1, 1) != L"#" && !IsServiceTabularAttributeName(value))
			return value;

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			String nested = FindFirstMeaningfulString(node->get_subnode(i));
			if (!nested.IsEmpty())
				return nested;
		}

		return L"";
	}

	void CollectMeaningfulStrings(tree* node, std::vector<String>& values)
	{
		if (!node)
			return;

		String value = Trim(node->get_value());
		if (!value.IsEmpty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.SubString(1, 1) != L"#" && !IsServiceTabularAttributeName(value))
			values.push_back(value);

		for (int i = 0; i < node->get_num_subnode(); i++)
			CollectMeaningfulStrings(node->get_subnode(i), values);
	}

	bool TryCollectAttributesFromSection(tree* root, int sectionIndex, std::vector<std::unique_ptr<TRequisite>>& attributes)
	{
		const std::vector<std::vector<int>> countPaths = {
			{0, 1, sectionIndex, 1},
			{0, 1, sectionIndex, 1, 1},
			{0, sectionIndex, 1},
			{0, sectionIndex, 1, 1}
		};

		const std::vector<std::vector<int>> itemPrefixes = {
			{0, 1, sectionIndex},
			{0, sectionIndex}
		};

		const std::vector<std::vector<int>> namePaths = {
			{0, 1, 1, 1, 2},
			{0, 1, 1, 1, 1, 2},
			{0, 1, 1, 2},
			{0, 1, 3, 2},
			{0, 1, 5, 1, 2},
			{1, 1, 1, 2},
			{1, 1, 2},
			{1, 3, 2}
		};

		for (const auto& countPath : countPaths)
		{
			tree* countNode = GetNodeByPath(root, countPath);
			int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
			if (count <= 0)
				continue;

			int delta = count - 2;
			int collected = 0;
			for (const auto& itemPrefix : itemPrefixes)
			{
				for (int i = 0; i < count; i++)
				{
					try
					{
						std::vector<int> itemPath = itemPrefix;
						itemPath.push_back(i + count - delta);
						tree* itemNode = GetNodeByPath(root, itemPath);
						if (!itemNode)
							continue;

						String attributeName = L"";
						for (const auto& namePath : namePaths)
						{
							tree* nameNode = GetNodeByPath(itemNode, namePath);
							if (!nameNode)
								continue;

							attributeName = Trim(nameNode->get_value());
							if (attributeName.IsEmpty())
								continue;

							break;
						}

						if (attributeName.IsEmpty())
							attributeName = FindFirstMeaningfulString(itemNode);

						if (!attributeName.IsEmpty())
						{
							attributes.push_back(std::make_unique<TRequisite>(attributeName, ""));
							collected++;
							break;
						}
					}
					catch (...)
					{
					}
				}

				if (collected > 0)
					return true;
			}
		}

		return false;
	}

	bool TryCollectCatalogTabularAttributesByGuid(tree* root, std::vector<std::unique_ptr<TRequisite>>& attributes)
	{
		tree* node = find_metadata_node_by_guid(root, GUID_AttCatalogs);
		if (!node)
			return false;

		tree* countNode = node->get_next();
		int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
		if (count <= 0)
			return false;

		int collected = 0;
		tree* current = countNode;
		while ((current = current->get_next()) != nullptr)
		{
			String attributeName = FindFirstMeaningfulString(current);
			if (attributeName.IsEmpty())
				continue;

			if (IsServiceTabularAttributeName(attributeName))
				continue;

			attributes.push_back(std::make_unique<TRequisite>(attributeName, ""));
			collected++;
			if (collected >= count)
				break;
		}

		return collected > 0;
	}

	bool TryCollectEmbeddedTabularAttributes(tree* root, std::vector<std::unique_ptr<TRequisite>>& attributes)
	{
		static const String EmbeddedTabularAttributeGuid = L"888744e1-b616-11d4-9436-004095e12fc7";

		auto tryCollectFromContainer = [&](tree* container) -> bool
		{
			if (!container)
				return false;

			for (int i = 0; i < container->get_num_subnode(); i++)
			{
				tree* sectionNode = container->get_subnode(i);
				if (!sectionNode || sectionNode->get_num_subnode() < 2)
					continue;

				String sectionGuid = Trim(sectionNode->get_subnode(0)->get_value());
				if (sectionGuid != EmbeddedTabularAttributeGuid)
					continue;

				int count = sectionNode->get_subnode(1)->get_value().ToIntDef(0);
				if (count <= 0)
					return false;

				int collected = 0;
				for (int itemIndex = 2; itemIndex < sectionNode->get_num_subnode(); itemIndex++)
				{
					String attributeName = FindFirstMeaningfulString(sectionNode->get_subnode(itemIndex));
					if (attributeName.IsEmpty())
						continue;

					if (IsServiceTabularAttributeName(attributeName))
						continue;

					attributes.push_back(std::make_unique<TRequisite>(attributeName, ""));
					collected++;
					if (collected >= count)
						break;
				}

				return collected > 0;
			}

			return false;
		};

		if (tryCollectFromContainer(root))
			return true;

		if (root->get_num_subnode() > 0 && tryCollectFromContainer(root->get_subnode(0)))
			return true;

		tree* node = find_metadata_node_by_guid(root, EmbeddedTabularAttributeGuid);
		if (!node)
			return false;

		tree* countNode = node->get_next();
		int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
		if (count <= 0)
			return false;

		int collected = 0;
		tree* current = countNode;
		while ((current = current->get_next()) != nullptr)
		{
			String attributeName = FindFirstMeaningfulString(current);
			if (attributeName.IsEmpty())
				continue;

			if (IsServiceTabularAttributeName(attributeName))
				continue;

			attributes.push_back(std::make_unique<TRequisite>(attributeName, ""));
			collected++;
			if (collected >= count)
				break;
		}

		return collected > 0;
	}
}


TTabular::TTabular()
{

}

TTabular::TTabular(String _name, String _guid)
{
	name = _name;
    guid = _guid;
}

TTabular::~TTabular()
{

}

void TTabular::initializeFromTree(tree* root)
{
	attributes.clear();
	if (!root)
		return;

	std::vector<std::unique_ptr<TRequisite>> parsedByGuid;
	if (TryCollectCatalogTabularAttributesByGuid(root, parsedByGuid))
	{
		attributes = std::move(parsedByGuid);
		return;
	}

	if (TryCollectEmbeddedTabularAttributes(root, parsedByGuid))
	{
		attributes = std::move(parsedByGuid);
		return;
	}

	// У разных объектов 1С секция реквизитов табличной части может располагаться по
	// разным индексам. Сначала пробуем наиболее вероятные секции, сохраняя первый
	// успешный набор реквизитов.
	const int candidateSections[] = {3, 2, 4, 5, 6, 7, 1};
	for (int sectionIndex : candidateSections)
	{
		std::vector<std::unique_ptr<TRequisite>> parsedAttributes;
		if (TryCollectAttributesFromSection(root, sectionIndex, parsedAttributes))
		{
			attributes = std::move(parsedAttributes);
			break;
		}
	}

	if (attributes.empty())
	{
		std::vector<String> rawValues;
		CollectMeaningfulStrings(root, rawValues);
		for (const auto& rawValue : rawValues)
		{
			String value = Trim(rawValue);
			if (value.IsEmpty() || value == name)
				continue;

			bool alreadyExists = false;
			for (const auto& attribute : attributes)
			{
				if (attribute->name == value)
				{
					alreadyExists = true;
					break;
				}
			}

			if (!alreadyExists)
				attributes.push_back(std::make_unique<TRequisite>(value, ""));
		}
	}
}


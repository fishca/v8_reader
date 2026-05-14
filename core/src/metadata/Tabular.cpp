//---------------------------------------------------------------------------


#include "Tabular.h"
#include "guids.h"
//---------------------------------------------------------------------------

namespace
{
    inline bool IsSpace16(char16_t c) { return c == 32 || c == 9 || c == 10 || c == 13; }
    inline Utf16String TrimUtf16(const Utf16String& value) {
        std::size_t start = 0; while (start < value.size() && IsSpace16(value[start])) ++start;
        std::size_t end = value.size(); while (end > start && IsSpace16(value[end - 1])) --end;
        return value.substr(start, end - start);
    }
    inline int ToIntDefUtf16(const Utf16String& value, int defValue) {
        try { return std::stoi(std::wstring(reinterpret_cast<const wchar_t*>(value.c_str()), value.size())); }
        catch (...) { return defValue; }
    }
	bool IsServiceTabularAttributeName(const Utf16String& value)
	{
		Utf16String trimmed = value;
		return trimmed == V8Utf16FromString(L"Реквизиты") || trimmed == V8Utf16FromString(L"Реквизит");
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

	bool IsGuidLikeValue(const Utf16String& value)
	{
		Utf16String trimmed = value;
		if (trimmed.size() != 36)
			return false;

		for (std::size_t i = 0; i < trimmed.size(); i++)
		{
			char16_t ch = trimmed[i];
			bool isHex = (ch >= u'0' && ch <= u'9') || (ch >= u'a' && ch <= u'f') || (ch >= u'A' && ch <= u'F');
			bool isDash = (ch == u'-');
			if (!isHex && !isDash)
				return false;
		}

		return true;
	}

	bool IsNumericLikeValue(const Utf16String& value)
	{
		Utf16String trimmed = value;
		if (trimmed.empty())
			return false;

		for (std::size_t i = 0; i < trimmed.size(); i++)
		{
			char16_t ch = trimmed[i];
			if (!((ch >= u'0' && ch <= u'9') || ch == u'.' || ch == u',' || ch == u'-'))
				return false;
		}

		return true;
	}

	Utf16String FindFirstMeaningfulString(tree* node)
	{
		if (!node)
			return Utf16String();

		Utf16String value = TrimUtf16(node->get_value());
		if (!value.empty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.front() != u'#' && !IsServiceTabularAttributeName(value))
			return value;

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			Utf16String nested = FindFirstMeaningfulString(node->get_subnode(i));
			if (!nested.empty())
				return nested;
		}

		return Utf16String();
	}

	void CollectMeaningfulStrings(tree* node, std::vector<Utf16String>& values)
	{
		if (!node)
			return;

		Utf16String value = TrimUtf16(node->get_value());
		if (!value.empty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.front() != u'#' && !IsServiceTabularAttributeName(value))
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
			int count = countNode ? ToIntDefUtf16(countNode->get_value(), 0) : 0;
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

						Utf16String attributeName;
						for (const auto& namePath : namePaths)
						{
							tree* nameNode = GetNodeByPath(itemNode, namePath);
							if (!nameNode)
								continue;

							attributeName = TrimUtf16(nameNode->get_value());
							if (attributeName.empty())
								continue;

							break;
						}

						if (attributeName.empty())
							attributeName = FindFirstMeaningfulString(itemNode);

						if (!attributeName.empty())
						{
							attributes.push_back(std::make_unique<TRequisite>(attributeName, u""));
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
		tree* node = find_metadata_node_by_guid(root, u"cf4abea7-37b2-11d4-940f-008048da11f9");
		if (!node)
			return false;

		tree* countNode = node->get_next();
		int count = countNode ? ToIntDefUtf16(countNode->get_value(), 0) : 0;
		if (count <= 0)
			return false;

		int collected = 0;
		tree* current = countNode;
		while ((current = current->get_next()) != nullptr)
		{
			Utf16String attributeName = FindFirstMeaningfulString(current);
			if (attributeName.empty())
				continue;

			if (IsServiceTabularAttributeName(attributeName))
				continue;

			attributes.push_back(std::make_unique<TRequisite>(attributeName, u""));
			collected++;
			if (collected >= count)
				break;
		}

		return collected > 0;
	}

	bool TryCollectEmbeddedTabularAttributes(tree* root, std::vector<std::unique_ptr<TRequisite>>& attributes)
	{
		static constexpr const wchar_t* EmbeddedTabularAttributeGuid = L"888744e1-b616-11d4-9436-004095e12fc7";

		auto tryCollectFromContainer = [&](tree* container) -> bool
		{
			if (!container)
				return false;

			for (int i = 0; i < container->get_num_subnode(); i++)
			{
				tree* sectionNode = container->get_subnode(i);
				if (!sectionNode || sectionNode->get_num_subnode() < 2)
					continue;

				Utf16String sectionGuid = TrimUtf16(sectionNode->get_subnode(0)->get_value());
				if (sectionGuid != u"888744e1-b616-11d4-9436-004095e12fc7")
					continue;

				int count = ToIntDefUtf16(sectionNode->get_subnode(1)->get_value(), 0);
				if (count <= 0)
					return false;

				int collected = 0;
				for (int itemIndex = 2; itemIndex < sectionNode->get_num_subnode(); itemIndex++)
				{
					Utf16String attributeName = FindFirstMeaningfulString(sectionNode->get_subnode(itemIndex));
					if (attributeName.empty())
						continue;

					if (IsServiceTabularAttributeName(attributeName))
						continue;

					attributes.push_back(std::make_unique<TRequisite>(attributeName, u""));
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

		tree* node = find_metadata_node_by_guid(root, u"888744e1-b616-11d4-9436-004095e12fc7");
		if (!node)
			return false;

		tree* countNode = node->get_next();
		int count = countNode ? ToIntDefUtf16(countNode->get_value(), 0) : 0;
		if (count <= 0)
			return false;

		int collected = 0;
		tree* current = countNode;
		while ((current = current->get_next()) != nullptr)
		{
			Utf16String attributeName = FindFirstMeaningfulString(current);
			if (attributeName.empty())
				continue;

			if (IsServiceTabularAttributeName(attributeName))
				continue;

			attributes.push_back(std::make_unique<TRequisite>(attributeName, u""));
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

TTabular::TTabular(const Utf16String& _name, const Utf16String& _guid)
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
		std::vector<Utf16String> rawValues;
		CollectMeaningfulStrings(root, rawValues);
		for (const auto& rawValue : rawValues)
		{
			Utf16String value = rawValue;
			if (value.empty() || value == name)
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


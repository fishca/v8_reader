//---------------------------------------------------------------------------


#include <vector>

#include "Common.h"
#include "ExchangePlans.h"
#include "Comand.h"
#include "Form.h"
//---------------------------------------------------------------------------

namespace
{
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
        if (!value.IsEmpty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.SubString(1, 1) != L"#")
            return value;

        for (int i = 0; i < node->get_num_subnode(); i++)
        {
            String nested = FindFirstMeaningfulString(node->get_subnode(i));
            if (!nested.IsEmpty())
                return nested;
        }

        return L"";
    }

    bool TryCollectExchangePlanAttributes(tree* root, std::vector<std::unique_ptr<TRequisite>>& attributes)
    {
        static const String ExchangePlanAttributeSectionGuid = L"1a1b4fea-e093-470d-94ff-1d2f16cda2ab";

        tree* sectionNodeByGuid = find_metadata_node_by_guid(root, ExchangePlanAttributeSectionGuid);
        if (sectionNodeByGuid)
        {
            tree* countNode = sectionNodeByGuid->get_next();
            int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
            if (count > 0)
            {
                std::vector<std::unique_ptr<TRequisite>> parsed;
                tree* current = countNode;
                while ((current = current->get_next()) != nullptr)
                {
                    String attributeName;

tree* nameNode = GetNodeByPath(current, {0, 1, 1, 1, 2});
                    if (nameNode)
                        attributeName = Trim(nameNode->get_value());

                    if (attributeName.IsEmpty())
                        attributeName = FindFirstMeaningfulString(current);

                    if (!attributeName.IsEmpty())
                        parsed.push_back(std::make_unique<TRequisite>(attributeName, L""));

                    if ((int)parsed.size() >= count)
                        break;
                }

                if (!parsed.empty())
                {
                    attributes = std::move(parsed);
                    return true;
                }
            }
        }

        const int candidateSections[] = {5, 7, 6, 3, 8, 4, 2, 1};
        const std::vector<std::vector<int>> itemPrefixes = {
            {0},
            {0, 1}
        };
        const std::vector<std::vector<int>> namePaths = {
            {0, 1, 1, 1, 2},
            {0, 1, 1, 1, 1, 2},
            {0, 1, 1, 2},
            {0, 1, 3, 2},
            {1, 1, 1, 2},
            {1, 1, 2},
            {1, 3, 2}
        };

        for (int sectionIndex : candidateSections)
        {
            tree* countNode = GetNodeByPath(root, {0, sectionIndex, 1});
            int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
            if (count <= 0)
                continue;

            int delta = count - 2;
            std::vector<std::unique_ptr<TRequisite>> parsed;

            for (const auto& itemPrefix : itemPrefixes)
            {
                for (int i = 0; i < count; i++)
                {
                    try
                    {
                        std::vector<int> itemPath = itemPrefix;
                        itemPath.push_back(sectionIndex);
                        itemPath.push_back(i + count - delta);

                        tree* itemNode = GetNodeByPath(root, itemPath);
                        if (!itemNode)
                            continue;

                        String attributeName;
                        for (const auto& namePath : namePaths)
                        {
                            tree* nameNode = GetNodeByPath(itemNode, namePath);
                            if (!nameNode)
                                continue;

                            attributeName = Trim(nameNode->get_value());
                            if (!attributeName.IsEmpty())
                                break;
                        }

                        if (attributeName.IsEmpty())
                            attributeName = FindFirstMeaningfulString(itemNode);

                        if (!attributeName.IsEmpty() && attributeName != Trim(FindFirstMeaningfulString(root)))
                            parsed.push_back(std::make_unique<TRequisite>(attributeName, L""));
                    }
                    catch (...)
                    {
                    }
                }

                if (!parsed.empty())
                {
                    attributes = std::move(parsed);
                    return true;
                }
            }
        }

        return false;
    }

    bool TryCollectExchangePlanTabularSections(tree* root, std::vector<std::unique_ptr<TTabular>>& tabulars)
    {
        static const String ExchangePlanTabularSectionGuid = L"52293f4b-f98c-43ea-a80f-41047ae7ab58";

        tree* sectionNodeByGuid = find_metadata_node_by_guid(root, ExchangePlanTabularSectionGuid);
        if (!sectionNodeByGuid)
            return false;

        tree* countNode = sectionNodeByGuid->get_next();
        int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
        if (count <= 0)
            return false;

        std::vector<std::unique_ptr<TTabular>> parsed;
        tree* current = countNode;
        while ((current = current->get_next()) != nullptr)
        {
            String tabularName;
            tree* nameNode = GetNodeByPath(current, {0, 1, 1, 1, 2});
            if (nameNode)
                tabularName = Trim(nameNode->get_value());

            if (tabularName.IsEmpty())
                tabularName = FindFirstMeaningfulString(current);

            if (tabularName.IsEmpty())
                continue;

            auto tabular = std::make_unique<TTabular>(tabularName, L"");

            tree* tabularAttributesNode = GetNodeByPath(current, {0, 1, 1, 1, 2});
            tabular->initializeFromTree(tabularAttributesNode ? tabularAttributesNode : current);
            parsed.push_back(std::move(tabular));

            if ((int)parsed.size() >= count)
                break;
        }

        if (parsed.empty())
            return false;

        tabulars = std::move(parsed);
        return true;
    }
}

bool TryCollectExchangePlanCommands(tree* root, std::vector<std::unique_ptr<TComand>>& commands)
{
    static const String ExchangePlanCommandsGuid = L"d5207c64-11d5-4d46-bba2-55b7b07ff4eb";

    tree* sectionNodeByGuid = find_metadata_node_by_guid(root, ExchangePlanCommandsGuid);
    if (!sectionNodeByGuid)
        return false;

    tree* countNode = sectionNodeByGuid->get_next();
    int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
    if (count <= 0)
        return false;

    std::vector<std::unique_ptr<TComand>> parsed;
    tree* current = countNode;
    while ((current = current->get_next()) != nullptr)
    {
        String commandName;
        tree* nameNode = GetNodeByPath(current, {0, 1, 3, 2, 9, 2});
        if (nameNode)
            commandName = Trim(nameNode->get_value());

        if (commandName.IsEmpty())
            commandName = FindFirstMeaningfulString(current);

        if (!commandName.IsEmpty())
            parsed.push_back(std::make_unique<TComand>(commandName, L""));

        if ((int)parsed.size() >= count)
            break;
    }

    if (parsed.empty())
        return false;

    commands = std::move(parsed);
    return true;
}

bool TryCollectExchangePlanForms(v8catalog* parent, tree* root, std::vector<std::unique_ptr<TForm1C>>& forms)
{
    static const String ExchangePlanFormsGuid = L"87c509ab-3d38-4d67-b379-aca796298578";

    if (!parent)
        return false;

    tree* sectionNodeByGuid = find_metadata_node_by_guid(root, ExchangePlanFormsGuid);
    if (!sectionNodeByGuid)
        return false;

    tree* countNode = sectionNodeByGuid->get_next();
    int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
    if (count <= 0)
        return false;

    std::vector<std::unique_ptr<TForm1C>> parsed;
    tree* current = countNode;
    while ((current = current->get_next()) != nullptr)
    {
        String guid_md = Trim(current->get_value());
        if (guid_md.IsEmpty())
            continue;

        String formName = GetNameFormCatalogs(parent, guid_md);

        if (!formName.IsEmpty())
            parsed.push_back(std::make_unique<TForm1C>(formName, L""));

        if ((int)parsed.size() >= count)
            break;
    }

    if (parsed.empty())
        return false;

    forms = std::move(parsed);
    return true;
}

bool TryCollectExchangePlanLayouts(v8catalog* parent, tree* root, std::vector<std::unique_ptr<TMoxel>>& moxels)
{
    static const String ExchangePlanLayoutsGuid = L"3daea016-69b7-4ed4-9453-127911372fe6";

    if (!parent)
        return false;

    tree* sectionNodeByGuid = find_metadata_node_by_guid(root, ExchangePlanLayoutsGuid);
    if (!sectionNodeByGuid)
        return false;

    tree* countNode = sectionNodeByGuid->get_next();
    int count = countNode ? countNode->get_value().ToIntDef(0) : 0;
    if (count <= 0)
        return false;

    std::vector<std::unique_ptr<TMoxel>> parsed;
    tree* current = countNode;
    while ((current = current->get_next()) != nullptr)
    {
        String guid_md = Trim(current->get_value());
        if (guid_md.IsEmpty())
            continue;

        String layoutName = GetNameMoxCatalogs(parent, guid_md);
        if (!layoutName.IsEmpty())
            parsed.push_back(std::make_unique<TMoxel>(layoutName, guid_md));

        if ((int)parsed.size() >= count)
            break;
    }

    if (parsed.empty())
        return false;

    moxels = std::move(parsed);
    return true;
}

static MetadataTreePaths GetExchangePlansPaths()
{
    MetadataTreePaths paths;
    paths.attIdx = 3;
    paths.attItemPath = {0, 1, 1, 1, 2};
    paths.tabIdx = 5;
    paths.tabItemPath = {0, 1, 5, 1, 2};
    paths.formsIdx = 6;
    paths.cmdIdx = 7;
    paths.cmdItemPath = {0, 1, 3, 2, 9, 2};
    paths.moxIdx = 4;
    paths.getFormNameFunc = GetNameFormCatalogs;
    paths.hasTabulars = true;
    return paths;
}

TExchangePlans::TExchangePlans() : MetadataObjectWithSections()
{
    exchangePlanName = "";
    root_data.reset();
}

TExchangePlans::TExchangePlans(v8catalog* _parent, const String& _guid) : MetadataObjectWithSections(_parent, _guid)
{
    exchangePlanName = "";
    initializeFromTree();
    root_data.reset();
}

TExchangePlans::TExchangePlans(v8catalog* _parent, const String& _guid, const String& _name) : MetadataObjectWithSections(_parent, _guid, _name)
{
    exchangePlanName = _name;
    initializeFromTree();
    root_data.reset();
}

TExchangePlans::~TExchangePlans()
{
}

String TExchangePlans::GetExchangePlanName()
{
    return exchangePlanName;
}

void TExchangePlans::SetExchangePlanName(String _name)
{
    exchangePlanName = _name;
}

void TExchangePlans::initializeFromTree()
{
    MetadataObjectWithSections::initializeFromTreeWithPaths(GetExchangePlansPaths());

    if (getAttributes().empty() && root_data)
        TryCollectExchangePlanAttributes(root_data.get(), getAttributes());

    if (getTabularSections().empty() && root_data)
        TryCollectExchangePlanTabularSections(root_data.get(), getTabularSections());

    if (getCommands().empty() && root_data)
        TryCollectExchangePlanCommands(root_data.get(), getCommands());

    if (getForms().empty() && root_data)
        TryCollectExchangePlanForms(parent, root_data.get(), getForms());

    if (getLayouts().empty() && root_data)
        TryCollectExchangePlanLayouts(parent, root_data.get(), getLayouts());
}


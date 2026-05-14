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

        Utf16String value = V8Utf16FromString(Trim(node->get_value()));
        if (!value.empty() && !IsGuidLikeValue(value) && !IsNumericLikeValue(value) && value.front() != u'#')
            return value;

        for (int i = 0; i < node->get_num_subnode(); i++)
        {
            Utf16String nested = FindFirstMeaningfulString(node->get_subnode(i));
            if (!nested.empty())
                return nested;
        }

        return Utf16String();
    }

    bool TryCollectExchangePlanAttributes(tree* root, std::vector<std::unique_ptr<TRequisite>>& attributes)
    {
        static constexpr const wchar_t* ExchangePlanAttributeSectionGuid = L"1a1b4fea-e093-470d-94ff-1d2f16cda2ab";

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
                    Utf16String attributeName;

tree* nameNode = GetNodeByPath(current, {0, 1, 1, 1, 2});
                    if (nameNode)
                        attributeName = V8Utf16FromString(Trim(nameNode->get_value()));

                    if (attributeName.empty())
                        attributeName = FindFirstMeaningfulString(current);

                    if (!attributeName.empty())
                        parsed.push_back(std::make_unique<TRequisite>(attributeName, u""));

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

                        Utf16String attributeName;
                        for (const auto& namePath : namePaths)
                        {
                            tree* nameNode = GetNodeByPath(itemNode, namePath);
                            if (!nameNode)
                                continue;

                            attributeName = V8Utf16FromString(Trim(nameNode->get_value()));
                            if (!attributeName.empty())
                                break;
                        }

                        if (attributeName.empty())
                            attributeName = FindFirstMeaningfulString(itemNode);

                        if (!attributeName.empty() && attributeName != Trim(FindFirstMeaningfulString(root)))
                            parsed.push_back(std::make_unique<TRequisite>(attributeName, u""));
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
        static constexpr const wchar_t* ExchangePlanTabularSectionGuid = L"52293f4b-f98c-43ea-a80f-41047ae7ab58";

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
            Utf16String tabularName;
            tree* nameNode = GetNodeByPath(current, {0, 1, 1, 1, 2});
            if (nameNode)
                tabularName = V8Utf16FromString(Trim(nameNode->get_value()));

            if (tabularName.empty())
                tabularName = FindFirstMeaningfulString(current);

            if (tabularName.empty())
                continue;

            auto tabular = std::make_unique<TTabular>(tabularName, u"");

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
    static constexpr const wchar_t* ExchangePlanCommandsGuid = L"d5207c64-11d5-4d46-bba2-55b7b07ff4eb";

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
        Utf16String commandName;
        tree* nameNode = GetNodeByPath(current, {0, 1, 3, 2, 9, 2});
        if (nameNode)
            commandName = V8Utf16FromString(Trim(nameNode->get_value()));

        if (commandName.empty())
            commandName = FindFirstMeaningfulString(current);

        if (!commandName.empty())
            parsed.push_back(std::make_unique<TComand>(commandName, u""));

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
    static constexpr const wchar_t* ExchangePlanFormsGuid = L"87c509ab-3d38-4d67-b379-aca796298578";

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
        Utf16String guid_md = V8Utf16FromString(Trim(current->get_value()));
        if (guid_md.empty())
            continue;

        Utf16String formName = GetNameFormCatalogs16(parent, guid_md);

        if (!formName.empty())
            parsed.push_back(std::make_unique<TForm1C>(formName, u""));

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
    static constexpr const wchar_t* ExchangePlanLayoutsGuid = L"3daea016-69b7-4ed4-9453-127911372fe6";

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
        Utf16String guid_md = V8Utf16FromString(Trim(current->get_value()));
        if (guid_md.empty())
            continue;

        Utf16String layoutName = GetNameMoxCatalogs16(parent, guid_md);
        if (!layoutName.empty())
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
    paths.getFormNameFunc = GetNameFormCatalogs16;
    paths.hasTabulars = true;
    return paths;
}

TExchangePlans::TExchangePlans() : MetadataObjectWithSections()
{
    name.clear();
    root_data.reset();
}

TExchangePlans::TExchangePlans(v8catalog* _parent, const Utf16String& _guid) : MetadataObjectWithSections(_parent, _guid)
{
    name.clear();
    initializeFromTree();
    root_data.reset();
}

TExchangePlans::TExchangePlans(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : MetadataObjectWithSections(_parent, _guid, _name)
{
    name = _name;
    initializeFromTree();
    root_data.reset();
}

TExchangePlans::~TExchangePlans()
{
}

Utf16String TExchangePlans::GetExchangePlanName() const
{
    return name;
}

void TExchangePlans::SetExchangePlanName(const Utf16String& _name)
{
    name = _name;
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


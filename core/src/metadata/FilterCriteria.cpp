//---------------------------------------------------------------------------


#include "guids.h"
#include "FilterCriteria.h"
//---------------------------------------------------------------------------

namespace
{
    constexpr const wchar_t* GUID_FilterCriteriaForms = L"00867c40-06b1-11d6-a3c7-0050bae0a776";

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

    tree* FindChildListByFirstValue(tree* root, const String& firstValue)
    {
        if (!root)
            return nullptr;

        tree* child = root->get_first();
        while (child)
        {
            tree* first = child->get_first();
            if (first && first->get_value().CompareIC(firstValue) == 0)
                return child;

            child = child->get_next();
        }

        return nullptr;
    }

    tree* FindMetadataDescriptor(tree* root)
    {
        if (!root)
            return nullptr;

        tree* first = root->get_subnode(0);
        tree* guidNode = GetNodeByPath(root, {1, 2});
        tree* nameNode = root->get_subnode(2);
        if (first && guidNode && nameNode && first->get_value() == L"3")
            return root;

        tree* child = root->get_first();
        while (child)
        {
            tree* descriptor = FindMetadataDescriptor(child);
            if (descriptor)
                return descriptor;

            child = child->get_next();
        }

        return nullptr;
    }

    String GetDescriptorName(tree* descriptor)
    {
        tree* nameNode = descriptor ? descriptor->get_subnode(2) : nullptr;
        return nameNode ? nameNode->get_value() : L"";
    }

    String GetDescriptorGuid(tree* descriptor)
    {
        tree* guidNode = GetNodeByPath(descriptor, {1, 2});
        return guidNode ? Trim(guidNode->get_value()) : L"";
    }

    String GetMetadataNameFromFile(v8catalog* parent, const Utf16String& guid)
    {
        if (!parent || guid.empty())
            return L"";

        v8file* file = parent->GetFile16(guid);
        if (!file)
            return L"";

        std::unique_ptr<tree> metadataTree(get_treeFromV8file(file));
        tree* descriptor = FindMetadataDescriptor(metadataTree.get());
        return GetDescriptorName(descriptor);
    }
}

TFilterCriteria::TFilterCriteria() : BaseMetadataObject()
{
    name = u"";
    root_data.reset();
}

TFilterCriteria::TFilterCriteria(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name = u"";
    initializeFromTree();
    root_data.reset();
}

TFilterCriteria::TFilterCriteria(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    initializeFromTree();
    root_data.reset();
}

TFilterCriteria::~TFilterCriteria()
{
}

Utf16String TFilterCriteria::GetFilterCriteriaName() const
{
    return name;
}

void TFilterCriteria::SetFilterCriteriaName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TFilterCriteria::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TFilterCriteria::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TFilterCriteria::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TFilterCriteria::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TFilterCriteria::getForms()
{
    return forms;
}

void TFilterCriteria::initializeFromTree()
{
    forms.clear();
    commands.clear();

    if (!root_data)
        return;

    if (name.empty())
    {
        tree* nameNode = GetNodeByPath(root_data.get(), {0, 1, 5, 1, 2});
        if (nameNode)
            name = V8Utf16FromString(nameNode->get_value());
    }

    tree* rootNode = root_data->get_subnode(0);

    tree* formsNode = FindChildListByFirstValue(rootNode, GUID_FilterCriteriaForms);
    if (!formsNode)
        formsNode = GetNodeByPath(root_data.get(), {0, 3});

    tree* formsCountNode = formsNode ? formsNode->get_subnode(1) : nullptr;
    int formsCount = formsCountNode ? formsCountNode->get_value().ToIntDef(0) : 0;
    for (int i = 0; i < formsCount; i++)
    {
        tree* formGuidNode = formsNode->get_subnode(i + 2);
        if (!formGuidNode)
            continue;

        String formGuid = Trim(formGuidNode->get_value());
        String formName = GetMetadataNameFromFile(parent, V8Utf16FromString(formGuid));
        if (formName.IsEmpty())
            formName = formGuid;

        forms.push_back(std::make_unique<TForm1C>(formName, formGuid));
    }

    tree* commandsNode = FindChildListByFirstValue(rootNode, GUID_SelCritCommands);
    if (!commandsNode)
        commandsNode = GetNodeByPath(root_data.get(), {0, 4});

    tree* commandsCountNode = commandsNode ? commandsNode->get_subnode(1) : nullptr;
    int commandsCount = commandsCountNode ? commandsCountNode->get_value().ToIntDef(0) : 0;
    for (int i = 0; i < commandsCount; i++)
    {
        tree* commandNode = commandsNode->get_subnode(i + 2);
        tree* descriptor = FindMetadataDescriptor(commandNode);
        String commandName = GetDescriptorName(descriptor);
        if (commandName.IsEmpty())
            continue;

        commands.push_back(std::make_unique<TComand>(commandName, GetDescriptorGuid(descriptor)));
    }
}



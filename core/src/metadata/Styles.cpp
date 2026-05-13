//---------------------------------------------------------------------------


#include "Styles.h"
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
}

TStyles::TStyles() : BaseMetadataObject()
{
    styleName = "";
    root_data.reset();
}

TStyles::TStyles(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    styleName = "";
    initializeFromTree();
    root_data.reset();
}

TStyles::TStyles(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    styleName = _name;
    initializeFromTree();
    root_data.reset();
}

TStyles::~TStyles()
{
}

String TStyles::GetStyleName()
{
    return styleName;
}

void TStyles::SetStyleName(String _name)
{
    styleName = _name;
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TStyles::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TStyles::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TStyles::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TStyles::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TStyles::getForms()
{
    return forms;
}

void TStyles::initializeFromTree()
{
    tree* nameNode = GetNodeByPath(root_data.get(), {0, 1, 1, 2});
    if (nameNode && !nameNode->get_value().IsEmpty())
    {
        name = nameNode->get_value();
        styleName = name;
        return;
    }

    if (styleName.IsEmpty())
        styleName = name;
}


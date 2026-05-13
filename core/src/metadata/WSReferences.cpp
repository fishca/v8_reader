//---------------------------------------------------------------------------


#include "WSReferences.h"
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

    String FindReferenceName(tree* node)
    {
        if (!node)
            return L"";

        if (node->get_type() == nd_list && node->get_num_subnode() >= 3)
        {
            tree* markerNode = node->get_subnode(0);
            tree* possibleNameNode = node->get_subnode(2);
            if (markerNode && possibleNameNode &&
                (markerNode->get_value() == L"2" || markerNode->get_value() == L"3") &&
                possibleNameNode->get_type() == nd_string &&
                !possibleNameNode->get_value().IsEmpty())
            {
                return possibleNameNode->get_value();
            }
        }

        for (int i = 0; i < node->get_num_subnode(); i++)
        {
            String result = FindReferenceName(node->get_subnode(i));
            if (!result.IsEmpty())
                return result;
        }

        return L"";
    }
}

TWSReferences::TWSReferences() : BaseMetadataObject()
{
	referenceName = "";
	root_data.reset();
}

TWSReferences::TWSReferences(v8catalog* _parent, const String& _guid)
	: BaseMetadataObject(_parent, _guid)
{
	referenceName = "";
	initializeFromTree();
	root_data.reset();
}

TWSReferences::TWSReferences(v8catalog* _parent, const String& _guid, const String& _name)
	: BaseMetadataObject(_parent, _guid, _name)
{
	referenceName = _name;
	initializeFromTree();
	root_data.reset();
}

TWSReferences::~TWSReferences()
{
}

String TWSReferences::GetReferenceName()
{
	return referenceName;
}

void TWSReferences::SetReferenceName(String _name)
{
	referenceName = _name;
	name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TWSReferences::getAttributes()
{
	return attributes;
}

std::vector<std::unique_ptr<TComand>>& TWSReferences::getCommands()
{
	return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TWSReferences::getLayouts()
{
	return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TWSReferences::getTabularSections()
{
	return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TWSReferences::getForms()
{
	return forms;
}

void TWSReferences::initializeFromTree()
{
	tree* nameNode = GetNodeByPath(root_data.get(), {1, 2, 2});
	if (nameNode && !nameNode->get_value().IsEmpty())
	{
		name = nameNode->get_value();
		referenceName = name;
		return;
	}

	String foundName = FindReferenceName(root_data.get());
	if (!foundName.IsEmpty())
	{
		name = foundName;
		referenceName = name;
		return;
	}

	if (referenceName.IsEmpty())
		referenceName = name;
}


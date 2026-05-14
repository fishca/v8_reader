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

    Utf16String FindReferenceName(tree* node)
    {
        if (!node)
            return u"";

        if (node->get_type() == nd_list && node->get_num_subnode() >= 3)
        {
            tree* markerNode = node->get_subnode(0);
            tree* possibleNameNode = node->get_subnode(2);
            if (markerNode && possibleNameNode &&
                (markerNode->get_value() == L"2" || markerNode->get_value() == L"3") &&
                possibleNameNode->get_type() == nd_string &&
                !possibleNameNode->get_value().IsEmpty())
            {
                return V8Utf16FromString(possibleNameNode->get_value());
            }
        }

        for (int i = 0; i < node->get_num_subnode(); i++)
        {
            Utf16String result = FindReferenceName(node->get_subnode(i));
            if (!result.empty())
                return result;
        }

        return u"";
    }
}

TWSReferences::TWSReferences() : BaseMetadataObject()
{
	name.clear();
	root_data.reset();
}

TWSReferences::TWSReferences(v8catalog* _parent, const Utf16String& _guid)
	: BaseMetadataObject(_parent, _guid)
{
	name.clear();
	initializeFromTree();
	root_data.reset();
}

TWSReferences::TWSReferences(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name)
	: BaseMetadataObject(_parent, _guid, _name)
{
	name = _name;
	initializeFromTree();
	root_data.reset();
}

TWSReferences::~TWSReferences()
{
}

Utf16String TWSReferences::GetReferenceName() const
{
	return name;
}

void TWSReferences::SetReferenceName(const Utf16String& _name)
{
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
		name = V8Utf16FromString(nameNode->get_value());
		return;
	}

	Utf16String foundName = FindReferenceName(root_data.get());
	if (!foundName.empty())
	{
		name = foundName;
	}
}


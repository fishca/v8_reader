//---------------------------------------------------------------------------


#include "WebSocketClients.h"
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

TWebSocketClients::TWebSocketClients() : BaseMetadataObject()
{
    name.clear();
    root_data.reset();
}

TWebSocketClients::TWebSocketClients(v8catalog* _parent, const Utf16String& _guid) : BaseMetadataObject(_parent, _guid)
{
    name.clear();
    initializeFromTree();
    root_data.reset();
}

TWebSocketClients::TWebSocketClients(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    name = _name;
    initializeFromTree();
    root_data.reset();
}

TWebSocketClients::~TWebSocketClients()
{
}

Utf16String TWebSocketClients::GetClientName() const
{
    return name;
}

void TWebSocketClients::SetClientName(const Utf16String& _name)
{
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TWebSocketClients::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TWebSocketClients::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TWebSocketClients::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TWebSocketClients::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TWebSocketClients::getForms()
{
    return forms;
}

void TWebSocketClients::initializeFromTree()
{
    tree* nameNode = GetNodeByPath(root_data.get(), {0, 1, 1, 2});
    if (nameNode && !nameNode->get_value().IsEmpty())
    {
        name = V8Utf16FromString(nameNode->get_value());
        return;
    }
}


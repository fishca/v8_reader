//---------------------------------------------------------------------------

#pragma hdrstop

#include "IntegrationServices.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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

TIntegrationServices::TIntegrationServices() : BaseMetadataObject()
{
    serviceName = "";
    root_data.reset();
}

TIntegrationServices::TIntegrationServices(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid)
{
    serviceName = "";
    initializeFromTree();
    root_data.reset();
}

TIntegrationServices::TIntegrationServices(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name)
{
    serviceName = _name;
    initializeFromTree();
    root_data.reset();
}

TIntegrationServices::~TIntegrationServices()
{
}

String TIntegrationServices::GetServiceName()
{
    return serviceName;
}

void TIntegrationServices::SetServiceName(String _name)
{
    serviceName = _name;
    name = _name;
}

std::vector<std::unique_ptr<TRequisite>>& TIntegrationServices::getAttributes()
{
    return attributes;
}

std::vector<std::unique_ptr<TComand>>& TIntegrationServices::getCommands()
{
    return commands;
}

std::vector<std::unique_ptr<TMoxel>>& TIntegrationServices::getLayouts()
{
    return layouts;
}

std::vector<std::unique_ptr<TTabular>>& TIntegrationServices::getTabularSections()
{
    return tabularSections;
}

std::vector<std::unique_ptr<TForm1C>>& TIntegrationServices::getForms()
{
    return forms;
}

void TIntegrationServices::initializeFromTree()
{
    tree* nameNode = GetNodeByPath(root_data.get(), {0, 1, 1, 2});
    if (nameNode && !nameNode->get_value().IsEmpty())
    {
        name = nameNode->get_value();
        serviceName = name;
        return;
    }

    if (serviceName.IsEmpty())
        serviceName = name;
}


//---------------------------------------------------------------------------

#pragma hdrstop

#include "MetadataObjectWithSections.h"
#include "Common.h"
#include "Class_1CD.h"
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
}

__fastcall MetadataObjectWithSections::MetadataObjectWithSections()
    : BaseMetadataObject()
{
}

__fastcall MetadataObjectWithSections::MetadataObjectWithSections(v8catalog* _parent, const String& _guid)
    : BaseMetadataObject(_parent, _guid)
{
}

__fastcall MetadataObjectWithSections::MetadataObjectWithSections(v8catalog* _parent, const String& _guid, const String& _name)
    : BaseMetadataObject(_parent, _guid, _name)
{
}

__fastcall MetadataObjectWithSections::~MetadataObjectWithSections()
{
}

void MetadataObjectWithSections::initializeFromTreeWithPaths(const MetadataTreePaths& paths)
{
    if (!root_data || !paths.getFormNameFunc) return;

    // Реквизиты
    attributes.clear();
    tree* node_att = GetNodeByPath(root_data.get(), {0, paths.attIdx, 1});
    int CountAtt = node_att ? node_att->get_value().ToIntDef(0) : 0;
    int Delta = CountAtt - 2;
    for (int i = 0; i < CountAtt; i++)
    {
        try {
            tree* itemNode = GetNodeByPath(root_data.get(), {0, paths.attIdx, i + CountAtt - Delta});
            itemNode = GetNodeByPath(itemNode, paths.attItemPath);
            if (!itemNode)
                continue;
            String NameAtt = itemNode->get_value();
            attributes.push_back(std::make_unique<TRequisite>(NameAtt, ""));
        } catch (...) {
        }
    }

    // Табличные части
    tabulars.clear();
    if (paths.hasTabulars)
    {
        tree* node_att_t = GetNodeByPath(root_data.get(), {0, paths.tabIdx, 1});
        int CountAttTab = node_att_t ? node_att_t->get_value().ToIntDef(0) : 0;
        int DeltaTab = CountAttTab - 2;
        for (int i = 0; i < CountAttTab; i++)
        {
            tree* tabularNode = GetNodeByPath(root_data.get(), {0, paths.tabIdx, i + CountAttTab - DeltaTab});
            tree* itemNode = GetNodeByPath(tabularNode, paths.tabItemPath);
            if (!itemNode || !tabularNode)
                continue;
            String NameAttTab = itemNode->get_value();
            String GuidAttTab;
            tree* guidNode = GetNodeByPath(tabularNode, {0, 1, 5, 1, 1});
            if (guidNode)
                GuidAttTab = Trim(guidNode->get_value());

            auto tabular = std::make_unique<TTabular>(NameAttTab, GuidAttTab);

            std::unique_ptr<tree> tabularRootData;
            if (parent && !GuidAttTab.IsEmpty())
            {
                v8file* tabularFile = parent->GetFile(GuidAttTab);
                if (tabularFile)
                    tabularRootData.reset(get_treeFromV8file(tabularFile));
            }

            tabular->initializeFromTree(tabularRootData ? tabularRootData.get() : tabularNode);
            tabulars.push_back(std::move(tabular));
        }
    }

    // Формы
    forms.clear();
    tree* node = GetNodeByPath(root_data.get(), {0, paths.formsIdx, 0});
    tree* curNodeChild = node ? node->get_next() : nullptr;
    while (curNodeChild)
    {
        curNodeChild = curNodeChild->get_next();
        if (curNodeChild)
        {
            try
            {
                String guid_md = curNodeChild->get_value();
                String NameForm = paths.getFormNameFunc(parent, guid_md);
                forms.push_back(std::make_unique<TForm1C>(NameForm, ""));
            }
            catch (...)
            {
            }
        }
    }

    // Команды
    comands.clear();
    tree* node_att_c = GetNodeByPath(root_data.get(), {0, paths.cmdIdx, 1});
    int CountCom = node_att_c ? node_att_c->get_value().ToIntDef(0) : 0;
    int DeltaCom = CountCom - 2;
    for (int i = 0; i < CountCom; i++)
    {
        try
        {
            tree* itemNode = GetNodeByPath(root_data.get(), {0, paths.cmdIdx, i + CountCom - DeltaCom});
            itemNode = GetNodeByPath(itemNode, paths.cmdItemPath);
            if (!itemNode)
                continue;
            String NameCom = itemNode->get_value();
            comands.push_back(std::make_unique<TComand>(NameCom, ""));
        }
        catch (...)
        {
        }
    }

    // Макеты
    moxels.clear();
    tree* node_mox = GetNodeByPath(root_data.get(), {0, paths.moxIdx, 0});
    tree* curNodeChildMox = node_mox ? node_mox->get_next() : nullptr;
    while (curNodeChildMox)
    {
        curNodeChildMox = curNodeChildMox->get_next();
        if (curNodeChildMox)
        {
            try
            {
                String NameMox = GetNameMoxCatalogs(parent, curNodeChildMox->get_value());
                moxels.push_back(std::make_unique<TMoxel>(NameMox, ""));
            }
            catch (...)
            {
            }
        }
    }
}

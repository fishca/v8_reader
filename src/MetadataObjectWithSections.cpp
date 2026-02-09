//---------------------------------------------------------------------------

#pragma hdrstop

#include "MetadataObjectWithSections.h"
#include "Common.h"
#include "Class_1CD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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
    tree* node_att = root_data;
    node_att = &(*node_att)[0][paths.attIdx][1];
    int CountAtt = node_att->get_value().ToInt();
    int Delta = CountAtt - 2;
    for (int i = 0; i < CountAtt; i++)
    {
        try {
            tree* node_att_att = root_data;
            tree* itemNode = &(*node_att_att)[0][paths.attIdx][i + CountAtt - Delta];
            for (size_t p = 0; p < paths.attItemPath.size(); p++)
                itemNode = &(*itemNode)[paths.attItemPath[p]];
            String NameAtt = itemNode->get_value();
            attributes.push_back(std::make_unique<TRequisite>(NameAtt, ""));
        } catch (...) {
        }
    }

    // Табличные части
    tabulars.clear();
    if (paths.hasTabulars)
    {
        tree* node_att_t = root_data;
        node_att_t = &(*node_att_t)[0][paths.tabIdx][1];
        int CountAttTab = node_att_t->get_value().ToInt();
        int DeltaTab = CountAttTab - 2;
        for (int i = 0; i < CountAttTab; i++)
        {
            tree* node_att_tab = root_data;
            tree* itemNode = &(*node_att_tab)[0][paths.tabIdx][i + CountAttTab - DeltaTab];
            for (size_t p = 0; p < paths.tabItemPath.size(); p++)
                itemNode = &(*itemNode)[paths.tabItemPath[p]];
            String NameAttTab = itemNode->get_value();
            tabulars.push_back(std::make_unique<TTabular>(NameAttTab, ""));
        }
    }

    // Формы
    forms.clear();
    tree* node = root_data;
    node = &(*node)[0][paths.formsIdx][0];
    int CountChild = (node->get_next())->get_value().ToInt();
    tree* curNodeChild = node->get_next();
    while (curNodeChild)
    {
        curNodeChild = curNodeChild->get_next();
        if (curNodeChild)
        {
            String guid_md = curNodeChild->get_value();
            String NameForm = paths.getFormNameFunc(parent, guid_md);
            forms.push_back(std::make_unique<TForm1C>(NameForm, ""));
        }
    }

    // Команды
    comands.clear();
    tree* node_att_c = root_data;
    node_att_c = &(*node_att_c)[0][paths.cmdIdx][1];
    int CountCom = node_att_c->get_value().ToInt();
    int DeltaCom = CountCom - 2;
    for (int i = 0; i < CountCom; i++)
    {
        tree* node_com = root_data;
        tree* itemNode = &(*node_com)[0][paths.cmdIdx][i + CountCom - DeltaCom];
        for (size_t p = 0; p < paths.cmdItemPath.size(); p++)
            itemNode = &(*itemNode)[paths.cmdItemPath[p]];
        String NameCom = itemNode->get_value();
        comands.push_back(std::make_unique<TComand>(NameCom, ""));
    }

    // Макеты
    moxels.clear();
    tree* node_mox = root_data;
    node_mox = &(*node_mox)[0][paths.moxIdx][0];
    int CountMox = (node_mox->get_next())->get_value().ToInt();
    tree* curNodeChildMox = node_mox->get_next();
    while (curNodeChildMox)
    {
        curNodeChildMox = curNodeChildMox->get_next();
        if (curNodeChildMox)
        {
            String NameMox = GetNameMoxCatalogs(parent, curNodeChildMox->get_value());
            moxels.push_back(std::make_unique<TMoxel>(NameMox, ""));
        }
    }
}

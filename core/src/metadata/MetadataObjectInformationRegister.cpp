//---------------------------------------------------------------------------

#pragma hdrstop

#include "MetadataObjectInformationRegister.h"
#include "Common.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
    String FindFirstGuid(tree* node)
    {
        if (!node)
            return L"";

        String value = Trim(node->get_value());
        if (ModuleTextStorage::IsGuidLike(value))
            return value;

        for (int i = 0; i < node->get_num_subnode(); i++)
        {
            String found = FindFirstGuid(node->get_subnode(i));
            if (!found.IsEmpty())
                return found;
        }

        return L"";
    }
}

MetadataObjectInformationRegister::MetadataObjectInformationRegister()
    : BaseMetadataObject()
{
}

MetadataObjectInformationRegister::MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid)
    : BaseMetadataObject(_parent, _guid)
{
}

MetadataObjectInformationRegister::MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid, const String& _name)
    : BaseMetadataObject(_parent, _guid, _name)
{
}

MetadataObjectInformationRegister::~MetadataObjectInformationRegister()
{
}

void MetadataObjectInformationRegister::initializeFromTreeWithPaths(const InfoRegisterTreePaths& paths)
{
    if (!root_data || !paths.getFormNameFunc) return;

    // Р РµРєРІРёР·РёС‚С‹
    attributes.clear();
    tree* node_att = root_data.get();
    node_att = &(*node_att)[0][paths.attIdx][1];
    int CountAtt = node_att->get_value().ToInt();
    int Delta = CountAtt - 2;
    for (int i = 0; i < CountAtt; i++)
    {
        try {
            tree* itemNode = &(*root_data.get())[0][paths.attIdx][i + CountAtt - Delta];
            for (size_t p = 0; p < paths.attItemPath.size(); p++)
                itemNode = &(*itemNode)[paths.attItemPath[p]];
            String NameAtt = itemNode->get_value();
            attributes.push_back(std::make_unique<TRequisite>(NameAtt, ""));
        } catch (...) {
        }
    }

    // РР·РјРµСЂРµРЅРёСЏ
    dimensions.clear();
    tree* node_dim = root_data.get();
    node_dim = &(*node_dim)[0][paths.dimIdx][1];
    int CountDim = node_dim->get_value().ToInt();
    int DeltaDim = CountDim - 2;
    for (int i = 0; i < CountDim; i++)
    {
        try {
            tree* itemNode = &(*root_data.get())[0][paths.dimIdx][i + CountDim - DeltaDim];
            for (size_t p = 0; p < paths.dimItemPath.size(); p++)
                itemNode = &(*itemNode)[paths.dimItemPath[p]];
            String NameDim = itemNode->get_value();
            dimensions.push_back(std::make_unique<TRequisite>(NameDim, ""));
        } catch (...) {
        }
    }

    // Р РµСЃСѓСЂСЃС‹
    resources.clear();
    tree* node_res = root_data.get();
    node_res = &(*node_res)[0][paths.resIdx][1];
    int CountRes = node_res->get_value().ToInt();
    int DeltaRes = CountRes - 2;
    for (int i = 0; i < CountRes; i++)
    {
        try {
            tree* itemNode = &(*root_data.get())[0][paths.resIdx][i + CountRes - DeltaRes];
            for (size_t p = 0; p < paths.resItemPath.size(); p++)
                itemNode = &(*itemNode)[paths.resItemPath[p]];
            String NameRes = itemNode->get_value();
            resources.push_back(std::make_unique<TRequisite>(NameRes, ""));
        } catch (...) {
        }
    }

    // Р¤РѕСЂРјС‹
    forms.clear();
    tree* node = root_data.get();
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
            forms.push_back(std::make_unique<TForm1C>(NameForm, guid_md));
        }
    }

    // РљРѕРјР°РЅРґС‹
    comands.clear();
    tree* node_att_c = root_data.get();
    node_att_c = &(*node_att_c)[0][paths.cmdIdx][1];
    int CountCom = node_att_c->get_value().ToInt();
    int DeltaCom = CountCom - 2;
    for (int i = 0; i < CountCom; i++)
    {
        tree* commandNode = &(*root_data.get())[0][paths.cmdIdx][i + CountCom - DeltaCom];
        String commandGuid = FindFirstGuid(commandNode);
        tree* itemNode = commandNode;
        for (size_t p = 0; p < paths.cmdItemPath.size(); p++)
            itemNode = &(*itemNode)[paths.cmdItemPath[p]];
        String NameCom = itemNode->get_value();
        comands.push_back(std::make_unique<TComand>(NameCom, commandGuid));
    }

    // РњР°РєРµС‚С‹
    moxels.clear();
    tree* node_mox = root_data.get();
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


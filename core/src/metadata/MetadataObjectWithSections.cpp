//---------------------------------------------------------------------------

#pragma hdrstop

#include "MetadataObjectWithSections.h"
#include "Common.h"
#include "Class_1CD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace
{
	bool SupportsMetadataObjectModuleKind(ModuleTextKind kind)
	{
		return kind == ModuleTextKind::Unknown
			|| kind == ModuleTextKind::ObjectModule
			|| kind == ModuleTextKind::ManagerModule;
	}

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

MetadataObjectWithSections::MetadataObjectWithSections()
    : BaseMetadataObject()
{
	objectModuleDocument.loaded = false;
	managerModuleDocument.loaded = false;
}

MetadataObjectWithSections::MetadataObjectWithSections(v8catalog* _parent, const String& _guid)
    : BaseMetadataObject(_parent, _guid)
{
	objectModuleDocument.loaded = false;
	managerModuleDocument.loaded = false;
}

MetadataObjectWithSections::MetadataObjectWithSections(v8catalog* _parent, const String& _guid, const String& _name)
    : BaseMetadataObject(_parent, _guid, _name)
{
	objectModuleDocument.loaded = false;
	managerModuleDocument.loaded = false;
}

MetadataObjectWithSections::~MetadataObjectWithSections()
{
}

void MetadataObjectWithSections::initializeFromTreeWithPaths(const MetadataTreePaths& paths)
{
    if (!root_data || !paths.getFormNameFunc) return;

    // Р РµРєРІРёР·РёС‚С‹
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

    // РўР°Р±Р»РёС‡РЅС‹Рµ С‡Р°СЃС‚Рё
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

    // Р¤РѕСЂРјС‹
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
                forms.push_back(std::make_unique<TForm1C>(NameForm, guid_md));
            }
            catch (...)
            {
            }
        }
    }

    // РљРѕРјР°РЅРґС‹
    comands.clear();
    tree* node_att_c = GetNodeByPath(root_data.get(), {0, paths.cmdIdx, 1});
    int CountCom = node_att_c ? node_att_c->get_value().ToIntDef(0) : 0;
    int DeltaCom = CountCom - 2;
    for (int i = 0; i < CountCom; i++)
    {
        try
        {
            tree* commandNode = GetNodeByPath(root_data.get(), {0, paths.cmdIdx, i + CountCom - DeltaCom});
            String commandGuid = FindFirstGuid(commandNode);
            tree* itemNode = GetNodeByPath(commandNode, paths.cmdItemPath);
            if (!itemNode)
                continue;
            String NameCom = itemNode->get_value();
            comands.push_back(std::make_unique<TComand>(NameCom, commandGuid));
        }
        catch (...)
        {
        }
    }

    // РњР°РєРµС‚С‹
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

ModuleTextDocument& MetadataObjectWithSections::GetModuleDocument(ModuleTextKind kind)
{
	return kind == ModuleTextKind::ManagerModule ? managerModuleDocument : objectModuleDocument;
}

void MetadataObjectWithSections::RefreshModuleDocument(ModuleTextKind kind)
{
	if (!SupportsMetadataObjectModuleKind(kind))
		return;

	ModuleTextKind effectiveKind = kind == ModuleTextKind::Unknown ? ModuleTextKind::ObjectModule : kind;
	ModuleTextDocument& document = GetModuleDocument(effectiveKind);

	if (document.loaded && document.location.editable)
		return;

	ModuleTextDocument refreshed = ModuleTextStorage::LoadByMetadataObject(parent, guid, name, effectiveKind);
	if (!document.loaded || refreshed.location.editable)
		document = refreshed;
	document.loaded = true;
}

bool MetadataObjectWithSections::HasEditableModuleText()
{
	return HasEditableModuleText(ModuleTextKind::ObjectModule);
}

String MetadataObjectWithSections::GetEditableModuleText()
{
	return GetEditableModuleText(ModuleTextKind::ObjectModule);
}

void MetadataObjectWithSections::SetEditableModuleText(const String& value)
{
	SetEditableModuleText(ModuleTextKind::ObjectModule, value);
}

bool MetadataObjectWithSections::SaveEditableModuleText(const String& value, String& errorText)
{
	return SaveEditableModuleText(ModuleTextKind::ObjectModule, value, errorText);
}

ModuleTextLocation MetadataObjectWithSections::GetEditableModuleLocation()
{
	return GetEditableModuleLocation(ModuleTextKind::ObjectModule);
}

bool MetadataObjectWithSections::HasEditableModuleText(ModuleTextKind kind)
{
	if (!SupportsMetadataObjectModuleKind(kind))
		return false;

	RefreshModuleDocument(kind);
	ModuleTextDocument& document = GetModuleDocument(kind);
	return !document.text.IsEmpty() || document.location.editable;
}

String MetadataObjectWithSections::GetEditableModuleText(ModuleTextKind kind)
{
	if (!SupportsMetadataObjectModuleKind(kind))
		return L"";

	RefreshModuleDocument(kind);
	return GetModuleDocument(kind).text;
}

void MetadataObjectWithSections::SetEditableModuleText(ModuleTextKind kind, const String& value)
{
	if (!SupportsMetadataObjectModuleKind(kind))
		return;

	RefreshModuleDocument(kind);
	ModuleTextDocument& document = GetModuleDocument(kind);
	document.text = value;
	document.dirty = true;
	document.loaded = true;
}

bool MetadataObjectWithSections::SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText)
{
	if (!SupportsMetadataObjectModuleKind(kind))
	{
		errorText = L"РќРµРїРѕРґРґРµСЂР¶РёРІР°РµРјС‹Р№ РІРёРґ РјРѕРґСѓР»СЏ РґР»СЏ РѕР±СЉРµРєС‚Р° РјРµС‚Р°РґР°РЅРЅС‹С….";
		return false;
	}

	RefreshModuleDocument(kind);
	return ModuleTextStorage::SaveDocument(GetModuleDocument(kind), value, errorText);
}

ModuleTextLocation MetadataObjectWithSections::GetEditableModuleLocation(ModuleTextKind kind)
{
	if (!SupportsMetadataObjectModuleKind(kind))
		return ModuleTextLocation();

	RefreshModuleDocument(kind);
	return GetModuleDocument(kind).location;
}


//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "ChartOfCharacteristicTypes.h"
#include "ModuleTextStorage.h"
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

__fastcall TChartOfCharacteristicTypes::TChartOfCharacteristicTypes():BaseMetadataObject()
{
}

__fastcall TChartOfCharacteristicTypes::TChartOfCharacteristicTypes(v8catalog *_parent, const String &_guid) : BaseMetadataObject(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TChartOfCharacteristicTypes::TChartOfCharacteristicTypes(v8catalog *_parent, const String &_guid, const String &_name) : BaseMetadataObject(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

__fastcall TChartOfCharacteristicTypes::~TChartOfCharacteristicTypes()
{
}

void __fastcall TChartOfCharacteristicTypes::initializeFromTree()
{

	if (!root_data) return;

	auto& attributes = getAttributes();
	// Получаем имена реквизитов
	attributes.clear();
	tree* node_att = root_data.get();

	node_att = &(*node_att)[0][3][1]; // количество элементов
	int CountAtt = node_att->get_value().ToInt();
	int Delta = CountAtt - 2;
	for (int i = 0; i < CountAtt; i++)
	{
		try {
			tree* node_att_att = root_data.get();
			node_att_att = &(*node_att_att)[0][3][i+CountAtt-Delta][0][1][1][1][2];
			String NameAtt = node_att_att->get_value();
			attributes.push_back(std::make_unique<TRequisite>(NameAtt, ""));

		} catch (...) {
		}
	}
	// Получаем табличные части
	auto& tabulars = getTabularSections();
	tabulars.clear();
	tree* node_att_t = root_data.get();
	node_att_t = &(*node_att_t)[0][5][1]; // количество элементов
	int CountAttTab = node_att_t->get_value().ToInt();
	int DeltaTab = CountAttTab - 2;
	for (int i = 0; i < CountAttTab; i++)
	{
		tree* tabularNode = &(*root_data.get())[0][5][i+CountAttTab-DeltaTab];
		tree* node_att_tab = &(*tabularNode)[0][1][5][1][2];
		String NameAttTab = node_att_tab->get_value();
		String GuidAttTab;
		try {
			GuidAttTab = (*tabularNode)[0][1][5][1][1].get_value();
		} catch (...) {
			GuidAttTab = L"";
		}

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

	// Получаем имена форм
	auto& forms = getForms();
	forms.clear();
	tree* node = root_data.get();
	node = &(*node)[0][7][0];

	int CountChild = (node->get_next())->get_value().ToInt();
	tree* curNodeChild = node->get_next();
	while (curNodeChild)
	{
		curNodeChild = curNodeChild->get_next();
		if (curNodeChild)
		{
			String formGuid = curNodeChild->get_value();
			String NameForm = GetNameFormPVH(parent, formGuid);
			forms.push_back(std::make_unique<TForm1C>(NameForm, formGuid));
		}
	}

	// Получаем имена команд
	auto& comands = getCommands();
	comands.clear();
	tree* node_att_c = root_data.get();

	node_att_c = &(*node_att_c)[0][6][1]; // количество элементов

	int CountCom = node_att_c->get_value().ToInt();
	int DeltaCom = CountCom - 2;
	for (int i = 0; i < CountCom; i++)
	{
		tree* commandNode = &(*root_data.get())[0][6][i+CountCom-DeltaCom];
		String commandGuid = FindFirstGuid(commandNode);
		tree* node_com = &(*commandNode)[0][1][3][2][9][2];
		String NameCom = node_com->get_value();
		comands.push_back(std::make_unique<TComand>(NameCom, commandGuid));
	}
	// Получаем макеты
	auto& moxels = getLayouts();
	moxels.clear();
	tree* node_mox = root_data.get();
	node_mox = &(*node_mox)[0][4][0];

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

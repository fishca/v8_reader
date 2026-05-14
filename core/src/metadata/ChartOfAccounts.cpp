//---------------------------------------------------------------------------


#include "Common.h"
#include "ChartOfAccounts.h"
#include "ModuleTextStorage.h"
//---------------------------------------------------------------------------

namespace
{
	String ToVclString(const Utf16String& value)
	{
		return String(reinterpret_cast<const wchar_t*>(value.c_str()));
	}

	Utf16String FindFirstGuid(tree* node)
	{
		if (!node)
		return Utf16String();

		String value = Trim(node->get_value());
		if (ModuleTextStorage::IsGuidLike(V8Utf16FromString(value)))
		return V8Utf16FromString(value);

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			Utf16String found = FindFirstGuid(node->get_subnode(i));
			if (!found.empty())
				return found;
		}

		return Utf16String();
	}
}

TChartOfAccounts::TChartOfAccounts()
	: BaseMetadataObject()
{
	root_data.reset();
}

TChartOfAccounts::TChartOfAccounts(v8catalog *_parent, const Utf16String& _guid)
	: BaseMetadataObject(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfAccounts::TChartOfAccounts(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
	: BaseMetadataObject(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfAccounts::~TChartOfAccounts()
{
}

void TChartOfAccounts::initializeFromTree()
{
	if (!root_data) return;

	// Получаем имена реквизитов
	attributes.clear();
	tree* node_att = root_data.get();

	node_att = &(*node_att)[0][7][1]; // количество элементов
	int CountAtt = node_att->get_value().ToInt();
	int Delta = CountAtt - 2;
	for (int i = 0; i < CountAtt; i++)
	{
		try {
			tree* node_att_att = root_data.get();
			node_att_att = &(*node_att_att)[0][7][i+CountAtt-Delta][0][1][1][1][2];
			String NameAtt = node_att_att->get_value();
			attributes.push_back(std::make_unique<TRequisite>(NameAtt, ""));
		} catch (...) {
		}
	}

	// получаем признаки учета
	accflags.clear();
	tree* node_acc = root_data.get();
	node_acc = &(*node_acc)[0][8][1]; // количество элементов
	int CountAcc = node_acc->get_value().ToInt();
	int DeltaAcc = CountAcc - 2;
	for (int i = 0; i < CountAcc; i++)
	{
		tree* node_acc_acc = root_data.get();
		node_acc_acc = &(*node_acc_acc)[0][8][i+CountAcc-DeltaAcc][0][1][1][1][2];
		String NameAcc = node_acc_acc->get_value();
		accflags.push_back(std::make_unique<TAccountingFlag>(NameAcc, ""));
	}

	// получаем признаки учета субконто
	dimaccflags.clear();
	tree* node_acc_dim = root_data.get();
	node_acc_dim = &(*node_acc_dim)[0][9][1]; // количество элементов
	int CountAcc_dim = node_acc_dim->get_value().ToInt();
	int DeltaAcc_dim = CountAcc_dim - 2;
	for (int i = 0; i < CountAcc_dim; i++)
	{
		tree* node_acc_acc_dim = root_data.get();
		node_acc_acc_dim = &(*node_acc_acc_dim)[0][9][i+CountAcc_dim-DeltaAcc_dim][0][1][1][1][2];
		String NameAcc_dim = node_acc_acc_dim->get_value();
		dimaccflags.push_back(std::make_unique<TDimensionAccountingFlag>(NameAcc_dim, ""));
	}


	// Получаем табличные части
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
		Utf16String guidAttTab;
		try {
			guidAttTab = V8Utf16FromString((*tabularNode)[0][1][5][1][1].get_value());
		} catch (...) {
			guidAttTab.clear();
		}

		auto tabular = std::make_unique<TTabular>(NameAttTab, ToVclString(guidAttTab));
		std::unique_ptr<tree> tabularRootData;
		if (parent && !guidAttTab.empty())
		{
			v8file* tabularFile = parent->GetFile16(guidAttTab);
			if (tabularFile)
				tabularRootData.reset(get_treeFromV8file(tabularFile));
		}

		tabular->initializeFromTree(tabularRootData ? tabularRootData.get() : tabularNode);
		tabulars.push_back(std::move(tabular));
	}

	// Получаем имена форм
	forms.clear();
	tree* node = root_data.get();
	node = &(*node)[0][6][0];

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
	comands.clear();
	tree* node_att_c = root_data.get();

	node_att_c = &(*node_att_c)[0][3][1]; // количество элементов

	int CountCom = node_att_c->get_value().ToInt();
	int DeltaCom = CountCom - 2;
	for (int i = 0; i < CountCom; i++)
	{
		tree* commandNode = &(*root_data.get())[0][3][i+CountCom-DeltaCom];
		Utf16String commandGuid = FindFirstGuid(commandNode);
		tree* node_com = &(*commandNode)[0][1][3][2][9][2];
		String NameCom = node_com->get_value();
		comands.push_back(std::make_unique<TComand>(NameCom, ToVclString(commandGuid)));
	}
	// Получаем макеты
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







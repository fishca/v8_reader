//---------------------------------------------------------------------------


#include "Common.h"
#include "ChartOfCharacteristicTypes.h"
#include "ModuleTextStorage.h"
//---------------------------------------------------------------------------

namespace
{
Utf16String FindFirstGuid(tree* node)
	{
		if (!node)
		return Utf16String();

		Utf16String value = V8Utf16FromString(Trim(node->get_value()));
		if (ModuleTextStorage::IsGuidLike(value))
		return value;

		for (int i = 0; i < node->get_num_subnode(); i++)
		{
			Utf16String found = FindFirstGuid(node->get_subnode(i));
			if (!found.empty())
				return found;
		}

		return Utf16String();
	}
}

TChartOfCharacteristicTypes::TChartOfCharacteristicTypes():BaseMetadataObject()
{
}

TChartOfCharacteristicTypes::TChartOfCharacteristicTypes(v8catalog *_parent, const Utf16String &_guid) : BaseMetadataObject(_parent, _guid)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfCharacteristicTypes::TChartOfCharacteristicTypes(v8catalog *_parent, const Utf16String &_guid, const Utf16String &_name) : BaseMetadataObject(_parent, _guid, _name)
{
	initializeFromTree();
	root_data.reset();
}

TChartOfCharacteristicTypes::~TChartOfCharacteristicTypes()
{
}

void TChartOfCharacteristicTypes::initializeFromTree()
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
			Utf16String NameAtt = V8Utf16FromString(node_att_att->get_value());
			attributes.push_back(std::make_unique<TRequisite>(NameAtt, u""));

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
		Utf16String NameAttTab = V8Utf16FromString(node_att_tab->get_value());
		Utf16String guidAttTab;
		try {
			guidAttTab = V8Utf16FromString((*tabularNode)[0][1][5][1][1].get_value());
		} catch (...) {
			guidAttTab.clear();
		}

		auto tabular = std::make_unique<TTabular>(NameAttTab, guidAttTab);
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
			Utf16String formGuid = V8Utf16FromString(curNodeChild->get_value());
			Utf16String NameForm = GetNameFormPVH16(parent, formGuid);
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
		Utf16String commandGuid = FindFirstGuid(commandNode);
		tree* node_com = &(*commandNode)[0][1][3][2][9][2];
		Utf16String NameCom = V8Utf16FromString(node_com->get_value());
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
			Utf16String NameMox = GetNameMoxCatalogs16(parent, V8Utf16FromString(curNodeChildMox->get_value()));
			moxels.push_back(std::make_unique<TMoxel>(NameMox, u""));
		}

	}
}







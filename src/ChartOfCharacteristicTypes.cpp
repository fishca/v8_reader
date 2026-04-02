//---------------------------------------------------------------------------

#pragma hdrstop

#include "Common.h"
#include "ChartOfCharacteristicTypes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

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
		tree* node_att_tab = root_data.get();
		node_att_tab = &(*node_att_tab)[0][5][i+CountAttTab-DeltaTab][0][1][5][1][2];
		String NameAttTab = node_att_tab->get_value();
		tabulars.push_back(std::make_unique<TTabular>(NameAttTab, ""));
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
			String NameForm = GetNameFormPVH(parent, curNodeChild->get_value());
			forms.push_back(std::make_unique<TForm1C>(NameForm, ""));
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
		tree* node_com = root_data.get();
		node_com = &(*node_com)[0][6][i+CountCom-DeltaCom][0][1][3][2][9][2];
		String NameCom = node_com->get_value();
		comands.push_back(std::make_unique<TComand>(NameCom, ""));
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

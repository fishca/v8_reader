//---------------------------------------------------------------------------


#include "Common.h"
#include "Enums.h"
//---------------------------------------------------------------------------


TEnums::TEnums()
{
	guid   = u"";
	name   = u"";
	parent = NULL;
}

TEnums::TEnums(v8catalog *_parent, const Utf16String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(_guid)));
}

TEnums::TEnums(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name)
{
	name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data.reset(get_treeFromV8file(parent->GetFile16(_guid)));

	// Получаем значения перечисления
	attributes.clear();
	tree* node_att = root_data.get();

	node_att = &(*node_att)[0][6][1]; // количество элементов
	int CountAtt = node_att->get_value().ToInt();
	int Delta = CountAtt - 2;
	for (int i = 0; i < CountAtt; i++)
	{
		try {
			tree* node_att_att = root_data.get();
			node_att_att = &(*node_att_att)[0][6][i+CountAtt-Delta][0][1][2];
			Utf16String NameAtt = V8Utf16FromString(node_att_att->get_value());
			attributes.push_back(NameAtt);  // здесь уже имена

		} catch (...) {
		}
	}

	// Получаем имена форм
	forms.clear();
	tree* node = root_data.get();
	node = &(*node)[0][3][0];

	int CountChild = (node->get_next())->get_value().ToInt();
	tree* curNodeChild = node->get_next();
	while (curNodeChild)
	{
		curNodeChild = curNodeChild->get_next();
		if (curNodeChild)
		{
			Utf16String NameForm = V8Utf16FromString(GetNameFormCatalogs(parent, curNodeChild->get_value()));
			forms.push_back(NameForm);  // здесь уже имена
		}
	}

	// Получаем имена команд
	comands.clear();
	tree* node_att_c = root_data.get();

	node_att_c = &(*node_att_c)[0][5][1]; // количество элементов

	int CountCom = node_att_c->get_value().ToInt();
	int DeltaCom = CountCom - 2;
	for (int i = 0; i < CountCom; i++)
	{
		tree* node_com = root_data.get();
		node_com = &(*node_com)[0][5][i+CountCom-DeltaCom][0][1][3][2][9][2];
		Utf16String NameCom = V8Utf16FromString(node_com->get_value());
		comands.push_back(NameCom);  // здесь уже имена
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
			Utf16String NameMox = V8Utf16FromString(GetNameMoxCatalogs(parent, curNodeChildMox->get_value()));
			moxels.push_back(NameMox);  // здесь уже имена
		}

	}

}

TEnums::~TEnums()
{

}


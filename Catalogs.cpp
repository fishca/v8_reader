//---------------------------------------------------------------------------

#pragma hdrstop

#include "Catalogs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

__fastcall TCatalogs::TCatalogs()
{
	guid   = "";
	name   = "";
	parent = NULL;
}


__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid)
{
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));
}

String GetNameFormCatalogs(v8catalog *cf, String &guid_md)
{
	String Result = "";
	v8file *filedata = cf->GetFile(guid_md);
	if(!filedata)
	{
		return Result;
	}
	tree* tree_md = get_treeFromV8file(filedata);
	if(!tree_md)
	{
		return Result;
	}
	tree* node = tree_md;

	node = &(*node)[0][1][1][1][2]; // guid подсистемы

	Result = node->get_value(); // имя подсистемы

	return Result;
}

String GetNameMoxCatalogs(v8catalog *cf, String &guid_md)
{
	String Result = "";
	v8file *filedata = cf->GetFile(guid_md);
	if(!filedata)
	{
		return Result;
	}
	tree* tree_md = get_treeFromV8file(filedata);
	if(!tree_md)
	{
		return Result;
	}
	tree* node = tree_md;

	node = &(*node)[0][1][2][2]; // guid подсистемы

	Result = node->get_value(); // имя подсистемы

	return Result;
}


String GetNameFormAtt(v8catalog *cf, String &guid_md)
{
	String Result = "";
	v8file *filedata = cf->GetFile(guid_md);
	if(!filedata)
	{
		return Result;
	}
	tree* tree_md = get_treeFromV8file(filedata);
	if(!tree_md)
	{
		return Result;
	}
	tree* node = tree_md;

	node = &(*node)[0][1][1][1][2]; // guid подсистемы

	Result = node->get_value(); // имя подсистемы

	return Result;
}



__fastcall TCatalogs::TCatalogs(v8catalog *_parent, const String& _guid, const String& _name)
{
	name      = _name;
	guid      = _guid;
	parent    = _parent;
	root_data = get_treeFromV8file(parent->GetFile(_guid));

	// Получаем имена реквизитов
	attributes.clear();
	tree* node_att = root_data;

	node_att = &(*node_att)[0][6][1]; // количество элементов

	int CountAtt = node_att->get_value().ToInt();
	for (int i = 0; i < CountAtt; i++)
	{
		tree* node_att_att = root_data;
		node_att_att = &(*node_att_att)[0][6][i+CountAtt-1][0][1][1][1][2];
		String NameAtt = node_att_att->get_value();
		attributes.push_back(NameAtt);  // здесь уже имена

	}
	// Получаем табличные части
	tabulars.clear();
	tree* node_att_t = root_data;

	node_att_t = &(*node_att_t)[0][5][1]; // количество элементов

	int CountAttTab = node_att_t->get_value().ToInt();
	for (int i = 0; i < CountAttTab; i++)
	{
		tree* node_att_tab = root_data;
		node_att_tab = &(*node_att_tab)[0][5][i+CountAttTab-1][0][1][5][1][2];
		String NameAttTab = node_att_tab->get_value();
		tabulars.push_back(NameAttTab);  // здесь уже имена

	}
	// Получаем имена форм
	forms.clear();
	tree* node = root_data;
	node = &(*node)[0][7][0];

	int CountChild = (node->get_next())->get_value().ToInt();
	tree* curNodeChild = node->get_next();
	while (curNodeChild)
	{
		curNodeChild = curNodeChild->get_next();
		if (curNodeChild)
		{
			String NameForm = GetNameFormCatalogs(parent, curNodeChild->get_value());
			forms.push_back(NameForm);  // здесь уже имена
		}

	}
	// Получаем имена команд
	comands.clear();
	tree* node_att_c = root_data;

	node_att_c = &(*node_att_c)[0][4][1]; // количество элементов

	int CountCom = node_att_c->get_value().ToInt();
	for (int i = 0; i < CountCom; i++)
	{
		tree* node_com = root_data;
		node_com = &(*node_com)[0][4][i+CountCom-2][0][1][3][2][9][2];
		String NameCom = node_com->get_value();
		comands.push_back(NameCom);  // здесь уже имена
	}
    // Получаем макеты
	moxels.clear();
	tree* node_mox = root_data;
	node_mox = &(*node_mox)[0][3][0];

	int CountMox = (node_mox->get_next())->get_value().ToInt();
	tree* curNodeChildMox = node_mox->get_next();
	while (curNodeChildMox)
	{
		curNodeChildMox = curNodeChildMox->get_next();
		if (curNodeChildMox)
		{
			String NameMox = GetNameMoxCatalogs(parent, curNodeChildMox->get_value());
			moxels.push_back(NameMox);  // здесь уже имена
		}

	}



}

__fastcall TCatalogs::~TCatalogs()
{

}


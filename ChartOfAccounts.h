//---------------------------------------------------------------------------

#ifndef ChartOfAccountsH
#define ChartOfAccountsH
//---------------------------------------------------------------------------
#include <vector>
#include "Class_1CD.h"
#include "APIcfBase.h"
#include "Parse_tree.h"
#include "MDObject.h"
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"

class TChartOfAccounts : public TObject
{
public:
	tree*  root_data;
	v8catalog* parent;

	String name;
	String guid;

	std::vector<std::unique_ptr<TRequisite>> attributes;    // список реквизитов
	std::vector<std::unique_ptr<TAccountingFlag>> accflags; // список признаков учета
	std::vector<std::unique_ptr<TDimensionAccountingFlag>> dimaccflags; // список признаков учета субконто
	std::vector<std::unique_ptr<TComand>> comands;          // список команд
	std::vector<std::unique_ptr<TMoxel>> moxels;            // список макетов
	std::vector<std::unique_ptr<TTabular>> tabulars;        // список табличных частей
	std::vector<std::unique_ptr<TForm1C>> forms;            // список форм

	__fastcall TChartOfAccounts();
	__fastcall TChartOfAccounts(v8catalog *_parent, const String& _guid);
	__fastcall TChartOfAccounts(v8catalog *_parent, const String& _guid, const String& _name);

	__fastcall ~TChartOfAccounts();
};

#endif

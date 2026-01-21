//---------------------------------------------------------------------------

#ifndef ChartOfCharacteristicTypesH
#define ChartOfCharacteristicTypesH
//---------------------------------------------------------------------------
#include <vector>
#include "Class_1CD.h"
#include "APIcfBase.h"
#include "Parse_tree.h"

//---------------------------------------------------------------------------
class TChartOfCharacteristicTypes : public TObject
{
public:

	tree*  root_data;
	v8catalog* parent;

	String name;
	String guid;

	std::vector<String> attributes;  // список реквизитов
	std::vector<String> comands;     // список команд
	std::vector<String> moxels;      // список макетов
	std::vector<String> tabulars;    // список табличных частей
	std::vector<String> forms;       // список форм
	/* TODO : Реализовать класс */
	__fastcall TChartOfCharacteristicTypes();
	__fastcall TChartOfCharacteristicTypes(v8catalog *_parent, const String& _guid);
	__fastcall TChartOfCharacteristicTypes(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TChartOfCharacteristicTypes();
};

#endif

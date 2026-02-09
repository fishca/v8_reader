//---------------------------------------------------------------------------

#ifndef ChartOfCharacteristicTypesH
#define ChartOfCharacteristicTypesH
//---------------------------------------------------------------------------
#include <vector>
#include "Class_1CD.h"
#include "APIcfBase.h"
#include "Parse_tree.h"
#include "BaseMetadataObject.h"

//---------------------------------------------------------------------------
class TChartOfCharacteristicTypes : public BaseMetadataObject
{
private:
	std::vector<std::unique_ptr<TRequisite>> attributes; // список реквизитов
	std::vector<std::unique_ptr<TComand>> comands;       // список команд
	std::vector<std::unique_ptr<TMoxel>> moxels;         // список макетов
	std::vector<std::unique_ptr<TTabular>> tabulars;     // список табличных частей
	std::vector<std::unique_ptr<TForm1C>> forms;         // список форм

public:
	/* TODO : Реализовать класс */
	__fastcall TChartOfCharacteristicTypes();
	__fastcall TChartOfCharacteristicTypes(v8catalog *_parent, const String& _guid);
	__fastcall TChartOfCharacteristicTypes(v8catalog *_parent, const String& _guid, const String& _name);
	__fastcall ~TChartOfCharacteristicTypes();

	// Реализация виртуальных методов
	virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
	virtual std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
	virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
	virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
	virtual std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	virtual void __fastcall initializeFromTree() override;

	void SetName();
	void SetGUID();
};

#endif

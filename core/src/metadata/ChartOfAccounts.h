//---------------------------------------------------------------------------

#ifndef ChartOfAccountsH
#define ChartOfAccountsH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "MDObject.h"
#include "BaseMetadataObject.h"
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"

class TChartOfAccounts : public BaseMetadataObject
{
public:
	std::vector<std::unique_ptr<TRequisite>> attributes;    // список реквизитов
	std::vector<std::unique_ptr<TAccountingFlag>> accflags; // список признаков учета
	std::vector<std::unique_ptr<TDimensionAccountingFlag>> dimaccflags; // список признаков учета субконто
	std::vector<std::unique_ptr<TComand>> comands;          // список команд
	std::vector<std::unique_ptr<TMoxel>> moxels;            // список макетов
	std::vector<std::unique_ptr<TTabular>> tabulars;        // список табличных частей
	std::vector<std::unique_ptr<TForm1C>> forms;            // список форм

	TChartOfAccounts();
	TChartOfAccounts(v8catalog *_parent, const String& _guid);
	TChartOfAccounts(v8catalog *_parent, const String& _guid, const String& _name);

	virtual ~TChartOfAccounts();

	// Реализация виртуальных методов BaseMetadataObject
	virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
	virtual std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
	virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
	virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
	virtual std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	virtual void initializeFromTree() override;
};

#endif


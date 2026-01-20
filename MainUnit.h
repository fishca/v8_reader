//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "VirtualTrees.hpp"
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.VirtualImageList.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ExtCtrls.hpp>

#include <System.Contnrs.hpp>

#include "guids.h"
#include "MessageRegistration.h"
#include "Parse_tree.h"

class Messager;

struct SubSys
{
	String              name;
	std::vector<String> children;
};

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditNameCF;
	TButton *btnGO;
	TOpenDialog *dlgOpenCF;
	TVirtualStringTree *VirtualStringTreeValue1C;
	TImageList *ImageList1;
	TImageCollection *ImageCollection1;
	TVirtualImageList *VirtualImageList1;
	TStatusBar *StatusBar1;
	TOpenDialog *dlgOpenCatalog;
	TPanel *LeftPanel;
	TSplitter *split1;
	TPanel *rPanel;
	TPageControl *pagesEdit;
	TActionList *ActionList1;
	TAction *ActionOpenCF;
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TTabSheet *TabModuleObject;
	TTabSheet *TabModuleManager;
	TMemo *MemoObject;
	TMemo *МemoManager;
	TListView *ListViewMessager;
	TSplitter *Splitter1;
	TTabSheet *TabSheet1;
	void __fastcall btnOpenEditNameClick(TObject *Sender);
	void __fastcall btnGOClick(TObject *Sender);
	void __fastcall VirtualStringTreeValue1CInitNode(TBaseVirtualTree *Sender, PVirtualNode ParentNode,
		  PVirtualNode Node, TVirtualNodeInitStates &InitialStates);
	void __fastcall VirtualStringTreeValue1CGetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall VirtualStringTreeValue1CFreeNode(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall VirtualStringTreeValue1CGetImageIndex(TBaseVirtualTree *Sender, PVirtualNode Node, TVTImageKind Kind, TColumnIndex Column,
		  bool &Ghosted, TImageIndex &ImageIndex);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ActionFileOpenExecute(TObject *Sender);
	void __fastcall ActionOpenCFExecute(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);


private:	// User declarations
	Messager* mess; // регистратор сообщений
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void __fastcall TreeInit();
	void __fastcall	FillVirtualTree();
	void __fastcall FillTreeMD(PVirtualNode parentNode, TObjectList *mdData, const String& md_name, int imgIndex);
	String ConfigName;

	std::vector<String> Catalogs;
	TObjectList *mdCatalogs;

	std::vector<String> Commonss;
	TObjectList *mdCommonss;

	std::vector<String> Languages;
	TObjectList *mdLanguages;

	std::vector<String> AccumulationRegisters;
	TObjectList *mdAccumulationRegisters;

	std::vector<String> AccountingRegisters;
	TObjectList *mdAccountingRegisters;

	std::vector<String> CalculationRegisters;
	TObjectList *mdCalculationRegisters;

	std::vector<String> BusinessProcesses;
	TObjectList *mdBusinessProcesses;

	std::vector<String> ChartsOfCharacteristicTypes;
	TObjectList *mdChartsOfCharacteristicTypes;

	std::vector<String> CommandGroups;
	TObjectList *mdCommandGroups;

	std::vector<String> CommonAttributes;
	TObjectList *mdCommonAttributes;

	std::vector<String> CommonCommands;
	TObjectList *mdCommonCommands;


	std::vector<String> CommonForms;
	TObjectList *mdCommonForms;

	std::vector<String> CommonModules;
	TObjectList *mdCommonModules;

	std::vector<String> CommonPictures;
	TObjectList *mdCommonPictures;

	std::vector<String> CommonTemplates;
	TObjectList *mdCommonTemplates;

	std::vector<String> Constants;
	TObjectList *mdConstants;

	std::vector<String> DataProcessors;
	TObjectList *mdDataProcessors;

	std::vector<String> DefinedTypes;
	TObjectList *mdDefinedTypes;

	std::vector<String> DocumentJournals;
	TObjectList *mdDocumentJournals;

	std::vector<String> DocumentNumerators;
	TObjectList *mdDocumentNumerators;

	std::vector<String> Documents;
	TObjectList *mdDocuments;

	std::vector<String> Enums;
	TObjectList *mdEnums;

	std::vector<String> EventSubscriptions;
	TObjectList *mdEventSubscriptions;

	std::vector<String> ExchangePlans;
	TObjectList *mdExchangePlans;

	std::vector<String> ChartOfAccounts;
	TObjectList *mdChartOfAccounts;

	std::vector<String> ChartOfCalculationTypes;
	TObjectList *mdChartOfCalculationTypes;

	std::vector<String> ExternalDataSources;
	TObjectList *mdExternalDataSources;

	std::vector<String> FilterCriteria;
	TObjectList *mdFilterCriteria;

	std::vector<String> FunctionalOptions;
	TObjectList *mdFunctionalOptions;

	std::vector<String> FunctionalOptionsParameters;
	TObjectList *mdFunctionalOptionsParameters;

	std::vector<String> HTTPServices;
	TObjectList *mdHTTPServices;

	std::vector<String> InformationRegisters;
	TObjectList *mdInformationRegisters;

	std::vector<String> Interfaces;
	TObjectList *mdInterfaces;

	std::vector<String> Reports;
	TObjectList *mdReports;

	std::vector<String> Roles;
	TObjectList *mdRoles;

	std::vector<String> Bots;
	TObjectList *mdBots;

	std::vector<String> ScheduledJobs;
	TObjectList *mdScheduledJobs;

	std::vector<String> SessionParameters;
	TObjectList *mdSessionParameters;

	std::vector<String> SettingsStorages;
	TObjectList *mdSettingsStorages;

	std::vector<String> StyleItems;
	TObjectList *mdStyleItems;

	std::vector<String> Styles;
	TObjectList *mdStyles;

	// необходимо хранить иерархию
	std::vector<SubSys> Subsystems;
	TObjectList *mdSubsystems;

	std::vector<String> Tasks;
	TObjectList *mdTasks;

	std::vector<String> WebServices;
	TObjectList *mdWebServices;

	std::vector<String> WSReferences;
	TObjectList *mdWSReferences;

	std::vector<String> XDTOPackages;
	TObjectList *mdXDTOPackages;

	std::vector<String> IntegrationServices;
	TObjectList *mdIntegrationServices;

	std::vector<String> Sequences;
	TObjectList *mdSequences;

	v8catalog *GlobalCF;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------

class Messager : public MessageRegistrator
{
private:
	TListView* ListView;
	TStatusBar* StatusBar;
	String logfile;
	TFormatSettings FormatSettings;
public:
	__fastcall Messager(TListView* lv, TStatusBar* sb);
	void __fastcall setlogfile(String _logfile);
	virtual void __fastcall AddMessage(const String& message, const MessageState mstate, TStringList* param = NULL);
	virtual void __fastcall Status(const String& message);
};


struct VirtualTreeData
{
	String Name;
	int Age;
    int ImgIndex;
};

void get_cf_name(v8catalog* cf, Messager* mess);
void get_cf_name(tree* tr,      Messager* mess);

#endif

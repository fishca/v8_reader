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
	String ConfigName;
	std::vector<String> Catalogs;
	std::vector<String> Languages;
	std::vector<String> AccumulationRegisters;
	std::vector<String> AccountingRegisters;
	std::vector<String> CalculationRegisters;
	std::vector<String> BusinessProcesses;

	std::vector<String> ChartsOfCharacteristicTypes;
	std::vector<String> CommandGroups;
	std::vector<String> CommonAttributes;
	std::vector<String> CommonCommands;
	std::vector<String> CommonForms;
	std::vector<String> CommonModules;
	std::vector<String> CommonPictures;
	std::vector<String> CommonTemplates;
	std::vector<String> Constants;
	std::vector<String> DataProcessors;
	std::vector<String> DefinedTypes;
	std::vector<String> DocumentJournals;
	std::vector<String> DocumentNumerators;
	std::vector<String> Documents;
	std::vector<String> Enums;
	std::vector<String> EventSubscriptions;
	std::vector<String> ExchangePlans;
	std::vector<String> ChartOfAccounts;
	std::vector<String> ChartOfCalculationTypes;
	std::vector<String> ExternalDataSources;
	std::vector<String> FilterCriteria;
	std::vector<String> FunctionalOptions;
	std::vector<String> FunctionalOptionsParameters;
	std::vector<String> HTTPServices;
	std::vector<String> InformationRegisters;
	std::vector<String> Interfaces;

	std::vector<String> Reports;
	std::vector<String> Roles;
	std::vector<String> Bots;
	std::vector<String> ScheduledJobs;
	std::vector<String> SessionParameters;
	std::vector<String> SettingsStorages;
	std::vector<String> StyleItems;
	std::vector<String> Styles;

	// необходимо хранить иерархию
	std::vector<SubSys> Subsystems;

	std::vector<String> Tasks;
	std::vector<String> WebServices;
	std::vector<String> WSReferences;
	std::vector<String> XDTOPackages;
	std::vector<String> IntegrationServices;
	std::vector<String> Sequences;



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

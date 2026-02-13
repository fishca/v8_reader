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
#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynMemo.hpp"

#include <memory>

#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"
#include "Enums.h"



#include "guids.h"
#include "MessageRegistration.h"
#include "MetaDataManager.h"
#include "Parse_tree.h"
#include "SmartPointers.h"
#include "SynEdit.hpp"
#include "SynMemo.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"

class Messager;

struct SubSys
{
	String              name;
	std::vector<String> children;
};

struct VirtualTreeData
{
	String Name;
    String text_module;
	int Age;
	int ImgIndex;
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
	TListView *ListViewMessager;
	TSplitter *Splitter1;
	TTabSheet *TabSheet1;
	TSynMemo *MemoObject;
	TSynMemo *MemoManager;
	TPanel *Panel1;
	TSynCppSyn *SynCppSyn1;
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
	void __fastcall VirtualStringTreeValue1CClick(TObject *Sender);


private:	// User declarations
	Messager* mess; // регистратор сообщений
    std::unique_ptr<MetaDataManager> MDManager; // Умный указатель для автоматического управления памятью
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void __fastcall TreeInit();
	void __fastcall	FillVirtualTree();
	void __fastcall FillTreeMD(PVirtualNode parentNode, const MetadataVector<TObject>& mdData, const String& md_name, int imgIndex);
	void __fastcall FillTreeMDConcrete(TVirtualStringTree *tree1C, PVirtualNode parentNode, const MetadataVector<TObject>& mdData, const String& md_name, int imgIndex);
	void __fastcall fillEnumTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, TEnums* CurCat);
	void __fastcall fillCatalogsTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TTabular>>& tabulars,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillJournalTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TTabular>>& tabulars,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillChartAccTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TAccountingFlag>>& accflags,
					const std::vector<std::unique_ptr<TDimensionAccountingFlag>>& dimaccflags,
					const std::vector<std::unique_ptr<TTabular>>& tabulars,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillInformationRegisterTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TRequisite>>& dimensions,
					const std::vector<std::unique_ptr<TRequisite>>& resources,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillAccumulationRegisterTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TRequisite>>& dimensions,
					const std::vector<std::unique_ptr<TRequisite>>& resources,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillAccountingRegisterTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TRequisite>>& dimensions,
					const std::vector<std::unique_ptr<TRequisite>>& resources,
					const std::vector<std::unique_ptr<TAccountingFlag>>& accountingFlags,
					const std::vector<std::unique_ptr<TDimensionAccountingFlag>>& dimensionAccountingFlags,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);
	void __fastcall fillCalculationRegisterTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, String name,
					const std::vector<std::unique_ptr<TRequisite>>& attributes,
					const std::vector<std::unique_ptr<TRequisite>>& dimensions,
					const std::vector<std::unique_ptr<TRequisite>>& resources,
					const std::vector<std::unique_ptr<TForm1C>>& forms,
					const std::vector<std::unique_ptr<TComand>>& comands,
					const std::vector<std::unique_ptr<TMoxel>>& moxels);

	String ConfigName;

	MetadataVector<TObject> mdCatalogs;
	MetadataVector<TObject> mdCommonss;
	MetadataVector<TObject> mdLanguages;
	MetadataVector<TObject> mdAccumulationRegisters;
	MetadataVector<TObject> mdAccountingRegisters;
	MetadataVector<TObject> mdCalculationRegisters;
	MetadataVector<TObject> mdBusinessProcesses;
	MetadataVector<TObject> mdChartsOfCharacteristicTypes;
	MetadataVector<TObject> mdCommandGroups;
	MetadataVector<TObject> mdCommonAttributes;
	MetadataVector<TObject> mdCommonCommands;
	MetadataVector<TObject> mdCommonForms;
	MetadataVector<TObject> mdCommonModules;
	MetadataVector<TObject> mdCommonPictures;
	MetadataVector<TObject> mdCommonTemplates;
	MetadataVector<TObject> mdConstants;
	MetadataVector<TObject> mdDataProcessors;
	MetadataVector<TObject> mdDefinedTypes;
	MetadataVector<TObject> mdDocumentJournals;
	MetadataVector<TObject> mdDocumentNumerators;
	MetadataVector<TObject> mdDocuments;
	MetadataVector<TObject> mdEnums;
	MetadataVector<TObject> mdEventSubscriptions;
	MetadataVector<TObject> mdExchangePlans;
	MetadataVector<TObject> mdChartOfAccounts;
	MetadataVector<TObject> mdChartOfCalculationTypes;
	MetadataVector<TObject> mdExternalDataSources;
	MetadataVector<TObject> mdFilterCriteria;
	MetadataVector<TObject> mdFunctionalOptions;
	MetadataVector<TObject> mdFunctionalOptionsParameters;
	MetadataVector<TObject> mdHTTPServices;
	MetadataVector<TObject> mdInformationRegisters;
	MetadataVector<TObject> mdInterfaces;
	MetadataVector<TObject> mdReports;
	MetadataVector<TObject> mdRoles;
	MetadataVector<TObject> mdBots;
	MetadataVector<TObject> mdScheduledJobs;
	MetadataVector<TObject> mdSessionParameters;
	MetadataVector<TObject> mdSettingsStorages;
	MetadataVector<TObject> mdStyleItems;
	MetadataVector<TObject> mdStyles;
	std::vector<SubSys> Subsystems;
	MetadataVector<TObject> mdSubsystems;
	MetadataVector<TObject> mdTasks;
	MetadataVector<TObject> mdWebServices;
	MetadataVector<TObject> mdWSReferences;
	MetadataVector<TObject> mdXDTOPackages;
	MetadataVector<TObject> mdIntegrationServices;
	MetadataVector<TObject> mdSequences;

	std::unique_ptr<v8catalog> GlobalCF;
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



void get_cf_name(v8catalog* cf, Messager* mess);
void get_cf_name(tree* tr,      Messager* mess);

#endif

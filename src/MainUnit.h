//---------------------------------------------------------------------------

#ifndef MainUnitH
#define MainUnitH
//---------------------------------------------------------------------------
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
#include <Vcl.Graphics.hpp>
#include <Vcl.Skia.hpp>
#include "SynEdit.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynEditCodeFolding.hpp"
#include "SynHighlighterGeneral.hpp"
#include "SynMemo.hpp"
#include "SynHighlighter1C.h"
#include "ModuleTextStorage.h"
#include "VirtualTreeData.h"

#include <memory>
#include <unordered_map>

#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"
#include "Enums.h"
#include "BaseMetadataObject.h"



#include "guids.h"
#include "../core/src/MessageRegistration.h"
#include "MetaDataManager.h"
#include "Parse_tree_vcl_adapter.h"
#include "SmartPointers.h"
#include "SynEdit.hpp"
#include "SynMemo.hpp"
#include "SynEditHighlighter.hpp"
#include "SynHighlighterCpp.hpp"
#include "SynEditCodeFolding.hpp"
#include "SynHighlighterGeneral.hpp"
#include "SynHighlighter1C.h"

class Messager;
class v8catalog;

struct SubSys
{
	String              name;
	std::vector<String> children;
};

struct ModuleEditorTabState
{
	TTabSheet* tab = nullptr;
	TSynMemo* memo = nullptr;
	String key;
	String title;
	PVirtualNode node = nullptr;
	BaseMetadataObject* metadataObject = nullptr;
	ModuleTextKind kind = ModuleTextKind::Unknown;
	ModuleTextDocument standaloneDocument;
	bool standalone = false;
	bool dirty = false;
	String originalText;
	ModuleTextLocation location;
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
	TProgressBar *LoadProgressBar;
	TSynCppSyn *SynCppSyn1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TAction *ActionSaveCF;
	TAction *ActionSaveModule;
	TMenuItem *N6;
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
	void __fastcall VirtualStringTreeValue1CChange(TBaseVirtualTree *Sender, PVirtualNode Node);
	void __fastcall VirtualStringTreeValue1CNodeClick(TBaseVirtualTree *Sender, const THitInfo &HitInfo);
	void __fastcall VirtualStringTreeValue1CFocusChanged(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column);
	void __fastcall ModuleMemoScanForFoldRanges(TObject *Sender, TSynFoldRanges *FoldRanges,
		  TStrings *LinesToScan, int FromLine, int ToLine);
	void __fastcall ModuleSelectionTimerTimer(TObject *Sender);
	void __fastcall N4Click(TObject *Sender);
	void __fastcall ActionSaveCFExecute(TObject *Sender);
	void __fastcall MemoObjectChange(TObject *Sender);
	void __fastcall ActionSaveModuleExecute(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);


private:	// User declarations
	Messager* mess; // регистратор сообщений
	TSyn1CSyn *Syn1CSyn;
	TSynGeneralSyn *ModuleGeneralSyn;
	TTabSheet *HighlightSettingsTab;
	TColorBox *HighlightKeywordColorBox;
	TColorBox *HighlightCommentColorBox;
	TColorBox *HighlightStringColorBox;
	TColorBox *HighlightNumberColorBox;
	TColorBox *HighlightPreprocessorColorBox;
	TColorBox *HighlightSymbolColorBox;
	TColorBox *HighlightAnnotationColorBox;
	TCheckBox *HighlightKeywordBoldCheckBox;
	TCheckBox *HighlightCommentItalicCheckBox;
	TCheckBox *UnpackCheckBox;
	TImage *CommonPicturePreviewImage;
	TSkSvg *CommonPicturePreviewSvg;
	TScrollBox *CommonPicturePreviewScrollBox;
	TLabel *CommonPicturePreviewInfoLabel;

	TSynMemo *HighlightPreviewMemo;
	TPopupMenu *ConfigurationPopupMenu;
	TMenuItem *ConstantsModulesMenuItem;
	TMenuItem *OpenConstantsManagerModuleMenuItem;
	TMenuItem *OpenConstantsValueManagerModuleMenuItem;
	TMenuItem *OpenApplicationModuleMenuItem;
	TMenuItem *OpenSessionModuleMenuItem;
	TMenuItem *OpenExternalConnectionModuleMenuItem;
	bool HighlightSettingsLoading;
	TTimer *ModuleSelectionTimer;
	PVirtualNode LastModuleNodeShown;
	PVirtualNode PendingModuleNode;
	PVirtualNode CurrentModuleNode;
	BaseMetadataObject* CurrentModuleObject;
	bool LoadingModuleText;
	bool CurrentModuleDirty;
	String CurrentModuleOriginalText;
	ModuleTextLocation CurrentModuleLocation;
	ModuleTextKind CurrentModuleKind;
	ModuleTextDocument CurrentStandaloneModuleDocument;
	bool CurrentModuleStandalone;
	bool SwitchingModuleTab;
	std::unordered_map<TTabSheet*, ModuleEditorTabState> ModuleTabs;
    std::unique_ptr<MetaDataManager> MDManager; // Умный указатель для автоматического управления памятью
	void CreateHighlightSettingsTab();
	void ApplyHighlightSettings();
	void LoadHighlightSettings();
	void SaveHighlightSettings();
	void SetDefaultHighlightSettingsControls();
	void __fastcall HighlightSettingsChanged(TObject *Sender);
	void __fastcall ResetHighlightSettingsClick(TObject *Sender);
	void ScheduleMetadataNodeText(PVirtualNode Node);
	void ShowMetadataNodeText(PVirtualNode Node);
	void EnsureCommonPicturePreviewControls();
	void CenterCommonPicturePreviewContent();
	void ClearCommonPicturePreview(const String& statusText);
	bool ShowCommonPicturePreviewForNode(VirtualTreeData* data);
	void __fastcall CommonPicturePreviewScrollBoxResize(TObject *Sender);
	void ShowConfigurationModule(ModuleTextKind kind, const String& caption);
	void ShowConstantsModule(ModuleTextKind kind, const String& caption);
	void __fastcall ConfigurationPopupMenuPopup(TObject *Sender);
	void __fastcall OpenConfigurationModuleMenuItemClick(TObject *Sender);
	void __fastcall OpenConstantsModuleMenuItemClick(TObject *Sender);
	void __fastcall VirtualStringTreeValue1CMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	bool SaveCurrentModuleTextIfNeeded(bool forcePrompt);
	bool FlushCurrentModuleBeforeBuild();
	void SetModuleEditorState(BaseMetadataObject* metadataObject, PVirtualNode node, const String& text, ModuleTextKind kind);
	String BuildModuleTabKey(PVirtualNode node, BaseMetadataObject* metadataObject, const String& moduleItemGuid, ModuleTextKind kind) const;
	TTabSheet* FindModuleTabByKey(const String& key) const;
	TTabSheet* CreateModuleTab(const String& key, const String& title);
	String BuildModuleTabTitle(const String& objectName, ModuleTextKind kind, const String& fallbackTitle) const;
	ModuleEditorTabState* GetModuleTabStateByMemo(TObject* sender);
	ModuleEditorTabState* GetActiveModuleTabState();
	void ActivateModuleTab(TTabSheet* tab);
	void PopulateModuleTab(ModuleEditorTabState& state, const String& text);
	bool SaveModuleTabIfNeeded(ModuleEditorTabState& state, bool forcePrompt);
	void SyncCurrentModuleFromTab(const ModuleEditorTabState* state);
	void __fastcall PagesEditChange(TObject *Sender);
	bool IsConstantsContextNode(PVirtualNode node) const;
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);
	void ResetLoadProgress(int maxValue, const String& statusText = L"");
	void AdvanceLoadProgress(const String& statusText);
	void CompleteLoadProgress(const String& statusText);
	void TreeInit();
	void FillVirtualTree();
	void FillTreeMD(PVirtualNode parentNode, const MetadataVector<MetadataEntity>& mdData, const String& md_name, int imgIndex);
	void FillTreeMDConcrete(TVirtualStringTree *tree1C, PVirtualNode parentNode, const MetadataVector<MetadataEntity>& mdData, const String& md_name, int imgIndex);


	String ConfigName;

	MetadataVector<MetadataEntity> mdCatalogs;
	MetadataVector<MetadataEntity> mdCommonss;
	MetadataVector<MetadataEntity> mdLanguages;
	MetadataVector<MetadataEntity> mdAccumulationRegisters;
	MetadataVector<MetadataEntity> mdAccountingRegisters;
	MetadataVector<MetadataEntity> mdCalculationRegisters;
	MetadataVector<MetadataEntity> mdBusinessProcesses;
	MetadataVector<MetadataEntity> mdChartsOfCharacteristicTypes;
	MetadataVector<MetadataEntity> mdCommandGroups;
	MetadataVector<MetadataEntity> mdCommonAttributes;
	MetadataVector<MetadataEntity> mdCommonCommands;
	MetadataVector<MetadataEntity> mdCommonForms;
	MetadataVector<MetadataEntity> mdCommonModules;
	MetadataVector<MetadataEntity> mdCommonPictures;
	MetadataVector<MetadataEntity> mdCommonTemplates;
	MetadataVector<MetadataEntity> mdConstants;
	MetadataVector<MetadataEntity> mdDataProcessors;
	MetadataVector<MetadataEntity> mdDefinedTypes;
	MetadataVector<MetadataEntity> mdDocumentJournals;
	MetadataVector<MetadataEntity> mdDocumentNumerators;
	MetadataVector<MetadataEntity> mdDocuments;
	MetadataVector<MetadataEntity> mdEnums;
	MetadataVector<MetadataEntity> mdEventSubscriptions;
	MetadataVector<MetadataEntity> mdExchangePlans;
	MetadataVector<MetadataEntity> mdChartOfAccounts;
	MetadataVector<MetadataEntity> mdChartOfCalculationTypes;
	MetadataVector<MetadataEntity> mdExternalDataSources;
	MetadataVector<MetadataEntity> mdFilterCriteria;
	MetadataVector<MetadataEntity> mdFunctionalOptions;
	MetadataVector<MetadataEntity> mdFunctionalOptionsParameters;
	MetadataVector<MetadataEntity> mdHTTPServices;
	MetadataVector<MetadataEntity> mdInformationRegisters;
	MetadataVector<MetadataEntity> mdInterfaces;
	MetadataVector<MetadataEntity> mdReports;
	MetadataVector<MetadataEntity> mdRoles;
	MetadataVector<MetadataEntity> mdBots;
	MetadataVector<MetadataEntity> mdScheduledJobs;
	MetadataVector<MetadataEntity> mdSessionParameters;
	MetadataVector<MetadataEntity> mdSettingsStorages;
	MetadataVector<MetadataEntity> mdStyleItems;
	MetadataVector<MetadataEntity> mdStyles;
	//std::vector<SubSys> Subsystems;  - возможно надо удалить, т.к. лишнее уже
	MetadataVector<MetadataEntity> mdSubsystems;
	MetadataVector<MetadataEntity> mdTasks;
	MetadataVector<MetadataEntity> mdWebServices;
	MetadataVector<MetadataEntity> mdWSReferences;
	MetadataVector<MetadataEntity> mdWebSocketClients;
	MetadataVector<MetadataEntity> mdXDTOPackages;
	MetadataVector<MetadataEntity> mdIntegrationServices;
	MetadataVector<MetadataEntity> mdSequences;

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
	bool uiMessagesEnabled;
	bool fileLoggingEnabled;
public:
	Messager(TListView* lv, TStatusBar* sb);
	using MessageRegistrator::AddMessage;
	using MessageRegistrator::Status;
	void setUiMessagesEnabled(bool enabled);
	bool getUiMessagesEnabled() const;
	void setFileLoggingEnabled(bool enabled);
	bool getFileLoggingEnabled() const;
	void setlogfile(String _logfile);
	String getlogfile() const;
	virtual void AddMessageCore(const Utf16String& message, const MessageState mstate, const MessageParams* param = nullptr) override;
	virtual void StatusCore(const Utf16String& message) override;
};

#endif


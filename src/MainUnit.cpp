//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <System.IOUtils.hpp>

#include <windows.h>

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "V8File.h"
#include "ApicfBase.h"
#include "Class_1CD.h"
#include "CommonModules.h"
#include "MainUnit.h"
#include "guids.h"
#include "Catalogs.h"
#include "Documents.h"
#include "Numerators.h"
#include "Sequences.h"
#include "Journals.h"
#include "Enums.h"
#include "Reports.h"
#include "DataProcessors.h"
#include "ChartOfCharacteristicTypes.h"
#include "ChartOfAccounts.h"
#include "ChartOfCalculationTypes.h"
#include "InformationRegisters.h"
#include "AccumulationRegisters.h"
#include "AccountingRegisters.h"
#include "CalculationRegisters.h"
#include "BusinessProceses.h"
#include "Tasks.h"
#include "SessionParameters.h"
#include "EventSubscriptions.h"
#include "Roles.h"
#include "CommonCommands.h"
#include "TConstants.h"
#include "CommonPictures.h"
#include "CommandGroups.h"
#include "CommonForms.h"
#include "Interfaces.h"
#include "ExternalDataSources.h"
#include "CommonAttributes.h"
#include "ExchangePlans.h"
#include "FilterCriteria.h"
#include "ScheduledJobs.h"
#include "Bots.h"
#include "FunctionalOptions.h"
#include "FunctionalOptionsParameters.h"
#include "DefinedTypes.h"
#include "SettingsStorages.h"
#include "XDTOPackages.h"
#include "WebServices.h"
#include "HTTPServices.h"
#include "Langs.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "SynEdit"
#pragma link "SynMemo"
#pragma link "SynEditHighlighter"
#pragma link "SynHighlighterCpp"
#pragma resource "*.dfm"
TMainForm *MainForm;
MessageRegistrator* msreg;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner), MDManager(std::make_unique<MetaDataManager>())
{
	VirtualStringTreeValue1C->NodeDataSize = sizeof(VirtualTreeData);
	mess = new Messager(ListViewMessager, StatusBar1);
	msreg = mess;
	String appDir = ExtractFilePath(ParamStr(0));
	String logfile = TPath::Combine(appDir, "v8reader.log");
	mess->setlogfile(logfile);

	mdCatalogs = new TObjectList(true);
	mdLanguages = new TObjectList(true);
	mdAccumulationRegisters = new TObjectList(true);
	mdAccountingRegisters = new TObjectList(true);
	mdCalculationRegisters = new TObjectList(true);
	mdBusinessProcesses = new TObjectList(true);
	mdChartsOfCharacteristicTypes = new TObjectList(true);
	mdCommandGroups = new TObjectList(true);
	mdCommonAttributes = new TObjectList(true);
	mdCommonCommands = new TObjectList(true);
	mdCommonForms = new TObjectList(true);
	mdCommonModules = new TObjectList(true);
	mdCommonPictures = new TObjectList(true);
	mdCommonTemplates = new TObjectList(true);
	mdConstants = new TObjectList(true);
	mdDataProcessors = new TObjectList(true);
	mdDefinedTypes = new TObjectList(true);
	mdDocumentJournals = new TObjectList(true);
	mdDocumentNumerators = new TObjectList(true);
	mdDocuments = new TObjectList(true);
	mdEnums = new TObjectList(true);
	mdEventSubscriptions = new TObjectList(true);
	mdExchangePlans = new TObjectList(true);
	mdChartOfAccounts = new TObjectList(true);
	mdChartOfCalculationTypes = new TObjectList(true);
	mdExternalDataSources = new TObjectList(true);
	mdFilterCriteria = new TObjectList(true);
	mdFunctionalOptions = new TObjectList(true);
	mdFunctionalOptionsParameters = new TObjectList(true);
	mdHTTPServices = new TObjectList(true);
	mdInformationRegisters = new TObjectList(true);
	mdInterfaces = new TObjectList(true);
	mdReports = new TObjectList(true);
	mdRoles = new TObjectList(true);
	mdBots = new TObjectList(true);
	mdScheduledJobs = new TObjectList(true);
	mdSessionParameters = new TObjectList(true);
	mdSettingsStorages = new TObjectList(true);
	mdStyleItems = new TObjectList(true);
	mdStyles = new TObjectList(true);
	mdSubsystems = new TObjectList(true);
	mdTasks = new TObjectList(true);
	mdWebServices = new TObjectList(true);
	mdWSReferences = new TObjectList(true);
	mdXDTOPackages = new TObjectList(true);
	mdIntegrationServices = new TObjectList(true);
	mdSequences = new TObjectList(true);

}
//---------------------------------------------------------------------------
void __fastcall TMainForm::btnOpenEditNameClick(TObject *Sender)
{
	if (dlgOpenCF->Execute())
	{
		if (FileExists(dlgOpenCF->FileName))
		  EditNameCF->Text = dlgOpenCF->FileName;
		else
		  throw(Exception("File does not exist."));
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::btnGOClick(TObject *Sender)
{
	std::vector<std::string> filter;
	//v8unpack::Parse(AnsiString(EditNameCF->Text).c_str(), AnsiString(editFolderName->Text).c_str(), filter);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::VirtualStringTreeValue1CInitNode(TBaseVirtualTree *Sender,
		  PVirtualNode ParentNode, PVirtualNode Node, TVirtualNodeInitStates &InitialStates)
{
	if(!ParentNode)
	{
		VirtualTreeData* d = (VirtualTreeData*)(Sender->GetNodeData(Node));
		d->Name = "Типы 1С";
		d->Age = 0;
		d->ImgIndex = 72;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CGetText(TBaseVirtualTree *Sender,
	  PVirtualNode Node, TColumnIndex Column, TVSTTextType TextType,
	  UnicodeString &CellText)
{
	VirtualTreeData *NodeData = (VirtualTreeData*)Sender->GetNodeData(Node);
	CellText = NodeData->Name;
	//    switch (Column)
	//    {
	//	case 0:
	//		CellText = NodeData->Name;
	//		break;
	//	case 1:
	//		CellText = IntToStr(NodeData->Age);
	//		break;
	//    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FillTreeMDConcrete(TVirtualStringTree *tree1C, PVirtualNode parentNode, TObjectList *mdData, const String& md_name, int imgIndex)
{
	TObject *CurCat;

	for(int i = 0; i < mdData->Count; i++)
	{
		PVirtualNode childNode = tree1C->AddChild(parentNode);
		VirtualTreeData *childData = (VirtualTreeData*)tree1C->GetNodeData(childNode);
		if (md_name == md_Catalogs)
		{
			CurCat = static_cast<TCatalogs*>(mdData->Items[i]);
		}
		else if(md_name == md_Documents)
		{
			CurCat = static_cast<TDocuments*>(mdData->Items[i]);
		}
		else if(md_name == md_DocumentJournals)
		{
			CurCat = static_cast<TJournals*>(mdData->Items[i]);
		}
		else if(md_name == md_Enums)
		{
			CurCat = static_cast<TEnums*>(mdData->Items[i]);
		}
		else if(md_name == md_Reports)
		{
			CurCat = static_cast<TReports*>(mdData->Items[i]);
		}
		else if(md_name == md_DataProcessors)
		{
			CurCat = static_cast<TDataProcessors*>(mdData->Items[i]);
		}
		else if(md_name == md_ChartsOfCharacteristicTypes)
		{
			CurCat = static_cast<TChartOfCharacteristicTypes*>(mdData->Items[i]);
		}

//		childData->Name = CurCat->GetName();
//		childData->Age = 30;
//		childData->ImgIndex = imgIndex;

//		// Реквизиты
//		PVirtualNode ChildNodeCatAtt = VirtualStringTreeValue1C->AddChild(childNode);
//		VirtualTreeData *ChildNodeDataCatAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatAtt);
//		ChildNodeDataCatAtt->Name = "Реквизиты";
//		ChildNodeDataCatAtt->Age = 30;
//		ChildNodeDataCatAtt->ImgIndex = 83;
//		// Список Реквизитов
//		for (int j = 0; j < CurCat->attributes.size(); j++)
//		{
//			PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
//			VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
//			ChildNodeDataCatCurAtt->Name = CurCat->attributes[j];
//			ChildNodeDataCatCurAtt->Age = 30;
//			ChildNodeDataCatCurAtt->ImgIndex = 83;
//		}

	}
}

void __fastcall TMainForm::fillCatalogsTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TTabular>>& tabulars,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Реквизиты
	PVirtualNode ChildNodeCatAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatAtt);
	ChildNodeDataCatAtt->Name = "Реквизиты";
	ChildNodeDataCatAtt->Age = 30;
	ChildNodeDataCatAtt->ImgIndex = 83;
	// Список Реквизитов
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 83;
	}
	// Табличные части
	PVirtualNode ChildNodeCatTabs = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatTabs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatTabs);
	ChildNodeDataCatTabs->Name = "Табличные части";
	ChildNodeDataCatTabs->Age = 30;
	ChildNodeDataCatTabs->ImgIndex = 82;
	// Список ТЧ
	for (int k = 0; k < tabulars.size(); k++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatTabs);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (tabulars[k])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 82;
	}
	// Формы
	PVirtualNode ChildNodeCatForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatForm);
	ChildNodeDataCatForm->Name = "Формы";
	ChildNodeDataCatForm->Age = 30;
	ChildNodeDataCatForm->ImgIndex = 86;
	// Список форм
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCatCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatForm);
		VirtualTreeData *ChildNodeDataCatCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurForm);
		ChildNodeDataCatCurForm->Name = (forms[l])->name;
		ChildNodeDataCatCurForm->Age = 30;
		ChildNodeDataCatCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCatCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCom);
	ChildNodeDataCatCom->Name = "Команды";
	ChildNodeDataCatCom->Age = 30;
	ChildNodeDataCatCom->ImgIndex = 98;
	// Список команд
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCatCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatCom);
		VirtualTreeData *ChildNodeDataCatCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurCom);
		ChildNodeDataCatCurCom->Name = (comands[ch])->name;
		ChildNodeDataCatCurCom->Age = 30;
		ChildNodeDataCatCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeCatMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatMoxel);
	ChildNodeDataCatMoxel->Name = "Макеты";
	ChildNodeDataCatMoxel->Age = 30;
	ChildNodeDataCatMoxel->ImgIndex = 79;
	// Список макетов
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCatCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeCatMoxel);
		VirtualTreeData *ChildNodeDataCatCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurMox);
		ChildNodeDataCatCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCatCurMox->Age = 30;
		ChildNodeDataCatCurMox->ImgIndex = 79;
	}

}

void __fastcall TMainForm::fillAccumulationRegisterTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TRequisite>>& dimensions,
						const std::vector<std::unique_ptr<TRequisite>>& resources,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Измерения
	PVirtualNode ChildNodeDim = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDim);
	ChildNodeDataDim->Name = "Измерения";
	ChildNodeDataDim->Age = 30;
	ChildNodeDataDim->ImgIndex = 10;
	for (int k = 0; k < dimensions.size(); k++)
	{
		PVirtualNode ChildNodeCurDim = VirtualStringTreeValue1C->AddChild(ChildNodeDim);
		VirtualTreeData *ChildNodeDataCurDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurDim);
		ChildNodeDataCurDim->Name = (dimensions[k])->name;
		ChildNodeDataCurDim->Age = 30;
		ChildNodeDataCurDim->ImgIndex = 10;
	}

	// Ресурсы
	PVirtualNode ChildNodeRes = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeRes);
	ChildNodeDataRes->Name = "Ресурсы";
	ChildNodeDataRes->Age = 30;
	ChildNodeDataRes->ImgIndex = 11;
	for (int k = 0; k < resources.size(); k++)
	{
		PVirtualNode ChildNodeCurRes = VirtualStringTreeValue1C->AddChild(ChildNodeRes);
		VirtualTreeData *ChildNodeDataCurRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurRes);
		ChildNodeDataCurRes->Name = (resources[k])->name;
		ChildNodeDataCurRes->Age = 30;
		ChildNodeDataCurRes->ImgIndex = 11;
	}

	// Реквизиты
	PVirtualNode ChildNodeAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAtt);
	ChildNodeDataAtt->Name = "Реквизиты";
	ChildNodeDataAtt->Age = 30;
	ChildNodeDataAtt->ImgIndex = 83;
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeAtt);
		VirtualTreeData *ChildNodeDataCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurAtt);
		ChildNodeDataCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCurAtt->Age = 30;
		ChildNodeDataCurAtt->ImgIndex = 83;
	}

	// Формы
	PVirtualNode ChildNodeForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeForm);
	ChildNodeDataForm->Name = "Формы";
	ChildNodeDataForm->Age = 30;
	ChildNodeDataForm->ImgIndex = 86;
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeForm);
		VirtualTreeData *ChildNodeDataCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurForm);
		ChildNodeDataCurForm->Name = (forms[l])->name;
		ChildNodeDataCurForm->Age = 30;
		ChildNodeDataCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCom);
	ChildNodeDataCom->Name = "Команды";
	ChildNodeDataCom->Age = 30;
	ChildNodeDataCom->ImgIndex = 98;
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCom);
		VirtualTreeData *ChildNodeDataCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurCom);
		ChildNodeDataCurCom->Name = (comands[ch])->name;
		ChildNodeDataCurCom->Age = 30;
		ChildNodeDataCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeMoxel);
	ChildNodeDataMoxel->Name = "Макеты";
	ChildNodeDataMoxel->Age = 30;
	ChildNodeDataMoxel->ImgIndex = 79;
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeMoxel);
		VirtualTreeData *ChildNodeDataCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurMox);
		ChildNodeDataCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCurMox->Age = 30;
		ChildNodeDataCurMox->ImgIndex = 79;
	}
}

void __fastcall TMainForm::fillAccountingRegisterTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TRequisite>>& dimensions,
						const std::vector<std::unique_ptr<TRequisite>>& resources,
						const std::vector<std::unique_ptr<TAccountingFlag>>& accountingFlags,
						const std::vector<std::unique_ptr<TDimensionAccountingFlag>>& dimensionAccountingFlags,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Измерения
	PVirtualNode ChildNodeDim = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDim);
	ChildNodeDataDim->Name = "Измерения";
	ChildNodeDataDim->Age = 30;
	ChildNodeDataDim->ImgIndex = 10;
	for (int k = 0; k < dimensions.size(); k++)
	{
		PVirtualNode ChildNodeCurDim = VirtualStringTreeValue1C->AddChild(ChildNodeDim);
		VirtualTreeData *ChildNodeDataCurDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurDim);
		ChildNodeDataCurDim->Name = (dimensions[k])->name;
		ChildNodeDataCurDim->Age = 30;
		ChildNodeDataCurDim->ImgIndex = 10;
	}

	// Ресурсы
	PVirtualNode ChildNodeRes = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeRes);
	ChildNodeDataRes->Name = "Ресурсы";
	ChildNodeDataRes->Age = 30;
	ChildNodeDataRes->ImgIndex = 11;
	for (int k = 0; k < resources.size(); k++)
	{
		PVirtualNode ChildNodeCurRes = VirtualStringTreeValue1C->AddChild(ChildNodeRes);
		VirtualTreeData *ChildNodeDataCurRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurRes);
		ChildNodeDataCurRes->Name = (resources[k])->name;
		ChildNodeDataCurRes->Age = 30;
		ChildNodeDataCurRes->ImgIndex = 11;
	}

	// Реквизиты
	PVirtualNode ChildNodeAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAtt);
	ChildNodeDataAtt->Name = "Реквизиты";
	ChildNodeDataAtt->Age = 30;
	ChildNodeDataAtt->ImgIndex = 83;
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeAtt);
		VirtualTreeData *ChildNodeDataCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurAtt);
		ChildNodeDataCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCurAtt->Age = 30;
		ChildNodeDataCurAtt->ImgIndex = 83;
	}

	// // Признаки учета
	// PVirtualNode ChildNodeAccFlags = VirtualStringTreeValue1C->AddChild(childNode);
	// VirtualTreeData *ChildNodeDataAccFlags = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAccFlags);
	// ChildNodeDataAccFlags->Name = "Признаки учета";
	// ChildNodeDataAccFlags->Age = 30;
	// ChildNodeDataAccFlags->ImgIndex = 118;
	// for (int j = 0; j < accountingFlags.size(); j++)
	// {
	// 	PVirtualNode ChildNodeCurAccFlag = VirtualStringTreeValue1C->AddChild(ChildNodeAccFlags);
	// 	VirtualTreeData *ChildNodeDataCurAccFlag = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurAccFlag);
	// 	ChildNodeDataCurAccFlag->Name = (accountingFlags[j])->name;
	// 	ChildNodeDataCurAccFlag->Age = 30;
	// 	ChildNodeDataCurAccFlag->ImgIndex = 118;
	// }

	// // Признаки учета субконто
	// PVirtualNode ChildNodeDimAccFlags = VirtualStringTreeValue1C->AddChild(childNode);
	// VirtualTreeData *ChildNodeDataDimAccFlags = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDimAccFlags);
	// ChildNodeDataDimAccFlags->Name = "Признаки учета субконто";
	// ChildNodeDataDimAccFlags->Age = 30;
	// ChildNodeDataDimAccFlags->ImgIndex = 119;
	// for (int j = 0; j < dimensionAccountingFlags.size(); j++)
	// {
	// 	PVirtualNode ChildNodeCurDimAccFlag = VirtualStringTreeValue1C->AddChild(ChildNodeDimAccFlags);
	// 	VirtualTreeData *ChildNodeDataCurDimAccFlag = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurDimAccFlag);
	// 	ChildNodeDataCurDimAccFlag->Name = (dimensionAccountingFlags[j])->name;
	// 	ChildNodeDataCurDimAccFlag->Age = 30;
	// 	ChildNodeDataCurDimAccFlag->ImgIndex = 119;
	// }

	// Формы
	PVirtualNode ChildNodeForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeForm);
	ChildNodeDataForm->Name = "Формы";
	ChildNodeDataForm->Age = 30;
	ChildNodeDataForm->ImgIndex = 86;
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeForm);
		VirtualTreeData *ChildNodeDataCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurForm);
		ChildNodeDataCurForm->Name = (forms[l])->name;
		ChildNodeDataCurForm->Age = 30;
		ChildNodeDataCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCom);
	ChildNodeDataCom->Name = "Команды";
	ChildNodeDataCom->Age = 30;
	ChildNodeDataCom->ImgIndex = 98;
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCom);
		VirtualTreeData *ChildNodeDataCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurCom);
		ChildNodeDataCurCom->Name = (comands[ch])->name;
		ChildNodeDataCurCom->Age = 30;
		ChildNodeDataCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeMoxel);
	ChildNodeDataMoxel->Name = "Макеты";
	ChildNodeDataMoxel->Age = 30;
	ChildNodeDataMoxel->ImgIndex = 79;
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeMoxel);
		VirtualTreeData *ChildNodeDataCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurMox);
		ChildNodeDataCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCurMox->Age = 30;
		ChildNodeDataCurMox->ImgIndex = 79;
	}
}

void __fastcall TMainForm::fillCalculationRegisterTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TRequisite>>& dimensions,
						const std::vector<std::unique_ptr<TRequisite>>& resources,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Измерения
	PVirtualNode ChildNodeDim = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDim);
	ChildNodeDataDim->Name = "Измерения";
	ChildNodeDataDim->Age = 30;
	ChildNodeDataDim->ImgIndex = 10;
	for (int k = 0; k < dimensions.size(); k++)
	{
		PVirtualNode ChildNodeCurDim = VirtualStringTreeValue1C->AddChild(ChildNodeDim);
		VirtualTreeData *ChildNodeDataCurDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurDim);
		ChildNodeDataCurDim->Name = (dimensions[k])->name;
		ChildNodeDataCurDim->Age = 30;
		ChildNodeDataCurDim->ImgIndex = 10;
	}

	// Ресурсы
	PVirtualNode ChildNodeRes = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeRes);
	ChildNodeDataRes->Name = "Ресурсы";
	ChildNodeDataRes->Age = 30;
	ChildNodeDataRes->ImgIndex = 11;
	for (int k = 0; k < resources.size(); k++)
	{
		PVirtualNode ChildNodeCurRes = VirtualStringTreeValue1C->AddChild(ChildNodeRes);
		VirtualTreeData *ChildNodeDataCurRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurRes);
		ChildNodeDataCurRes->Name = (resources[k])->name;
		ChildNodeDataCurRes->Age = 30;
		ChildNodeDataCurRes->ImgIndex = 11;
	}

	// Реквизиты
	PVirtualNode ChildNodeAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAtt);
	ChildNodeDataAtt->Name = "Реквизиты";
	ChildNodeDataAtt->Age = 30;
	ChildNodeDataAtt->ImgIndex = 83;
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeAtt);
		VirtualTreeData *ChildNodeDataCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurAtt);
		ChildNodeDataCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCurAtt->Age = 30;
		ChildNodeDataCurAtt->ImgIndex = 83;
	}

	// Формы
	PVirtualNode ChildNodeForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeForm);
	ChildNodeDataForm->Name = "Формы";
	ChildNodeDataForm->Age = 30;
	ChildNodeDataForm->ImgIndex = 86;
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeForm);
		VirtualTreeData *ChildNodeDataCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurForm);
		ChildNodeDataCurForm->Name = (forms[l])->name;
		ChildNodeDataCurForm->Age = 30;
		ChildNodeDataCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCom);
	ChildNodeDataCom->Name = "Команды";
	ChildNodeDataCom->Age = 30;
	ChildNodeDataCom->ImgIndex = 98;
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCom);
		VirtualTreeData *ChildNodeDataCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurCom);
		ChildNodeDataCurCom->Name = (comands[ch])->name;
		ChildNodeDataCurCom->Age = 30;
		ChildNodeDataCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeMoxel);
	ChildNodeDataMoxel->Name = "Макеты";
	ChildNodeDataMoxel->Age = 30;
	ChildNodeDataMoxel->ImgIndex = 79;
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeMoxel);
		VirtualTreeData *ChildNodeDataCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurMox);
		ChildNodeDataCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCurMox->Age = 30;
		ChildNodeDataCurMox->ImgIndex = 79;
	}
}

void __fastcall TMainForm::fillInformationRegisterTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TRequisite>>& dimensions,
						const std::vector<std::unique_ptr<TRequisite>>& resources,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Измерения
	PVirtualNode ChildNodeDim = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDim);
	ChildNodeDataDim->Name = "Измерения";
	ChildNodeDataDim->Age = 30;
	ChildNodeDataDim->ImgIndex = 10;
	for (int k = 0; k < dimensions.size(); k++)
	{
		PVirtualNode ChildNodeCurDim = VirtualStringTreeValue1C->AddChild(ChildNodeDim);
		VirtualTreeData *ChildNodeDataCurDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurDim);
		ChildNodeDataCurDim->Name = (dimensions[k])->name;
		ChildNodeDataCurDim->Age = 30;
		ChildNodeDataCurDim->ImgIndex = 10;
	}

	// Ресурсы
	PVirtualNode ChildNodeRes = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeRes);
	ChildNodeDataRes->Name = "Ресурсы";
	ChildNodeDataRes->Age = 30;
	ChildNodeDataRes->ImgIndex = 11;
	for (int k = 0; k < resources.size(); k++)
	{
		PVirtualNode ChildNodeCurRes = VirtualStringTreeValue1C->AddChild(ChildNodeRes);
		VirtualTreeData *ChildNodeDataCurRes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurRes);
		ChildNodeDataCurRes->Name = (resources[k])->name;
		ChildNodeDataCurRes->Age = 30;
		ChildNodeDataCurRes->ImgIndex = 11;
	}

	// Реквизиты
	PVirtualNode ChildNodeAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAtt);
	ChildNodeDataAtt->Name = "Реквизиты";
	ChildNodeDataAtt->Age = 30;
	ChildNodeDataAtt->ImgIndex = 83;
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeAtt);
		VirtualTreeData *ChildNodeDataCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurAtt);
		ChildNodeDataCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCurAtt->Age = 30;
		ChildNodeDataCurAtt->ImgIndex = 83;
	}


	// Формы
	PVirtualNode ChildNodeForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeForm);
	ChildNodeDataForm->Name = "Формы";
	ChildNodeDataForm->Age = 30;
	ChildNodeDataForm->ImgIndex = 86;
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeForm);
		VirtualTreeData *ChildNodeDataCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurForm);
		ChildNodeDataCurForm->Name = (forms[l])->name;
		ChildNodeDataCurForm->Age = 30;
		ChildNodeDataCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCom);
	ChildNodeDataCom->Name = "Команды";
	ChildNodeDataCom->Age = 30;
	ChildNodeDataCom->ImgIndex = 98;
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCom);
		VirtualTreeData *ChildNodeDataCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurCom);
		ChildNodeDataCurCom->Name = (comands[ch])->name;
		ChildNodeDataCurCom->Age = 30;
		ChildNodeDataCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeMoxel);
	ChildNodeDataMoxel->Name = "Макеты";
	ChildNodeDataMoxel->Age = 30;
	ChildNodeDataMoxel->ImgIndex = 79;
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeMoxel);
		VirtualTreeData *ChildNodeDataCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCurMox);
		ChildNodeDataCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCurMox->Age = 30;
		ChildNodeDataCurMox->ImgIndex = 79;
	}
}

void __fastcall TMainForm::fillChartAccTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TAccountingFlag>>& accflags,
						const std::vector<std::unique_ptr<TDimensionAccountingFlag>>& dimaccflags,
						const std::vector<std::unique_ptr<TTabular>>& tabulars,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Реквизиты
	PVirtualNode ChildNodeCatAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatAtt);
	ChildNodeDataCatAtt->Name = "Реквизиты";
	ChildNodeDataCatAtt->Age = 30;
	ChildNodeDataCatAtt->ImgIndex = 83;
	// Список Реквизитов
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 83;
	}

	// Признаки учета
	PVirtualNode ChildNodeCCTAttAcc = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCCTAttAcc = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCCTAttAcc);
	ChildNodeDataCCTAttAcc->Name = "Признаки учета";
	ChildNodeDataCCTAttAcc->Age = 30;
	ChildNodeDataCCTAttAcc->ImgIndex = 118;
	// Список признаков учета
	for (int j = 0; j < accflags.size(); j++)
	{
		PVirtualNode ChildNodeCCTCurAttAcc = VirtualStringTreeValue1C->AddChild(ChildNodeCCTAttAcc);
		VirtualTreeData *ChildNodeDataCCTCurAttAcc = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCCTCurAttAcc);
		ChildNodeDataCCTCurAttAcc->Name = (accflags[j])->name;
		ChildNodeDataCCTCurAttAcc->Age = 30;
		ChildNodeDataCCTCurAttAcc->ImgIndex = 118;
	}
	// Признаки учета субконто
	PVirtualNode ChildNodeCCTAttAccDim = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCCTAttAccDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCCTAttAccDim);
	ChildNodeDataCCTAttAccDim->Name = "Признаки учета субконто";
	ChildNodeDataCCTAttAccDim->Age = 30;
	ChildNodeDataCCTAttAccDim->ImgIndex = 119;
	// Список признаков учета
	for (int j = 0; j < dimaccflags.size(); j++)
	{
		PVirtualNode ChildNodeCCTCurAttAccDim = VirtualStringTreeValue1C->AddChild(ChildNodeCCTAttAccDim);
		VirtualTreeData *ChildNodeDataCCTCurAttAccDim = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCCTCurAttAccDim);
		ChildNodeDataCCTCurAttAccDim->Name = (dimaccflags[j])->name;
		ChildNodeDataCCTCurAttAccDim->Age = 30;
		ChildNodeDataCCTCurAttAccDim->ImgIndex = 119;
	}




	// Табличные части
	PVirtualNode ChildNodeCatTabs = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatTabs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatTabs);
	ChildNodeDataCatTabs->Name = "Табличные части";
	ChildNodeDataCatTabs->Age = 30;
	ChildNodeDataCatTabs->ImgIndex = 82;
	// Список ТЧ
	for (int k = 0; k < tabulars.size(); k++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatTabs);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (tabulars[k])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 82;
	}
	// Формы
	PVirtualNode ChildNodeCatForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatForm);
	ChildNodeDataCatForm->Name = "Формы";
	ChildNodeDataCatForm->Age = 30;
	ChildNodeDataCatForm->ImgIndex = 86;
	// Список форм
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCatCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatForm);
		VirtualTreeData *ChildNodeDataCatCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurForm);
		ChildNodeDataCatCurForm->Name = (forms[l])->name;
		ChildNodeDataCatCurForm->Age = 30;
		ChildNodeDataCatCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCatCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCom);
	ChildNodeDataCatCom->Name = "Команды";
	ChildNodeDataCatCom->Age = 30;
	ChildNodeDataCatCom->ImgIndex = 98;
	// Список команд
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCatCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatCom);
		VirtualTreeData *ChildNodeDataCatCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurCom);
		ChildNodeDataCatCurCom->Name = (comands[ch])->name;
		ChildNodeDataCatCurCom->Age = 30;
		ChildNodeDataCatCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeCatMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatMoxel);
	ChildNodeDataCatMoxel->Name = "Макеты";
	ChildNodeDataCatMoxel->Age = 30;
	ChildNodeDataCatMoxel->ImgIndex = 79;
	// Список макетов
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCatCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeCatMoxel);
		VirtualTreeData *ChildNodeDataCatCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurMox);
		ChildNodeDataCatCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCatCurMox->Age = 30;
		ChildNodeDataCatCurMox->ImgIndex = 79;
	}

}


void __fastcall TMainForm::fillJournalTree(TObjectList *mdData, PVirtualNode childNode, VirtualTreeData *childData,
						int i, int imgIndex, String name,
						const std::vector<std::unique_ptr<TRequisite>>& attributes,
						const std::vector<std::unique_ptr<TTabular>>& tabulars,
						const std::vector<std::unique_ptr<TForm1C>>& forms,
						const std::vector<std::unique_ptr<TComand>>& comands,
						const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
	childData->Name = name;
	childData->Age = 30;
	childData->ImgIndex = imgIndex;

	// Реквизиты
	PVirtualNode ChildNodeCatAtt = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatAtt);
	ChildNodeDataCatAtt->Name = "Графы";
	ChildNodeDataCatAtt->Age = 30;
	ChildNodeDataCatAtt->ImgIndex = 6;
	// Список Реквизитов
	for (int j = 0; j < attributes.size(); j++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (attributes[j])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 6;
	}
	// Табличные части
	PVirtualNode ChildNodeCatTabs = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatTabs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatTabs);
	ChildNodeDataCatTabs->Name = "Табличные части";
	ChildNodeDataCatTabs->Age = 30;
	ChildNodeDataCatTabs->ImgIndex = 82;
	// Список ТЧ
	for (int k = 0; k < tabulars.size(); k++)
	{
		PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatTabs);
		VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
		ChildNodeDataCatCurAtt->Name = (tabulars[k])->name;
		ChildNodeDataCatCurAtt->Age = 30;
		ChildNodeDataCatCurAtt->ImgIndex = 82;
	}
	// Формы
	PVirtualNode ChildNodeCatForm = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatForm);
	ChildNodeDataCatForm->Name = "Формы";
	ChildNodeDataCatForm->Age = 30;
	ChildNodeDataCatForm->ImgIndex = 86;
	// Список форм
	for (int l = 0; l < forms.size(); l++)
	{
		PVirtualNode ChildNodeCatCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatForm);
		VirtualTreeData *ChildNodeDataCatCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurForm);
		ChildNodeDataCatCurForm->Name = (forms[l])->name;
		ChildNodeDataCatCurForm->Age = 30;
		ChildNodeDataCatCurForm->ImgIndex = 86;
	}

	// Команды
	PVirtualNode ChildNodeCatCom = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCom);
	ChildNodeDataCatCom->Name = "Команды";
	ChildNodeDataCatCom->Age = 30;
	ChildNodeDataCatCom->ImgIndex = 98;
	// Список команд
	for (int ch = 0; ch < comands.size(); ch++)
	{
		PVirtualNode ChildNodeCatCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatCom);
		VirtualTreeData *ChildNodeDataCatCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurCom);
		ChildNodeDataCatCurCom->Name = (comands[ch])->name;
		ChildNodeDataCatCurCom->Age = 30;
		ChildNodeDataCatCurCom->ImgIndex = 98;
	}

	// Макеты
	PVirtualNode ChildNodeCatMoxel = VirtualStringTreeValue1C->AddChild(childNode);
	VirtualTreeData *ChildNodeDataCatMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatMoxel);
	ChildNodeDataCatMoxel->Name = "Макеты";
	ChildNodeDataCatMoxel->Age = 30;
	ChildNodeDataCatMoxel->ImgIndex = 79;
	// Список макетов
	for (int ch1 = 0; ch1 < moxels.size(); ch1++)
	{
		PVirtualNode ChildNodeCatCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeCatMoxel);
		VirtualTreeData *ChildNodeDataCatCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurMox);
		ChildNodeDataCatCurMox->Name = (moxels[ch1])->name;
		ChildNodeDataCatCurMox->Age = 30;
		ChildNodeDataCatCurMox->ImgIndex = 79;
	}
}


// Вспомогательная функция для заполнения дерева перечислений
void __fastcall TMainForm::fillEnumTree(PVirtualNode childNode, VirtualTreeData *childData, int imgIndex, TEnums* CurCat)
{
    childData->Name = CurCat->name;
    childData->Age = 30;
    childData->ImgIndex = imgIndex;

    // Значения перечисления
    PVirtualNode ChildNodeEnumAtt = VirtualStringTreeValue1C->AddChild(childNode);
    VirtualTreeData *ChildNodeDataEnumAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumAtt);
    ChildNodeDataEnumAtt->Name = "Значения";
    ChildNodeDataEnumAtt->Age = 30;
    ChildNodeDataEnumAtt->ImgIndex = 83;
    // Список значений
    for (size_t j = 0; j < CurCat->attributes.size(); j++)
    {
        PVirtualNode ChildNodeEnumAttCur = VirtualStringTreeValue1C->AddChild(ChildNodeEnumAtt);
        VirtualTreeData *ChildNodeDataEnumAttCur = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumAttCur);
        ChildNodeDataEnumAttCur->Name = CurCat->attributes[j];
        ChildNodeDataEnumAttCur->Age = 30;
        ChildNodeDataEnumAttCur->ImgIndex = 83;
    }

    // Формы
    PVirtualNode ChildNodeEnumForm = VirtualStringTreeValue1C->AddChild(childNode);
    VirtualTreeData *ChildNodeDataEnumForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumForm);
    ChildNodeDataEnumForm->Name = "Формы";
    ChildNodeDataEnumForm->Age = 30;
    ChildNodeDataEnumForm->ImgIndex = 86;
    // Список форм
    for (size_t l = 0; l < CurCat->forms.size(); l++)
    {
        PVirtualNode ChildNodeEnumCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeEnumForm);
        VirtualTreeData *ChildNodeDataEnumCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumCurForm);
        ChildNodeDataEnumCurForm->Name = CurCat->forms[l];
        ChildNodeDataEnumCurForm->Age = 30;
        ChildNodeDataEnumCurForm->ImgIndex = 86;
    }

    // Команды
    PVirtualNode ChildNodeEnumCom = VirtualStringTreeValue1C->AddChild(childNode);
    VirtualTreeData *ChildNodeDataEnumCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumCom);
    ChildNodeDataEnumCom->Name = "Команды";
    ChildNodeDataEnumCom->Age = 30;
    ChildNodeDataEnumCom->ImgIndex = 98;
    // Список команд
    for (size_t ch = 0; ch < CurCat->comands.size(); ch++)
    {
        PVirtualNode ChildNodeEnumCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeEnumCom);
        VirtualTreeData *ChildNodeDataEnumCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumCurCom);
        ChildNodeDataEnumCurCom->Name = CurCat->comands[ch];
        ChildNodeDataEnumCurCom->Age = 30;
        ChildNodeDataEnumCurCom->ImgIndex = 98;
    }

    // Макеты
    PVirtualNode ChildNodeEnumMoxel = VirtualStringTreeValue1C->AddChild(childNode);
    VirtualTreeData *ChildNodeDataEnumMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumMoxel);
    ChildNodeDataEnumMoxel->Name = "Макеты";
    ChildNodeDataEnumMoxel->Age = 30;
    ChildNodeDataEnumMoxel->ImgIndex = 79;
    // Список макетов
    for (size_t ch1 = 0; ch1 < CurCat->moxels.size(); ch1++)
    {
        PVirtualNode ChildNodeEnumCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeEnumMoxel);
        VirtualTreeData *ChildNodeDataEnumCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnumCurMox);
        ChildNodeDataEnumCurMox->Name = CurCat->moxels[ch1];
        ChildNodeDataEnumCurMox->Age = 30;
        ChildNodeDataEnumCurMox->ImgIndex = 79;
    }
}

void __fastcall TMainForm::FillTreeMD(PVirtualNode parentNode, TObjectList *mdData, const String& md_name, int imgIndex)
{
    // Карта для типов, использующих fillCatalogsTree
    static const std::unordered_set<String> catalogTypes = {md_Catalogs, md_Documents, md_Reports, md_DataProcessors, md_ChartsOfCharacteristicTypes, md_ChartOfCalculationTypes};

    // Карта для типов, использующих fillJournalTree
    static const std::unordered_set<String> journalTypes = {md_DocumentJournals};

    // Карта для типов, использующих fillChartAccTree
    static const std::unordered_set<String> chartAccTypes = {md_ChartOfAccounts};

    // Карта для типов, использующих fillInformationRegisterTree
    static const std::unordered_set<String> informationRegisterTypes = {md_InformationRegisters, md_AccumulationRegisters, md_AccountingRegisters, md_CalculationRegisters};

	for(int i = 0; i < mdData->Count; i++)
	{
		PVirtualNode childNode = VirtualStringTreeValue1C->AddChild(parentNode);
		VirtualTreeData *childData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNode);

        if (catalogTypes.count(md_name))
        {
            // Обработка типов, подобных каталогам
            if (md_name == md_Catalogs)
            {
                TCatalogs* CurCat = static_cast<TCatalogs*>(mdData->Items[i]);
                fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
            else if (md_name == md_Documents)
            {
                TDocuments* CurCat = static_cast<TDocuments*>(mdData->Items[i]);
                fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
			else if (md_name == md_Reports)
            {
                TReports* CurCat = static_cast<TReports*>(mdData->Items[i]);
				fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
			}
			else if (md_name == md_DataProcessors)
			{
				TDataProcessors* CurCat = static_cast<TDataProcessors*>(mdData->Items[i]);
				fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
			}
            else if (md_name == md_ChartsOfCharacteristicTypes)
            {
                TChartOfCharacteristicTypes* CurCat = static_cast<TChartOfCharacteristicTypes*>(mdData->Items[i]);
				fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
			else if (md_name == md_ChartOfCalculationTypes)
			{
				TChartOfCalculationTypes* CurCat = static_cast<TChartOfCalculationTypes*>(mdData->Items[i]);
				fillCatalogsTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
			}
		}
        else if (journalTypes.count(md_name))
        {
            // Обработка типов, подобных журналам
            if (md_name == md_DocumentJournals)
            {
                TJournals* CurCat = static_cast<TJournals*>(mdData->Items[i]);
                fillJournalTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->getAttributes(), CurCat->getTabularSections(), CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
		}
        else if (chartAccTypes.count(md_name))
        {
            // Обработка типов, подобных планам счетов
            if (md_name == md_ChartOfAccounts)
            {
                TChartOfAccounts* CurCat = static_cast<TChartOfAccounts*>(mdData->Items[i]);
                fillChartAccTree(mdData, childNode, childData, i, imgIndex, CurCat->name, CurCat->attributes, CurCat->accflags, CurCat->dimaccflags, CurCat->tabulars, CurCat->forms, CurCat->comands, CurCat->moxels);
            }
        }
        else if (informationRegisterTypes.count(md_name))
        {
            if (md_name == md_InformationRegisters)
            {
                TInformationRegisters* CurCat = static_cast<TInformationRegisters*>(mdData->Items[i]);
                fillInformationRegisterTree(mdData, childNode, childData, i, imgIndex, CurCat->name,
                    CurCat->getAttributes(), CurCat->getDimensions(), CurCat->getResources(),
                    CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
            else if (md_name == md_AccumulationRegisters)
            {
                TAccumulationRegisters* CurCat = static_cast<TAccumulationRegisters*>(mdData->Items[i]);
                fillAccumulationRegisterTree(mdData, childNode, childData, i, imgIndex, CurCat->name,
                    CurCat->getAttributes(), CurCat->getDimensions(), CurCat->getResources(),
                    CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
            else if (md_name == md_AccountingRegisters)
            {
                TAccountingRegisters* CurCat = static_cast<TAccountingRegisters*>(mdData->Items[i]);
				fillAccountingRegisterTree(mdData, childNode, childData, i, imgIndex, CurCat->name,
                    CurCat->getAttributes(), CurCat->getDimensions(), CurCat->getResources(),
                    CurCat->getAccountingFlags(), CurCat->getDimensionAccountingFlags(),
                    CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
            else if (md_name == md_CalculationRegisters)
            {
                TCalculationRegisters* CurCat = static_cast<TCalculationRegisters*>(mdData->Items[i]);
                fillCalculationRegisterTree(mdData, childNode, childData, i, imgIndex, CurCat->name,
                    CurCat->getAttributes(), CurCat->getDimensions(), CurCat->getResources(),
                    CurCat->getForms(), CurCat->getCommands(), CurCat->getLayouts());
            }
        }
        else if (md_name == md_Enums)
        {
            // Специальная обработка для перечислений
            TEnums* CurCat = static_cast<TEnums*>(mdData->Items[i]);
            fillEnumTree(childNode, childData, imgIndex, CurCat);
		}
        else
        {
            // Простые типы: только имя и изображение
            if (md_name == md_DocumentNumerators)
            {
                TNumerators* CurCat = static_cast<TNumerators*>(mdData->Items[i]);
				childData->Name = CurCat->name;
				childData->Age = 30;
				childData->ImgIndex = imgIndex;
			}
			else if (md_name == md_Sequences)
			{
				TSequences* CurCat = static_cast<TSequences*>(mdData->Items[i]);
				childData->Name = CurCat->name;
				childData->Age = 30;
				childData->ImgIndex = imgIndex;
			}
		}
	}
}

void __fastcall TMainForm::FillVirtualTree() {
	// Структура для хранения данных о категориях
	struct CategoryData
	{
		//const std::vector<String>& data;
		TObjectList *data;
		const String name;
		int imgIndex;
		int age;
	};

	// Массив с описанием всех категорий
	std::vector<CategoryData> md_categories = {
		{MainForm->mdCommonss,                    md_Common,                      84,  25},
		{MainForm->mdConstants,                   md_Constants,                   0,   25},
		{MainForm->mdCatalogs,                    md_Catalogs,                    1,   25},
		{MainForm->mdDocuments,                   md_Documents,                   4,   25},
		{MainForm->mdDocumentJournals,            md_DocumentJournals,            5,   25},
		{MainForm->mdEnums,                       md_Enums,                       2,   25},
		{MainForm->mdReports,                     md_Reports,                     9,   25},
		{MainForm->mdDataProcessors,              md_DataProcessors,              7,   25},
		{MainForm->mdChartsOfCharacteristicTypes, md_ChartsOfCharacteristicTypes, 16,  25},
		{MainForm->mdChartOfAccounts,             md_ChartOfAccounts,             116, 25},
		{MainForm->mdChartOfCalculationTypes,     md_ChartOfCalculationTypes,     17,  25},
		{MainForm->mdInformationRegisters,        md_InformationRegisters,        14,  25},
		{MainForm->mdAccumulationRegisters,       md_AccumulationRegisters,       13,  25},
		{MainForm->mdAccountingRegisters,         md_AccountingRegisters,         117, 25},
		{MainForm->mdCalculationRegisters,        md_CalculationRegisters,        18,  25},
		{MainForm->mdBusinessProcesses,           md_BusinessProcesses,           58,  25},
		{MainForm->mdTasks,                       md_Tasks,                       59,  25},
		{MainForm->mdExternalDataSources,         md_ExternalDataSources,         27,  25}
	};


	// Массив с описанием всех категорий
	std::vector<CategoryData> md_categoriesCommon = {

		//{MainForm->Subsystems,                  "Подсистемы",                     73,  25},
		{MainForm->mdCommonModules,               md_CommonModules,                   87,  25},
		{MainForm->mdSessionParameters,           md_SessionParameters,               90,  25},
		{MainForm->mdRoles,                       md_Roles,                           81,  25},
		{MainForm->mdCommonAttributes,            md_CommonAttributes,                24,  25},
		{MainForm->mdExchangePlans,               md_ExchangePlans,                   41,  25},
		{MainForm->mdFilterCriteria,              md_FilterCriteria,                  85,  25},
		{MainForm->mdEventSubscriptions,          md_EventSubscriptions,              100, 25},
		{MainForm->mdScheduledJobs,               md_ScheduledJobs,                   104, 25},
		{MainForm->mdBots,                        md_Bots,                            132, 25},
		{MainForm->mdFunctionalOptions,           md_FunctionalOptions,               108, 25},
		{MainForm->mdFunctionalOptionsParameters, md_FunctionalOptionsParameters,     109, 25},
		{MainForm->mdDefinedTypes,                md_DefinedTypes,                    111, 25},
		{MainForm->mdSettingsStorages,            md_SettingsStorages,                52,  25},
		{MainForm->mdCommonCommands,              md_CommonCommands,                  98,  25},
		{MainForm->mdCommonTemplates,             md_CommonTemplates,                 79,  25},
		{MainForm->mdCommandGroups,               md_CommandGroups,                   99,  25},
		{MainForm->mdCommonForms,                 md_CommonForms,                     86,  25},
		{MainForm->mdInterfaces,                  md_Interfaces,                      80,  25},
		{MainForm->mdCommonTemplates,             md_CommonTemplates,                 79,  25},
		{MainForm->mdCommonPictures,              md_CommonPictures,                  77,  25},
		{MainForm->mdXDTOPackages,                md_XDTOPackages,                    91,  25},
		{MainForm->mdWebServices,                 md_WebServices,                     92,  25},
		{MainForm->mdHTTPServices,                md_HTTPServices,                    113, 25},
		{MainForm->mdWSReferences,                md_WSReferences,                    96,  25},
		{MainForm->mdIntegrationServices,         md_IntegrationServices,             131, 25},
		{MainForm->mdStyleItems,                  md_StyleItems,                      76,  25},
		{MainForm->mdStyles,                      md_Styles,                          75,  25},
		{MainForm->mdLanguages,                   md_Languages,                       73,  25}
	};



	// Создаем корневой узел
	VirtualStringTreeValue1C->Clear();
	PVirtualNode RootNode = VirtualStringTreeValue1C->AddChild(nullptr);


	VirtualTreeData *RootData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(RootNode);

	// Обработка каждой категории
	for (const auto& category : md_categories)
	{
		PVirtualNode parentNode = VirtualStringTreeValue1C->AddChild(RootNode);
		VirtualTreeData *parentNodeData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(parentNode);

		parentNodeData->Name = category.name;
		parentNodeData->Age = category.age;
		parentNodeData->ImgIndex = category.imgIndex;

		if (category.name == "Общие")
		{
			for (const auto& categoryCom : md_categoriesCommon)
			{
				PVirtualNode parentNodeCom = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *parentNodeDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(parentNodeCom);

				parentNodeDataCom->Name = categoryCom.name;
				parentNodeDataCom->Age = categoryCom.age;
				parentNodeDataCom->ImgIndex = categoryCom.imgIndex;

				for (const auto& item : categoryCom.data)
				{
					PVirtualNode childNodeCom = VirtualStringTreeValue1C->AddChild(parentNodeCom);
					VirtualTreeData *childDataCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeCom);

					if (categoryCom.name == md_CommonModules)
					{
						TCommonModules* CurModule = static_cast<TCommonModules*>(item);
						childDataCom->Name = CurModule->name;
						childDataCom->text_module = CurModule->GetText();
					}
					else if (categoryCom.name == md_SessionParameters)
					{
						TSessionParameters* CurParam = static_cast<TSessionParameters*>(item);
						childDataCom->Name = CurParam->name;
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommonAttributes)
					{
						TCommonAttributes* CurCommonAtt = static_cast<TCommonAttributes*>(item);
						childDataCom->Name = CurCommonAtt->name;
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_ExchangePlans)
					{
						TExchangePlans* CurExchPlan = static_cast<TExchangePlans*>(item);
						childDataCom->Name = CurExchPlan->GetExchangePlanName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_FilterCriteria)
					{
						TFilterCriteria* CurFilter = static_cast<TFilterCriteria*>(item);
						childDataCom->Name = CurFilter->GetFilterCriteriaName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_EventSubscriptions)
					{
						TEventSubscriptions* CurEventSub = static_cast<TEventSubscriptions*>(item);
						childDataCom->Name = CurEventSub->GetEventSubscriptionName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_ScheduledJobs)
					{
						TScheduledJobs* CurScheduledJob = static_cast<TScheduledJobs*>(item);
						childDataCom->Name = CurScheduledJob->GetScheduledJobsName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommonCommands)
					{
						TCommonCommands* CurCommonCommand = static_cast<TCommonCommands*>(item);
						childDataCom->Name = CurCommonCommand->GetCommandName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommandGroups)
					{
						TCommandGroups* CurCommandGroup = static_cast<TCommandGroups*>(item);
						childDataCom->Name = CurCommandGroup->GetCommandName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommonForms)
					{
						TCommonForms* CurCommonForm = static_cast<TCommonForms*>(item);
						childDataCom->Name = CurCommonForm->GetFormName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_Interfaces)
					{
						TInterfaces* CurInterface = static_cast<TInterfaces*>(item);
						childDataCom->Name = CurInterface->GetInterfaceName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommonTemplates)
					{
						TCommonTemplates* CurCommonTemplate = static_cast<TCommonTemplates*>(item);
						childDataCom->Name = CurCommonTemplate->GetTemplateName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_CommonPictures)
					{
						TCommonPictures* CurCommonPicture = static_cast<TCommonPictures*>(item);
						childDataCom->Name = CurCommonPicture->GetPictureName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_XDTOPackages)
					{
						TXDTOPackages* CurXDTOPackage = static_cast<TXDTOPackages*>(item);
						childDataCom->Name = CurXDTOPackage->GetXDTOPackageName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_WebServices)
					{
						TWebServices* CurWebService = static_cast<TWebServices*>(item);
						childDataCom->Name = CurWebService->GetWebServiceName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_HTTPServices)
					{
						THTTPServices* CurHTTPServices = static_cast<THTTPServices*>(item);
						childDataCom->Name = CurHTTPServices->GetHTTPServicesName();
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_FunctionalOptions)
					{
						TFunctionalOptions* CurFO = static_cast<TFunctionalOptions*>(item);
						childDataCom->Name = CurFO->name;
						childDataCom->text_module = L"";
						childDataCom->Age = 99;
						childDataCom->ImgIndex = categoryCom.imgIndex;
					}
					else if (categoryCom.name == md_FunctionalOptionsParameters)
					{
						TFunctionalOptionsParameters* CurFOP = static_cast<TFunctionalOptionsParameters*>(item);
						childDataCom->Name = CurFOP->name;
						childDataCom->Age = 99;
						childDataCom->ImgIndex = categoryCom.imgIndex;
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_DefinedTypes)
					{
						TDefinedTypes* CurDT = static_cast<TDefinedTypes*>(item);
						childDataCom->Name = CurDT->name;
						childDataCom->Age = 99;
						childDataCom->ImgIndex = categoryCom.imgIndex;
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_SettingsStorages)
					{
						TSettingsStorages* CurSS = static_cast<TSettingsStorages*>(item);
						childDataCom->Name = CurSS->name;
						childDataCom->Age = 99;
						childDataCom->ImgIndex = categoryCom.imgIndex;
						childDataCom->text_module = L"";
					}
					else if (categoryCom.name == md_Languages)
					{
						TLangs* CurLang = static_cast<TLangs*>(item);
						childDataCom->Name = CurLang->name;
						childDataCom->Age = 99;
						childDataCom->ImgIndex = categoryCom.imgIndex;
						childDataCom->text_module = L"";
					}
					else
					{
						childDataCom->Name = L"";
						childDataCom->text_module = L"";
					}
					childDataCom->Age = 99;
					childDataCom->ImgIndex = categoryCom.imgIndex;
				}

				// Для Roles добавляем элементы из MainForm->Roles (vector<String>)
				if (categoryCom.name == md_Roles)
				{
					for (size_t i = 0; i < MainForm->Roles.size(); i++)
					{
						PVirtualNode childNodeRoles = VirtualStringTreeValue1C->AddChild(parentNodeCom);
						VirtualTreeData *childDataRoles = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeRoles);
						childDataRoles->Name = MainForm->Roles[i];
						childDataRoles->Age = 99;
						childDataRoles->ImgIndex = categoryCom.imgIndex;
						childDataRoles->text_module = L"";
					}
				}


				// Для Bots добавляем элементы из MainForm->mdBots (TObjectList)
				if (categoryCom.name == md_Bots && MainForm->mdBots != nullptr && MainForm->mdBots->Count > 0)
				{
					for (int i = 0; i < MainForm->mdBots->Count; i++)
					{
						TBots* CurBot = static_cast<TBots*>(MainForm->mdBots->Items[i]);
						PVirtualNode childNodeBots = VirtualStringTreeValue1C->AddChild(parentNodeCom);
						VirtualTreeData *childDataBots = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeBots);
						childDataBots->Name = CurBot->name;
						childDataBots->Age = 99;
						childDataBots->ImgIndex = categoryCom.imgIndex;
						childDataBots->text_module = L"";
					}
				}
			}
		}

		//for(int i = 0; i < MainForm->mdCatalogs->Count; i++)
		if(category.name == md_Catalogs)
		{
			FillTreeMD(parentNode, MainForm->mdCatalogs, md_Catalogs, category.imgIndex);
		}
		else if(category.name == md_Documents)
		{
			if (parentNode->ChildCount == 0)
			{
				PVirtualNode childNodeNum = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataNum = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeNum);
				childDataNum->Name = md_DocumentNumerators;
				childDataNum->Age = 30;
				childDataNum->ImgIndex = 8;

				FillTreeMD(childNodeNum, MainForm->mdDocumentNumerators, md_DocumentNumerators, 8);

				PVirtualNode childNodeSeq = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataSeq = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeSeq);
				childDataSeq->Name = md_Sequences;
				childDataSeq->Age = 30;
				childDataSeq->ImgIndex = 12;

				FillTreeMD(childNodeSeq, MainForm->mdSequences,          md_Sequences,          12);
			}
			FillTreeMD(parentNode, MainForm->mdDocuments, md_Documents, category.imgIndex);
		}
		else if(category.name == md_Reports)
		{
			FillTreeMD(parentNode, MainForm->mdReports, md_Reports, category.imgIndex);
		}
		else if(category.name == md_DataProcessors)
		{
			FillTreeMD(parentNode, MainForm->mdDataProcessors, md_DataProcessors, category.imgIndex);
		}
		else if(category.name == md_ChartsOfCharacteristicTypes)
		{
			FillTreeMD(parentNode, MainForm->mdChartsOfCharacteristicTypes, md_ChartsOfCharacteristicTypes, category.imgIndex);
		}
		else if(category.name == md_BusinessProcesses)
		{
			FillTreeMD(parentNode, MainForm->mdBusinessProcesses, md_BusinessProcesses, category.imgIndex);
		}
		else if (category.name == md_DocumentJournals)
		{
			FillTreeMD(parentNode, MainForm->mdDocumentJournals, md_DocumentJournals, category.imgIndex);
		}
		else if (category.name == md_Enums)
		{
			FillTreeMD(parentNode, MainForm->mdEnums, md_Enums, category.imgIndex);
		}
        else if (category.name == md_ChartOfAccounts)
		{
			FillTreeMD(parentNode, MainForm->mdChartOfAccounts, md_ChartOfAccounts, category.imgIndex);
		}
		else if (category.name == md_ChartOfCalculationTypes)
		{
			FillTreeMD(parentNode, MainForm->mdChartOfCalculationTypes, md_ChartOfCalculationTypes, category.imgIndex);
		}
		else if (category.name == md_AccumulationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdAccumulationRegisters, md_AccumulationRegisters, category.imgIndex);
		}
		else if (category.name == md_AccountingRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdAccountingRegisters, md_AccountingRegisters, category.imgIndex);
		}
		else if (category.name == md_CalculationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdCalculationRegisters, md_CalculationRegisters, category.imgIndex);
		}
		else if (category.name == md_Constants)
		{
			// Константы
			for (int i = 0; i < MainForm->mdConstants->Count; i++)
			{
				PVirtualNode childNodeConst = VirtualStringTreeValue1C->AddChild(parentNode);
				VirtualTreeData *childDataConst = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(childNodeConst);
				TConstants* CurConstant = static_cast<TConstants*>(MainForm->mdConstants->Items[i]);
				childDataConst->Name = CurConstant->name;
				childDataConst->Age = 30;
				childDataConst->ImgIndex = category.imgIndex;
			}
		}
		else if (category.name == md_InformationRegisters)
		{
			FillTreeMD(parentNode, MainForm->mdInformationRegisters, md_InformationRegisters, category.imgIndex);
		}

	}

	VirtualStringTreeValue1C->Expanded[RootNode] = true;
	RootData->Name = MainForm->ConfigName;
	RootData->Age = 100;
	RootData->ImgIndex = 72;

}


void __fastcall TMainForm::TreeInit()
{
	// Корень конфигурации
	VirtualStringTreeValue1C->Clear();
	PVirtualNode RootNode = VirtualStringTreeValue1C->AddChild(nullptr);

	VirtualTreeData *RootData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(RootNode);




	// Добавляем дочерний узел
	PVirtualNode ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	VirtualTreeData *ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Common; // Общие
	ChildData->Age = 30;
	ChildData->ImgIndex = 84;

	//================================= поддерево Общие ==============================================
	PVirtualNode ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	VirtualTreeData *ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Subsystems; //"Подсистемы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 74;
	// у подсистем есть иерархия, так что это нужно переделать
	for(int i = 0; i < MainForm->Subsystems.size(); i++)
	{
		PVirtualNode ChildNodeSub = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataSub = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeSub);
		ChildNodeDataSub->Name = MainForm->Subsystems[i].name;
		ChildNodeDataSub->Age = 30;
		ChildNodeDataSub->ImgIndex = 74;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonModules; //"Общие модули";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 87;
	for(int i = 0; i < MainForm->CommonModules.size(); i++)
	{
		PVirtualNode ChildNodeCommonModules = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataCommonModules = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCommonModules);
		ChildNodeDataCommonModules->Name = MainForm->CommonModules[i];
		ChildNodeDataCommonModules->Age = 30;
		ChildNodeDataCommonModules->ImgIndex = 87;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_SessionParameters; //"Параметры сеанса";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 90;
	for(int i = 0; i < MainForm->SessionParameters.size(); i++)
	{
		PVirtualNode ChildNodePar = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataPar = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodePar);
		ChildNodeDataPar->Name = MainForm->SessionParameters[i];
		ChildNodeDataPar->Age = 30;
		ChildNodeDataPar->ImgIndex = 90;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Roles; //"Роли";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 81;
	for(int i = 0; i < MainForm->Roles.size(); i++)
	{
		PVirtualNode ChildNodeRoles = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataRoles = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeRoles);
		ChildNodeDataRoles->Name = MainForm->Roles[i];
		ChildNodeDataRoles->Age = 30;
		ChildNodeDataRoles->ImgIndex = 81;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonAttributes; // "Общие реквизиты";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 24;
	for(int i = 0; i < MainForm->CommonAttributes .size(); i++)
	{
		PVirtualNode ChildNodeCommonAtt = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataCommonAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCommonAtt);
		ChildNodeDataCommonAtt->Name = MainForm->CommonAttributes[i];
		ChildNodeDataCommonAtt->Age = 30;
		ChildNodeDataCommonAtt->ImgIndex = 24;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_ExchangePlans; //"Планы обмена";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 41;
	for(int i = 0; i < MainForm->ExchangePlans.size(); i++)
	{
		PVirtualNode ChildNodeExch = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataExch = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeExch);
		ChildNodeDataExch->Name = MainForm->ExchangePlans[i];
		ChildNodeDataExch->Age = 30;
		ChildNodeDataExch->ImgIndex = 41;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_FilterCriteria; //"Критерии отбора";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 85;
	for(int i = 0; i < MainForm->FilterCriteria.size(); i++)
	{
		PVirtualNode ChildNodeFC = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataFC = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeFC);
		ChildNodeDataFC->Name = MainForm->FilterCriteria[i];
		ChildNodeDataFC->Age = 30;
		ChildNodeDataFC->ImgIndex = 85;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_EventSubscriptions; //"Подписки на события";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 100;
	for(int i = 0; i < MainForm->EventSubscriptions.size(); i++)
	{
		PVirtualNode ChildNodeEvt = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataEvt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEvt);
		ChildNodeDataEvt->Name = MainForm->EventSubscriptions[i];
		ChildNodeDataEvt->Age = 30;
		ChildNodeDataEvt->ImgIndex = 100;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_ScheduledJobs; //"Регламентные задания";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 104;
	for(int i = 0; i < MainForm->ScheduledJobs.size(); i++)
	{
		PVirtualNode ChildNodeJobs = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataJobs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeJobs);
		ChildNodeDataJobs->Name = MainForm->ScheduledJobs[i];
		ChildNodeDataJobs->Age = 30;
		ChildNodeDataJobs->ImgIndex = 104;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Bots; //"Боты";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 132;

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_FunctionalOptions; //"Функциональные опции";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 108;
	for(int i = 0; i < MainForm->FunctionalOptions.size(); i++)
	{
		PVirtualNode ChildNodeFO = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataFO = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeFO);
		ChildNodeDataFO->Name = MainForm->FunctionalOptions[i];
		ChildNodeDataFO->Age = 30;
		ChildNodeDataFO->ImgIndex = 108;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_FunctionalOptionsParameters; //"Параметры функциональных опций";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 109;
	for(int i = 0; i < MainForm->FunctionalOptionsParameters .size(); i++)
	{
		PVirtualNode ChildNodeFOP = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataFOP = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeFOP);
		ChildNodeDataFOP->Name = MainForm->FunctionalOptionsParameters[i];
		ChildNodeDataFOP->Age = 30;
		ChildNodeDataFOP->ImgIndex = 109;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_DefinedTypes; //"Определяемые типы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 111;
	for(int i = 0; i < MainForm->DefinedTypes.size(); i++)
	{
		PVirtualNode ChildNodeDT = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataDT = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDT);
		ChildNodeDataDT->Name = MainForm->DefinedTypes[i];
		ChildNodeDataDT->Age = 30;
		ChildNodeDataDT->ImgIndex = 111;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_SettingsStorages; //"Хранилища настроек";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 52;
	for(int i = 0; i < MainForm->SettingsStorages.size(); i++)
	{
		PVirtualNode ChildNodeSS = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataSS = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeSS);
		ChildNodeDataSS->Name = MainForm->SettingsStorages[i];
		ChildNodeDataSS->Age = 30;
		ChildNodeDataSS->ImgIndex = 52;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonCommands; //"Общие команды";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 98;
	for(int i = 0; i < MainForm->CommonCommands.size(); i++)
	{
		PVirtualNode ChildNodeComCom = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataComCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeComCom);
		ChildNodeDataComCom->Name = MainForm->CommonCommands[i];
		ChildNodeDataComCom->Age = 30;
		ChildNodeDataComCom->ImgIndex = 98;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommandGroups; //"Группы команд";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 99;
	for(int i = 0; i < MainForm->mdCommandGroups->Count; i++)
	{
		PVirtualNode ChildNodeComGroup = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataComGroup = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeComGroup);
		TCommandGroups* CurCommandGroup = static_cast<TCommandGroups*>(MainForm->mdCommandGroups->Items[i]);
		ChildNodeDataComGroup->Name = CurCommandGroup->GetCommandName();
		ChildNodeDataComGroup->Age = 30;
		ChildNodeDataComGroup->ImgIndex = 99;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonForms; //"Общие формы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 86;
	for(int i = 0; i < MainForm->mdCommonForms->Count; i++)
	{
		PVirtualNode ChildNodeComF = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataComF = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeComF);
		TCommonForms* CurCommonForm = static_cast<TCommonForms*>(MainForm->mdCommonForms->Items[i]);
		ChildNodeDataComF->Name = CurCommonForm->GetFormName();
		ChildNodeDataComF->Age = 30;
		ChildNodeDataComF->ImgIndex = 86;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Interfaces; //"Интерфейсы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 80;
	for(int i = 0; i < MainForm->mdInterfaces->Count; i++)
	{
		PVirtualNode ChildNodeInt = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataInt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeInt);
		TInterfaces* CurInterface = static_cast<TInterfaces*>(MainForm->mdInterfaces->Items[i]);
		ChildNodeDataInt->Name = CurInterface->GetInterfaceName();
		ChildNodeDataInt->Age = 30;
		ChildNodeDataInt->ImgIndex = 80;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonTemplates;//"Общие макеты";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 79;
	for(int i = 0; i < MainForm->CommonTemplates.size(); i++)
	{
		PVirtualNode ChildNodeCTemp = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataCTemp = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCTemp);
		ChildNodeDataCTemp->Name = MainForm->CommonTemplates[i];
		ChildNodeDataCTemp->Age = 30;
		ChildNodeDataCTemp->ImgIndex = 79;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonPictures; //"Общие картинки";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 77;
	for(int i = 0; i < MainForm->CommonPictures.size(); i++)
	{
		PVirtualNode ChildNodePic = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataPic = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodePic);
		ChildNodeDataPic->Name = MainForm->CommonPictures[i];
		ChildNodeDataPic->Age = 30;
		ChildNodeDataPic->ImgIndex = 77;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_XDTOPackages; //"XDTO-пакеты";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 91;
	for(int i = 0; i < MainForm->XDTOPackages.size(); i++)
	{
		PVirtualNode ChildNodeXDTO = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataXDTO = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeXDTO);
		ChildNodeDataXDTO->Name = MainForm->XDTOPackages[i];
		ChildNodeDataXDTO->Age = 30;
		ChildNodeDataXDTO->ImgIndex = 91;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_WebServices; //"Web-сервисы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 92;
	for(int i = 0; i < MainForm->WebServices.size(); i++)
	{
		PVirtualNode ChildNodeWS = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataWS = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeWS);
		ChildNodeDataWS->Name = MainForm->WebServices[i];
		ChildNodeDataWS->Age = 30;
		ChildNodeDataWS->ImgIndex = 92;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_HTTPServices; //"HTTP-сервисы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 113;
	for(int i = 0; i < MainForm->mdHTTPServices->Count; i++)
	{
		PVirtualNode ChildNodeHTTPServices = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataHTTPServices = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeHTTPServices);
		THTTPServices* CurHTTPService = static_cast<THTTPServices*>(MainForm->mdHTTPServices->Items[i]);
		ChildNodeDataHTTPServices->Name = CurHTTPService->GetHTTPServicesName();
		ChildNodeDataHTTPServices->Age = 30;
		ChildNodeDataHTTPServices->ImgIndex = 113;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_WSReferences; //"WS-ссылки";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 96;

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_IntegrationServices; //"Сервисы интеграции";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 131;

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_StyleItems; //"Элементы стиля";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 76;
	for(int i = 0; i < MainForm->StyleItems.size(); i++)
	{
		PVirtualNode ChildNodeStlStl = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataStlStl = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeStlStl);
		ChildNodeDataStlStl->Name = MainForm->StyleItems[i];
		ChildNodeDataStlStl->Age = 30;
		ChildNodeDataStlStl->ImgIndex = 76;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Styles; //"Стили";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 75;
	for(int i = 0; i < MainForm->Styles.size(); i++)
	{
		PVirtualNode ChildNodeStl = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataStl = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeStl);
		ChildNodeDataStl->Name = MainForm->Styles[i];
		ChildNodeDataStl->Age = 30;
		ChildNodeDataStl->ImgIndex = 75;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Languages; // "Языки";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 73;

	for(int i = 0; i < MainForm->Languages.size(); i++)
	{
		PVirtualNode ChildNodeLang = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataLang = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeLang);
		ChildNodeDataLang->Name = MainForm->Languages[i];
		ChildNodeDataLang->Age = 30;
		ChildNodeDataLang->ImgIndex = 73;
	}
	//================================================================================================

	// Константы
	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Constants; // "Константы";
	ChildData->Age = 25;
	ChildData->ImgIndex = 0;
	for(int i = 0; i < MainForm->Constants.size(); i++)
	{
		PVirtualNode ChildNodeConst = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataConst = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeConst);
		ChildNodeDataConst->Name = MainForm->Constants[i];
		ChildNodeDataConst->Age = 30;
		ChildNodeDataConst->ImgIndex = 0;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Catalogs; // "Справочники";
	ChildData->Age = 25;
	ChildData->ImgIndex = 1;

	for(int i = 0; i < MainForm->mdCatalogs->Count; i++)
	{
		PVirtualNode ChildNodeCatalogs = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataCatalogs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatalogs);
		TCatalogs* CurCat = static_cast<TCatalogs*>(MainForm->mdCatalogs->Items[i]);
		ChildNodeDataCatalogs->Name = CurCat->name;
		ChildNodeDataCatalogs->Age = 30;
		ChildNodeDataCatalogs->ImgIndex = 1;

		// Реквизиты
		PVirtualNode ChildNodeCatAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatalogs);
		VirtualTreeData *ChildNodeDataCatAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatAtt);
		ChildNodeDataCatAtt->Name = "Реквизиты";
		ChildNodeDataCatAtt->Age = 30;
		ChildNodeDataCatAtt->ImgIndex = 83;
		// Список Реквизитов
		for (i = 0; i < CurCat->getAttributes().size(); i++)
		{
			PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
			VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
			ChildNodeDataCatCurAtt->Name = ((CurCat->getAttributes())[i])->name;
			ChildNodeDataCatCurAtt->Age = 30;
			ChildNodeDataCatCurAtt->ImgIndex = 83;
		}

		// Табличные части
		PVirtualNode ChildNodeCatTabs = VirtualStringTreeValue1C->AddChild(ChildNodeCatalogs);
		VirtualTreeData *ChildNodeDataCatTabs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatTabs);
		ChildNodeDataCatTabs->Name = "Табличные части";
		ChildNodeDataCatTabs->Age = 30;
		ChildNodeDataCatTabs->ImgIndex = 82;
		// Список ТЧ
		for (i = 0; i < CurCat->getTabularSections().size(); i++)
		{
			PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatTabs);
			VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
			ChildNodeDataCatCurAtt->Name = ((CurCat->getTabularSections())[i])->name;
			ChildNodeDataCatCurAtt->Age = 30;
			ChildNodeDataCatCurAtt->ImgIndex = 82;
		}

		// Формы
		PVirtualNode ChildNodeCatForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatalogs);
		VirtualTreeData *ChildNodeDataCatForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatForm);
		ChildNodeDataCatForm->Name = "Формы";
		ChildNodeDataCatForm->Age = 30;
		ChildNodeDataCatForm->ImgIndex = 86;
		// Список форм
		for (i = 0; i < CurCat->getForms().size(); i++)
		{
			PVirtualNode ChildNodeCatCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatForm);
			VirtualTreeData *ChildNodeDataCatCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurForm);
			ChildNodeDataCatCurForm->Name = ((CurCat->getForms())[i])->name;
			ChildNodeDataCatCurForm->Age = 30;
			ChildNodeDataCatCurForm->ImgIndex = 86;
		}

		// Команды
		PVirtualNode ChildNodeCatCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatalogs);
		VirtualTreeData *ChildNodeDataCatCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCom);
		ChildNodeDataCatCom->Name = "Команды";
		ChildNodeDataCatCom->Age = 30;
		ChildNodeDataCatCom->ImgIndex = 98;
		// Список команд
		for (i = 0; i < CurCat->getCommands().size(); i++)
		{
			PVirtualNode ChildNodeCatCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatCom);
			VirtualTreeData *ChildNodeDataCatCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurCom);
			ChildNodeDataCatCurCom->Name = ((CurCat->getCommands())[i])->name;
			ChildNodeDataCatCurCom->Age = 30;
			ChildNodeDataCatCurCom->ImgIndex = 98;
		}
		// Макеты
		PVirtualNode ChildNodeCatMoxel = VirtualStringTreeValue1C->AddChild(ChildNodeCatalogs);
		VirtualTreeData *ChildNodeDataCatMoxel = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatMoxel);
		ChildNodeDataCatMoxel->Name = "Макеты";
		ChildNodeDataCatMoxel->Age = 30;
		ChildNodeDataCatMoxel->ImgIndex = 79;
		// Список макетов
		for (i = 0; i < CurCat->getLayouts().size(); i++)
		{
			PVirtualNode ChildNodeCatCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeCatMoxel);
			VirtualTreeData *ChildNodeDataCatCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurMox);
			ChildNodeDataCatCurMox->Name = ((CurCat->getLayouts())[i])->name;
			ChildNodeDataCatCurMox->Age = 30;
			ChildNodeDataCatCurMox->ImgIndex = 79;
		}
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Documents; // "Документы";
	ChildData->Age = 25;
	ChildData->ImgIndex = 4;

	//================================================================================

	PVirtualNode ChildNode2 = VirtualStringTreeValue1C->AddChild(ChildNode);
	VirtualTreeData *ChildData2 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode2);
	ChildData2->Name = md_DocumentNumerators; // "Нумераторы";
	ChildData2->Age = 30;
	ChildData2->ImgIndex = 8;
	for(int i = 0; i < MainForm->DocumentNumerators.size(); i++)
	{
		PVirtualNode ChildNodeDocsNum = VirtualStringTreeValue1C->AddChild(ChildNode2);
		VirtualTreeData *ChildNodeDataDocsNum = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDocsNum);
		ChildNodeDataDocsNum->Name = MainForm->DocumentNumerators[i];
		ChildNodeDataDocsNum->Age = 30;
		ChildNodeDataDocsNum->ImgIndex = 8;
	}

	PVirtualNode ChildNode3 = VirtualStringTreeValue1C->AddChild(ChildNode);
	VirtualTreeData *ChildData3 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode3);
	ChildData3->Name = md_Sequences; // "Последовательности";
	ChildData3->Age = 30;
	ChildData3->ImgIndex = 12;
	for(int i = 0; i < MainForm->Sequences.size(); i++)
	{
		PVirtualNode ChildNodeSeq = VirtualStringTreeValue1C->AddChild(ChildNode3);
		VirtualTreeData *ChildNodeDataSeq = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeSeq);
		ChildNodeDataSeq->Name = MainForm->Sequences[i];
		ChildNodeDataSeq->Age = 30;
		ChildNodeDataSeq->ImgIndex = 12;
	}

	for(int i = 0; i < MainForm->Documents.size(); i++)
	{
		PVirtualNode ChildNodeDocs = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataDocs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDocs);
		ChildNodeDataDocs->Name = MainForm->Documents[i];
		ChildNodeDataDocs->Age = 30;
		ChildNodeDataDocs->ImgIndex = 4;
	}

	//================================================================================

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_DocumentJournals; //"Журналы документов";
	ChildData->Age = 25;
	ChildData->ImgIndex = 5;

	for(int i = 0; i < MainForm->DocumentJournals.size(); i++)
	{
		PVirtualNode ChildNodeDocsJ = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataDocsJ = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDocsJ);
		ChildNodeDataDocsJ->Name = MainForm->DocumentJournals[i];
		ChildNodeDataDocsJ->Age = 30;
		ChildNodeDataDocsJ->ImgIndex = 5;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Enums; // "Перечисления";
	ChildData->Age = 25;
	ChildData->ImgIndex = 2;
	for(int i = 0; i < MainForm->Enums.size(); i++)
	{
		PVirtualNode ChildNodeEnums = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataEnums = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEnums);
		ChildNodeDataEnums->Name = MainForm->Enums[i];
		ChildNodeDataEnums->Age = 30;
		ChildNodeDataEnums->ImgIndex = 2;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Reports; // "Отчеты";
	ChildData->Age = 25;
	ChildData->ImgIndex = 9;
	for(int i = 0; i < MainForm->Reports.size(); i++)
	{
		PVirtualNode ChildNodeReports = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataReports = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeReports);
		ChildNodeDataReports->Name = MainForm->Reports[i];
		ChildNodeDataReports->Age = 30;
		ChildNodeDataReports->ImgIndex = 9;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_DataProcessors; // "Обработки";
	ChildData->Age = 25;
	ChildData->ImgIndex = 7;
	for(int i = 0; i < MainForm->DataProcessors.size(); i++)
	{
		PVirtualNode ChildNodeDP = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataDP = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeDP);
		ChildNodeDataDP->Name = MainForm->DataProcessors[i];
		ChildNodeDataDP->Age = 30;
		ChildNodeDataDP->ImgIndex = 7;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_ChartsOfCharacteristicTypes ;// "Планы видов характеристик";
	ChildData->Age = 25;
	ChildData->ImgIndex = 16;
	for(int i = 0; i < MainForm->ChartsOfCharacteristicTypes.size(); i++)
	{
		PVirtualNode ChildNodeChartsTypes = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataChartsTypes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeChartsTypes);
		ChildNodeDataChartsTypes->Name = MainForm->ChartsOfCharacteristicTypes[i];
		ChildNodeDataChartsTypes->Age = 30;
		ChildNodeDataChartsTypes->ImgIndex = 16;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_ChartOfAccounts; // "Планы счетов";
	ChildData->Age = 25;
	ChildData->ImgIndex = 116;
	for(int i = 0; i < MainForm->ChartOfAccounts.size(); i++)
	{
		PVirtualNode ChildNodeChartOfAccounts = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataChartOfAccounts = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeChartOfAccounts);
		ChildNodeDataChartOfAccounts->Name = MainForm->ChartOfAccounts[i];
		ChildNodeDataChartOfAccounts->Age = 30;
		ChildNodeDataChartOfAccounts->ImgIndex = 116;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_ChartOfCalculationTypes; // "Планы видов расчета";
	ChildData->Age = 25;
	ChildData->ImgIndex = 17;
	for(int i = 0; i < MainForm->ChartOfCalculationTypes.size(); i++)
	{
		PVirtualNode ChildNodeChartOfCalculationTypes = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataChartOfCalculationTypes = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeChartOfCalculationTypes);
		ChildNodeDataChartOfCalculationTypes->Name = MainForm->ChartOfCalculationTypes[i];
		ChildNodeDataChartOfCalculationTypes->Age = 30;
		ChildNodeDataChartOfCalculationTypes->ImgIndex = 17;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_InformationRegisters; // "Регистры сведений";
	ChildData->Age = 25;
	ChildData->ImgIndex = 14;
	for(int i = 0; i < MainForm->InformationRegisters.size(); i++)
	{
		PVirtualNode ChildNodeIReg = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataIReg = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeIReg);
		ChildNodeDataIReg->Name = MainForm->InformationRegisters[i];
		ChildNodeDataIReg->Age = 30;
		ChildNodeDataIReg->ImgIndex = 14;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_AccumulationRegisters; // "Регистры накопления";
	ChildData->Age = 25;
	ChildData->ImgIndex = 13;
	for(int i = 0; i < MainForm->AccumulationRegisters.size(); i++)
	{
		PVirtualNode ChildNodeAReg = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataAReg = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAReg);
		ChildNodeDataAReg->Name = MainForm->AccumulationRegisters[i];
		ChildNodeDataAReg->Age = 30;
		ChildNodeDataAReg->ImgIndex = 13;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_AccountingRegisters; // "Регистры бухгалтерии";
	ChildData->Age = 25;
	ChildData->ImgIndex = 117;
	for(int i = 0; i < MainForm->AccountingRegisters.size(); i++)
	{
		PVirtualNode ChildNodeAccReg = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataAccReg = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeAccReg);
		ChildNodeDataAccReg->Name = MainForm->AccountingRegisters[i];
		ChildNodeDataAccReg->Age = 30;
		ChildNodeDataAccReg->ImgIndex = 117;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_CalculationRegisters; //  "Регистры расчета";
	ChildData->Age = 18;
	ChildData->ImgIndex = 18;
	for(int i = 0; i < MainForm->CalculationRegisters.size(); i++)
	{
		PVirtualNode ChildNodeCalcReg = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataCalcReg = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCalcReg);
		ChildNodeDataCalcReg->Name = MainForm->CalculationRegisters[i];
		ChildNodeDataCalcReg->Age = 30;
		ChildNodeDataCalcReg->ImgIndex = 18;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_BusinessProcesses; // "Бизнес-процессы";
	ChildData->Age = 25;
	ChildData->ImgIndex = 58;
	for(int i = 0; i < MainForm->BusinessProcesses.size(); i++)
	{
		PVirtualNode ChildNodeBP = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataBP = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeBP);
		ChildNodeDataBP->Name = MainForm->BusinessProcesses[i];
		ChildNodeDataBP->Age = 30;
		ChildNodeDataBP->ImgIndex = 58;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_Tasks; // "Задачи";
	ChildData->Age = 25;
	ChildData->ImgIndex = 59;
	for(int i = 0; i < MainForm->Tasks.size(); i++)
	{
		PVirtualNode ChildNodeTasks = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataTasks = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeTasks);
		ChildNodeDataTasks->Name = MainForm->Tasks[i];
		ChildNodeDataTasks->Age = 30;
		ChildNodeDataTasks->ImgIndex = 59;
	}

	ChildNode = VirtualStringTreeValue1C->AddChild(RootNode);
	ChildData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode);
	ChildData->Name = md_ExternalDataSources; // "Внешние источники данных";
	ChildData->Age = 25;
	ChildData->ImgIndex = 27;
	for(int i = 0; i < MainForm->ExternalDataSources.size(); i++)
	{
		PVirtualNode ChildNodeEDS = VirtualStringTreeValue1C->AddChild(ChildNode);
		VirtualTreeData *ChildNodeDataEDS = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeEDS);
		ChildNodeDataEDS->Name = MainForm->ExternalDataSources[i];
		ChildNodeDataEDS->Age = 30;
		ChildNodeDataEDS->ImgIndex = 27;
	}

	VirtualStringTreeValue1C->Expanded[RootNode] = true;

	RootData->Name = MainForm->ConfigName;
	RootData->Age = 100;
	RootData->ImgIndex = 72;

}



void __fastcall TMainForm::VirtualStringTreeValue1CFreeNode(TBaseVirtualTree *Sender, PVirtualNode Node)
{
//	VirtualTreeData *RootData =(VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);
//	RootData->Name.~UnicodeString();
//	if(!RootData)
//		delete RootData;
	VirtualTreeData *NodeData =(VirtualTreeData*)Sender->GetNodeData(Node);
	NodeData->Name = L"";
	NodeData->text_module = L"";

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CGetImageIndex(TBaseVirtualTree *Sender, PVirtualNode Node, TVTImageKind Kind,
		  TColumnIndex Column, bool &Ghosted, TImageIndex &ImageIndex)
{
	VirtualTreeData *NodeRec = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);
	if (Kind != ikState)
	{
		ImageIndex = NodeRec->ImgIndex;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Button1Click(TObject *Sender)
{
	if (dlgOpenCatalog->Execute())
	{
		//editFolderName->Text = dlgOpenCatalog->FileName;
	}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ActionFileOpenExecute(TObject *Sender)
{
	if (dlgOpenCF->Execute())
	{
		if (FileExists(dlgOpenCF->FileName))
		{
		  String filename = dlgOpenCF->FileName;
		  EditNameCF->Text = filename;

		  // Удаляем предыдущую конфигурацию
		  if (GlobalCF)
		  {
			  delete GlobalCF;
			  GlobalCF = nullptr;
		  }

		  // Очищаем все TObjectList
		  mdCatalogs->Clear();
		  mdLanguages->Clear();
		  mdAccumulationRegisters->Clear();
		  mdAccountingRegisters->Clear();
		  mdCalculationRegisters->Clear();
		  mdBusinessProcesses->Clear();
		  mdChartsOfCharacteristicTypes->Clear();
		  mdCommandGroups->Clear();
		  mdCommonAttributes->Clear();
		  mdCommonCommands->Clear();
		  mdCommonTemplates->Clear();
		  mdCommonForms->Clear();
		  mdCommonModules->Clear();
		  mdCommonPictures->Clear();
		  mdCommonTemplates->Clear();
		  mdConstants->Clear();
		  mdDataProcessors->Clear();
		  mdDefinedTypes->Clear();
		  mdDocumentJournals->Clear();
		  mdDocumentNumerators->Clear();
		  mdDocuments->Clear();
		  mdEnums->Clear();
		  mdEventSubscriptions->Clear();
		  mdExchangePlans->Clear();
		  mdChartOfAccounts->Clear();
		  mdChartOfCalculationTypes->Clear();
		  mdExternalDataSources->Clear();
		  mdFilterCriteria->Clear();
		  mdFunctionalOptions->Clear();
		  mdFunctionalOptionsParameters->Clear();
		  mdHTTPServices->Clear();
		  mdInformationRegisters->Clear();
		  mdInterfaces->Clear();
		  mdReports->Clear();
		  mdRoles->Clear();
		  mdBots->Clear();
		  mdScheduledJobs->Clear();
		  mdSessionParameters->Clear();
		  mdSettingsStorages->Clear();
		  mdStyleItems->Clear();
		  mdStyles->Clear();
		  mdSubsystems->Clear();
		  mdTasks->Clear();
		  mdWebServices->Clear();
		  mdWSReferences->Clear();
		  mdXDTOPackages->Clear();
		  mdIntegrationServices->Clear();
		  mdSequences->Clear();

		  GlobalCF = new v8catalog(filename, true);

		  get_cf_name(GlobalCF, mess);

		  VirtualStringTreeValue1C->BeginUpdate();
		  try
		  {
			//TreeInit();
			FillVirtualTree();
		  }
		  __finally
		  {
			VirtualStringTreeValue1C->EndUpdate();
		  }

		  //VirtualStringTreeValue1C.exp


		  //delete MainForm->GlobalCF;
		}
		else
		  throw(Exception("File does not exist."));
	}
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::ActionOpenCFExecute(TObject *Sender)
{
	TMainForm::ActionFileOpenExecute(Sender);
}
//---------------------------------------------------------------------------
//                           Messager
//---------------------------------------------------------------------------
__fastcall Messager::Messager(TListView* lv, TStatusBar* sb)
{
	ListView = lv;
	StatusBar = sb;
	FormatSettings.DateSeparator = L'.';
	FormatSettings.TimeSeparator = L':';
	//FormatSettings.LongDateFormat = L"dd.mm.yyyy";
	FormatSettings.ShortDateFormat = L"dd.mm.yyyy";
	FormatSettings.LongTimeFormat = L"hh:mm:ss:zzz";
}

//---------------------------------------------------------------------------
void __fastcall Messager::setlogfile(String _logfile)
{
	logfile = System::Ioutils::TPath::GetFullPath(_logfile);
	if(FileExists(logfile))
    	DeleteFile(logfile);
}


//---------------------------------------------------------------------------
void __fastcall Messager::Status(const String& message)
{
	StatusBar->Panels->Items[0]->Text = message;
	StatusBar->Update();
}

//---------------------------------------------------------------------------
void __fastcall Messager::AddMessage(const String& message, const MessageState mstate, TStringList* param)
{
	TFileStream* log = NULL;
	TStreamWriter* sw;
	String s;

	ListView->AddItem(message, param);
	TListItem* item = ListView->Items->Item[ListView->Items->Count - 1];
	item->StateIndex = mstate;
	ListView->Selected = item;
	ListView->Scroll(0, 0xfffffff);
	ListView->Update();

	if(logfile.Length())
	{
		if(FileExists(logfile))
		{
			log = new TFileStream(logfile, fmOpenReadWrite | fmShareDenyNone);
			log->Seek(0, soFromEnd);
		}
		else
		{
			log = new TFileStream(logfile, fmCreate | fmShareDenyNone);
			log->Write(TEncoding::UTF8->GetPreamble(), TEncoding::UTF8->GetPreamble().Length);
		}
		sw = new TStreamWriter(log, TEncoding::UTF8, 4096);
		sw->Write(DateTimeToStr(Now(), FormatSettings));
		s = L" ";
        sw->Write(s);
		switch(mstate)
		{
			case msEmpty:      s = L"<>";        break;
			case msSuccesfull: s = L"<ok>";      break;
			case msWarning:    s = L"<warning>"; break;
			case msInfo:       s = L"<info>";    break;
			case msError:      s = L"<error>";   break;
			case msWait:       s = L"<wait>";    break;
			case msHint:       s = L"<hint>";    break;
			default:           s = L"<>";
		}
		sw->Write(s);
		s = L" ";
        sw->Write(s);
		sw->Write(message);
		if(param)
        {
            for(int i = 0; i < param->Count; i++)
            {
                s = L"\r\n\t";
                sw->Write(s);
                sw->Write((*param)[i]);
            }
        }
		s = L"\r\n\r\n";
        sw->Write(s);

		delete sw;
		delete log;
	}

}

void get_cf_name(v8catalog* cf, Messager* mess)
{
	tree* tr;
	tree* node;
	v8catalog* cat;
	v8file* filedata;
	String meta;
	String s;
	int ver;

	if(!cf)
	{
		mess->AddError(L"Ошибка открытия файла");
		return;
	}

	filedata = cf->GetFile(L"version");
	if(!filedata)
	{
		mess->AddError(L"Ошибка получения файла root конфигурации");
		return;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		mess->AddError(L"Ошибка разбора файла root конфигурации");
		return;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
		return;

	node = tr;

	node = &(*node)[0][0][0];
	if(node->get_type() != nd_number)
	{
		mess->AddError(L"Ошибка получения версии формата конфигурации");
		delete tr;
		return;
	}

	ver = node->get_value().ToInt();
	delete tr;

	if(ver < 100)
	{
		// 8.0
		filedata = cf->GetFile(L"metadata");
		if(!filedata)
		{
			mess->AddError(L"Ошибка получения файла metadata конфигурации");
			return;
		}

		cat = filedata->GetCatalog();
		if(!cat)
		{
			mess->AddError(L"Ошибка открытия файла metadata конфигурации");
			return;
		}

	}
	else
	{
		//8.1 или 8.2
		cat = cf;
	}

	filedata = cat->GetFile(L"root");
	if(!filedata)
	{
		mess->AddError(L"Ошибка получения файла root конфигурации");
		return;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		mess->AddError(L"Ошибка разбора файла root конфигурации");
		return;
	}

	node = tr;
	node = &(*node)[0][1];

	if(node->get_type() != nd_guid)
	{
		mess->AddError(L"Ошибка получения имени файла метаданных");
		delete tr;
		return;
	}

	meta = node->get_value();
	delete tr;

	filedata = cat->GetFile(meta);
	if(!filedata)
	{
		s = L"Ошибка получения файла ";
		s += meta;
		s += L" конфигурации";
		mess->AddError(s);
		return;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		s = L"Ошибка разбора файла ";
		s += meta;
		s += L" конфигурации";
		mess->AddError(s);
		return;
	}

	get_cf_name(tr, mess);
	//delete tr;
}

String GetNameSubsystem(v8catalog *cf, String &guid_md)
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

	node = &(*node)[0][1][1][2]; // guid подсистемы

	Result = node->get_value(); // имя подсистемы

	delete tree_md;

	return Result;
}

void GetListChildrenSubsystem(v8catalog *cf, String &guid_md, std::vector<String>& child)
{
	v8file *filedata = cf->GetFile(guid_md);
	if(!filedata)
	{
		return;
	}
	tree* tree_md = get_treeFromV8file(filedata);
	if(!tree_md)
	{
		return;
	}
	tree* node = tree_md;

	node = &(*node)[0][3][0];

	int CountChild = (node->get_next())->get_value().ToInt();

	tree* curNodeChild = node->get_next();

	while (curNodeChild)
	{
		curNodeChild = curNodeChild->get_next();
		if (curNodeChild)
		{
		   child.push_back(curNodeChild->get_value());
		}

	}

	delete tree_md;
}


void fill_subsystem(tree* tr, std::vector<SubSys> &md_subsys)
{
	v8file *filedata;
	tree* tree_md;
	tree* node;
	tree* node_children;
	String s = "";

	String guid_md = GUID_Subsystems;

	v8catalog *cf = MainForm->GlobalCF;

	tree* node_md = find_node_by_guid(tr, guid_md);

	int CountMD = (node_md->get_next())->get_value().ToInt();

	md_subsys.clear();

	tree* curNode = node_md->get_next();

	while (curNode)
	{
		curNode = curNode->get_next();
		if (curNode)
		{
			s = curNode->get_value();
			String val = GetNameSubsystem(cf, s); // имя подсистемы

			std::vector<String> children;

			GetListChildrenSubsystem(cf, s, children);

			md_subsys.push_back( {val, children} );
		}
	}
}


// Процедура заполняет метаданные по корневому гуиду
void fill_md(tree* tr, String guid_md, std::vector<String> &md_list)
{
	v8file *filedata;
	tree* tree_md;
	tree* node;
	String s;

	v8catalog *cf = MainForm->GlobalCF;

	//tree* node_md = find_node_by_guid(tr, guid_md); //"cf4abea6-37b2-11d4-940f-008048da11f9"

	// Карта путей для извлечения имен
	std::unordered_map<String, std::vector<int>> namePaths = {
		{GUID_Catalogs,          {0,1,9,1,2}},
		{GUID_Languages,         {0,1,1,2}},
		{GUID_CommonModules,     {0,1,1,2}},
		{GUID_Roles,             {0,1,1,2}},
		{GUID_CommonTemplates,   {0,1,1,2}},
		{GUID_HTTPServices,      {0,1,2,2}},
		{GUID_ScheduledJobs,     {0,1,1,2}},
		{GUID_CommonAttributes,  {0,1,1,1,1,2}},
		{GUID_SessionParameters, {0,1,1,1,2}},
		{GUID_FunctionalOptionsParameters, {0,1,1,2}},
		{GUID_Subsystems,           {0,1,1,2}},
		{GUID_Interfaces,           {0,1,2,2}},
		{GUID_Styles,               {0,1,1,2}},
		{GUID_FilterCriteria,       {0,1,5,1,2}},
		{GUID_SettingsStorages,     {0,1,1,1,2}},
		{GUID_EventSubscriptions,   {0,1,1,2}},
		{GUID_StyleItems,           {0,1,3,2}},
		{GUID_CommonPictures,       {0,1,1,2}},
		{GUID_ExchangePlans,        {0,1,12,2}},
		{GUID_WebServices,          {0,1,2,2}},
		{GUID_FunctionalOptions,    {0,1,1,2}},
		{GUID_DefinedTypes,         {0,1,3,2}},
		{GUID_XDTOPackages,         {0,1,1,2}},
		{GUID_Constants,            {0,1,1,1,1,2}},
		{GUID_Documents,            {0,1,9,1,2}},
		{GUID_InformationRegisters, {0,1,15,1,2}},
		{GUID_CalculationRegisters, {0,1,15,1,2}},
		{GUID_BusinessProcesses,    {0,1,1,2}},
		{GUID_Tasks,                {0,1,1,2}},
		{GUID_AccountingRegisters,  {0,1,16,1,2}},
		{GUID_CommandGroups,        {0,1,6,2}},
		{GUID_CommonCommands,       {0,1,1,2,9,2}},
		{GUID_CommonForms,         {0,1,1,1,2}},
		{GUID_Numerators,           {0,1,1,2}},
		{GUID_JournDocuments,       {0,1,3,1,2}},
		{GUID_Reports,              {0,1,3,1,2}},
		{GUID_ChartOfCharacteristicTypes, {0,1,13,1,2}},
		{GUID_ChartsOfAccounts,           {0,1,15,1,2}},
		{GUID_ChartsOfCalculationTypes,   {0,1,1,1,2}},
		{GUID_AccumulationRegisters,      {0,1,13,1,2}},
		{GUID_Sequences,                  {0,1,7,1,2}},
		{GUID_DataProcessors,             {0,1,3,1,2}},
		{GUID_Enums,                      {0,1,5,1,2}},
        {GUID_DefinedTypes,               {0,1,3,2}},
		{GUID_Bots,                       {0,1,1,2}}
	};

	auto pathIt = namePaths.find(guid_md);

	if (pathIt == namePaths.end()) {
		// GUID не найден в карте путей, пропустить
		return;
	}

	tree* node_md = find_node_by_guid(tr, guid_md);
	if (!node_md) {
		return; // Защита от nullptr
	}

	const std::vector<int>& path = pathIt->second;

	int CountMD = (node_md->get_next())->get_value().ToInt();

	md_list.clear();

	tree* curNode = node_md->get_next();
	while (curNode)
	{
		curNode = curNode->get_next();
		if (curNode)
		{
			filedata = cf->GetFile(curNode->get_value());
			if(!filedata)
			{
				s = L"Ошибка получения файла ";
				s += (curNode->get_value());
				s += L" конфигурации";
				//mess->AddError(s);
				//return;
				continue; // Продолжить с следующим
			}

			tree_md = get_treeFromV8file(filedata);
			if(!tree_md)
			{
				s = L"Ошибка разбора файла ";
				s += (curNode->get_value());
				s += L" конфигурации";
				//mess->AddError(s);
				//return;
				continue;
			}
			node = tree_md;

			for (int idx : path)
			{
				node = &(*node)[idx];
			}

			String val = node->get_value();

			// Создание объектов для специфических типов
			if (guid_md == GUID_Catalogs)
			{
				TCatalogs* CurCatalogs = new TCatalogs(cf, curNode->get_value(), val);
				MainForm->mdCatalogs->Add(CurCatalogs);
			}
			else if (guid_md == GUID_Languages)
			{
				TLangs* CurLang = new TLangs(cf, curNode->get_value(), val);
                MainForm->mdLanguages->Add(CurLang);
			}
			else if (guid_md == GUID_CommonModules)
			{
				// TODO: Реализовать чтение общих модулей
				TCommonModules* CurModule = new TCommonModules(cf, curNode->get_value(), val);
                MainForm->mdCommonModules->Add(CurModule);
			}
			else if (guid_md == GUID_Roles)
			{}
			else if (guid_md == GUID_CommonTemplates)
			{
				TCommonTemplates* CurCommonTemplate = new TCommonTemplates(cf, curNode->get_value(), val);
				MainForm->mdCommonTemplates->Add(CurCommonTemplate);
			}
			else if (guid_md == GUID_HTTPServices)
			{
				THTTPServices* CurHTTPService = new THTTPServices(cf, curNode->get_value(), val);
				MainForm->mdHTTPServices->Add(CurHTTPService);
			}
			else if (guid_md == GUID_ScheduledJobs)
			{
				TScheduledJobs* CurScheduledJob = new TScheduledJobs(cf, curNode->get_value(), val);
				MainForm->mdScheduledJobs->Add(CurScheduledJob);
			}
			else if (guid_md == GUID_CommonAttributes)
			{
				TCommonAttributes* CurCommonAtt = new TCommonAttributes(cf, curNode->get_value(), val);
				MainForm->mdCommonAttributes->Add(CurCommonAtt);
			}
			else if (guid_md == GUID_SessionParameters)
			{
				TSessionParameters* CurSessionParam = new TSessionParameters(cf, curNode->get_value(), val);
				MainForm->mdSessionParameters->Add(CurSessionParam);
			}
			else if (guid_md == GUID_FunctionalOptionsParameters)
			{
				TFunctionalOptionsParameters* CurFOP = new TFunctionalOptionsParameters(cf, curNode->get_value(), val);
				MainForm->mdFunctionalOptionsParameters->Add(CurFOP);
			}
			else if (guid_md == GUID_Subsystems)
			{}
			else if (guid_md == GUID_Interfaces)
			{
				TInterfaces* CurInterface = new TInterfaces(cf, curNode->get_value(), val);
				MainForm->mdInterfaces->Add(CurInterface);
			}
			else if (guid_md == GUID_Styles)
			{}
			else if (guid_md == GUID_FilterCriteria)
			{
				TFilterCriteria* CurFilter = new TFilterCriteria(cf, curNode->get_value(), val);
				MainForm->mdFilterCriteria->Add(CurFilter);
			}
			else if (guid_md == GUID_SettingsStorages)
			{
				TSettingsStorages* CurSettingsStorage = new TSettingsStorages(cf, curNode->get_value(), val);
				MainForm->mdSettingsStorages->Add(CurSettingsStorage);
			}

			else if (guid_md == GUID_StyleItems)
			{}
			else if (guid_md == GUID_CommonPictures)
			{
				TCommonPictures* CurCommonPicture = new TCommonPictures(cf, curNode->get_value(), val);
				MainForm->mdCommonPictures->Add(CurCommonPicture);
			}
			else if (guid_md == GUID_ExchangePlans)
			{
				TExchangePlans* CurExchPlan = new TExchangePlans(cf, curNode->get_value(), val);
				MainForm->mdExchangePlans->Add(CurExchPlan);
			}
			else if (guid_md == GUID_EventSubscriptions)
			{
				TEventSubscriptions* CurEventSub = new TEventSubscriptions(cf, curNode->get_value(), val);
				MainForm->mdEventSubscriptions->Add(CurEventSub);
			}
			else if (guid_md == GUID_WebServices)
			{
				TWebServices* CurWebService = new TWebServices(cf, curNode->get_value(), val);
				MainForm->mdWebServices->Add(CurWebService);
			}
			else if (guid_md == GUID_FunctionalOptions)
			{
				TFunctionalOptions* CurFO = new TFunctionalOptions(cf, curNode->get_value(), val);
				MainForm->mdFunctionalOptions->Add(CurFO);
			}
			else if (guid_md == GUID_DefinedTypes)
			{
				TDefinedTypes* CurDefinedType = new TDefinedTypes(cf, curNode->get_value(), val);
				MainForm->mdDefinedTypes->Add(CurDefinedType);
			}
			else if (guid_md == GUID_XDTOPackages)
			{
				TXDTOPackages* CurXDTOPackage = new TXDTOPackages(cf, curNode->get_value(), val);
				MainForm->mdXDTOPackages->Add(CurXDTOPackage);
			}
			else if (guid_md == GUID_WSReferences)
			{}
			else if (guid_md == GUID_Constants)
			{
				TConstants* CurConstant = new TConstants(cf, curNode->get_value(), val);
				MainForm->mdConstants->Add(CurConstant);
			}
			else if (guid_md == GUID_Documents)
			{
				TDocuments* CurDocuments = new TDocuments(cf, curNode->get_value(), val);
				MainForm->mdDocuments->Add(CurDocuments);
			}
			else if (guid_md == GUID_CommonForms)
			{
				TCommonForms* CurCommonForm = new TCommonForms(cf, curNode->get_value(), val);
				MainForm->mdCommonForms->Add(CurCommonForm);
			}
			else if (guid_md == GUID_InformationRegisters)
			{
				TInformationRegisters* CurIReg = new TInformationRegisters(cf, curNode->get_value(), val);
				MainForm->mdInformationRegisters->Add(CurIReg);
			}
			else if (guid_md == GUID_CalculationRegisters)
			{
				TCalculationRegisters* CurCReg = new TCalculationRegisters(cf, curNode->get_value(), val);
				MainForm->mdCalculationRegisters->Add(CurCReg);
			}
			else if (guid_md == GUID_BusinessProcesses)
			{}
			else if (guid_md == GUID_Tasks)
			{}
			else if (guid_md == GUID_AccountingRegisters)
			{
				TAccountingRegisters* CurAReg = new TAccountingRegisters(cf, curNode->get_value(), val);
				MainForm->mdAccountingRegisters->Add(CurAReg);
			}
			else if (guid_md == GUID_CommandGroups)
			{
				TCommandGroups* CurCommandGroup = new TCommandGroups(cf, curNode->get_value(), val);
				MainForm->mdCommandGroups->Add(CurCommandGroup);
			}
			else if (guid_md == GUID_CommonCommands)
			{
				TCommonCommands* CurCommonCommand = new TCommonCommands(cf, curNode->get_value(), val);
				MainForm->mdCommonCommands->Add(CurCommonCommand);
			}
			else if (guid_md == GUID_Numerators)
			{
				TNumerators* CurNumerator = new TNumerators(cf, curNode->get_value(), val);
				MainForm->mdDocumentNumerators->Add(CurNumerator);
			}
			else if (guid_md == GUID_JournDocuments)
			{
				TJournals* CurJournal = new TJournals(cf, curNode->get_value(), val);
				MainForm->mdDocumentJournals->Add(CurJournal);
			}
			else if (guid_md == GUID_Reports)
			{
				TReports* CurReport = new TReports(cf, curNode->get_value(), val);
				MainForm->mdReports->Add(CurReport);
			}
			else if (guid_md == GUID_ChartOfCharacteristicTypes)
			{
				TChartOfCharacteristicTypes* CCT = new TChartOfCharacteristicTypes(cf, curNode->get_value(), val);
				MainForm->mdChartsOfCharacteristicTypes->Add(CCT);
			}
			else if (guid_md == GUID_ChartsOfAccounts)  // план счетов
			{
				TChartOfAccounts* CurCACC = new TChartOfAccounts(cf, curNode->get_value(), val);
				MainForm->mdChartOfAccounts->Add(CurCACC);
			}
			else if (guid_md == GUID_ChartsOfCalculationTypes)
			{
				TChartOfCalculationTypes* CurCCT = new TChartOfCalculationTypes(cf, curNode->get_value(), val);
				MainForm->mdChartOfCalculationTypes->Add(CurCCT);
			}
			else if (guid_md == GUID_AccumulationRegisters)
			{
				TAccumulationRegisters* CurAReg = new TAccumulationRegisters(cf, curNode->get_value(), val);
				MainForm->mdAccumulationRegisters->Add(CurAReg);
			}
			else if (guid_md == GUID_Sequences)
			{
				TSequences* CurSequence = new TSequences(cf, curNode->get_value(), val);
				MainForm->mdSequences->Add(CurSequence);
			}
			else if (guid_md == GUID_DataProcessors)
			{
				TDataProcessors* CurDataProcessor = new TDataProcessors(cf, curNode->get_value(), val);
				MainForm->mdDataProcessors->Add(CurDataProcessor);
			}
			else if (guid_md == GUID_Enums)
			{
				TEnums* CurEnums = new TEnums(cf, curNode->get_value(), val);
				MainForm->mdEnums->Add(CurEnums);
			}
			else if (guid_md == GUID_Bots)
			{
				TBots* CurBot = new TBots(cf, curNode->get_value(), val);
				MainForm->mdBots->Add(CurBot);
			}
			md_list.push_back(val);
			delete tree_md;
		}

	}

}

void get_cf_name(tree* tr, Messager* mess)
{
	int j, k;
	tree* node;
	tree* node2;
	tree* node3;
	tree* node_Catalogs;
	tree* node_md;
	tree* curNode;
	String cf_synonym;
	String cf_version;
	String s;
	bool ok;
	int structver;
	int offset_name;
	int offset_ver;
	int CountCatalogs;

	node = tr;
	node = &(*node)[0][3][1][1];

	node3 = tr;

	// Заполняем справочники
	fill_md(tr, GUID_Catalogs, MainForm->Catalogs);
	mess->AddMessage(L"Справочники обработаны", MessageState::msInfo);

	// Заполняем языки
	fill_md(tr, GUID_Languages, MainForm->Languages);
	mess->AddMessage(L"Языки обработаны", MessageState::msInfo);

	// Заполняем регистры накопления
	fill_md(tr, GUID_AccumulationRegisters, MainForm->AccumulationRegisters);
	mess->AddMessage(L"Регистры накопления обработаны", MessageState::msInfo);

	// Заполняем регистры бухгалтерии
	fill_md(tr, GUID_AccountingRegisters, MainForm->AccountingRegisters);
	mess->AddMessage(L"Регистры бухгалтерии обработаны", MessageState::msInfo);

	// Заполняем регистры расчета
	fill_md(tr, GUID_CalculationRegisters, MainForm->CalculationRegisters);
	mess->AddMessage(L"Регистры расчета обработаны", MessageState::msInfo);

	// Заполняем бизнес-процессы
	fill_md(tr, GUID_BusinessProcesses, MainForm->BusinessProcesses);
	mess->AddMessage(L"Бизнес-процессы обработаны", MessageState::msInfo);

	// ПВХ
	fill_md(tr, GUID_ChartOfCharacteristicTypes, MainForm->ChartsOfCharacteristicTypes);
	mess->AddMessage(L"Планы видов характеристик обработаны", MessageState::msInfo);


	// группы команд
	fill_md(tr, GUID_CommandGroups, MainForm->CommandGroups);
	mess->AddMessage(L"Группы команд обработаны", MessageState::msInfo);


	// общие реквизиты
	fill_md(tr, GUID_CommonAttributes, MainForm->CommonAttributes);
	mess->AddMessage(L"Общие реквизиты обработаны", MessageState::msInfo);

	// общие команды
	fill_md(tr, GUID_CommonCommands, MainForm->CommonCommands);
	mess->AddMessage(L"Общие команды обработаны", MessageState::msInfo);

	// общие формы
	fill_md(tr, GUID_CommonForms, MainForm->CommonForms);
	mess->AddMessage(L"Общие формы обработаны", MessageState::msInfo);

	// общие модули
	fill_md(tr, GUID_CommonModules, MainForm->CommonModules);
	mess->AddMessage(L"Общие модули обработаны", MessageState::msInfo);


	// общие картинки
	fill_md(tr, GUID_CommonPictures, MainForm->CommonPictures);
	mess->AddMessage(L"Общие картинки обработаны", MessageState::msInfo);

	// общие макеты
	fill_md(tr, GUID_CommonTemplates, MainForm->CommonTemplates);
	mess->AddMessage(L"Общие макеты обработаны", MessageState::msInfo);

	// константы
	fill_md(tr, GUID_Constants, MainForm->Constants);
	mess->AddMessage(L"Константы обработаны: " + IntToStr((int)MainForm->Constants.size()), MessageState::msInfo);

	// обработки
	fill_md(tr, GUID_DataProcessors, MainForm->DataProcessors);
	mess->AddMessage(L"Обработки обработаны", MessageState::msInfo);

	// определяемые типы
	fill_md(tr, GUID_DefinedTypes, MainForm->DefinedTypes);
	mess->AddMessage(L"Определяемые типы обработаны", MessageState::msInfo);

	// журналы документов
	fill_md(tr, GUID_JournDocuments, MainForm->DocumentJournals);
	mess->AddMessage(L"Журналы документов обработаны", MessageState::msInfo);

	// нумераторы
	fill_md(tr, GUID_Numerators, MainForm->DocumentNumerators);
	mess->AddMessage(L"Нумераторы обработаны", MessageState::msInfo);

	// документы
	fill_md(tr, GUID_Documents, MainForm->Documents);
	mess->AddMessage(L"Документы обработаны", MessageState::msInfo);

	// перечисления
	fill_md(tr, GUID_Enums, MainForm->Enums);
	mess->AddMessage(L"Перечисления обработаны", MessageState::msInfo);

	// подписки на события
	fill_md(tr, GUID_EventSubscriptions, MainForm->EventSubscriptions);
	mess->AddMessage(L"Подписки на события обработаны", MessageState::msInfo);

	// планы обмена
	fill_md(tr, GUID_ExchangePlans, MainForm->ExchangePlans);
	mess->AddMessage(L"Планы обмена обработаны", MessageState::msInfo);

	// планы счетов
	fill_md(tr, GUID_ChartsOfAccounts, MainForm->ChartOfAccounts);
	mess->AddMessage(L"Планы счетов обработаны", MessageState::msInfo);

	// планы видов расчета
	fill_md(tr, GUID_ChartsOfCalculationTypes, MainForm->ChartOfCalculationTypes);
	mess->AddMessage(L"Планы видов расчета обработаны", MessageState::msInfo);

	// внешние источники данных
	fill_md(tr, GUID_ExternalDataSources, MainForm->ExternalDataSources);
	mess->AddMessage(L"Внешние источники данных обработаны", MessageState::msInfo);

	// критерии отбора
	fill_md(tr, GUID_FilterCriteria, MainForm->FilterCriteria);
	mess->AddMessage(L"Критерии отбора обработаны", MessageState::msInfo);

	// функциональные опции
	fill_md(tr, GUID_FunctionalOptions, MainForm->FunctionalOptions);
	mess->AddMessage(L"Функциональные опции обработаны", MessageState::msInfo);

	// параметры функциональных опций
	fill_md(tr, GUID_FunctionalOptionsParameters, MainForm->FunctionalOptionsParameters);
	mess->AddMessage(L"Параметры функциональных опций обработаны", MessageState::msInfo);

	// http - сервисы
	fill_md(tr, GUID_HTTPServices, MainForm->HTTPServices);
	mess->AddMessage(L"http - сервисы обработаны", MessageState::msInfo);

	// регистры сведений
	fill_md(tr, GUID_InformationRegisters, MainForm->InformationRegisters);
	mess->AddMessage(L"Регистры сведений обработаны", MessageState::msInfo);

	// интерфейсы
	fill_md(tr, GUID_Interfaces, MainForm->Interfaces);
	mess->AddMessage(L"Интерфейсы обработаны", MessageState::msInfo);

	// отчеты
	fill_md(tr, GUID_Reports, MainForm->Reports);
	mess->AddMessage(L"Отчеты обработаны", MessageState::msInfo);

	// роли
	fill_md(tr, GUID_Roles, MainForm->Roles);
	mess->AddMessage(L"Роли обработаны", MessageState::msInfo);

	// параметры сеанса
	fill_md(tr, GUID_SessionParameters, MainForm->SessionParameters);
	mess->AddMessage(L"Параметры сеанса обработаны", MessageState::msInfo);

	// хранилища настроек
	fill_md(tr, GUID_SettingsStorages, MainForm->SettingsStorages);
	mess->AddMessage(L"Хранилища настроек обработаны", MessageState::msInfo);

	// элементы стиля
	fill_md(tr, GUID_StyleItems, MainForm->StyleItems);
	mess->AddMessage(L"Элементы стиля обработаны", MessageState::msInfo);

	// стили
	fill_md(tr, GUID_Styles, MainForm->Styles);
	mess->AddMessage(L"Стили обработаны", MessageState::msInfo);

	// подсистемы
	fill_subsystem(tr, MainForm->Subsystems);
	mess->AddMessage(L"Подсистемы обработаны", MessageState::msInfo);

	// задачи
	fill_md(tr, GUID_Tasks, MainForm->Tasks);
	mess->AddMessage(L"Задачи обработаны", MessageState::msInfo);

	// веб-сервисы
	fill_md(tr, GUID_WebServices, MainForm->WebServices);
	mess->AddMessage(L"веб-сервисы обработаны", MessageState::msInfo);

	// ws-ссылки
	fill_md(tr, GUID_WSReferences, MainForm->WSReferences);
	mess->AddMessage(L"ws-ссылки обработаны", MessageState::msInfo);

	// xdto-пакеты
	fill_md(tr, GUID_XDTOPackages, MainForm->XDTOPackages);
	mess->AddMessage(L"xdto-пакеты обработаны", MessageState::msInfo);

	// регл задания
	fill_md(tr, GUID_ScheduledJobs, MainForm->ScheduledJobs);
	mess->AddMessage(L"Регламентные задания обработаны", MessageState::msInfo);

	// боты
	fill_md(tr, GUID_Bots, MainForm->Bots);
	mess->AddMessage(L"Боты обработаны", MessageState::msInfo);

	// последовательности
	fill_md(tr, GUID_Sequences, MainForm->Sequences);
	mess->AddMessage(L"Последовательности обработаны", MessageState::msInfo);

	structver = (*node)[0].get_value().ToInt();

//	switch(structver)
//	{
//		case 15:
//			offset_name = 1;
//			offset_ver = 12;
//			break;
//		case 22:
//		case 32:
//		case 34:
//		case 36:
//		case 37:
//		case 46:
//			offset_name = 1;
//			offset_ver = 15;
//			break;
//		default:
//			s = L"Неизвестная версия ";
//			s += structver;
//			s += L" блока параметров конфигурации";
//			mess->AddError(s);
//			delete tr;
//			return;
//	}

	if(structver <= 15)
	{
		offset_name = 1;
		offset_ver = 12;
	}
	else
	{
		offset_name = 1;
		offset_ver = 15;
	}

	node2 = &(*node)[offset_name][1][3];

	if(node2->get_type() != nd_list)
	{
		mess->AddError(L"Ошибка получения синонима имени конфигурации");
		delete tr;
		return;
	}
	if((*node2)[0].get_type() != nd_number)
	{
		mess->AddError(L"Ошибка получения синонима имени конфигурации");
		delete tr;
		return;
	}

	j = (*node2)[0].get_value().ToIntDef(0);

	if(j == 0)
		cf_synonym = (*node)[offset_name][1][2].get_value();
	else
	{
		ok = false;
		for(k = 0; k < j; k++)
		{
			if((*node2)[k * 2 + 1].get_value().CompareIC(L"ru") == 0)
			{
				cf_synonym = (*node2)[k * 2 + 2].get_value();
				ok = true;
				break;
			}
		}

		if(!ok)
			cf_synonym = (*node2)[2].get_value();
	}

	cf_version = (*node)[offset_ver].get_value();
	delete tr;

	//mess->AddMessage(cf_synonym + " (" + cf_version + ")", msEmpty);
	MainForm->ConfigName = cf_synonym + " (" + cf_version + ")";
	//ConfigName = cf_synonym + " (" + cf_version + ")";
	mess->AddMessage("Прочитана конфигурация: " + cf_synonym + " (" + cf_version + ")", msInfo);

}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete GlobalCF;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::VirtualStringTreeValue1CClick(TObject *Sender)
{
	PVirtualNode Node = VirtualStringTreeValue1C->FocusedNode;

	VirtualTreeData* Data = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);

	MemoObject->Clear();

	if (Data)
	{
		MemoObject->Text = Data->text_module;
	}
}
//---------------------------------------------------------------------------





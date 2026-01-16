//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <System.IOUtils.hpp>
#include <windows.h>
#include <vector>

#include "V8File.h"
#include "ApicfBase.h"
#include "Class_1CD.h"
#include "MainUnit.h"
#include "guids.h"
#include "Catalogs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TMainForm *MainForm;
MessageRegistrator* msreg;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner) : TForm(Owner)
{
	VirtualStringTreeValue1C->NodeDataSize = sizeof(VirtualTreeData);
	mess = new Messager(ListViewMessager, StatusBar1);
	msreg = mess;
	mess->setlogfile(L"S:\\work\\CPP\\BDS13\\v8reader\\Win32\\Debug\\v8reader.log");

	mdCatalogs = new TObjectList(true);
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

void __fastcall TMainForm::TreeInit()
{
    VirtualStringTreeValue1C->Clear();
	PVirtualNode RootNode = VirtualStringTreeValue1C->AddChild(nullptr);
	VirtualTreeData *RootData = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(RootNode);
	//RootData->Name = "Типы_ 1С";
    RootData->Name = MainForm->ConfigName;
	RootData->Age = 100;
	RootData->ImgIndex = 72;

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
	for(int i = 0; i < MainForm->CommandGroups.size(); i++)
	{
		PVirtualNode ChildNodeComGroup = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataComGroup = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeComGroup);
		ChildNodeDataComGroup->Name = MainForm->CommandGroups[i];
		ChildNodeDataComGroup->Age = 30;
		ChildNodeDataComGroup->ImgIndex = 99;
	}




	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_CommonForms; //"Общие формы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 86;
	for(int i = 0; i < MainForm->CommonForms.size(); i++)
	{
		PVirtualNode ChildNodeComF = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataComF = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeComF);
		ChildNodeDataComF->Name = MainForm->CommonForms[i];
		ChildNodeDataComF->Age = 30;
		ChildNodeDataComF->ImgIndex = 86;
	}

	ChildNode1 = VirtualStringTreeValue1C->AddChild(ChildNode);
	ChildData1 = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNode1);
	ChildData1->Name = md_Interfaces; //"Интерфейсы";
	ChildData1->Age = 30;
	ChildData1->ImgIndex = 80;
	for(int i = 0; i < MainForm->Interfaces.size(); i++)
	{
		PVirtualNode ChildNodeInt = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataInt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeInt);
		ChildNodeDataInt->Name = MainForm->Interfaces[i];
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
	for(int i = 0; i < MainForm->HTTPServices.size(); i++)
	{
		PVirtualNode ChildNodeHTTPServices = VirtualStringTreeValue1C->AddChild(ChildNode1);
		VirtualTreeData *ChildNodeDataHTTPServices = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeHTTPServices);
		ChildNodeDataHTTPServices->Name = MainForm->HTTPServices[i];
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


	// Еще один дочерний узел
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
		for (i = 0; i < CurCat->attributes.size(); i++)
		{
			PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatAtt);
			VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
			ChildNodeDataCatCurAtt->Name = CurCat->attributes[i];
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
		for (i = 0; i < CurCat->tabulars.size(); i++)
		{
			PVirtualNode ChildNodeCatCurAtt = VirtualStringTreeValue1C->AddChild(ChildNodeCatTabs);
			VirtualTreeData *ChildNodeDataCatCurAtt = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurAtt);
			ChildNodeDataCatCurAtt->Name = CurCat->tabulars[i];
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
		for (i = 0; i < CurCat->forms.size(); i++)
		{
			PVirtualNode ChildNodeCatCurForm = VirtualStringTreeValue1C->AddChild(ChildNodeCatForm);
			VirtualTreeData *ChildNodeDataCatCurForm = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurForm);
			ChildNodeDataCatCurForm->Name = CurCat->forms[i];
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
		for (i = 0; i < CurCat->comands.size(); i++)
		{
			PVirtualNode ChildNodeCatCurCom = VirtualStringTreeValue1C->AddChild(ChildNodeCatCom);
			VirtualTreeData *ChildNodeDataCatCurCom = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurCom);
			ChildNodeDataCatCurCom->Name = CurCat->comands[i];
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
		for (i = 0; i < CurCat->moxels.size(); i++)
		{
			PVirtualNode ChildNodeCatCurMox = VirtualStringTreeValue1C->AddChild(ChildNodeCatMoxel);
			VirtualTreeData *ChildNodeDataCatCurMox = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatCurMox);
			ChildNodeDataCatCurMox->Name = CurCat->moxels[i];
			ChildNodeDataCatCurMox->Age = 30;
			ChildNodeDataCatCurMox->ImgIndex = 79;
		}
	}

//	for(int i = 0; i < MainForm->Catalogs.size(); i++)
//	{
//		PVirtualNode ChildNodeCatalogs = VirtualStringTreeValue1C->AddChild(ChildNode);
//		VirtualTreeData *ChildNodeDataCatalogs = (VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(ChildNodeCatalogs);
//		ChildNodeDataCatalogs->Name = MainForm->Catalogs[i];
//		ChildNodeDataCatalogs->Age = 30;
//		ChildNodeDataCatalogs->ImgIndex = 1;
//	}

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
}



void __fastcall TMainForm::VirtualStringTreeValue1CFreeNode(TBaseVirtualTree *Sender, PVirtualNode Node)
{
	VirtualTreeData *RootData =(VirtualTreeData*)VirtualStringTreeValue1C->GetNodeData(Node);
	if(!RootData)
		delete RootData;
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
		  //v8catalog *cf = new v8catalog(filename, true);
		  //MainForm->GlobalCF = new v8catalog(filename, true);
          GlobalCF = new v8catalog(filename, true);
		  //mess->AddMessage("Тестовое сообщение", MessageState::msInfo);
		  get_cf_name(GlobalCF, mess);
		  TreeInit();
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


	tree* node_md = find_node_by_guid(tr, guid_md); //"cf4abea6-37b2-11d4-940f-008048da11f9"

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
				return;
			}

			tree_md = get_treeFromV8file(filedata);
			if(!tree_md)
			{
				s = L"Ошибка разбора файла ";
				s += (curNode->get_value());
				s += L" конфигурации";
				//mess->AddError(s);
				return;
			}
			node = tree_md;

			if (guid_md == GUID_Catalogs)
			{
				node = &(*node)[0][1][9][1][2];
				auto val = node->get_value();
				TCatalogs* CurCatalogs = new TCatalogs(cf, curNode->get_value(), val);
				MainForm->mdCatalogs->Add(CurCatalogs);

				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Languages)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}

			else if (guid_md == GUID_CommonModules)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Roles)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommonTemplates)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_HTTPServices)
			{
				node = &(*node)[0][1][2][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_ScheduledJobs)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommonAttributes)
			{
				node = &(*node)[0][1][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_SessionParameters)
			{
				node = &(*node)[0][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_FunctionalOptionsParameters)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Subsystems)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Interfaces)
			{
				node = &(*node)[0][1][2][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Styles)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_FilterCriteria)
			{
				node = &(*node)[0][1][5][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_SettingsStorages)
			{
				node = &(*node)[0][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_EventSubscriptions)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_StyleItems)
			{
				node = &(*node)[0][1][3][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommonPictures)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_ExchangePlans)
			{
				node = &(*node)[0][1][12][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_WebServices)
			{
				node = &(*node)[0][1][2][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_FunctionalOptions)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_DefinedTypes)
			{
				node = &(*node)[0][1][3][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_XDTOPackages)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_WSReferences)
			{
//				node = &(*node)[0][1][9][1][2];
//				auto val = node->get_value();
//				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Constants)
			{
				node = &(*node)[0][1][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Documents)
			{
				node = &(*node)[0][1][9][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommonForms)
			{
				node = &(*node)[0][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_InformationRegisters)
			{
				node = &(*node)[0][1][15][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CalculationRegisters)
			{
				node = &(*node)[0][1][15][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_BusinessProcesses)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Tasks)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_AccountingRegisters)
			{
				node = &(*node)[0][1][16][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommandGroups)
			{
				node = &(*node)[0][1][6][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_CommonCommands)
			{
				node = &(*node)[0][1][1][2][9][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Numerators)
			{
				node = &(*node)[0][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_JournDocuments)
			{
				node = &(*node)[0][1][3][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Reports)
			{
				node = &(*node)[0][1][3][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_ChartOfCharacteristicTypes)
			{
				node = &(*node)[0][1][13][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_ChartsOfAccounts)
			{
				node = &(*node)[0][1][15][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_ChartsOfCalculationTypes)
			{
				node = &(*node)[0][1][1][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}

			else if (guid_md == GUID_AccumulationRegisters)
			{
				node = &(*node)[0][1][13][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Sequences)
			{
				node = &(*node)[0][1][7][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_DataProcessors)
			{
				node = &(*node)[0][1][3][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}
			else if (guid_md == GUID_Enums)
			{
				node = &(*node)[0][1][5][1][2];
				auto val = node->get_value();
				md_list.push_back(node->get_value());
			}


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
    mess->AddError(L"Справочники обработаны");
	// Заполняем языки
	fill_md(tr, GUID_Languages, MainForm->Languages);
	mess->AddError(L"Языки обработаны");
	// Заполняем регистры накопления
	fill_md(tr, GUID_AccumulationRegisters, MainForm->AccumulationRegisters);
	mess->AddError(L"РН обработаны");
	// Заполняем регистры бухгалтерии
	fill_md(tr, GUID_AccountingRegisters, MainForm->AccountingRegisters);
	mess->AddError(L"РБ обработаны");
	// Заполняем регистры расчета
	fill_md(tr, GUID_CalculationRegisters, MainForm->CalculationRegisters);
    mess->AddError(L"РР обработаны");
	// Заполняем бизнес-процессы
	fill_md(tr, GUID_BusinessProcesses, MainForm->BusinessProcesses);
	// ПВХ
	fill_md(tr, GUID_ChartOfCharacteristicTypes, MainForm->ChartsOfCharacteristicTypes);
	// группы команд
	fill_md(tr, GUID_CommandGroups, MainForm->CommandGroups);
	// общие реквизиты
	fill_md(tr, GUID_CommonAttributes, MainForm->CommonAttributes);
	// общие команды
	fill_md(tr, GUID_CommonCommands, MainForm->CommonCommands);
	// общие формы
	fill_md(tr, GUID_CommonForms, MainForm->CommonForms);
	// общие модули
	fill_md(tr, GUID_CommonModules, MainForm->CommonModules);
	// общие картинки
	fill_md(tr, GUID_CommonPictures, MainForm->CommonPictures);
	// общие макеты
	fill_md(tr, GUID_CommonTemplates, MainForm->CommonTemplates);
	// константы
	fill_md(tr, GUID_Constants, MainForm->Constants);
	// обработки
	fill_md(tr, GUID_DataProcessors, MainForm->DataProcessors);
	// определяемые типы
	fill_md(tr, GUID_DefinedTypes, MainForm->DefinedTypes);
	// журналы документов
	fill_md(tr, GUID_JournDocuments, MainForm->DocumentJournals);
	// нумераторы
	fill_md(tr, GUID_Numerators, MainForm->DocumentNumerators);
	// документы
	fill_md(tr, GUID_Documents, MainForm->Documents);
	// перечисления
	fill_md(tr, GUID_Enums, MainForm->Enums);
	// подписки на события
	fill_md(tr, GUID_EventSubscriptions, MainForm->EventSubscriptions);
	// планы обмена
	fill_md(tr, GUID_ExchangePlans, MainForm->ExchangePlans);
	// планы счетов
	fill_md(tr, GUID_ChartsOfAccounts, MainForm->ChartOfAccounts);
	// планы видов расчета
	fill_md(tr, GUID_ChartsOfCalculationTypes, MainForm->ChartOfCalculationTypes);
	// внешние источники данных
	fill_md(tr, GUID_ExternalDataSources, MainForm->ExternalDataSources);
	// критерии отбора
	fill_md(tr, GUID_FilterCriteria, MainForm->FilterCriteria);
	// функциональные опции
	fill_md(tr, GUID_FunctionalOptions, MainForm->FunctionalOptions);
	// параметры функциональных опций
	fill_md(tr, GUID_FunctionalOptionsParameters, MainForm->FunctionalOptionsParameters);
	// http - сервисы
	fill_md(tr, GUID_HTTPServices, MainForm->HTTPServices);
	// регистры сведений
	fill_md(tr, GUID_InformationRegisters, MainForm->InformationRegisters);
	// интерфейсы
	fill_md(tr, GUID_Interfaces, MainForm->Interfaces);
	// отчеты
	fill_md(tr, GUID_Reports, MainForm->Reports);
	// роли
	fill_md(tr, GUID_Roles, MainForm->Roles);
	//
	//fill_md(tr, GUID_Bots, MainForm->Bots);
	//
	//fill_md(tr, GUID_, MainForm->ScheduledJobs);
	// параметры сеанса
	fill_md(tr, GUID_SessionParameters, MainForm->SessionParameters);
	// хранилища настроек
	fill_md(tr, GUID_SettingsStorages, MainForm->SettingsStorages);
	// элементы стиля
	fill_md(tr, GUID_StyleItems, MainForm->StyleItems);
	// стили
	fill_md(tr, GUID_Styles, MainForm->Styles);
	// подсистемы
	//fill_md(tr, GUID_Subsystems, MainForm->Subsystems);
	fill_subsystem(tr, MainForm->Subsystems);
	// задачи
	fill_md(tr, GUID_Tasks, MainForm->Tasks);
	// веб-сервисы
	fill_md(tr, GUID_WebServices, MainForm->WebServices);
	// ws-ссылки
	fill_md(tr, GUID_WSReferences, MainForm->WSReferences);
	// xdto-пакеты
	fill_md(tr, GUID_XDTOPackages, MainForm->XDTOPackages);
	// регл задания
	fill_md(tr, GUID_ScheduledJobs, MainForm->ScheduledJobs);
	//
	fill_md(tr, GUID_Sequences, MainForm->Sequences);



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
	mess->AddMessage(cf_synonym + " (" + cf_version + ")", msInfo);

}

void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
	delete GlobalCF;
}
//---------------------------------------------------------------------------


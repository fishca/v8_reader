//---------------------------------------------------------------------------

#pragma hdrstop

#include "APIcfBase.h"
#include "Parse_tree.h"
#include "Class_1CD.h"
#include "guids.h"
#include "MetaDataManager.h"
#include "SessionParameters.h"
#include "Roles.h"
#include "Bots.h"
#include "CommonAttributes.h"
#include "CommonCommands.h"
#include "TConstants.h"
#include "CommandGroups.h"
#include "CommonTemplates.h"
#include "ExchangePlans.h"
#include "EventSubscriptions.h"
#include "ScheduledJobs.h"
#include "FunctionalOptions.h"
#include "FunctionalOptionsParameters.h"
#include "DefinedTypes.h"
#include "SettingsStorages.h"
#include "Interfaces.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


v8catalog* MetaDataManager::loadFromFile(const String& filename)
{
    return new v8catalog(filename, true);
}

bool MetaDataManager::Initialize(v8catalog* cf)
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
		return false;
	}

	filedata = cf->GetFile(L"version");
	if(!filedata)
	{
		return false;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		return false;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
		return false;

	node = tr;

	node = &(*node)[0][0][0];
	if(node->get_type() != nd_number)
	{
		delete tr;
		return false;
	}

	ver = node->get_value().ToInt();
	delete tr;

	if(ver < 100)
	{
		// 8.0
		filedata = cf->GetFile(L"metadata");
		if(!filedata)
		{
			return false;
		}

		cat = filedata->GetCatalog();
		if(!cat)
		{
			return false;
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
		return false;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		return false;
	}

	node = tr;
	node = &(*node)[0][1];

	if(node->get_type() != nd_guid)
	{
		delete tr;
		return false;
	}

	meta = node->get_value();
	delete tr;

	filedata = cat->GetFile(meta);
	if(!filedata)
	{
		return false;
	}

	tr = get_treeFromV8file(filedata);
	if(!tr)
	{
		return false;
	}

	return true;
}

void MetaDataManager::populateTreeView(TVirtualStringTree* tvSringTree)
{

}

std::shared_ptr<MetaObject> MetaDataManager::getObject(const String& type, const String& name)
{

}

void PreFillingMD(tree* tr)
{
//	int j, k;
//	tree* node;
//	tree* node2;
//	tree* node3;
//	tree* node_Catalogs;
//	tree* node_md;
//	tree* curNode;
//	String cf_synonym;
//	String cf_version;
//	String s;
//	bool ok;
//	int structver;
//	int offset_name;
//	int offset_ver;
//	int CountCatalogs;
//
//	node = tr;
//	node = &(*node)[0][3][1][1];
//
//	node3 = tr;
//
//	// Заполняем справочники
//	fill_md(tr, GUID_Catalogs, MainForm->Catalogs);
//
//	// Заполняем языки
//	fill_md(tr, GUID_Languages, MainForm->Languages);
//
//	// Заполняем регистры накопления
//	fill_md(tr, GUID_AccumulationRegisters, MainForm->AccumulationRegisters);
//
//	// Заполняем регистры бухгалтерии
//	fill_md(tr, GUID_AccountingRegisters, MainForm->AccountingRegisters);
//
//	// Заполняем регистры расчета
//	fill_md(tr, GUID_CalculationRegisters, MainForm->CalculationRegisters);
//
//	// Заполняем бизнес-процессы
//	fill_md(tr, GUID_BusinessProcesses, MainForm->BusinessProcesses);
//
//	// ПВХ
//	fill_md(tr, GUID_ChartOfCharacteristicTypes, MainForm->ChartsOfCharacteristicTypes);
//
//	// группы команд
//	fill_md(tr, GUID_CommandGroups, MainForm->CommandGroups);
//
//	// общие реквизиты
//	fill_md(tr, GUID_CommonAttributes, MainForm->CommonAttributes);
//
//	// общие команды
//	fill_md(tr, GUID_CommonCommands, MainForm->CommonCommands);
//
//	// общие формы
//	fill_md(tr, GUID_CommonForms, MainForm->CommonForms);
//
//	// общие модули
//	fill_md(tr, GUID_CommonModules, MainForm->CommonModules);
//
//	// общие картинки
//	fill_md(tr, GUID_CommonPictures, MainForm->CommonPictures);
//
//	// общие макеты
//	fill_md(tr, GUID_CommonTemplates, MainForm->CommonTemplates);
//
//	// константы
//	fill_md(tr, GUID_Constants, MainForm->Constants);
//
//	// обработки
//	fill_md(tr, GUID_DataProcessors, MainForm->DataProcessors);
//
//	// определяемые типы
//	fill_md(tr, GUID_DefinedTypes, MainForm->DefinedTypes);
//
//	// журналы документов
//	fill_md(tr, GUID_JournDocuments, MainForm->DocumentJournals);
//
//	// нумераторы
//	fill_md(tr, GUID_Numerators, MainForm->DocumentNumerators);
//
//	// документы
//	fill_md(tr, GUID_Documents, MainForm->Documents);
//
//	// перечисления
//	fill_md(tr, GUID_Enums, MainForm->Enums);
//
//	// подписки на события
//	fill_md(tr, GUID_EventSubscriptions, MainForm->EventSubscriptions);
//
//	// планы обмена
//	fill_md(tr, GUID_ExchangePlans, MainForm->ExchangePlans);
//
//	// планы счетов
//	fill_md(tr, GUID_ChartsOfAccounts, MainForm->ChartOfAccounts);
//
//	// планы видов расчета
//	fill_md(tr, GUID_ChartsOfCalculationTypes, MainForm->ChartOfCalculationTypes);
//
//	// внешние источники данных
//	fill_md(tr, GUID_ExternalDataSources, MainForm->ExternalDataSources);
//
//	// критерии отбора
//	fill_md(tr, GUID_FilterCriteria, MainForm->FilterCriteria);
//
//	// функциональные опции
//	fill_md(tr, GUID_FunctionalOptions, MainForm->FunctionalOptions);
//
//	// параметры функциональных опций
//	fill_md(tr, GUID_FunctionalOptionsParameters, MainForm->FunctionalOptionsParameters);
//
//	// http - сервисы
//	fill_md(tr, GUID_HTTPServices, MainForm->HTTPServices);
//
//	// регистры сведений
//	fill_md(tr, GUID_InformationRegisters, MainForm->InformationRegisters);
//
//	// интерфейсы
//	fill_md(tr, GUID_Interfaces, MainForm->Interfaces);
//
//	// отчеты
//	fill_md(tr, GUID_Reports, MainForm->Reports);
//
//	// роли
//	fill_md(tr, GUID_Roles, MainForm->Roles);
//
//	// параметры сеанса
//	fill_md(tr, GUID_SessionParameters, MainForm->SessionParameters);
//
//	// хранилища настроек
//	fill_md(tr, GUID_SettingsStorages, MainForm->SettingsStorages);
//
//	// элементы стиля
//	fill_md(tr, GUID_StyleItems, MainForm->StyleItems);
//
//	// стили
//	fill_md(tr, GUID_Styles, MainForm->Styles);
//
//	// подсистемы
//	fill_subsystem(tr, MainForm->Subsystems);
//
//	// задачи
//	fill_md(tr, GUID_Tasks, MainForm->Tasks);
//
//	// веб-сервисы
//	fill_md(tr, GUID_WebServices, MainForm->WebServices);
//
//	// ws-ссылки
//	fill_md(tr, GUID_WSReferences, MainForm->WSReferences);
//
//	// xdto-пакеты
//	fill_md(tr, GUID_XDTOPackages, MainForm->XDTOPackages);
//
//	// регл задания
//	fill_md(tr, GUID_ScheduledJobs, MainForm->ScheduledJobs);
//
//	// последовательности
//	fill_md(tr, GUID_Sequences, MainForm->Sequences);
//
//	structver = (*node)[0].get_value().ToInt();
//
//	if(structver <= 15)
//	{
//		offset_name = 1;
//		offset_ver = 12;
//	}
//	else
//	{
//		offset_name = 1;
//		offset_ver = 15;
//	}
//
//	node2 = &(*node)[offset_name][1][3];
//
//	if(node2->get_type() != nd_list)
//	{
//		delete tr;
//		return;
//	}
//	if((*node2)[0].get_type() != nd_number)
//	{
//		delete tr;
//		return;
//	}
//
//	j = (*node2)[0].get_value().ToIntDef(0);
//
//	if(j == 0)
//		cf_synonym = (*node)[offset_name][1][2].get_value();
//	else
//	{
//		ok = false;
//		for(k = 0; k < j; k++)
//		{
//			if((*node2)[k * 2 + 1].get_value().CompareIC(L"ru") == 0)
//			{
//				cf_synonym = (*node2)[k * 2 + 2].get_value();
//				ok = true;
//				break;
//			}
//		}
//
//		if(!ok)
//			cf_synonym = (*node2)[2].get_value();
//	}
//
//	cf_version = (*node)[offset_ver].get_value();
//	delete tr;
//
//	//mess->AddMessage(cf_synonym + " (" + cf_version + ")", msEmpty);
//	//MainForm->ConfigName = cf_synonym + " (" + cf_version + ")";
//	//ConfigName = cf_synonym + " (" + cf_version + ")";
//	//mess->AddMessage("Прочитана конфигурация: " + cf_synonym + " (" + cf_version + ")", msInfo);

}

// Процедура заполняет метаданные по корневому гуиду
void MetaDataManager::fill_md(v8catalog *cf, tree* tr, String guid_md)
{
//	v8file *filedata;
//	tree* tree_md;
//	tree* node;
//	String s;
//
//	tree* node_md = find_node_by_guid(tr, guid_md); //"cf4abea6-37b2-11d4-940f-008048da11f9"
//
//	int CountMD = (node_md->get_next())->get_value().ToInt();
//
//	tree* curNode = node_md->get_next();
//	while (curNode)
//	{
//		curNode = curNode->get_next();
//		if (curNode)
//		{
//			filedata = cf->GetFile(curNode->get_value());
//			if(!filedata)
//			{
//				return;
//			}
//
//			tree_md = get_treeFromV8file(filedata);
//			if(!tree_md)
//			{
//				return;
//			}
//			node = tree_md;
//
//			if (guid_md == GUID_Catalogs)
//			{
//				node = &(*node)[0][1][9][1][2];
//				auto val = node->get_value();
//				TCatalogs* CurCatalogs = new TCatalogs(cf, curNode->get_value(), val);
//				MainForm->mdCatalogs->Add(CurCatalogs);
//			}
//			else if (guid_md == GUID_Languages)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//
//			else if (guid_md == GUID_CommonModules)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Roles)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CommonTemplates)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_HTTPServices)
//			{
//				node = &(*node)[0][1][2][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_ScheduledJobs)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CommonAttributes)
//			{
//				node = &(*node)[0][1][1][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_SessionParameters)
//			{
//				node = &(*node)[0][1][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_FunctionalOptionsParameters)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Subsystems)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Interfaces)
//			{
//				node = &(*node)[0][1][2][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Styles)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_FilterCriteria)
//			{
//				node = &(*node)[0][1][5][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_SettingsStorages)
//			{
//				node = &(*node)[0][1][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_EventSubscriptions)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_StyleItems)
//			{
//				node = &(*node)[0][1][3][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CommonPictures)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_ExchangePlans)
//			{
//				node = &(*node)[0][1][12][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_WebServices)
//			{
//				node = &(*node)[0][1][2][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_FunctionalOptions)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_DefinedTypes)
//			{
//				node = &(*node)[0][1][3][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_XDTOPackages)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_WSReferences)
//			{
////				node = &(*node)[0][1][9][1][2];
////				auto val = node->get_value();
////				md_list.push_back(node->get_value());
//			}
//			else if (guid_md == GUID_Constants)
//			{
//				node = &(*node)[0][1][1][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Documents)
//			{
//				node = &(*node)[0][1][9][1][2];
//				auto val = node->get_value();
//				TDocuments* CurDocuments = new TDocuments(cf, curNode->get_value(), val);
//				MainForm->mdDocuments->Add(CurDocuments);
//			}
//			else if (guid_md == GUID_CommonForms)
//			{
//				node = &(*node)[0][1][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_InformationRegisters)
//			{
//				node = &(*node)[0][1][15][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CalculationRegisters)
//			{
//				node = &(*node)[0][1][15][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_BusinessProcesses)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Tasks)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_AccountingRegisters)
//			{
//				node = &(*node)[0][1][16][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CommandGroups)
//			{
//				node = &(*node)[0][1][6][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_CommonCommands)
//			{
//				node = &(*node)[0][1][1][2][9][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Numerators)
//			{
//				node = &(*node)[0][1][1][2];
//				auto val = node->get_value();
//				TNumerators* CurNumerator = new TNumerators(cf, curNode->get_value(), val);
//				MainForm->mdDocumentNumerators->Add(CurNumerator);
//			}
//			else if (guid_md == GUID_JournDocuments)
//			{
//				node = &(*node)[0][1][3][1][2];
//				auto val = node->get_value();
//				TJournals* CurJournal = new TJournals(cf, curNode->get_value(), val);
//				MainForm->mdDocumentJournals->Add(CurJournal);
//			}
//			else if (guid_md == GUID_Reports)
//			{
//				node = &(*node)[0][1][3][1][2];
//				auto val = node->get_value();
//				TReports* CurReport = new TReports(cf, curNode->get_value(), val);
//				MainForm->mdReports->Add(CurReport);
//			}
//			else if (guid_md == GUID_ChartOfCharacteristicTypes)
//			{
//				node = &(*node)[0][1][13][1][2];
//				auto val = node->get_value();
//				TChartOfCharacteristicTypes* CCT = new TChartOfCharacteristicTypes(cf, curNode->get_value(), val);
//				MainForm->mdChartsOfCharacteristicTypes->Add(CCT);
//			}
//			else if (guid_md == GUID_ChartsOfAccounts)
//			{
//				node = &(*node)[0][1][15][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_ChartsOfCalculationTypes)
//			{
//				node = &(*node)[0][1][1][1][2];
//				auto val = node->get_value();
//			}
//
//			else if (guid_md == GUID_AccumulationRegisters)
//			{
//				node = &(*node)[0][1][13][1][2];
//				auto val = node->get_value();
//			}
//			else if (guid_md == GUID_Sequences)
//			{
//				node = &(*node)[0][1][7][1][2];
//				auto val = node->get_value();
//				TSequences* CurSequence = new TSequences(cf, curNode->get_value(), val);
//				MainForm->mdSequences->Add(CurSequence);
//			}
//			else if (guid_md == GUID_DataProcessors)
//			{
//				node = &(*node)[0][1][3][1][2];
//				auto val = node->get_value();
//				TDataProcessors* CurDataProcessor = new TDataProcessors(cf, curNode->get_value(), val);
//				MainForm->mdDataProcessors->Add(CurDataProcessor);
//			}
//			else if (guid_md == GUID_Enums)
//			{
//				node = &(*node)[0][1][5][1][2];
//				auto val = node->get_value();
//				TEnums* CurEnums = new TEnums(cf, curNode->get_value(), val);
//				MainForm->mdEnums->Add(CurEnums);
//			}
//
//
//		}
//
//	}

}

// Метод для получения списка параметров сеанса
vector<shared_ptr<TSessionParameters>>& MetaDataManager::getSessionParameters()
{
	return SessionParameters;
}

// Метод для получения списка общих реквизитов
vector<shared_ptr<TCommonAttributes>>& MetaDataManager::getCommonAttributes()
{
	return CommonAttributes;
}

// Метод для получения списка общих команд
vector<shared_ptr<TCommonCommands>>& MetaDataManager::getCommonCommands()
{
	return CommonCommands;
}

// Метод для получения списка общих макетов
vector<shared_ptr<TCommonTemplates>>& MetaDataManager::getCommonTemplates()
{
	return CommonTemplates;
}

// Метод для получения списка групп команд
vector<shared_ptr<TCommandGroups>>& MetaDataManager::getCommandGroups()
{
	return CommandGroups;
}

// Метод для получения списка планов обмена
vector<shared_ptr<TExchangePlans>>& MetaDataManager::getExchangePlans()
{
	return ExchangePlans;
}

// Метод для получения списка подписок на события
vector<shared_ptr<TEventSubscriptions>>& MetaDataManager::getEventSubscriptions()
{
	return EventSubscriptions;
}

// Метод для получения списка регламентных заданий
vector<shared_ptr<TScheduledJobs>>& MetaDataManager::getScheduledJobs()
{
	return ScheduledJobs;
}

// Метод для получения списка ботов
vector<shared_ptr<TBots>>& MetaDataManager::getBots()
{
	return Bots;
}

// Метод для получения списка функциональных опций
vector<shared_ptr<TFunctionalOptions>>& MetaDataManager::getFunctionalOptions()
{
	return FunctionalOptions;
}

// Метод для получения списка параметров функциональных опций
vector<shared_ptr<TFunctionalOptionsParameters>>& MetaDataManager::getFunctionalOptionsParameters()
{
	return FunctionalOptionsParameters;
}

// Метод для получения списка определяемых типов
vector<shared_ptr<TDefinedTypes>>& MetaDataManager::getDefinedTypes()
{
	return DefinedTypes;
}

// Метод для получения списка хранилищ настроек
vector<shared_ptr<TSettingsStorages>>& MetaDataManager::getSettingsStorages()
{
	return SettingsStorages;
}

// Метод для получения списка интерфейсов
vector<shared_ptr<TInterfaces>>& MetaDataManager::getInterfaces()
{
	return Interfaces;
}

// Метод для получения списка констант
vector<shared_ptr<TConstants>>& MetaDataManager::getConstants()
{
	return Constants;
}

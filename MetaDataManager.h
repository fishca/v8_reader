//---------------------------------------------------------------------------

#ifndef MetaDataManagerH
#define MetaDataManagerH
//---------------------------------------------------------------------------

#include "VirtualTrees.hpp"

#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <map>
#include <optional>
#include <variant>

#include "APIcfBase.h"
#include "MetaObject.h"
#include "SessionParameters.h"
#include "Roles.h"
#include "Bots.h"
#include "CommonAttributes.h"
#include "CommonCommands.h"
#include "CommonTemplates.h"
#include "CommandGroups.h"
#include "ExchangePlans.h"
#include "EventSubscriptions.h"
#include "ScheduledJobs.h"
#include "FunctionalOptions.h"
#include "FunctionalOptionsParameters.h"
#include "DefinedTypes.h"
#include "SettingsStorages.h"
#include "Interfaces.h"


using namespace std;


class MetaDataManager {
private:
	map<String, vector<shared_ptr<MetaObject>>> ObjectsByType;
	vector<shared_ptr<TSessionParameters>> SessionParameters;
	vector<shared_ptr<TRoles>> Roles;
	vector<shared_ptr<TBots>> Bots;
	vector<shared_ptr<TCommonAttributes>> CommonAttributes;
	vector<shared_ptr<TCommonCommands>> CommonCommands;
	vector<shared_ptr<TCommonTemplates>> CommonTemplates;
	vector<shared_ptr<TCommandGroups>> CommandGroups;
	vector<shared_ptr<TExchangePlans>> ExchangePlans;
	vector<shared_ptr<TEventSubscriptions>> EventSubscriptions;
	vector<shared_ptr<TScheduledJobs>> ScheduledJobs;
	vector<shared_ptr<TFunctionalOptions>> FunctionalOptions;
	vector<shared_ptr<TFunctionalOptionsParameters>> FunctionalOptionsParameters;
	vector<shared_ptr<TDefinedTypes>> DefinedTypes;
	vector<shared_ptr<TSettingsStorages>> SettingsStorages;
	vector<shared_ptr<TInterfaces>> Interfaces;
public:
	v8catalog* loadFromFile(const String& filename);
	bool Initialize(v8catalog* cf);
    void fill_md(v8catalog *cf, tree* tr, String guid_md);
	void populateTreeView(TVirtualStringTree* tvSringTree);
	shared_ptr<MetaObject> getObject(const String& type, const String& name);
	vector<shared_ptr<TSessionParameters>>& getSessionParameters();
	vector<shared_ptr<TRoles>>& getRoles();
	vector<shared_ptr<TBots>>& getBots();
	vector<shared_ptr<TCommonAttributes>>& getCommonAttributes();
	vector<shared_ptr<TCommonCommands>>& getCommonCommands();
	vector<shared_ptr<TCommonTemplates>>& getCommonTemplates();
	vector<shared_ptr<TCommandGroups>>& getCommandGroups();
	vector<shared_ptr<TExchangePlans>>& getExchangePlans();
	vector<shared_ptr<TEventSubscriptions>>& getEventSubscriptions();
	vector<shared_ptr<TScheduledJobs>>& getScheduledJobs();
	vector<shared_ptr<TFunctionalOptions>>& getFunctionalOptions();
	vector<shared_ptr<TFunctionalOptionsParameters>>& getFunctionalOptionsParameters();
	vector<shared_ptr<TDefinedTypes>>& getDefinedTypes();
	vector<shared_ptr<TSettingsStorages>>& getSettingsStorages();
	vector<shared_ptr<TInterfaces>>& getInterfaces();

	MetaDataManager() = default;  // Явно указываем использование конструктора по умолчанию
	MetaDataManager(const MetaDataManager&) = delete; // запретить копирование
	MetaDataManager& operator=(const MetaDataManager&) = delete; // запретить копирование
	virtual ~MetaDataManager() = default;  // И деструктор тоже
};

#endif

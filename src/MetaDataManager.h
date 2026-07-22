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
#include "TConstants.h"
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

// Примечание: НЕ используем "using namespace std" в заголовочных файлах
// Все типы используются с явным пространством имен std::


class MetaDataManager {
private:
	std::map<String, std::vector<std::shared_ptr<MetaObject>>> ObjectsByType;
	std::vector<std::shared_ptr<TSessionParameters>> SessionParameters;
	std::vector<std::shared_ptr<TRoles>> Roles;
	std::vector<std::shared_ptr<TBots>> Bots;
	std::vector<std::shared_ptr<TCommonAttributes>> CommonAttributes;
	std::vector<std::shared_ptr<TCommonCommands>> CommonCommands;
	std::vector<std::shared_ptr<TConstants>> Constants;
	std::vector<std::shared_ptr<TCommonTemplates>> CommonTemplates;
	std::vector<std::shared_ptr<TCommandGroups>> CommandGroups;
	std::vector<std::shared_ptr<TExchangePlans>> ExchangePlans;
	std::vector<std::shared_ptr<TEventSubscriptions>> EventSubscriptions;
	std::vector<std::shared_ptr<TScheduledJobs>> ScheduledJobs;
	std::vector<std::shared_ptr<TFunctionalOptions>> FunctionalOptions;
	std::vector<std::shared_ptr<TFunctionalOptionsParameters>> FunctionalOptionsParameters;
	std::vector<std::shared_ptr<TDefinedTypes>> DefinedTypes;
	std::vector<std::shared_ptr<TSettingsStorages>> SettingsStorages;
	std::vector<std::shared_ptr<TInterfaces>> Interfaces;
public:
	v8catalog* loadFromFile(const String& filename);
	bool Initialize(v8catalog* cf);
    void fill_md(v8catalog *cf, tree* tr, String guid_md);
	void populateTreeView(TVirtualStringTree* tvSringTree);
	std::shared_ptr<MetaObject> getObject(const String& type, const String& name);
	std::vector<std::shared_ptr<TSessionParameters>>& getSessionParameters() { return SessionParameters; }
	std::vector<std::shared_ptr<TRoles>>& getRoles() { return Roles; }
	std::vector<std::shared_ptr<TBots>>& getBots() { return Bots; }
	std::vector<std::shared_ptr<TCommonAttributes>>& getCommonAttributes() { return CommonAttributes; }
	std::vector<std::shared_ptr<TCommonCommands>>& getCommonCommands() { return CommonCommands; }
	std::vector<std::shared_ptr<TConstants>>& getConstants() { return Constants; }
	std::vector<std::shared_ptr<TCommonTemplates>>& getCommonTemplates() { return CommonTemplates; }
	std::vector<std::shared_ptr<TCommandGroups>>& getCommandGroups() { return CommandGroups; }
	std::vector<std::shared_ptr<TExchangePlans>>& getExchangePlans() { return ExchangePlans; }
	std::vector<std::shared_ptr<TEventSubscriptions>>& getEventSubscriptions() { return EventSubscriptions; }
	std::vector<std::shared_ptr<TScheduledJobs>>& getScheduledJobs() { return ScheduledJobs; }
	std::vector<std::shared_ptr<TFunctionalOptions>>& getFunctionalOptions() { return FunctionalOptions; }
	std::vector<std::shared_ptr<TFunctionalOptionsParameters>>& getFunctionalOptionsParameters() { return FunctionalOptionsParameters; }
	std::vector<std::shared_ptr<TDefinedTypes>>& getDefinedTypes() { return DefinedTypes; }
	std::vector<std::shared_ptr<TSettingsStorages>>& getSettingsStorages() { return SettingsStorages; }
	std::vector<std::shared_ptr<TInterfaces>>& getInterfaces() { return Interfaces; }

	MetaDataManager() = default;  // Явно указываем использование конструктора по умолчанию
	MetaDataManager(const MetaDataManager&) = delete; // запретить копирование
	MetaDataManager& operator=(const MetaDataManager&) = delete; // запретить копирование
	virtual ~MetaDataManager() = default;  // И деструктор тоже
};

#endif

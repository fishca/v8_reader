//---------------------------------------------------------------------------


#include "MetaObject.h"
//#include "Visitor.h"
//---------------------------------------------------------------------------

// Для работы с UUID
#ifdef _WIN32
#include <objbase.h>
#pragma comment(lib, "ole32.lib")
#else
#include <uuid/uuid.h>
#endif

// Для работы с датами
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>


// ========== Статические переменные ==========

//std::map<MetaObject::ObjectType, MetaObject::CreatorFunc>&
//MetaObject::getTypeRegistry() {
//    static std::map<ObjectType, CreatorFunc> registry;
//    return registry;
//}
//
//std::map<std::string, MetaObject::ObjectType>&
//MetaObject::getNameRegistry() {
//    static std::map<std::string, ObjectType> registry;
//    return registry;
//}

// ========== Конструкторы и деструктор ==========

MetaObject::MetaObject()
    : state(ObjectState::New), signalData(std::make_shared<SignalData>()) {
    initialize();
}


MetaObject::MetaObject(const std::string& name, const std::string& synonym, const std::string& comment) : name(name),
																						   synonym(synonym),
																						   comment(comment),
																						   state(ObjectState::New),
																				           signalData(std::make_shared<SignalData>())
{
    initialize();
}

MetaObject::~MetaObject() {
    // Уведомляем о удалении объекта
    //notifyStateChanged(state, ObjectState::Deleted);
}

MetaObject::MetaObject(MetaObject&& other) noexcept
    : name(std::move(other.name)),
      synonym(std::move(other.synonym)),
      comment(std::move(other.comment)),
      created(std::move(other.created)),
      modified(std::move(other.modified)),
      uuid(std::move(other.uuid)),
      state(other.state),
      dependencies(std::move(other.dependencies)),
      dependents(std::move(other.dependents)),
      extendedProperties(std::move(other.extendedProperties)),
      signalData(std::move(other.signalData)) {
    // При перемещении генерируем новый UUID?
    // Нет, сохраняем старый, чтобы сохранить идентичность
}

MetaObject& MetaObject::operator=(MetaObject&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        synonym = std::move(other.synonym);
        comment = std::move(other.comment);
        created = std::move(other.created);
        modified = std::move(other.modified);
        uuid = std::move(other.uuid);
        state = other.state;
        dependencies = std::move(other.dependencies);
        dependents = std::move(other.dependents);
        extendedProperties = std::move(other.extendedProperties);
        signalData = std::move(other.signalData);
    }
    return *this;
}

void MetaObject::initialize() {
    auto now = std::chrono::system_clock::now();
    created = now;
    modified = now;

    // Генерируем UUID только если он еще не установлен
//    if (uuid.empty()) {
//        uuid = generateUUID();
//    }
	uuid = generateUUID();
}

// ========== Идентификация и информация о типе ==========

std::string MetaObject::getFullName() const {
    // Базовая реализация - просто имя
    // В потомках можно добавить пространство имен или префикс
    return name;
}

std::string MetaObject::getUUID() const {
    return uuid;
}

bool MetaObject::isSameType(const MetaObject& other) const {
    return typeid(*this) == typeid(other);
}

template<typename T>
bool MetaObject::isInstanceOf() const {
    return dynamic_cast<const T*>(this) != nullptr;
}

template<typename T>
T* MetaObject::as() {
    return dynamic_cast<T*>(this);
}

template<typename T>
const T* MetaObject::as() const {
    return dynamic_cast<const T*>(this);
}

// Явная специализация шаблонов для избежания линковочных ошибок
template bool MetaObject::isInstanceOf<MetaObject>() const;
template MetaObject* MetaObject::as<MetaObject>();
template const MetaObject* MetaObject::as<MetaObject>() const;

// ========== Основные свойства ==========

void MetaObject::setName(const std::string& name) {
    if (this->name != name) {
        this->name = normalizeName(name);
    }
}

std::string MetaObject::getName() const {
    return name;
}

void MetaObject::setSynonym(const std::string& synonym) {
	if (this->synonym != synonym) {
		this->synonym = synonym;
	}
}

std::string MetaObject::getSynonym() const {
	return synonym;
}

void MetaObject::setComment(const std::string& comment) {
	if (this->comment != comment) {
		this->comment = comment;
	}
}

std::string MetaObject::getComment() const {
	return comment;
}

// ========== Управление зависимостями ==========

void MetaObject::addDependency(const std::shared_ptr<MetaObject>& object) {
    if (!object || object.get() == this) return;

    // Проверяем, нет ли уже такой зависимости
    auto it = std::find_if(dependencies.begin(), dependencies.end(),
        [&object](const std::weak_ptr<MetaObject>& weak) {
            auto shared = weak.lock();
            return shared && shared == object;
        });

    if (it == dependencies.end()) {
        dependencies.push_back(object);

        // Обновляем кэш зависимых объектов у зависимого объекта
        object->dependents.push_back(shared_from_this());
    }
}

void MetaObject::removeDependency(const std::shared_ptr<MetaObject>& object) {
    if (!object) return;

    // Удаляем из зависимостей
    dependencies.erase(
        std::remove_if(dependencies.begin(), dependencies.end(),
            [&object](const std::weak_ptr<MetaObject>& weak) {
                auto shared = weak.lock();
                return !shared || shared == object;
            }),
        dependencies.end()
    );

    // Удаляем из зависимых объектов
    object->dependents.erase(
        std::remove_if(object->dependents.begin(), object->dependents.end(),
            [this](const std::weak_ptr<MetaObject>& weak) {
                auto shared = weak.lock();
                return !shared || shared.get() == this;
            }),
        object->dependents.end()
    );
}

std::vector<std::weak_ptr<MetaObject>> MetaObject::getDependencies() const {
    return dependencies;
}

std::vector<std::weak_ptr<MetaObject>> MetaObject::getDependents() const {
    // Очищаем "протухшие" weak_ptr
    dependents.erase(
        std::remove_if(dependents.begin(), dependents.end(),
            [](const std::weak_ptr<MetaObject>& weak) {
                return weak.expired();
            }),
        dependents.end()
    );

    return dependents;
}

bool MetaObject::checkCircularDependencies(std::vector<std::string>& errors) const {
//    std::vector<const MetaObject*> visited;
//    std::vector<const MetaObject*> stack;
//
//    // Рекурсивная функция для проверки
//    std::function<bool(const MetaObject*)> checkCycle =
//        [&](const MetaObject* obj) -> bool {
//            if (std::find(stack.begin(), stack.end(), obj) != stack.end()) {
//                // Нашли цикл
//                std::string cyclePath;
//                for (const auto* node : stack) {
//                    cyclePath += node->getName() + " -> ";
//                }
//                cyclePath += obj->getName();
//                errors.push_back("Circular dependency detected: " + cyclePath);
//                return true;
//            }
//
//            if (std::find(visited.begin(), visited.end(), obj) != visited.end()) {
//                return false; // Уже проверяли
//            }
//
//            visited.push_back(obj);
//            stack.push_back(obj);
//
//            // Проверяем зависимости
//            for (const auto& weakDep : obj->dependencies) {
//                if (auto dep = weakDep.lock()) {
//                    if (checkCycle(dep.get())) {
//                        return true;
//                    }
//                }
//            }
//
//            stack.pop_back();
//            return false;
//        };
//
//    return !checkCycle(this);
    return true;
}

// ========== Расширяемые свойства ==========

void MetaObject::setExtendedProperty(const std::string& key,
                                    const std::variant<std::string, int, double, bool>& value) {
    extendedProperties[key] = value;
    notifyPropertyChanged("extendedProperty." + key);
}

std::optional<std::variant<std::string, int, double, bool>>
MetaObject::getExtendedProperty(const std::string& key) const {
    auto it = extendedProperties.find(key);
    if (it != extendedProperties.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool MetaObject::removeExtendedProperty(const std::string& key) {
    auto it = extendedProperties.find(key);
    if (it != extendedProperties.end()) {
        extendedProperties.erase(it);
        notifyPropertyChanged("extendedProperty." + key);
        return true;
    }
    return false;
}

std::map<std::string, std::variant<std::string, int, double, bool>>
MetaObject::getAllExtendedProperties() const {
    return extendedProperties;
}

// ========== Сигналы и события ==========

size_t MetaObject::subscribeToPropertyChanged(PropertyChangedSignal callback) {
    size_t id = signalData->nextId++;
    signalData->propertyChangedCallbacks[id] = callback;
    return id;
}

size_t MetaObject::subscribeToStateChanged(StateChangedSignal callback) {
    size_t id = signalData->nextId++;
    signalData->stateChangedCallbacks[id] = callback;
    return id;
}

void MetaObject::unsubscribe(size_t subscriptionId) {
    signalData->propertyChangedCallbacks.erase(subscriptionId);
    signalData->stateChangedCallbacks.erase(subscriptionId);
}

void MetaObject::notifyPropertyChanged(const std::string& propertyName) {
    for (const auto& [id, callback] : signalData->propertyChangedCallbacks) {
        try {
            callback(propertyName);
        } catch (...) {
            // Игнорируем исключения в коллбеках
        }
    }
}

void MetaObject::notifyStateChanged(ObjectState oldState, ObjectState newState) {
    for (const auto& [id, callback] : signalData->stateChangedCallbacks) {
        try {
            callback(oldState, newState);
        } catch (...) {
            // Игнорируем исключения в коллбеках
        }
    }
}

// ========== Вспомогательные методы ==========

std::string MetaObject::generateUUID() {
//#ifdef _WIN32
//    GUID guid;
//    if (CoCreateGuid(&guid) == S_OK) {
//        char buffer[37];
//        snprintf(buffer, sizeof(buffer),
//                 "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
//                 guid.Data1, guid.Data2, guid.Data3,
//                 guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
//                 guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
//        return buffer;
//    }
//#else
//    uuid_t uuid;
//    uuid_generate(uuid);
//    char buffer[37];
//    uuid_unparse(uuid, buffer);
//    return buffer;
//#endif

    // Fallback - генерация случайного UUID
//    static std::random_device rd;
//    static std::mt19937 gen(rd());
//    static std::uniform_int_distribution<> dis(0, 15);
//    static std::uniform_int_distribution<> dis2(8, 11);
//
//    const char* hex = "0123456789abcdef";
	std::stringstream ss;

//	for (int i = 0; i < 32; i++) {
//		if (i == 8 || i == 12 || i == 16 || i == 20) {
//			ss << "-";
//		}
//
//		if (i == 12) {
//			ss << "4"; // version 4
//		} else if (i == 16) {
//			ss << hex[dis2(gen)];
//		} else {
//			ss << hex[dis(gen)];
//		}
//	}

	//return ss.str();
    return "";
}

std::string MetaObject::normalizeName(const std::string& name) {
	//if (name.empty()) return name;

	std::string result = name;

//	// Заменяем пробелы и специальные символы на подчеркивания
//	std::replace_if(result.begin(), result.end(),
//		[](char c) { return !std::isalnum(c) && c != '_' && c != '.'; }, '_');
//
//	// Удаляем двойные подчеркивания
//	result.erase(std::unique(result.begin(), result.end(),
//		[](char a, char b) { return a == '_' && b == '_'; }), result.end());
//
//	// Обрезаем начальные и конечные подчеркивания
//	while (!result.empty() && result.front() == '_') {
//		result.erase(result.begin());
//	}
//	while (!result.empty() && result.back() == '_') {
//		result.pop_back();
//	}

    return result;
}

// ========== Статические методы фабрики ==========

std::unique_ptr<MetaObject> MetaObject::create(ObjectType type,
                                              const std::string& name) {
    auto& registry = getTypeRegistry();
    auto it = registry.find(type);
    if (it != registry.end()) {
        return it->second(name);
    }
    return nullptr;
}

std::unique_ptr<MetaObject> MetaObject::createByName(const std::string& typeName,
                                                    const std::string& name) {
    auto& nameRegistry = getNameRegistry();
    auto it = nameRegistry.find(typeName);
    if (it != nameRegistry.end()) {
        return create(it->second, name);
    }
    return nullptr;
}

std::vector<std::pair<ObjectType, std::string>> MetaObject::getSupportedTypes() {
    std::vector<std::pair<ObjectType, std::string>> result;

    // Базовые типы
    result.emplace_back(ObjectType::Constant, "Constant");
    result.emplace_back(ObjectType::Directory, "Directory");
    result.emplace_back(ObjectType::Document, "Document");
    result.emplace_back(ObjectType::DocumentJournal, "DocumentJournal");
    result.emplace_back(ObjectType::Enum, "Enum");
    result.emplace_back(ObjectType::Report, "Report");
    result.emplace_back(ObjectType::Processing, "Processing");
    result.emplace_back(ObjectType::CharacteristicPlan, "CharacteristicPlan");
    result.emplace_back(ObjectType::ChartOfAccounts, "ChartOfAccounts");
    result.emplace_back(ObjectType::CalculationPlan, "CalculationPlan");
    result.emplace_back(ObjectType::InformationRegister, "InformationRegister");
    result.emplace_back(ObjectType::AccumulationRegister, "AccumulationRegister");
    result.emplace_back(ObjectType::AccountingRegister, "AccountingRegister");
    result.emplace_back(ObjectType::CalculationRegister, "CalculationRegister");
    result.emplace_back(ObjectType::BusinessProcess, "BusinessProcess");
    result.emplace_back(ObjectType::Task, "Task");
    result.emplace_back(ObjectType::ExternalDataSource, "ExternalDataSource");

    return result;
}

template<typename T>
bool MetaObject::registerType(const std::string& typeName) {
    static_assert(std::is_base_of<MetaObject, T>::value,
                  "T must be derived from MetaObject");

    // Получаем тип из статического метода класса T
    ObjectType type = T::getStaticType();

    // Регистрируем фабричную функцию
    getTypeRegistry()[type] = [typeName](const std::string& name) -> std::unique_ptr<MetaObject> {
        auto obj = std::make_unique<T>();
        obj->setName(name);
        return obj;
    };

    // Регистрируем имя типа
    getNameRegistry()[typeName] = type;

    return true;
}

// ========== Реализация Visitor ==========

// Visitor.cpp должен быть реализован отдельно
// Включаем только заголовок для компиляции

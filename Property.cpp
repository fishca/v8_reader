//---------------------------------------------------------------------------

#pragma hdrstop

#include "Property.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "MetaObject.h"

// Для работы с UUID
#ifdef _WIN32
#include <objbase.h>
#pragma comment(lib, "ole32.lib")
#else
#include <uuid/uuid.h>
#endif

// Для работы с датами и строками
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <regex>
#include <cmath>

// Для XML сериализации
#ifdef USE_TINYXML2
#include <tinyxml2.h>
using namespace tinyxml2;
#endif

// Для JSON сериализации
#ifdef USE_NLOHMANN_JSON
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif

// ========== Конструкторы и деструктор ==========

Property::Property()
    : propertyType(PropertyType::Unknown),
      dataType(DataType::Unknown),
      flags(PF_None),
      sortOrder(0),
	  signalData(std::make_shared<SignalData>()) {
    initialize();
}

Property::Property(const std::string& name,
                   PropertyType type,
                   const std::string& description)
    : name(normalizeName(name)),
      description(description),
      propertyType(type),
      dataType(DataType::Unknown),
      flags(PF_None),
      sortOrder(0),
      signalData(std::make_shared<SignalData>()) {
    initialize();
}

Property::~Property() {
    // Уведомляем об удалении свойства
    notifyPropertyModified();
}

Property::Property(Property&& other) noexcept
    : name(std::move(other.name)),
      synonym(std::move(other.synonym)),
      description(std::move(other.description)),
      propertyType(other.propertyType),
      dataType(other.dataType),
      flags(other.flags),
      defaultValue(std::move(other.defaultValue)),
      currentValue(std::move(other.currentValue)),
      sortOrder(other.sortOrder),
      group(std::move(other.group)),
      category(std::move(other.category)),
      created(std::move(other.created)),
      modified(std::move(other.modified)),
      uuid(std::move(other.uuid)),
      owner(std::move(other.owner)),
      linkedProperty(std::move(other.linkedProperty)),
      dependentProperties(std::move(other.dependentProperties)),
      validationRules(std::move(other.validationRules)),
      minValue(other.minValue),
      maxValue(other.maxValue),
      minLength(other.minLength),
      maxLength(other.maxLength),
      regExp(std::move(other.regExp)),
      attributes(std::move(other.attributes)),
      signalData(std::move(other.signalData)) {
    // При перемещении сохраняем UUID
}

Property& Property::operator=(Property&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        synonym = std::move(other.synonym);
        description = std::move(other.description);
        propertyType = other.propertyType;
        dataType = other.dataType;
        flags = other.flags;
        defaultValue = std::move(other.defaultValue);
        currentValue = std::move(other.currentValue);
        sortOrder = other.sortOrder;
        group = std::move(other.group);
        category = std::move(other.category);
        created = std::move(other.created);
        modified = std::move(other.modified);
        uuid = std::move(other.uuid);
        owner = std::move(other.owner);
        linkedProperty = std::move(other.linkedProperty);
        dependentProperties = std::move(other.dependentProperties);
        validationRules = std::move(other.validationRules);
        minValue = other.minValue;
        maxValue = other.maxValue;
        minLength = other.minLength;
        maxLength = other.maxLength;
        regExp = std::move(other.regExp);
        attributes = std::move(other.attributes);
        signalData = std::move(other.signalData);
    }
    return *this;
}

void Property::initialize() {
    auto now = std::chrono::system_clock::now();
    created = now;
    modified = now;

    // Генерируем UUID только если он еще не установлен
    if (uuid.empty()) {
        uuid = generateUUID();
    }
}

// ========== Идентификация и информация о типе ==========

std::string Property::getUUID() const {
    return uuid;
}

bool Property::isSameType(const Property& other) const {
    return typeid(*this) == typeid(other);
}

template<typename T>
bool Property::isInstanceOf() const {
    return dynamic_cast<const T*>(this) != nullptr;
}

template<typename T>
T* Property::as() {
    return dynamic_cast<T*>(this);
}

template<typename T>
const T* Property::as() const {
    return dynamic_cast<const T*>(this);
}

// Явная специализация шаблонов
template bool Property::isInstanceOf<Property>() const;
template Property* Property::as<Property>();
template const Property* Property::as<Property>() const;

// ========== Основные свойства ==========

void Property::setName(const std::string& name) {
    std::string normalized = normalizeName(name);
    if (this->name != normalized) {
        this->name = normalized;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getName() const {
    return name;
}

void Property::setSynonym(const std::string& synonym) {
    if (this->synonym != synonym) {
        this->synonym = synonym;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getSynonym() const {
    return synonym;
}

void Property::setDescription(const std::string& description) {
    if (this->description != description) {
        this->description = description;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getDescription() const {
    return description;
}

void Property::setDataType(DataType dataType) {
    if (this->dataType != dataType) {
        this->dataType = dataType;
        updateModified();
        notifyPropertyModified();
    }
}

DataType Property::getDataType() const {
    return dataType;
}

std::string Property::getDataTypeName() const {
    return dataTypeToString(dataType);
}

void Property::setFlags(uint32_t flags) {
    if (this->flags != flags) {
        this->flags = flags;
        updateModified();
        notifyPropertyModified();
    }
}

uint32_t Property::getFlags() const {
    return flags;
}

void Property::addFlag(PropertyFlags flag) {
    uint32_t newFlags = flags | static_cast<uint32_t>(flag);
    setFlags(newFlags);
}

void Property::removeFlag(PropertyFlags flag) {
    uint32_t newFlags = flags & ~static_cast<uint32_t>(flag);
    setFlags(newFlags);
}

bool Property::hasFlag(PropertyFlags flag) const {
    return (flags & static_cast<uint32_t>(flag)) != 0;
}

bool Property::isRequired() const {
    return hasFlag(PF_Required);
}

bool Property::isReadOnly() const {
    return hasFlag(PF_ReadOnly);
}

bool Property::isHidden() const {
    return hasFlag(PF_Hidden);
}

bool Property::isSystem() const {
    return hasFlag(PF_System);
}

void Property::setDefaultValue(const std::string& value) {
    if (defaultValue != value) {
        defaultValue = value;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getDefaultValue() const {
    return defaultValue;
}

void Property::setSortOrder(int sortOrder) {
    if (this->sortOrder != sortOrder) {
        this->sortOrder = sortOrder;
        updateModified();
        notifyPropertyModified();
    }
}

int Property::getSortOrder() const {
    return sortOrder;
}

void Property::setGroup(const std::string& group) {
    if (this->group != group) {
        this->group = group;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getGroup() const {
    return group;
}

void Property::setCategory(const std::string& category) {
    if (this->category != category) {
        this->category = category;
        updateModified();
        notifyPropertyModified();
    }
}

std::string Property::getCategory() const {
    return category;
}

void Property::setCreated(const std::chrono::system_clock::time_point& created) {
    if (this->created != created) {
        this->created = created;
        notifyPropertyModified();
    }
}

std::chrono::system_clock::time_point Property::getCreated() const {
    return created;
}

void Property::setModified(const std::chrono::system_clock::time_point& modified) {
    if (this->modified != modified) {
        this->modified = modified;
        notifyPropertyModified();
    }
}

std::chrono::system_clock::time_point Property::getModified() const {
    return modified;
}

void Property::updateModified() {
    auto now = std::chrono::system_clock::now();
    setModified(now);
}

std::string Property::getCreatedString(const std::string& format) const {
    std::time_t tt = std::chrono::system_clock::to_time_t(created);
    std::tm tm = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

std::string Property::getModifiedString(const std::string& format) const {
    std::time_t tt = std::chrono::system_clock::to_time_t(modified);
    std::tm tm = *std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

// ========== Значения и валидация ==========

bool Property::setValue(const std::string& value) {
    // Проверяем, можно ли изменять значение
    if (isReadOnly()) {
        return false;
    }

    // Проверяем валидность нового значения
    std::vector<std::string> errors;
    if (!validateValue(value, errors)) {
        return false;
    }

    std::string oldValue = currentValue;
    currentValue = value;

    updateModified();
    notifyValueChanged(oldValue, currentValue);
    notifyPropertyModified();

    return true;
}

std::string Property::getValue() const {
    // Если значение не установлено, возвращаем значение по умолчанию
    if (currentValue.empty() && !defaultValue.empty()) {
        return defaultValue;
    }
    return currentValue;
}

void Property::clearValue() {
    if (!isReadOnly()) {
        std::string oldValue = currentValue;
        currentValue.clear();

        updateModified();
        notifyValueChanged(oldValue, currentValue);
        notifyPropertyModified();
    }
}

bool Property::hasValue() const {
    return !currentValue.empty();
}

void Property::addValidationRule(const ValidationRule& rule) {
    // Проверяем, нет ли уже правила с таким именем
    auto it = std::find_if(validationRules.begin(), validationRules.end(),
        [&rule](const ValidationRule& r) {
            return r.name == rule.name;
        });

    if (it == validationRules.end()) {
        validationRules.push_back(rule);
        updateModified();
        notifyPropertyModified();
    }
}

bool Property::removeValidationRule(const std::string& ruleName) {
    auto it = std::remove_if(validationRules.begin(), validationRules.end(),
        [&ruleName](const ValidationRule& rule) {
            return rule.name == ruleName;
        });

    if (it != validationRules.end()) {
        validationRules.erase(it, validationRules.end());
        updateModified();
        notifyPropertyModified();
        return true;
    }

    return false;
}

std::vector<ValidationRule> Property::getValidationRules() const {
    return validationRules;
}

bool Property::validate(std::vector<std::string>& errors) const {
    return validateValue(getValue(), errors);
}

bool Property::validateValue(const std::string& value, std::vector<std::string>& errors) const {
    errors.clear();

    // Проверка обязательности
    if (isRequired() && value.empty()) {
        errors.push_back("Property '" + name + "' is required");
        return false;
    }

    // Если значение пустое и свойство не обязательное - оно валидно
    if (value.empty() && !isRequired()) {
        return true;
    }

    // Проверка типа данных
    if (!validateDataType(value, errors)) {
        return false;
    }

    // Проверка минимальной/максимальной длины для строк
    if (dataType == DataType::String) {
        size_t length = value.length();
        if (minLength && length < *minLength) {
            errors.push_back("Value length is less than minimum: " +
                           std::to_string(*minLength));
            return false;
        }
        if (maxLength && length > *maxLength) {
            errors.push_back("Value length exceeds maximum: " +
                           std::to_string(*maxLength));
            return false;
        }
    }

    // Проверка регулярного выражения
    if (regExp && !regExp->empty()) {
        try {
            std::regex re(*regExp);
            if (!std::regex_match(value, re)) {
                errors.push_back("Value does not match pattern: " + *regExp);
                return false;
            }
        } catch (const std::regex_error& e) {
            errors.push_back("Invalid regular expression: " + std::string(e.what()));
            return false;
        }
    }

    // Проверка пользовательских правил валидации
    for (const auto& rule : validationRules) {
        // Здесь должна быть реализация проверки выражения
        // Для простоты предполагаем, что выражение - это код на JavaScript или подобном
        // В реальной реализации нужно интегрировать движок скриптов
        if (!rule.expression.empty()) {
            // Заглушка для демонстрации
            if (rule.expression == "not_empty" && value.empty()) {
                errors.push_back(rule.errorMessage.empty() ?
                    "Validation failed for rule: " + rule.name : rule.errorMessage);
                return false;
            }
        }
    }

    return true;
}

std::optional<double> Property::getMinValue() const {
    return minValue;
}

void Property::setMinValue(double minValue) {
    if (!this->minValue || *this->minValue != minValue) {
        this->minValue = minValue;
        updateModified();
        notifyPropertyModified();
    }
}

std::optional<double> Property::getMaxValue() const {
    return maxValue;
}

void Property::setMaxValue(double maxValue) {
    if (!this->maxValue || *this->maxValue != maxValue) {
        this->maxValue = maxValue;
        updateModified();
        notifyPropertyModified();
    }
}

std::optional<size_t> Property::getMinLength() const {
    return minLength;
}

void Property::setMinLength(size_t minLength) {
    if (!this->minLength || *this->minLength != minLength) {
        this->minLength = minLength;
        updateModified();
        notifyPropertyModified();
    }
}

std::optional<size_t> Property::getMaxLength() const {
    return maxLength;
}

void Property::setMaxLength(size_t maxLength) {
    if (!this->maxLength || *this->maxLength != maxLength) {
        this->maxLength = maxLength;
        updateModified();
        notifyPropertyModified();
    }
}

std::optional<std::string> Property::getRegExp() const {
    return regExp;
}

void Property::setRegExp(const std::string& regExp) {
    if (!this->regExp || *this->regExp != regExp) {
        this->regExp = regExp;
        updateModified();
        notifyPropertyModified();
    }
}

// ========== Паттерн Prototype ==========

std::unique_ptr<Property> Property::cloneWithName(const std::string& newName) const {
    auto cloneProp = clone();
    cloneProp->setName(newName);
    cloneProp->uuid = generateUUID(); // Новый UUID для клона

    // Обновляем даты
    auto now = std::chrono::system_clock::now();
    cloneProp->created = now;
    cloneProp->modified = now;

    return cloneProp;
}

// ========== Сериализация ==========

void Property::toXML(void* parent) const {
#ifdef USE_TINYXML2
    XMLElement* element = static_cast<XMLElement*>(parent);
    if (element) {
        element->SetAttribute("name", name.c_str());
        element->SetAttribute("type", propertyTypeToString(propertyType).c_str());
        element->SetAttribute("dataType", dataTypeToString(dataType).c_str());
        element->SetAttribute("uuid", uuid.c_str());
        element->SetAttribute("flags", static_cast<int>(flags));

        if (!synonym.empty()) {
            element->SetAttribute("synonym", synonym.c_str());
        }

        if (!defaultValue.empty()) {
            element->SetAttribute("defaultValue", defaultValue.c_str());
        }

        if (!currentValue.empty()) {
            element->SetAttribute("value", currentValue.c_str());
        }

        if (sortOrder != 0) {
            element->SetAttribute("sortOrder", sortOrder);
        }

        if (!group.empty()) {
            element->SetAttribute("group", group.c_str());
        }

        if (!category.empty()) {
            element->SetAttribute("category", category.c_str());
        }

        element->SetAttribute("created", getCreatedString().c_str());
        element->SetAttribute("modified", getModifiedString().c_str());

        // Добавляем описание как текстовый узел
        if (!description.empty()) {
            XMLElement* descElem = element->GetDocument()->NewElement("description");
            descElem->SetText(description.c_str());
            element->InsertEndChild(descElem);
        }

        // Добавляем правила валидации
        if (!validationRules.empty()) {
            XMLElement* rulesElem = element->GetDocument()->NewElement("validationRules");
            for (const auto& rule : validationRules) {
                XMLElement* ruleElem = element->GetDocument()->NewElement("rule");
                ruleElem->SetAttribute("name", rule.name.c_str());
                ruleElem->SetAttribute("expression", rule.expression.c_str());
                ruleElem->SetAttribute("errorMessage", rule.errorMessage.c_str());
                if (!rule.description.empty()) {
                    ruleElem->SetText(rule.description.c_str());
                }
                rulesElem->InsertEndChild(ruleElem);
            }
            element->InsertEndChild(rulesElem);
        }

        // Добавляем ограничения
        if (minValue || maxValue || minLength || maxLength || (regExp && !regExp->empty())) {
            XMLElement* constraintsElem = element->GetDocument()->NewElement("constraints");

            if (minValue) {
                constraintsElem->SetAttribute("minValue", *minValue);
            }
            if (maxValue) {
                constraintsElem->SetAttribute("maxValue", *maxValue);
            }
            if (minLength) {
                constraintsElem->SetAttribute("minLength", static_cast<int>(*minLength));
            }
            if (maxLength) {
                constraintsElem->SetAttribute("maxLength", static_cast<int>(*maxLength));
            }
            if (regExp && !regExp->empty()) {
                constraintsElem->SetAttribute("regExp", regExp->c_str());
            }

            element->InsertEndChild(constraintsElem);
        }

        // Добавляем атрибуты
        if (!attributes.empty()) {
            XMLElement* attrsElem = element->GetDocument()->NewElement("attributes");
            for (const auto& [key, value] : attributes) {
                XMLElement* attrElem = element->GetDocument()->NewElement("attribute");
                attrElem->SetAttribute("key", key.c_str());

                std::visit([&](auto&& arg) {
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, std::string>) {
                        attrElem->SetAttribute("type", "string");
                        attrElem->SetAttribute("value", arg.c_str());
                    } else if constexpr (std::is_same_v<T, int>) {
                        attrElem->SetAttribute("type", "int");
                        attrElem->SetAttribute("value", arg);
                    } else if constexpr (std::is_same_v<T, double>) {
                        attrElem->SetAttribute("type", "double");
                        attrElem->SetAttribute("value", arg);
                    } else if constexpr (std::is_same_v<T, bool>) {
                        attrElem->SetAttribute("type", "bool");
                        attrElem->SetAttribute("value", arg);
                    }
                }, value);

                attrsElem->InsertEndChild(attrElem);
            }
            element->InsertEndChild(attrsElem);
        }
    }
#endif
}

bool Property::fromXML(const void* element) {
#ifdef USE_TINYXML2
    const XMLElement* xmlElem = static_cast<const XMLElement*>(element);
    if (!xmlElem) return false;

    // Читаем атрибуты
    const char* nameAttr = xmlElem->Attribute("name");
    if (nameAttr) setName(nameAttr);

    const char* typeAttr = xmlElem->Attribute("type");
    if (typeAttr) {
        propertyType = stringToPropertyType(typeAttr);
    }

    const char* dataTypeAttr = xmlElem->Attribute("dataType");
    if (dataTypeAttr) {
        dataType = stringToDataType(dataTypeAttr);
    }

    const char* uuidAttr = xmlElem->Attribute("uuid");
    if (uuidAttr) uuid = uuidAttr;

    const char* flagsAttr = xmlElem->Attribute("flags");
    if (flagsAttr) {
        flags = static_cast<uint32_t>(std::stoi(flagsAttr));
    }

    const char* synonymAttr = xmlElem->Attribute("synonym");
    if (synonymAttr) setSynonym(synonymAttr);

    const char* defaultValueAttr = xmlElem->Attribute("defaultValue");
    if (defaultValueAttr) setDefaultValue(defaultValueAttr);

    const char* valueAttr = xmlElem->Attribute("value");
    if (valueAttr) setValue(valueAttr);

    const char* sortOrderAttr = xmlElem->Attribute("sortOrder");
    if (sortOrderAttr) {
        sortOrder = std::stoi(sortOrderAttr);
    }

    const char* groupAttr = xmlElem->Attribute("group");
    if (groupAttr) setGroup(groupAttr);

    const char* categoryAttr = xmlElem->Attribute("category");
    if (categoryAttr) setCategory(categoryAttr);

    const char* createdAttr = xmlElem->Attribute("created");
    if (createdAttr) {
        std::tm tm = {};
        std::stringstream ss(createdAttr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (!ss.fail()) {
            created = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
    }

    const char* modifiedAttr = xmlElem->Attribute("modified");
    if (modifiedAttr) {
        std::tm tm = {};
        std::stringstream ss(modifiedAttr);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        if (!ss.fail()) {
            modified = std::chrono::system_clock::from_time_t(std::mktime(&tm));
        }
    }

    // Читаем описание
    const XMLElement* descElem = xmlElem->FirstChildElement("description");
    if (descElem && descElem->GetText()) {
        setDescription(descElem->GetText());
    }

    // Читаем правила валидации
    const XMLElement* rulesElem = xmlElem->FirstChildElement("validationRules");
    if (rulesElem) {
        const XMLElement* ruleElem = rulesElem->FirstChildElement("rule");
        while (ruleElem) {
            ValidationRule rule;
            const char* ruleName = ruleElem->Attribute("name");
            const char* expression = ruleElem->Attribute("expression");
            const char* errorMessage = ruleElem->Attribute("errorMessage");
            const char* ruleDesc = ruleElem->GetText();

            if (ruleName) rule.name = ruleName;
            if (expression) rule.expression = expression;
            if (errorMessage) rule.errorMessage = errorMessage;
            if (ruleDesc) rule.description = ruleDesc;

            if (!rule.name.empty()) {
                addValidationRule(rule);
            }

            ruleElem = ruleElem->NextSiblingElement("rule");
        }
    }

    // Читаем ограничения
    const XMLElement* constraintsElem = xmlElem->FirstChildElement("constraints");
    if (constraintsElem) {
        const char* minValueAttr = constraintsElem->Attribute("minValue");
        if (minValueAttr) {
            minValue = std::stod(minValueAttr);
        }

        const char* maxValueAttr = constraintsElem->Attribute("maxValue");
        if (maxValueAttr) {
            maxValue = std::stod(maxValueAttr);
        }

        const char* minLengthAttr = constraintsElem->Attribute("minLength");
        if (minLengthAttr) {
            minLength = static_cast<size_t>(std::stoi(minLengthAttr));
        }

        const char* maxLengthAttr = constraintsElem->Attribute("maxLength");
        if (maxLengthAttr) {
            maxLength = static_cast<size_t>(std::stoi(maxLengthAttr));
        }

        const char* regExpAttr = constraintsElem->Attribute("regExp");
        if (regExpAttr) {
            regExp = regExpAttr;
        }
    }

    // Читаем атрибуты
    const XMLElement* attrsElem = xmlElem->FirstChildElement("attributes");
    if (attrsElem) {
        const XMLElement* attrElem = attrsElem->FirstChildElement("attribute");
        while (attrElem) {
            const char* key = attrElem->Attribute("key");
            const char* type = attrElem->Attribute("type");
            const char* value = attrElem->Attribute("value");

            if (key && type && value) {
                if (strcmp(type, "string") == 0) {
                    attributes[key] = std::string(value);
                } else if (strcmp(type, "int") == 0) {
                    attributes[key] = std::stoi(value);
                } else if (strcmp(type, "double") == 0) {
                    attributes[key] = std::stod(value);
                } else if (strcmp(type, "bool") == 0) {
                    attributes[key] = (strcmp(value, "true") == 0);
                }
            }

            attrElem = attrElem->NextSiblingElement("attribute");
        }
    }

    return true;
#else
    return false;
#endif
}

std::string Property::toJSON() const {
#ifdef USE_NLOHMANN_JSON
    json j;
    j["name"] = name;
    j["propertyType"] = propertyTypeToString(propertyType);
    j["dataType"] = dataTypeToString(dataType);
    j["uuid"] = uuid;
    j["flags"] = flags;
    j["synonym"] = synonym;
    j["description"] = description;
    j["defaultValue"] = defaultValue;
    j["value"] = getValue();
    j["sortOrder"] = sortOrder;
    j["group"] = group;
    j["category"] = category;
    j["created"] = getCreatedString();
    j["modified"] = getModifiedString();

    // Правила валидации
    if (!validationRules.empty()) {
        json rulesArray = json::array();
        for (const auto& rule : validationRules) {
            json ruleJson;
            ruleJson["name"] = rule.name;
            ruleJson["expression"] = rule.expression;
            ruleJson["errorMessage"] = rule.errorMessage;
            ruleJson["description"] = rule.description;
            rulesArray.push_back(ruleJson);
        }
        j["validationRules"] = rulesArray;
    }

    // Ограничения
    json constraints;
    if (minValue) constraints["minValue"] = *minValue;
    if (maxValue) constraints["maxValue"] = *maxValue;
    if (minLength) constraints["minLength"] = *minLength;
    if (maxLength) constraints["maxLength"] = *maxLength;
    if (regExp) constraints["regExp"] = *regExp;

    if (!constraints.empty()) {
        j["constraints"] = constraints;
    }

    // Атрибуты
    if (!attributes.empty()) {
        json attrs = json::object();
        for (const auto& [key, value] : attributes) {
            std::visit([&](auto&& arg) {
                attrs[key] = arg;
            }, value);
        }
        j["attributes"] = attrs;
    }

    return j.dump(2);
#else
    return "{}";
#endif
}

bool Property::fromJSON(const std::string& jsonStr) {
#ifdef USE_NLOHMANN_JSON
    try {
        json j = json::parse(jsonStr);

        if (j.contains("name")) setName(j["name"]);
        if (j.contains("propertyType")) {
            propertyType = stringToPropertyType(j["propertyType"]);
        }
        if (j.contains("dataType")) {
            dataType = stringToDataType(j["dataType"]);
        }
        if (j.contains("uuid")) uuid = j["uuid"];
        if (j.contains("flags")) flags = j["flags"];
        if (j.contains("synonym")) setSynonym(j["synonym"]);
        if (j.contains("description")) setDescription(j["description"]);
        if (j.contains("defaultValue")) setDefaultValue(j["defaultValue"]);
        if (j.contains("value")) setValue(j["value"]);
        if (j.contains("sortOrder")) sortOrder = j["sortOrder"];
        if (j.contains("group")) setGroup(j["group"]);
        if (j.contains("category")) setCategory(j["category"]);

        if (j.contains("created")) {
            std::string createdStr = j["created"];
            std::tm tm = {};
            std::stringstream ss(createdStr);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            if (!ss.fail()) {
                created = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            }
        }

        if (j.contains("modified")) {
            std::string modifiedStr = j["modified"];
            std::tm tm = {};
            std::stringstream ss(modifiedStr);
            ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
            if (!ss.fail()) {
                modified = std::chrono::system_clock::from_time_t(std::mktime(&tm));
            }
        }

        // Правила валидации
        if (j.contains("validationRules") && j["validationRules"].is_array()) {
            for (const auto& ruleJson : j["validationRules"]) {
                ValidationRule rule;
                if (ruleJson.contains("name")) rule.name = ruleJson["name"];
                if (ruleJson.contains("expression")) rule.expression = ruleJson["expression"];
                if (ruleJson.contains("errorMessage")) rule.errorMessage = ruleJson["errorMessage"];
                if (ruleJson.contains("description")) rule.description = ruleJson["description"];

                if (!rule.name.empty()) {
                    addValidationRule(rule);
                }
            }
        }

        // Ограничения
        if (j.contains("constraints")) {
            json constraints = j["constraints"];
            if (constraints.contains("minValue")) {
                minValue = constraints["minValue"];
            }
            if (constraints.contains("maxValue")) {
                maxValue = constraints["maxValue"];
            }
            if (constraints.contains("minLength")) {
                minLength = constraints["minLength"];
            }
            if (constraints.contains("maxLength")) {
                maxLength = constraints["maxLength"];
            }
            if (constraints.contains("regExp")) {
                regExp = constraints["regExp"];
            }
        }

        // Атрибуты
        if (j.contains("attributes") && j["attributes"].is_object()) {
            json attrs = j["attributes"];
            for (auto it = attrs.begin(); it != attrs.end(); ++it) {
                std::string key = it.key();
                json value = it.value();

                if (value.is_string()) {
                    attributes[key] = value.get<std::string>();
                } else if (value.is_number_integer()) {
                    attributes[key] = value.get<int>();
                } else if (value.is_number_float()) {
                    attributes[key] = value.get<double>();
                } else if (value.is_boolean()) {
                    attributes[key] = value.get<bool>();
                }
            }
        }

        return true;
    } catch (const std::exception& e) {
        return false;
    }
#else
    return false;
#endif
}

// ========== Работа с UI (C++ Builder VCL) ==========

#ifdef __BORLANDC__

void Property::populateTreeView(TTreeNode* parent, TTreeView* treeView) const {
//    if (!parent || !treeView) return;
//
//    // Создаем узел для свойства
//    std::string displayName = name;
//    if (!synonym.empty()) {
//        displayName += " (" + synonym + ")";
//    }
//
//    TTreeNode* node = treeView->Items->AddChild(parent,
//        UnicodeString(displayName.c_str(), displayName.length()));
//
//    // Устанавливаем иконку
//    node->ImageIndex = getTreeViewIconIndex();
//    node->SelectedIndex = getTreeViewIconIndex();
//
//    // Устанавливаем цвет текста
//    node->FontColor = getTreeViewTextColor();
//
//    // Сохраняем указатель на свойство
//    node->Data = const_cast<Property*>(this);
//
//    // Добавляем дочерние узлы для деталей свойства
//    TTreeNode* detailsNode = treeView->Items->AddChild(node, "Details");
//    detailsNode->ImageIndex = 1;
//    detailsNode->SelectedIndex = 1;
//
//    // Тип свойства
//    TTreeNode* typeNode = treeView->Items->AddChild(detailsNode,
//        UnicodeString(("Type: " + getPropertyTypeName()).c_str()));
//    typeNode->ImageIndex = 2;
//    typeNode->SelectedIndex = 2;
//
//    // Тип данных
//    TTreeNode* dataTypeNode = treeView->Items->AddChild(detailsNode,
//        UnicodeString(("Data Type: " + getDataTypeName()).c_str()));
//    dataTypeNode->ImageIndex = 2;
//    dataTypeNode->SelectedIndex = 2;
//
//    // Обязательность
//    if (isRequired()) {
//        TTreeNode* requiredNode = treeView->Items->AddChild(detailsNode, "Required: Yes");
//        requiredNode->ImageIndex = 2;
//        requiredNode->SelectedIndex = 2;
//    }
//
//    // Только для чтения
//    if (isReadOnly()) {
//        TTreeNode* readOnlyNode = treeView->Items->AddChild(detailsNode, "Read Only: Yes");
//        readOnlyNode->ImageIndex = 2;
//        readOnlyNode->SelectedIndex = 2;
//    }
//
//    // Значение
//    if (hasValue()) {
//        TTreeNode* valueNode = treeView->Items->AddChild(detailsNode,
//            UnicodeString(("Value: " + getValue()).c_str()));
//        valueNode->ImageIndex = 2;
//        valueNode->SelectedIndex = 2;
//    }
//
//    // Значение по умолчанию
//    if (!defaultValue.empty()) {
//        TTreeNode* defaultValueNode = treeView->Items->AddChild(detailsNode,
//            UnicodeString(("Default: " + defaultValue).c_str()));
//        defaultValueNode->ImageIndex = 2;
//        defaultValueNode->SelectedIndex = 2;
//    }
//
//    // Описание
//    if (!description.empty()) {
//        TTreeNode* descNode = treeView->Items->AddChild(detailsNode,
//            UnicodeString(("Description: " + description).c_str()));
//        descNode->ImageIndex = 2;
//        descNode->SelectedIndex = 2;
//    }
}

TStringList* Property::getDisplayProperties() const {
    TStringList* properties = new TStringList();

    properties->Add(("Name: " + name).c_str());
    properties->Add(("Property Type: " + getPropertyTypeName()).c_str());
    properties->Add(("Data Type: " + getDataTypeName()).c_str());

    if (!synonym.empty()) {
        properties->Add(("Synonym: " + synonym).c_str());
    }

    if (!description.empty()) {
        properties->Add(("Description: " + description).c_str());
    }

    properties->Add(("UUID: " + uuid).c_str());

    // Флаги
    std::string flagsStr;
    if (isRequired()) flagsStr += "Required, ";
    if (isReadOnly()) flagsStr += "ReadOnly, ";
    if (isHidden()) flagsStr += "Hidden, ";
    if (isSystem()) flagsStr += "System, ";

    if (!flagsStr.empty()) {
        flagsStr = flagsStr.substr(0, flagsStr.length() - 2); // Убираем последнюю запятую
        properties->Add(("Flags: " + flagsStr).c_str());
    }

    // Значения
    if (hasValue()) {
        properties->Add(("Value: " + getValue()).c_str());
    }

    if (!defaultValue.empty()) {
        properties->Add(("Default Value: " + defaultValue).c_str());
    }

    if (sortOrder != 0) {
        properties->Add(("Sort Order: " + std::to_string(sortOrder)).c_str());
    }

    if (!group.empty()) {
        properties->Add(("Group: " + group).c_str());
    }

    if (!category.empty()) {
        properties->Add(("Category: " + category).c_str());
    }

    properties->Add(("Created: " + getCreatedString()).c_str());
    properties->Add(("Modified: " + getModifiedString()).c_str());

    // Валидация
    if (minValue) {
        properties->Add(("Min Value: " + std::to_string(*minValue)).c_str());
    }

    if (maxValue) {
        properties->Add(("Max Value: " + std::to_string(*maxValue)).c_str());
    }

    if (minLength) {
        properties->Add(("Min Length: " + std::to_string(*minLength)).c_str());
    }

    if (maxLength) {
        properties->Add(("Max Length: " + std::to_string(*maxLength)).c_str());
    }

    if (regExp && !regExp->empty()) {
        properties->Add(("RegExp: " + *regExp).c_str());
    }

    // Правила валидации
    if (!validationRules.empty()) {
        properties->Add("--- Validation Rules ---");
        for (const auto& rule : validationRules) {
            properties->Add(("Rule: " + rule.name).c_str());
            if (!rule.description.empty()) {
                properties->Add(("  Description: " + rule.description).c_str());
            }
        }
    }

    // Атрибуты
    if (!attributes.empty()) {
        properties->Add("--- Attributes ---");
        for (const auto& [key, value] : attributes) {
            std::string attrStr = key + ": ";
            std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, std::string>) {
                    attrStr += arg;
                } else if constexpr (std::is_same_v<T, int>) {
                    attrStr += std::to_string(arg);
                } else if constexpr (std::is_same_v<T, double>) {
                    attrStr += std::to_string(arg);
                } else if constexpr (std::is_same_v<T, bool>) {
                    attrStr += arg ? "true" : "false";
                }
            }, value);
            properties->Add(attrStr.c_str());
        }
    }

    return properties;
}

int Property::getTreeViewIconIndex() const {
    // Базовая реализация - иконка в зависимости от типа свойства
    switch (propertyType) {
        case PropertyType::Requisite: return 10;
        case PropertyType::Column: return 11;
        case PropertyType::Form: return 12;
        case PropertyType::Command: return 13;
        case PropertyType::Layout: return 14;
        case PropertyType::TablePart: return 15;
        case PropertyType::Dimension: return 16;
        case PropertyType::Resource: return 17;
        default: return 0;
    }
}

TColor Property::getTreeViewTextColor() const {
    // Цвет в зависимости от типа и состояния
    if (isReadOnly()) {
        return clGray;
    } else if (isRequired()) {
        return clRed;
    } else if (isSystem()) {
        return clBlue;
    } else if (isHidden()) {
        return clSilver;
    }
    return clBlack;
}

TWinControl* Property::createEditor(TWinControl* parent) const {
    // Базовая реализация создает TEdit для строковых значений
    // В конкретных классах-наследниках нужно переопределять
    TEdit* editor = new TEdit(parent);
    editor->Parent = parent;
    editor->Text = UnicodeString(getValue().c_str(), getValue().length());
    editor->ReadOnly = isReadOnly();

//    // Настраиваем в зависимости от типа данных
//    if (dataType == DataType::Password) {
//        editor->PasswordChar = '*';
//    }
//
//    if (dataType == DataType::Number || dataType == DataType::Integer ||
//        dataType == DataType::Float) {
//        // Для чисел можно использовать TSpinEdit или TMaskEdit
//        // Здесь для простоты оставляем TEdit
//    }
//
//    if (dataType == DataType::Boolean) {
//        // Для логических значений лучше использовать TCheckBox
//        // Возвращаем nullptr, чтобы показать, что нужен специальный редактор
//        delete editor;
//        return nullptr;
//    }

    return editor;
}

bool Property::loadFromEditor(TWinControl* editor) {
    // Базовая реализация для TEdit
    TEdit* edit = dynamic_cast<TEdit*>(editor);
    if (edit) {
        std::string newValue = AnsiString(edit->Text).c_str();
        return setValue(newValue);
    }
    return false;
}

void Property::saveToEditor(TWinControl* editor) const {
    // Базовая реализация для TEdit
    TEdit* edit = dynamic_cast<TEdit*>(editor);
    if (edit) {
        edit->Text = UnicodeString(getValue().c_str(), getValue().length());
        edit->ReadOnly = isReadOnly();
    }
}

#endif

// ========== Сравнение свойств ==========

bool Property::compare(const Property& other,
                      std::vector<std::string>& differences) const {
    bool equal = true;

    if (name != other.name) {
        differences.push_back("Name differs: " + name + " vs " + other.name);
        equal = false;
    }

    if (propertyType != other.propertyType) {
        differences.push_back("Property type differs");
        equal = false;
    }

    if (dataType != other.dataType) {
        differences.push_back("Data type differs");
        equal = false;
    }

    if (flags != other.flags) {
        differences.push_back("Flags differ");
        equal = false;
    }

    if (synonym != other.synonym) {
        differences.push_back("Synonym differs");
        equal = false;
    }

    if (description != other.description) {
        differences.push_back("Description differs");
        equal = false;
    }

    if (defaultValue != other.defaultValue) {
        differences.push_back("Default value differs");
        equal = false;
    }

    if (getValue() != other.getValue()) {
        differences.push_back("Current value differs");
        equal = false;
    }

    if (sortOrder != other.sortOrder) {
        differences.push_back("Sort order differs");
        equal = false;
    }

    if (group != other.group) {
        differences.push_back("Group differs");
        equal = false;
    }

    if (category != other.category) {
        differences.push_back("Category differs");
        equal = false;
    }

    // Сравниваем правила валидации
    if (validationRules.size() != other.validationRules.size()) {
        differences.push_back("Validation rules count differs");
        equal = false;
    } else {
        for (size_t i = 0; i < validationRules.size(); ++i) {
            if (validationRules[i] != other.validationRules[i]) {
                differences.push_back("Validation rule " + std::to_string(i) + " differs");
                equal = false;
            }
        }
    }

    // Сравниваем ограничения
    if (minValue != other.minValue) {
        differences.push_back("Min value differs");
        equal = false;
    }

    if (maxValue != other.maxValue) {
        differences.push_back("Max value differs");
        equal = false;
    }

    if (minLength != other.minLength) {
        differences.push_back("Min length differs");
        equal = false;
    }

    if (maxLength != other.maxLength) {
        differences.push_back("Max length differs");
        equal = false;
    }

    if (regExp != other.regExp) {
        differences.push_back("Regular expression differs");
        equal = false;
    }

    // Сравниваем атрибуты
    if (attributes.size() != other.attributes.size()) {
        differences.push_back("Attributes count differs");
        equal = false;
    } else {
        for (const auto& [key, value] : attributes) {
            auto it = other.attributes.find(key);
            if (it == other.attributes.end()) {
                differences.push_back("Missing attribute: " + key);
                equal = false;
            } else if (value != it->second) {
                differences.push_back("Attribute '" + key + "' differs");
                equal = false;
            }
        }
    }

    return equal;
}

bool Property::compareByName(const Property& other) const {
    return name == other.name;
}

bool Property::operator==(const Property& other) const {
    return compareByName(other);
}

bool Property::operator!=(const Property& other) const {
    return !(*this == other);
}

bool Property::operator<(const Property& other) const {
    // Сначала по сортировке, затем по имени
    if (sortOrder != other.sortOrder) {
        return sortOrder < other.sortOrder;
    }
    return name < other.name;
}

// ========== Зависимости и связи ==========

void Property::setOwner(const std::weak_ptr<MetaObject>& owner) {
    this->owner = owner;
}

std::shared_ptr<MetaObject> Property::getOwner() const {
    return owner.lock();
}

void Property::setLinkedProperty(const std::weak_ptr<Property>& property) {
    linkedProperty = property;
}

std::shared_ptr<Property> Property::getLinkedProperty() const {
    return linkedProperty.lock();
}

void Property::addDependentProperty(const std::weak_ptr<Property>& property) {
    dependentProperties.push_back(property);
}

std::vector<std::weak_ptr<Property>> Property::getDependentProperties() const {
    // Очищаем "протухшие" weak_ptr
    auto mutableThis = const_cast<Property*>(this);
    mutableThis->dependentProperties.erase(
        std::remove_if(mutableThis->dependentProperties.begin(),
                      mutableThis->dependentProperties.end(),
                      [](const std::weak_ptr<Property>& weak) {
                          return weak.expired();
                      }),
        mutableThis->dependentProperties.end()
    );

    return dependentProperties;
}

bool Property::dependsOn(const std::shared_ptr<Property>& property) const {
    for (const auto& weakDep : dependentProperties) {
        if (auto dep = weakDep.lock()) {
            if (dep == property) {
                return true;
            }
        }
    }
    return false;
}

// ========== Расширяемые атрибуты ==========

void Property::setAttribute(const std::string& key,
                           const std::variant<std::string, int, double, bool>& value) {
    attributes[key] = value;
    notifyPropertyModified();
}

std::optional<std::variant<std::string, int, double, bool>>
Property::getAttribute(const std::string& key) const {
    auto it = attributes.find(key);
    if (it != attributes.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool Property::removeAttribute(const std::string& key) {
    auto it = attributes.find(key);
    if (it != attributes.end()) {
        attributes.erase(it);
        notifyPropertyModified();
        return true;
    }
    return false;
}

std::map<std::string, std::variant<std::string, int, double, bool>>
Property::getAllAttributes() const {
    return attributes;
}

// ========== Сигналы и события ==========

size_t Property::subscribeToValueChanged(ValueChangedSignal callback) {
    size_t id = signalData->nextId++;
    signalData->valueChangedCallbacks[id] = callback;
    return id;
}

size_t Property::subscribeToPropertyModified(PropertyModifiedSignal callback) {
    size_t id = signalData->nextId++;
    signalData->propertyModifiedCallbacks[id] = callback;
    return id;
}

void Property::unsubscribe(size_t subscriptionId) {
    signalData->valueChangedCallbacks.erase(subscriptionId);
    signalData->propertyModifiedCallbacks.erase(subscriptionId);
}

void Property::notifyValueChanged(const std::string& oldValue, const std::string& newValue) {
    for (const auto& [id, callback] : signalData->valueChangedCallbacks) {
        try {
            callback(oldValue, newValue);
        } catch (...) {
            // Игнорируем исключения в коллбеках
        }
    }
}

void Property::notifyPropertyModified() {
    for (const auto& [id, callback] : signalData->propertyModifiedCallbacks) {
        try {
            callback();
        } catch (...) {
            // Игнорируем исключения в коллбеках
        }
    }
}

// ========== Вспомогательные методы ==========

std::string Property::generateUUID() {
#ifdef _WIN32
    GUID guid;
    if (CoCreateGuid(&guid) == S_OK) {
        char buffer[37];
        snprintf(buffer, sizeof(buffer),
                 "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
                 guid.Data1, guid.Data2, guid.Data3,
                 guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
                 guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
        return buffer;
    }
#else
    uuid_t uuid;
    uuid_generate(uuid);
    char buffer[37];
    uuid_unparse(uuid, buffer);
    return buffer;
#endif

//    // Fallback - генерация случайного UUID
//    static std::random_device rd;
//    static std::mt19937 gen(rd());
//    static std::uniform_int_distribution<> dis(0, 15);
//    static std::uniform_int_distribution<> dis2(8, 11);
//
//    const char* hex = "0123456789abcdef";
    std::stringstream ss;
//
//    for (int i = 0; i < 32; i++) {
//        if (i == 8 || i == 12 || i == 16 || i == 20) {
//            ss << "-";
//        }
//
//        if (i == 12) {
//            ss << "4"; // version 4
//        } else if (i == 16) {
//            ss << hex[dis2(gen)];
//        } else {
//            ss << hex[dis(gen)];
//        }
//    }

    return ss.str();
}

std::string Property::normalizeName(const std::string& name) {
    if (name.empty()) return name;

    std::string result = name;

    // Заменяем пробелы и специальные символы на подчеркивания
    std::replace_if(result.begin(), result.end(),
        [](char c) { return !std::isalnum(c) && c != '_' && c != '.'; }, '_');

    // Удаляем двойные подчеркивания
    result.erase(std::unique(result.begin(), result.end(),
        [](char a, char b) { return a == '_' && b == '_'; }), result.end());

    // Обрезаем начальные и конечные подчеркивания
    while (!result.empty() && result.front() == '_') {
        result.erase(result.begin());
    }
    while (!result.empty() && result.back() == '_') {
        result.pop_back();
    }

    return result;
}

// ========== Валидация типов данных ==========

bool Property::validateDataType(const std::string& value, std::vector<std::string>& errors) const {
    if (value.empty()) {
        return true; // Пустая строка валидна для всех типов (кроме обязательных)
    }

    switch (dataType) {
        case DataType::String:
            return validateString(value, errors);
        case DataType::Number:
            return validateNumber(value, errors);
        case DataType::Integer:
            return validateInteger(value, errors);
        case DataType::Float:
            return validateFloat(value, errors);
        case DataType::Boolean:
            return validateBoolean(value, errors);
        case DataType::Date:
            return validateDate(value, errors);
        case DataType::DateTime:
            return validateDateTime(value, errors);
        case DataType::Time:
            return validateTime(value, errors);
        case DataType::UUID:
            return validateString(value, errors); // UUID проверяется regex
        default:
            return true; // Для неизвестных типов принимаем любое значение
    }
}

bool Property::validateString(const std::string& value, std::vector<std::string>& errors) const {
    // Проверка диапазона значений
    if (minValue || maxValue) {
        try {
            double numValue = std::stod(value);
            if (minValue && numValue < *minValue) {
                errors.push_back("String value " + value + " is less than minimum: " +
                               std::to_string(*minValue));
                return false;
            }
            if (maxValue && numValue > *maxValue) {
                errors.push_back("String value " + value + " exceeds maximum: " +
                               std::to_string(*maxValue));
                return false;
            }
        } catch (const std::exception&) {
            // Не число, пропускаем проверку диапазона
        }
    }

    return true;
}

bool Property::validateNumber(const std::string& value, std::vector<std::string>& errors) const {
    try {
        double numValue = std::stod(value);

        // Проверка NaN и Infinity
        if (std::isnan(numValue) || std::isinf(numValue)) {
            errors.push_back("Value is not a valid number");
            return false;
        }

        // Проверка диапазона
        if (minValue && numValue < *minValue) {
            errors.push_back("Value " + value + " is less than minimum: " +
                           std::to_string(*minValue));
            return false;
        }
        if (maxValue && numValue > *maxValue) {
            errors.push_back("Value " + value + " exceeds maximum: " +
                           std::to_string(*maxValue));
            return false;
        }

        return true;
    } catch (const std::exception&) {
        errors.push_back("Value '" + value + "' is not a valid number");
        return false;
    }
}

bool Property::validateInteger(const std::string& value, std::vector<std::string>& errors) const {
    try {
        long long intValue = std::stoll(value);

        // Проверка диапазона
        if (minValue && intValue < static_cast<long long>(*minValue)) {
            errors.push_back("Integer value " + value + " is less than minimum: " +
                           std::to_string(static_cast<long long>(*minValue)));
            return false;
        }
        if (maxValue && intValue > static_cast<long long>(*maxValue)) {
            errors.push_back("Integer value " + value + " exceeds maximum: " +
                           std::to_string(static_cast<long long>(*maxValue)));
            return false;
        }

        // Проверка, что это действительно целое число
        double doubleValue = std::stod(value);
        if (doubleValue != static_cast<double>(intValue)) {
            errors.push_back("Value '" + value + "' is not an integer");
            return false;
        }

        return true;
    } catch (const std::exception&) {
        errors.push_back("Value '" + value + "' is not a valid integer");
        return false;
    }
}

bool Property::validateFloat(const std::string& value, std::vector<std::string>& errors) const {
    try {
        double floatValue = std::stod(value);

        // Проверка NaN и Infinity
        if (std::isnan(floatValue) || std::isinf(floatValue)) {
            errors.push_back("Value is not a valid float");
            return false;
        }

        // Проверка диапазона
        if (minValue && floatValue < *minValue) {
            errors.push_back("Float value " + value + " is less than minimum: " +
                           std::to_string(*minValue));
            return false;
        }
        if (maxValue && floatValue > *maxValue) {
            errors.push_back("Float value " + value + " exceeds maximum: " +
                           std::to_string(*maxValue));
            return false;
        }

        return true;
    } catch (const std::exception&) {
        errors.push_back("Value '" + value + "' is not a valid float");
        return false;
    }
}

bool Property::validateBoolean(const std::string& value, std::vector<std::string>& errors) const {
    std::string lowerValue = value;
    std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    if (lowerValue != "true" && lowerValue != "false" &&
        lowerValue != "1" && lowerValue != "0" &&
        lowerValue != "yes" && lowerValue != "no") {
        errors.push_back("Value '" + value + "' is not a valid boolean");
        return false;
    }

    return true;
}

bool Property::validateDate(const std::string& value, std::vector<std::string>& errors) const {
    std::tm tm = {};
    std::stringstream ss(value);

    // Пробуем разные форматы даты
    ss >> std::get_time(&tm, "%Y-%m-%d");
    if (ss.fail()) {
        ss.clear();
        ss.str(value);
        ss >> std::get_time(&tm, "%d.%m.%Y");
    }
    if (ss.fail()) {
        ss.clear();
        ss.str(value);
        ss >> std::get_time(&tm, "%m/%d/%Y");
    }

    if (ss.fail()) {
        errors.push_back("Value '" + value + "' is not a valid date");
        return false;
    }

    return true;
}

bool Property::validateDateTime(const std::string& value, std::vector<std::string>& errors) const {
    std::tm tm = {};
    std::stringstream ss(value);

    // Пробуем разные форматы даты и времени
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    if (ss.fail()) {
        ss.clear();
        ss.str(value);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
    }
    if (ss.fail()) {
        ss.clear();
        ss.str(value);
        ss >> std::get_time(&tm, "%d.%m.%Y %H:%M:%S");
    }

    if (ss.fail()) {
        errors.push_back("Value '" + value + "' is not a valid date-time");
        return false;
    }

    return true;
}

bool Property::validateTime(const std::string& value, std::vector<std::string>& errors) const {
    std::tm tm = {};
    std::stringstream ss(value);

    // Пробуем разные форматы времени
    ss >> std::get_time(&tm, "%H:%M:%S");
    if (ss.fail()) {
        ss.clear();
        ss.str(value);
        ss >> std::get_time(&tm, "%H:%M");
    }

    if (ss.fail()) {
        errors.push_back("Value '" + value + "' is not a valid time");
        return false;
    }

    return true;
}

// ========== Статические методы ==========

std::string Property::propertyTypeToString(PropertyType type) {
    switch (type) {
        case PropertyType::Requisite: return "Requisite";
        case PropertyType::Column: return "Column";
        case PropertyType::Form: return "Form";
        case PropertyType::Command: return "Command";
        case PropertyType::Layout: return "Layout";
        case PropertyType::TablePart: return "TablePart";
        case PropertyType::Dimension: return "Dimension";
        case PropertyType::Resource: return "Resource";
        case PropertyType::Recalculation: return "Recalculation";
        case PropertyType::Custom: return "Custom";
        default: return "Unknown";
    }
}

PropertyType Property::stringToPropertyType(const std::string& typeName) {
    static std::map<std::string, PropertyType> typeMap = {
        {"Requisite", PropertyType::Requisite},
        {"Column", PropertyType::Column},
        {"Form", PropertyType::Form},
        {"Command", PropertyType::Command},
        {"Layout", PropertyType::Layout},
        {"TablePart", PropertyType::TablePart},
        {"Dimension", PropertyType::Dimension},
        {"Resource", PropertyType::Resource},
        {"Recalculation", PropertyType::Recalculation},
        {"Custom", PropertyType::Custom}
    };

    auto it = typeMap.find(typeName);
    if (it != typeMap.end()) {
        return it->second;
    }
    return PropertyType::Unknown;
}

std::string Property::dataTypeToString(DataType dataType) {
    switch (dataType) {
        case DataType::String: return "String";
        case DataType::Number: return "Number";
        case DataType::Integer: return "Integer";
        case DataType::Float: return "Float";
        case DataType::Boolean: return "Boolean";
        case DataType::Date: return "Date";
        case DataType::DateTime: return "DateTime";
        case DataType::Time: return "Time";
        case DataType::Binary: return "Binary";
        case DataType::Reference: return "Reference";
        case DataType::Table: return "Table";
        case DataType::ValueList: return "ValueList";
        case DataType::Enum: return "Enum";
        case DataType::UUID: return "UUID";
        case DataType::XML: return "XML";
        case DataType::JSON: return "JSON";
        default: return "Unknown";
    }
}

DataType Property::stringToDataType(const std::string& typeName) {
    static std::map<std::string, DataType> typeMap = {
        {"String", DataType::String},
        {"Number", DataType::Number},
        {"Integer", DataType::Integer},
        {"Float", DataType::Float},
        {"Boolean", DataType::Boolean},
        {"Date", DataType::Date},
        {"DateTime", DataType::DateTime},
        {"Time", DataType::Time},
        {"Binary", DataType::Binary},
        {"Reference", DataType::Reference},
        {"Table", DataType::Table},
        {"ValueList", DataType::ValueList},
        {"Enum", DataType::Enum},
        {"UUID", DataType::UUID},
        {"XML", DataType::XML},
        {"JSON", DataType::JSON}
    };

    auto it = typeMap.find(typeName);
    if (it != typeMap.end()) {
        return it->second;
    }
    return DataType::Unknown;
}

bool Property::isValidName(const std::string& name, std::string& error) {
    if (name.empty()) {
        error = "Name cannot be empty";
        return false;
    }

    // Проверяем длину
    if (name.length() > 255) {
        error = "Name is too long (max 255 characters)";
        return false;
    }

    // Проверяем первый символ
    if (!std::isalpha(name[0]) && name[0] != '_') {
        error = "Name must start with a letter or underscore";
        return false;
    }

    // Проверяем остальные символы
    for (char c : name) {
        if (!std::isalnum(c) && c != '_' && c != '.' && c != '-') {
            error = "Name can only contain letters, digits, underscores, dots and hyphens";
            return false;
        }
    }

    // Зарезервированные имена
    static const std::vector<std::string> reservedNames = {
        "null", "undefined", "new", "delete", "this", "self",
        "true", "false", "yes", "no", "on", "off"
    };

    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    for (const auto& reserved : reservedNames) {
        if (lowerName == reserved) {
            error = "Name '" + name + "' is reserved";
            return false;
        }
    }

    return true;
}


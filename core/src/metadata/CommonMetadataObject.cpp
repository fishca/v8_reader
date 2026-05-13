//---------------------------------------------------------------------------


#include "CommonMetadataObject.h"
//---------------------------------------------------------------------------

//#include "Column.h"
//#include "Visitor.h"
//#include "XMLHelper.h"
//#include "JSONHelper.h"
//#include "StringUtils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>

// Вспомогательные заголовки
#ifdef USE_TINYXML2
#include <tinyxml2.h>
using namespace tinyxml2;
#endif

#ifdef USE_NLOHMANN_JSON
#include <nlohmann/json.hpp>
using json = nlohmann::json;
#endif

// ========== Конструкторы ==========

//CommonMetadataObject::CommonMetadataObject()
//    : MetaObject(), indexesDirty(true) {
//    // Базовый конструктор
//}

CommonMetadataObject::CommonMetadataObject()
	: MetaObject() {
	// Базовый конструктор
}


//CommonMetadataObject::CommonMetadataObject(const std::string& name,
//										 const std::string& synonym,
//										 const std::string& comment)
//	: MetaObject(name, synonym, comment), indexesDirty(true) {
//	// Инициализация с параметрами
//}

CommonMetadataObject::CommonMetadataObject(const std::string& name, const std::string& synonym, const std::string& comment)
	: MetaObject(name, synonym, comment) {
	// Инициализация с параметрами
}


//// ========== Методы управления реквизитами ==========
//
//Requisite& CommonMetadataObject::addRequisite(std::unique_ptr<Requisite> requisite) {
//    if (!requisite) {
//        throw std::invalid_argument("Cannot add null requisite");
//    }
//
//    std::string name = requisite->getName();
//    if (hasRequisite(name)) {
//        throw std::runtime_error("Requisite with name '" + name + "' already exists");
//    }
//
//    Requisite& ref = *requisite;
//    requisites.push_back(std::move(requisite));
//
//    // Обновляем индексы
//    if (!indexesDirty) {
//        requisiteIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    afterRequisiteAdded(ref);
//    return ref;
//}
//
//Requisite& CommonMetadataObject::createRequisite(const std::string& name,
//                                                const std::string& type,
//                                                const std::string& description,
//                                                bool required) {
//    auto requisite = std::make_unique<Requisite>();
//    requisite->setName(name);
//    requisite->setType(type);
//    requisite->setDescription(description);
//    requisite->setRequired(required);
//
//    return addRequisite(std::move(requisite));
//}
//
//Requisite* CommonMetadataObject::getRequisite(const std::string& name) {
//    updateIndexes();
//    auto it = requisiteIndex.find(name);
//    return (it != requisiteIndex.end()) ? it->second : nullptr;
//}
//
//const Requisite* CommonMetadataObject::getRequisite(const std::string& name) const {
//    updateIndexes();
//    auto it = requisiteIndex.find(name);
//    return (it != requisiteIndex.end()) ? it->second : nullptr;
//}
//
//Requisite* CommonMetadataObject::getRequisite(size_t index) {
//    if (index < requisites.size()) {
//        return requisites[index].get();
//    }
//    return nullptr;
//}
//
//const Requisite* CommonMetadataObject::getRequisite(size_t index) const {
//    if (index < requisites.size()) {
//        return requisites[index].get();
//    }
//    return nullptr;
//}
//
//bool CommonMetadataObject::hasRequisite(const std::string& name) const {
//    return getRequisite(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeRequisite(const std::string& name) {
//    updateIndexes();
//
//    auto it = requisiteIndex.find(name);
//    if (it != requisiteIndex.end()) {
//        Requisite* requisite = it->second;
//        beforeRequisiteRemoved(*requisite);
//
//        // Удаляем из вектора
//        auto vecIt = std::remove_if(requisites.begin(), requisites.end(),
//            [name](const std::unique_ptr<Requisite>& req) {
//                return req->getName() == name;
//            });
//
//        if (vecIt != requisites.end()) {
//            requisites.erase(vecIt, requisites.end());
//            requisiteIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getRequisiteCount() const {
//    return requisites.size();
//}
//
//// ========== Методы управления формами ==========
//
//Form& CommonMetadataObject::addForm(std::unique_ptr<Form> form) {
//    if (!form) {
//        throw std::invalid_argument("Cannot add null form");
//    }
//
//    std::string name = form->getName();
//    if (hasForm(name)) {
//        throw std::runtime_error("Form with name '" + name + "' already exists");
//    }
//
//    Form& ref = *form;
//    forms.push_back(std::move(form));
//
//    if (!indexesDirty) {
//        formIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    afterFormAdded(ref);
//    return ref;
//}
//
//Form& CommonMetadataObject::createForm(const std::string& name,
//                                      const std::string& formType,
//                                      const std::string& fileName) {
//    auto form = std::make_unique<Form>();
//    form->setName(name);
//    form->setFormType(formType);
//    form->setFileName(fileName);
//
//    return addForm(std::move(form));
//}
//
//Form* CommonMetadataObject::getForm(const std::string& name) {
//    updateIndexes();
//    auto it = formIndex.find(name);
//    return (it != formIndex.end()) ? it->second : nullptr;
//}
//
//const Form* CommonMetadataObject::getForm(const std::string& name) const {
//    updateIndexes();
//    auto it = formIndex.find(name);
//    return (it != formIndex.end()) ? it->second : nullptr;
//}
//
//Form* CommonMetadataObject::getFormByType(const std::string& formType) {
//    for (const auto& form : forms) {
//        if (form->getFormType() == formType) {
//            return form.get();
//        }
//    }
//    return nullptr;
//}
//
//bool CommonMetadataObject::hasForm(const std::string& name) const {
//    return getForm(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeForm(const std::string& name) {
//    updateIndexes();
//
//    auto it = formIndex.find(name);
//    if (it != formIndex.end()) {
//        Form* form = it->second;
//        beforeFormRemoved(*form);
//
//        auto vecIt = std::remove_if(forms.begin(), forms.end(),
//            [name](const std::unique_ptr<Form>& f) {
//                return f->getName() == name;
//            });
//
//        if (vecIt != forms.end()) {
//            forms.erase(vecIt, forms.end());
//            formIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getFormCount() const {
//    return forms.size();
//}
//
//// ========== Методы управления командами ==========
//
//Command& CommonMetadataObject::addCommand(std::unique_ptr<Command> command) {
//    if (!command) {
//        throw std::invalid_argument("Cannot add null command");
//    }
//
//    std::string name = command->getName();
//    if (hasCommand(name)) {
//        throw std::runtime_error("Command with name '" + name + "' already exists");
//    }
//
//    Command& ref = *command;
//    commands.push_back(std::move(command));
//
//    if (!indexesDirty) {
//        commandIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    return ref;
//}
//
//Command& CommonMetadataObject::createCommand(const std::string& name,
//                                            const std::string& handler,
//                                            const std::string& icon) {
//    auto command = std::make_unique<Command>();
//    command->setName(name);
//    command->setHandler(handler);
//    command->setIcon(icon);
//
//    return addCommand(std::move(command));
//}
//
//Command* CommonMetadataObject::getCommand(const std::string& name) {
//    updateIndexes();
//    auto it = commandIndex.find(name);
//    return (it != commandIndex.end()) ? it->second : nullptr;
//}
//
//const Command* CommonMetadataObject::getCommand(const std::string& name) const {
//    updateIndexes();
//    auto it = commandIndex.find(name);
//    return (it != commandIndex.end()) ? it->second : nullptr;
//}
//
//bool CommonMetadataObject::hasCommand(const std::string& name) const {
//    return getCommand(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeCommand(const std::string& name) {
//    updateIndexes();
//
//    auto it = commandIndex.find(name);
//    if (it != commandIndex.end()) {
//        auto vecIt = std::remove_if(commands.begin(), commands.end(),
//            [name](const std::unique_ptr<Command>& cmd) {
//                return cmd->getName() == name;
//            });
//
//        if (vecIt != commands.end()) {
//            commands.erase(vecIt, commands.end());
//            commandIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getCommandCount() const {
//    return commands.size();
//}
//
//// ========== Методы управления макетами ==========
//
//Layout& CommonMetadataObject::addLayout(std::unique_ptr<Layout> layout) {
//    if (!layout) {
//        throw std::invalid_argument("Cannot add null layout");
//    }
//
//    std::string name = layout->getName();
//    if (hasLayout(name)) {
//        throw std::runtime_error("Layout with name '" + name + "' already exists");
//    }
//
//    Layout& ref = *layout;
//    layouts.push_back(std::move(layout));
//
//    if (!indexesDirty) {
//        layoutIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    return ref;
//}
//
//Layout& CommonMetadataObject::createLayout(const std::string& name,
//                                          const std::string& layoutType,
//                                          const std::string& fileName) {
//    auto layout = std::make_unique<Layout>();
//    layout->setName(name);
//    layout->setLayoutType(layoutType);
//    layout->setFileName(fileName);
//
//    return addLayout(std::move(layout));
//}
//
//Layout* CommonMetadataObject::getLayout(const std::string& name) {
//    updateIndexes();
//    auto it = layoutIndex.find(name);
//    return (it != layoutIndex.end()) ? it->second : nullptr;
//}
//
//const Layout* CommonMetadataObject::getLayout(const std::string& name) const {
//    updateIndexes();
//    auto it = layoutIndex.find(name);
//    return (it != layoutIndex.end()) ? it->second : nullptr;
//}
//
//Layout* CommonMetadataObject::getLayoutByType(const std::string& layoutType) {
//    for (const auto& layout : layouts) {
//        if (layout->getLayoutType() == layoutType) {
//            return layout.get();
//        }
//    }
//    return nullptr;
//}
//
//bool CommonMetadataObject::hasLayout(const std::string& name) const {
//    return getLayout(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeLayout(const std::string& name) {
//    updateIndexes();
//
//    auto it = layoutIndex.find(name);
//    if (it != layoutIndex.end()) {
//        auto vecIt = std::remove_if(layouts.begin(), layouts.end(),
//            [name](const std::unique_ptr<Layout>& layout) {
//                return layout->getName() == name;
//            });
//
//        if (vecIt != layouts.end()) {
//            layouts.erase(vecIt, layouts.end());
//            layoutIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getLayoutCount() const {
//    return layouts.size();
//}
//
//// ========== Методы управления табличными частями ==========
//
//TablePart& CommonMetadataObject::addTablePart(std::unique_ptr<TablePart> tablePart) {
//    if (!tablePart) {
//        throw std::invalid_argument("Cannot add null table part");
//    }
//
//    std::string name = tablePart->getName();
//    if (hasTablePart(name)) {
//        throw std::runtime_error("TablePart with name '" + name + "' already exists");
//    }
//
//    TablePart& ref = *tablePart;
//    tableParts.push_back(std::move(tablePart));
//
//    if (!indexesDirty) {
//        tablePartIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    return ref;
//}
//
//TablePart& CommonMetadataObject::createTablePart(const std::string& name,
//                                                const std::string& description) {
//    auto tablePart = std::make_unique<TablePart>();
//    tablePart->setName(name);
//    tablePart->setDescription(description);
//
//    return addTablePart(std::move(tablePart));
//}
//
//TablePart* CommonMetadataObject::getTablePart(const std::string& name) {
//    updateIndexes();
//    auto it = tablePartIndex.find(name);
//    return (it != tablePartIndex.end()) ? it->second : nullptr;
//}
//
//const TablePart* CommonMetadataObject::getTablePart(const std::string& name) const {
//    updateIndexes();
//    auto it = tablePartIndex.find(name);
//    return (it != tablePartIndex.end()) ? it->second : nullptr;
//}
//
//bool CommonMetadataObject::hasTablePart(const std::string& name) const {
//    return getTablePart(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeTablePart(const std::string& name) {
//    updateIndexes();
//
//    auto it = tablePartIndex.find(name);
//    if (it != tablePartIndex.end()) {
//        auto vecIt = std::remove_if(tableParts.begin(), tableParts.end(),
//            [name](const std::unique_ptr<TablePart>& tp) {
//                return tp->getName() == name;
//            });
//
//        if (vecIt != tableParts.end()) {
//            tableParts.erase(vecIt, tableParts.end());
//            tablePartIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getTablePartCount() const {
//    return tableParts.size();
//}
//
//// ========== Методы управления колонками ==========
//
//Column& CommonMetadataObject::addColumn(std::unique_ptr<Column> column) {
//    if (!column) {
//        throw std::invalid_argument("Cannot add null column");
//    }
//
//    std::string name = column->getName();
//    if (hasColumn(name)) {
//        throw std::runtime_error("Column with name '" + name + "' already exists");
//    }
//
//    Column& ref = *column;
//    columns.push_back(std::move(column));
//
//    if (!indexesDirty) {
//        columnIndex[name] = &ref;
//    } else {
//        indexesDirty = true;
//    }
//
//    return ref;
//}
//
//Column& CommonMetadataObject::createColumn(const std::string& name,
//                                          const std::string& type,
//                                          int width) {
//    auto column = std::make_unique<Column>();
//    column->setName(name);
//    column->setType(type);
//    column->setWidth(width);
//
//    return addColumn(std::move(column));
//}
//
//Column* CommonMetadataObject::getColumn(const std::string& name) {
//    updateIndexes();
//    auto it = columnIndex.find(name);
//    return (it != columnIndex.end()) ? it->second : nullptr;
//}
//
//const Column* CommonMetadataObject::getColumn(const std::string& name) const {
//    updateIndexes();
//    auto it = columnIndex.find(name);
//    return (it != columnIndex.end()) ? it->second : nullptr;
//}
//
//bool CommonMetadataObject::hasColumn(const std::string& name) const {
//    return getColumn(name) != nullptr;
//}
//
//bool CommonMetadataObject::removeColumn(const std::string& name) {
//    updateIndexes();
//
//    auto it = columnIndex.find(name);
//    if (it != columnIndex.end()) {
//        auto vecIt = std::remove_if(columns.begin(), columns.end(),
//            [name](const std::unique_ptr<Column>& col) {
//                return col->getName() == name;
//            });
//
//        if (vecIt != columns.end()) {
//            columns.erase(vecIt, columns.end());
//            columnIndex.erase(it);
//            return true;
//        }
//    }
//
//    return false;
//}
//
//size_t CommonMetadataObject::getColumnCount() const {
//    return columns.size();
//}
//
//// ========== Сериализация XML ==========
//
//void CommonMetadataObject::toXML(tinyxml2::XMLElement* parent) const {
//    // Сначала вызываем базовый метод
//    MetaObject::toXML(parent);
//
//    if (parent) {
//        XMLElement* root = parent->GetDocument()->NewElement("CommonProperties");
//        parent->InsertEndChild(root);
//
//        // Сериализуем реквизиты
//        if (!requisites.empty()) {
//            XMLElement* requisitesElem = parent->GetDocument()->NewElement("Requisites");
//            for (const auto& req : requisites) {
//                XMLElement* reqElem = parent->GetDocument()->NewElement("Requisite");
//                req->toXML(reqElem);
//                requisitesElem->InsertEndChild(reqElem);
//            }
//            root->InsertEndChild(requisitesElem);
//        }
//
//        // Сериализуем формы
//        if (!forms.empty()) {
//            XMLElement* formsElem = parent->GetDocument()->NewElement("Forms");
//            for (const auto& form : forms) {
//                XMLElement* formElem = parent->GetDocument()->NewElement("Form");
//                form->toXML(formElem);
//                formsElem->InsertEndChild(formElem);
//            }
//            root->InsertEndChild(formsElem);
//        }
//
//        // Сериализуем команды
//        if (!commands.empty()) {
//            XMLElement* commandsElem = parent->GetDocument()->NewElement("Commands");
//            for (const auto& cmd : commands) {
//                XMLElement* cmdElem = parent->GetDocument()->NewElement("Command");
//                cmd->toXML(cmdElem);
//                commandsElem->InsertEndChild(cmdElem);
//            }
//            root->InsertEndChild(commandsElem);
//        }
//
//        // Сериализуем макеты
//        if (!layouts.empty()) {
//            XMLElement* layoutsElem = parent->GetDocument()->NewElement("Layouts");
//            for (const auto& layout : layouts) {
//                XMLElement* layoutElem = parent->GetDocument()->NewElement("Layout");
//                layout->toXML(layoutElem);
//                layoutsElem->InsertEndChild(layoutElem);
//            }
//            root->InsertEndChild(layoutsElem);
//        }
//
//        // Сериализуем табличные части
//        if (!tableParts.empty()) {
//            XMLElement* tablePartsElem = parent->GetDocument()->NewElement("TableParts");
//            for (const auto& tp : tableParts) {
//                XMLElement* tpElem = parent->GetDocument()->NewElement("TablePart");
//                tp->toXML(tpElem);
//                tablePartsElem->InsertEndChild(tpElem);
//            }
//            root->InsertEndChild(tablePartsElem);
//        }
//
//        // Сериализуем колонки
//        if (!columns.empty()) {
//            XMLElement* columnsElem = parent->GetDocument()->NewElement("Columns");
//            for (const auto& col : columns) {
//                XMLElement* colElem = parent->GetDocument()->NewElement("Column");
//                col->toXML(colElem);
//                columnsElem->InsertEndChild(colElem);
//            }
//            root->InsertEndChild(columnsElem);
//        }
//    }
//}
//
//bool CommonMetadataObject::fromXML(const tinyxml2::XMLElement* element) {
//    if (!MetaObject::fromXML(element)) {
//        return false;
//    }
//
//    // Очищаем существующие свойства
//    clearAllProperties();
//
//    // Парсим реквизиты
//    const XMLElement* requisitesElem = element->FirstChildElement("Requisites");
//    if (requisitesElem) {
//        const XMLElement* reqElem = requisitesElem->FirstChildElement("Requisite");
//        while (reqElem) {
//            auto requisite = std::make_unique<Requisite>();
//            if (requisite->fromXML(reqElem)) {
//                addRequisite(std::move(requisite));
//            }
//            reqElem = reqElem->NextSiblingElement("Requisite");
//        }
//    }
//
//    // Парсим формы
//    const XMLElement* formsElem = element->FirstChildElement("Forms");
//    if (formsElem) {
//        const XMLElement* formElem = formsElem->FirstChildElement("Form");
//        while (formElem) {
//            auto form = std::make_unique<Form>();
//            if (form->fromXML(formElem)) {
//                addForm(std::move(form));
//            }
//            formElem = formElem->NextSiblingElement("Form");
//        }
//    }
//
//    // Парсим команды
//    const XMLElement* commandsElem = element->FirstChildElement("Commands");
//    if (commandsElem) {
//        const XMLElement* cmdElem = commandsElem->FirstChildElement("Command");
//        while (cmdElem) {
//            auto command = std::make_unique<Command>();
//            if (command->fromXML(cmdElem)) {
//                addCommand(std::move(command));
//            }
//            cmdElem = cmdElem->NextSiblingElement("Command");
//        }
//    }
//
//    // Парсим макеты
//    const XMLElement* layoutsElem = element->FirstChildElement("Layouts");
//    if (layoutsElem) {
//        const XMLElement* layoutElem = layoutsElem->FirstChildElement("Layout");
//        while (layoutElem) {
//            auto layout = std::make_unique<Layout>();
//            if (layout->fromXML(layoutElem)) {
//                addLayout(std::move(layout));
//            }
//            layoutElem = layoutElem->NextSiblingElement("Layout");
//        }
//    }
//
//    // Парсим табличные части
//    const XMLElement* tablePartsElem = element->FirstChildElement("TableParts");
//    if (tablePartsElem) {
//        const XMLElement* tpElem = tablePartsElem->FirstChildElement("TablePart");
//        while (tpElem) {
//            auto tablePart = std::make_unique<TablePart>();
//            if (tablePart->fromXML(tpElem)) {
//                addTablePart(std::move(tablePart));
//            }
//            tpElem = tpElem->NextSiblingElement("TablePart");
//        }
//    }
//
//    // Парсим колонки
//    const XMLElement* columnsElem = element->FirstChildElement("Columns");
//    if (columnsElem) {
//        const XMLElement* colElem = columnsElem->FirstChildElement("Column");
//        while (colElem) {
//            auto column = std::make_unique<Column>();
//            if (column->fromXML(colElem)) {
//                addColumn(std::move(column));
//            }
//            colElem = colElem->NextSiblingElement("Column");
//        }
//    }
//
//    rebuildIndexes();
//    return true;
//}
//
//// ========== Сериализация JSON ==========
//
//nlohmann::json CommonMetadataObject::toJSON() const {
//    json j = MetaObject::toJSON();
//
//    // Добавляем общие свойства
//    j["type"] = "CommonMetadataObject";
//
//    // Реквизиты
//    if (!requisites.empty()) {
//        json requisitesArray = json::array();
//        for (const auto& req : requisites) {
//            requisitesArray.push_back(req->toJSON());
//        }
//        j["requisites"] = requisitesArray;
//    }
//
//    // Формы
//    if (!forms.empty()) {
//        json formsArray = json::array();
//        for (const auto& form : forms) {
//            formsArray.push_back(form->toJSON());
//        }
//        j["forms"] = formsArray;
//    }
//
//    // Команды
//    if (!commands.empty()) {
//        json commandsArray = json::array();
//        for (const auto& cmd : commands) {
//            commandsArray.push_back(cmd->toJSON());
//        }
//        j["commands"] = commandsArray;
//    }
//
//    // Макеты
//    if (!layouts.empty()) {
//        json layoutsArray = json::array();
//        for (const auto& layout : layouts) {
//            layoutsArray.push_back(layout->toJSON());
//        }
//        j["layouts"] = layoutsArray;
//    }
//
//    // Табличные части
//    if (!tableParts.empty()) {
//        json tablePartsArray = json::array();
//        for (const auto& tp : tableParts) {
//            tablePartsArray.push_back(tp->toJSON());
//        }
//        j["tableParts"] = tablePartsArray;
//    }
//
//    // Колонки
//    if (!columns.empty()) {
//        json columnsArray = json::array();
//        for (const auto& col : columns) {
//            columnsArray.push_back(col->toJSON());
//        }
//        j["columns"] = columnsArray;
//    }
//
//    return j;
//}
//
//bool CommonMetadataObject::fromJSON(const nlohmann::json& json) {
//    if (!MetaObject::fromJSON(json)) {
//        return false;
//    }
//
//    // Очищаем существующие свойства
//    clearAllProperties();
//
//    // Загружаем реквизиты
//    if (json.contains("requisites") && json["requisites"].is_array()) {
//        for (const auto& reqJson : json["requisites"]) {
//            auto requisite = std::make_unique<Requisite>();
//            if (requisite->fromJSON(reqJson)) {
//                addRequisite(std::move(requisite));
//            }
//        }
//    }
//
//    // Загружаем формы
//    if (json.contains("forms") && json["forms"].is_array()) {
//        for (const auto& formJson : json["forms"]) {
//            auto form = std::make_unique<Form>();
//            if (form->fromJSON(formJson)) {
//                addForm(std::move(form));
//            }
//        }
//    }
//
//    // Загружаем команды
//    if (json.contains("commands") && json["commands"].is_array()) {
//        for (const auto& cmdJson : json["commands"]) {
//            auto command = std::make_unique<Command>();
//            if (command->fromJSON(cmdJson)) {
//                addCommand(std::move(command));
//            }
//        }
//    }
//
//    // Загружаем макеты
//    if (json.contains("layouts") && json["layouts"].is_array()) {
//        for (const auto& layoutJson : json["layouts"]) {
//            auto layout = std::make_unique<Layout>();
//            if (layout->fromJSON(layoutJson)) {
//                addLayout(std::move(layout));
//            }
//        }
//    }
//
//    // Загружаем табличные части
//    if (json.contains("tableParts") && json["tableParts"].is_array()) {
//        for (const auto& tpJson : json["tableParts"]) {
//            auto tablePart = std::make_unique<TablePart>();
//            if (tablePart->fromJSON(tpJson)) {
//                addTablePart(std::move(tablePart));
//            }
//        }
//    }
//
//    // Загружаем колонки
//    if (json.contains("columns") && json["columns"].is_array()) {
//        for (const auto& colJson : json["columns"]) {
//            auto column = std::make_unique<Column>();
//            if (column->fromJSON(colJson)) {
//                addColumn(std::move(column));
//            }
//        }
//    }
//
//    rebuildIndexes();
//    return true;
//}
//
//// ========== Методы для работы с UI ==========
//
//void CommonMetadataObject::populateTreeView(TTreeNode* parent, TTreeView* treeView) const {
//    if (!parent || !treeView) return;
//
//    // Добавляем базовую информацию
//    MetaObject::populateTreeView(parent, treeView);
//
//    // Добавляем реквизиты как дочерние узлы
//    if (!requisites.empty()) {
//        TTreeNode* reqNode = treeView->Items->AddChild(parent, "Реквизиты");
//        reqNode->ImageIndex = ICON_REQUISITES;
//        reqNode->SelectedIndex = ICON_REQUISITES;
//
//        for (const auto& req : requisites) {
//            TTreeNode* childNode = treeView->Items->AddChild(reqNode, req->getName().c_str());
//            childNode->ImageIndex = ICON_REQUISITE;
//            childNode->SelectedIndex = ICON_REQUISITE;
//            childNode->Data = (void*)req.get();  // Сохраняем указатель
//        }
//    }
//
//    // Добавляем формы
//    if (!forms.empty()) {
//        TTreeNode* formsNode = treeView->Items->AddChild(parent, "Формы");
//        formsNode->ImageIndex = ICON_FORMS;
//        formsNode->SelectedIndex = ICON_FORMS;
//
//        for (const auto& form : forms) {
//            std::string displayName = form->getName() + " (" + form->getFormType() + ")";
//            TTreeNode* childNode = treeView->Items->AddChild(formsNode, displayName.c_str());
//            childNode->ImageIndex = ICON_FORM;
//            childNode->SelectedIndex = ICON_FORM;
//            childNode->Data = (void*)form.get();
//        }
//    }
//
//    // Добавляем команды
//    if (!commands.empty()) {
//        TTreeNode* commandsNode = treeView->Items->AddChild(parent, "Команды");
//        commandsNode->ImageIndex = ICON_COMMANDS;
//        commandsNode->SelectedIndex = ICON_COMMANDS;
//
//        for (const auto& cmd : commands) {
//            TTreeNode* childNode = treeView->Items->AddChild(commandsNode, cmd->getName().c_str());
//            childNode->ImageIndex = ICON_COMMAND;
//            childNode->SelectedIndex = ICON_COMMAND;
//            childNode->Data = (void*)cmd.get();
//        }
//    }
//
//    // Добавляем макеты
//    if (!layouts.empty()) {
//        TTreeNode* layoutsNode = treeView->Items->AddChild(parent, "Макеты");
//        layoutsNode->ImageIndex = ICON_LAYOUTS;
//        layoutsNode->SelectedIndex = ICON_LAYOUTS;
//
//        for (const auto& layout : layouts) {
//            std::string displayName = layout->getName() + " (" + layout->getLayoutType() + ")";
//            TTreeNode* childNode = treeView->Items->AddChild(layoutsNode, displayName.c_str());
//            childNode->ImageIndex = ICON_LAYOUT;
//            childNode->SelectedIndex = ICON_LAYOUT;
//            childNode->Data = (void*)layout.get();
//        }
//    }
//
//    // Добавляем табличные части
//    if (!tableParts.empty()) {
//        TTreeNode* tablePartsNode = treeView->Items->AddChild(parent, "Табличные части");
//        tablePartsNode->ImageIndex = ICON_TABLE_PARTS;
//        tablePartsNode->SelectedIndex = ICON_TABLE_PARTS;
//
//        for (const auto& tp : tableParts) {
//            TTreeNode* childNode = treeView->Items->AddChild(tablePartsNode, tp->getName().c_str());
//            childNode->ImageIndex = ICON_TABLE_PART;
//            childNode->SelectedIndex = ICON_TABLE_PART;
//            childNode->Data = (void*)tp.get();
//        }
//    }
//
//    // Добавляем колонки
//    if (!columns.empty()) {
//        TTreeNode* columnsNode = treeView->Items->AddChild(parent, "Колонки");
//        columnsNode->ImageIndex = ICON_COLUMNS;
//        columnsNode->SelectedIndex = ICON_COLUMNS;
//
//        for (const auto& col : columns) {
//            TTreeNode* childNode = treeView->Items->AddChild(columnsNode, col->getName().c_str());
//            childNode->ImageIndex = ICON_COLUMN;
//            childNode->SelectedIndex = ICON_COLUMN;
//            childNode->Data = (void*)col.get();
//        }
//    }
//}
//
//std::vector<std::pair<std::string, std::string>> CommonMetadataObject::getProperties() const {
//    auto props = MetaObject::getProperties();
//
//    // Добавляем статистику
//    props.push_back({"Общее количество свойств", std::to_string(getTotalPropertiesCount())});
//    props.push_back({"Количество реквизитов", std::to_string(getRequisiteCount())});
//    props.push_back({"Количество форм", std::to_string(getFormCount())});
//    props.push_back({"Количество команд", std::to_string(getCommandCount())});
//    props.push_back({"Количество макетов", std::to_string(getLayoutCount())});
//    props.push_back({"Количество табличных частей", std::to_string(getTablePartCount())});
//    props.push_back({"Количество колонок", std::to_string(getColumnCount())});
//
//    return props;
//}
//
//std::vector<const Requisite*> CommonMetadataObject::getRequisitesForDisplay() const {
//    std::vector<const Requisite*> result;
//    result.reserve(requisites.size());
//
//    for (const auto& req : requisites) {
//        result.push_back(req.get());
//    }
//
//    return result;
//}
//
//std::vector<const Form*> CommonMetadataObject::getFormsForDisplay() const {
//    std::vector<const Form*> result;
//    result.reserve(forms.size());
//
//    for (const auto& form : forms) {
//        result.push_back(form.get());
//    }
//
//    return result;
//}
//
//std::vector<const Command*> CommonMetadataObject::getCommandsForDisplay() const {
//    std::vector<const Command*> result;
//    result.reserve(commands.size());
//
//    for (const auto& cmd : commands) {
//        result.push_back(cmd.get());
//    }
//
//    return result;
//}
//
//std::vector<const Layout*> CommonMetadataObject::getLayoutsForDisplay() const {
//    std::vector<const Layout*> result;
//    result.reserve(layouts.size());
//
//    for (const auto& layout : layouts) {
//        result.push_back(layout.get());
//    }
//
//    return result;
//}
//
//std::vector<const TablePart*> CommonMetadataObject::getTablePartsForDisplay() const {
//    std::vector<const TablePart*> result;
//    result.reserve(tableParts.size());
//
//    for (const auto& tp : tableParts) {
//        result.push_back(tp.get());
//    }
//
//    return result;
//}
//
//std::vector<const Column*> CommonMetadataObject::getColumnsForDisplay() const {
//    std::vector<const Column*> result;
//    result.reserve(columns.size());
//
//    for (const auto& col : columns) {
//        result.push_back(col.get());
//    }
//
//    return result;
//}
//
//// ========== Методы поиска и фильтрации ==========
//
//std::vector<const Requisite*> CommonMetadataObject::searchRequisites(
//    const std::string& searchText, bool caseSensitive) const {
//
//    std::vector<const Requisite*> result;
//
//    for (const auto& req : requisites) {
//        bool found = false;
//
//        if (caseSensitive) {
//            found = (req->getName().find(searchText) != std::string::npos) ||
//                   (req->getDescription().find(searchText) != std::string::npos);
//        } else {
//            std::string searchLower = StringUtils::toLower(searchText);
//            std::string nameLower = StringUtils::toLower(req->getName());
//            std::string descLower = StringUtils::toLower(req->getDescription());
//
//            found = (nameLower.find(searchLower) != std::string::npos) ||
//                   (descLower.find(searchLower) != std::string::npos);
//        }
//
//        if (found) {
//            result.push_back(req.get());
//        }
//    }
//
//    return result;
//}
//
//std::vector<const Form*> CommonMetadataObject::searchForms(
//    const std::string& searchText, bool searchInType) const {
//
//    std::vector<const Form*> result;
//    std::string searchLower = StringUtils::toLower(searchText);
//
//    for (const auto& form : forms) {
//        bool found = false;
//        std::string nameLower = StringUtils::toLower(form->getName());
//
//        found = (nameLower.find(searchLower) != std::string::npos);
//
//        if (!found && searchInType) {
//            std::string typeLower = StringUtils::toLower(form->getFormType());
//            found = (typeLower.find(searchLower) != std::string::npos);
//        }
//
//        if (found) {
//            result.push_back(form.get());
//        }
//    }
//
//    return result;
//}
//
//std::vector<const Requisite*> CommonMetadataObject::filterRequisitesByType(
//    const std::string& type) const {
//
//    std::vector<const Requisite*> result;
//
//    for (const auto& req : requisites) {
//        if (req->getType() == type) {
//            result.push_back(req.get());
//        }
//    }
//
//    return result;
//}
//
//std::vector<const Requisite*> CommonMetadataObject::getRequiredRequisites() const {
//    std::vector<const Requisite*> result;
//
//    for (const auto& req : requisites) {
//        if (req->isRequired()) {
//            result.push_back(req.get());
//        }
//    }
//
//    return result;
//}
//
//// ========== Валидация ==========
//
//bool CommonMetadataObject::validate(std::vector<std::string>& errors) const {
//    bool valid = MetaObject::validate(errors);
//
//    // Проверяем уникальность имен реквизитов
//    if (!validateRequisiteNames(errors)) {
//        valid = false;
//    }
//
//    // Проверяем уникальность имен форм
//    std::unordered_set<std::string> formNames;
//    for (const auto& form : forms) {
//        if (!formNames.insert(form->getName()).second) {
//            errors.push_back("Дублирующееся имя формы: " + form->getName());
//            valid = false;
//        }
//    }
//
//    // Проверяем обязательные поля
//    for (const auto& req : requisites) {
//        if (req->isRequired() && req->getDefaultValue().empty()) {
//            errors.push_back("Обязательный реквизит '" + req->getName() +
//                            "' не имеет значения по умолчанию");
//            valid = false;
//        }
//    }
//
//    return valid;
//}
//
//bool CommonMetadataObject::validateRequisiteNames(std::vector<std::string>& errors) const {
//    std::unordered_set<std::string> names;
//    bool valid = true;
//
//    for (const auto& req : requisites) {
//        if (!names.insert(req->getName()).second) {
//            errors.push_back("Дублирующееся имя реквизита: " + req->getName());
//            valid = false;
//        }
//    }
//
//    return valid;
//}
//
//// ========== Паттерн Visitor ==========
//
//void CommonMetadataObject::accept(Visitor* visitor) {
//    if (visitor) {
//        visitor->visitCommonMetadataObject(this);
//
//        // Посещаем все реквизиты
//        for (const auto& req : requisites) {
//            req->accept(visitor);
//        }
//
//        // Посещаем все формы
//        for (const auto& form : forms) {
//            form->accept(visitor);
//        }
//
//        // Посещаем все команды
//        for (const auto& cmd : commands) {
//            cmd->accept(visitor);
//        }
//
//        // Посещаем все макеты
//        for (const auto& layout : layouts) {
//            layout->accept(visitor);
//        }
//
//        // Посещаем все табличные части
//        for (const auto& tp : tableParts) {
//            tp->accept(visitor);
//        }
//
//        // Посещаем все колонки
//        for (const auto& col : columns) {
//            col->accept(visitor);
//        }
//    }
//}
//
//// ========== Методы клонирования ==========
//
//std::unique_ptr<CommonMetadataObject> CommonMetadataObject::clone() const {
//    auto cloneObj = std::make_unique<CommonMetadataObject>();
//
//    // Копируем базовые свойства
//    cloneObj->setName(getName());
//    cloneObj->setSynonym(getSynonym());
//    cloneObj->setComment(getComment());
//    cloneObj->setCreated(getCreated());
//    cloneObj->setModified(getModified());
//
//    // Клонируем реквизиты
//    for (const auto& req : requisites) {
//        cloneObj->addRequisite(req->clone());
//    }
//
//    // Клонируем формы
//    for (const auto& form : forms) {
//        cloneObj->addForm(form->clone());
//    }
//
//    // Клонируем команды
//    for (const auto& cmd : commands) {
//        cloneObj->addCommand(cmd->clone());
//    }
//
//    // Клонируем макеты
//    for (const auto& layout : layouts) {
//        cloneObj->addLayout(layout->clone());
//    }
//
//    // Клонируем табличные части
//    for (const auto& tp : tableParts) {
//        cloneObj->addTablePart(tp->clone());
//    }
//
//    // Клонируем колонки
//    for (const auto& col : columns) {
//        cloneObj->addColumn(col->clone());
//    }
//
//    return cloneObj;
//}
//
//std::unique_ptr<CommonMetadataObject> CommonMetadataObject::cloneWithName(
//    const std::string& newName) const {
//
//    auto cloneObj = clone();
//    cloneObj->setName(newName);
//    return cloneObj;
//}
//
//// ========== Статистика ==========
//
//size_t CommonMetadataObject::getTotalPropertiesCount() const {
//    return getRequisiteCount() + getFormCount() + getCommandCount() +
//           getLayoutCount() + getTablePartCount() + getColumnCount();
//}
//
//size_t CommonMetadataObject::getTotalElementsCount() const {
//    size_t count = getTotalPropertiesCount();
//
//    // Добавляем элементы внутри табличных частей
//    for (const auto& tp : tableParts) {
//        count += tp->getColumnCount();
//    }
//
//    return count;
//}
//
//// ========== Методы для работы с контейнерами ==========
//
//void CommonMetadataObject::clearAllProperties() {
//    requisites.clear();
//    forms.clear();
//    commands.clear();
//    layouts.clear();
//    tableParts.clear();
//    columns.clear();
//
//    requisiteIndex.clear();
//    formIndex.clear();
//    commandIndex.clear();
//    layoutIndex.clear();
//    tablePartIndex.clear();
//    columnIndex.clear();
//
//    indexesDirty = false;
//}
//
//void CommonMetadataObject::sortRequisitesByName(bool ascending) {
//    std::sort(requisites.begin(), requisites.end(),
//        [ascending](const std::unique_ptr<Requisite>& a,
//                   const std::unique_ptr<Requisite>& b) {
//            if (ascending) {
//                return a->getName() < b->getName();
//            } else {
//                return a->getName() > b->getName();
//            }
//        });
//
//    indexesDirty = true;
//}
//
//void CommonMetadataObject::sortForms() {
//    std::sort(forms.begin(), forms.end(),
//        [](const std::unique_ptr<Form>& a, const std::unique_ptr<Form>& b) {
//            // Сначала по типу, затем по имени
//            if (a->getFormType() != b->getFormType()) {
//                return a->getFormType() < b->getFormType();
//            }
//            return a->getName() < b->getName();
//        });
//
//    indexesDirty = true;
//}
//
//// ========== Импорт/Экспорт ==========
//
//bool CommonMetadataObject::importRequisitesFromCSV(const std::string& filename) {
//    std::ifstream file(filename);
//    if (!file.is_open()) {
//        return false;
//    }
//
//    std::string line;
//    // Пропускаем заголовок
//    std::getline(file, line);
//
//    while (std::getline(file, line)) {
//        std::istringstream ss(line);
//        std::vector<std::string> columns;
//        std::string column;
//
//        while (std::getline(ss, column, ',')) {
//            columns.push_back(column);
//        }
//
//        if (columns.size() >= 2) {
//            std::string name = columns[0];
//            std::string type = columns[1];
//            std::string description = (columns.size() > 2) ? columns[2] : "";
//            bool required = (columns.size() > 3) ? (columns[3] == "1" || columns[3] == "true") : false;
//
//            createRequisite(name, type, description, required);
//        }
//    }
//
//    file.close();
//    return true;
//}
//
//bool CommonMetadataObject::exportRequisitesToCSV(const std::string& filename) const {
//    std::ofstream file(filename);
//    if (!file.is_open()) {
//        return false;
//    }
//
//    // Заголовок
//    file << "Name,Type,Description,Required,DefaultValue" << std::endl;
//
//    for (const auto& req : requisites) {
//        file << req->getName() << ","
//             << req->getType() << ","
//             << req->getDescription() << ","
//             << (req->isRequired() ? "1" : "0") << ","
//             << req->getDefaultValue() << std::endl;
//    }
//
//    file.close();
//    return true;
//}
//
//// ========== Индексация ==========
//
//void CommonMetadataObject::rebuildIndexes() {
//    rebuildIndex(requisiteIndex, requisites);
//    rebuildIndex(formIndex, forms);
//    rebuildIndex(commandIndex, commands);
//    rebuildIndex(layoutIndex, layouts);
//    rebuildIndex(tablePartIndex, tableParts);
//    rebuildIndex(columnIndex, columns);
//
//    indexesDirty = false;
//}
//
//void CommonMetadataObject::updateIndexes() const {
//    if (indexesDirty) {
//        // Константный метод, но нам нужно обновить индексы
//        // Используем const_cast для обновления кэша
//        const_cast<CommonMetadataObject*>(this)->rebuildIndexes();
//    }
//}
//
//template<typename T>
//void CommonMetadataObject::rebuildIndex(std::unordered_map<std::string, T*>& index,
//                                       const std::vector<std::unique_ptr<T>>& container) {
//    index.clear();
//    for (const auto& item : container) {
//        index[item->getName()] = item.get();
//    }
//}
//
//// ========== Вспомогательные методы ==========
//
//void CommonMetadataObject::afterRequisiteAdded(Requisite& requisite) {
//    // Виртуальный метод для переопределения в потомках
//    // По умолчанию ничего не делаем
//}
//
//void CommonMetadataObject::beforeRequisiteRemoved(Requisite& requisite) {
//    // Виртуальный метод для переопределения в потомках
//}
//
//void CommonMetadataObject::afterFormAdded(Form& form) {
//    // Виртуальный метод для переопределения в потомках
//}
//
//void CommonMetadataObject::beforeFormRemoved(Form& form) {
//    // Виртуальный метод для переопределения в потомках
//}
//
//// ========== Итератор ==========
//
//CommonMetadataObjectIterator::CommonMetadataObjectIterator(const CommonMetadataObject* obj)
//    : object(obj) {}
//
//CommonMetadataObjectIterator::Iterator CommonMetadataObjectIterator::begin() const {
//    return Iterator(object, 0, 0, 0, 0, 0, 0);
//}
//
//CommonMetadataObjectIterator::Iterator CommonMetadataObjectIterator::end() const {
//    return Iterator(object,
//                   object->getRequisiteCount(),
//                   object->getFormCount(),
//                   object->getCommandCount(),
//                   object->getLayoutCount(),
//                   object->getTablePartCount(),
//                   object->getColumnCount());
//}
//
//// Реализация методов Iterator
//CommonMetadataObjectIterator::Iterator::Iterator(const CommonMetadataObject* obj,
//                                               size_t reqIdx, size_t formIdx,
//                                               size_t cmdIdx, size_t layoutIdx,
//                                               size_t tpIdx, size_t colIdx)
//    : object(obj), requisiteIndex(reqIdx), formIndex(formIdx),
//      commandIndex(cmdIdx), layoutIndex(layoutIdx),
//      tablePartIndex(tpIdx), columnIndex(colIdx) {
//
//    // Пропускаем пустые позиции
//    if (requisiteIndex >= object->getRequisiteCount()) {
//        advance();
//    }
//}
//
//CommonMetadataObjectIterator::Iterator::Item CommonMetadataObjectIterator::Iterator::operator*() const {
//    Item item;
//
//    if (requisiteIndex < object->getRequisiteCount()) {
//        item.type = Item::Type::Requisite;
//        item.property = object->getRequisite(requisiteIndex);
//        item.typeName = "Requisite";
//        item.index = requisiteIndex;
//    } else if (formIndex < object->getFormCount()) {
//        item.type = Item::Type::Form;
//        item.property = object->getForm(formIndex);
//        item.typeName = "Form";
//        item.index = formIndex;
//    } else if (commandIndex < object->getCommandCount()) {
//        item.type = Item::Type::Command;
//        item.property = object->getCommand(commandIndex);
//        item.typeName = "Command";
//        item.index = commandIndex;
//    } else if (layoutIndex < object->getLayoutCount()) {
//        item.type = Item::Type::Layout;
//        item.property = object->getLayout(layoutIndex);
//        item.typeName = "Layout";
//        item.index = layoutIndex;
//    } else if (tablePartIndex < object->getTablePartCount()) {
//        item.type = Item::Type::TablePart;
//        item.property = object->getTablePart(tablePartIndex);
//        item.typeName = "TablePart";
//        item.index = tablePartIndex;
//    } else {
//        item.type = Item::Type::Column;
//        item.property = object->getColumn(columnIndex);
//        item.typeName = "Column";
//        item.index = columnIndex;
//    }
//
//    return item;
//}
//
//CommonMetadataObjectIterator::Iterator& CommonMetadataObjectIterator::Iterator::operator++() {
//    advance();
//    return *this;
//}
//
//bool CommonMetadataObjectIterator::Iterator::operator!=(const Iterator& other) const {
//    return object != other.object ||
//           requisiteIndex != other.requisiteIndex ||
//           formIndex != other.formIndex ||
//           commandIndex != other.commandIndex ||
//           layoutIndex != other.layoutIndex ||
//           tablePartIndex != other.tablePartIndex ||
//           columnIndex != other.columnIndex;
//}
//
//void CommonMetadataObjectIterator::Iterator::advance() {
//    if (requisiteIndex < object->getRequisiteCount()) {
//        requisiteIndex++;
//        if (requisiteIndex >= object->getRequisiteCount()) {
//            // Переходим к следующему типу свойств
//            requisiteIndex = object->getRequisiteCount();
//        }
//    } else if (formIndex < object->getFormCount()) {
//        formIndex++;
//        if (formIndex >= object->getFormCount()) {
//            formIndex = object->getFormCount();
//        }
//    } else if (commandIndex < object->getCommandCount()) {
//        commandIndex++;
//        if (commandIndex >= object->getCommandCount()) {
//            commandIndex = object->getCommandCount();
//        }
//    } else if (layoutIndex < object->getLayoutCount()) {
//        layoutIndex++;
//        if (layoutIndex >= object->getLayoutCount()) {
//            layoutIndex = object->getLayoutCount();
//        }
//    } else if (tablePartIndex < object->getTablePartCount()) {
//        tablePartIndex++;
//        if (tablePartIndex >= object->getTablePartCount()) {
//            tablePartIndex = object->getTablePartCount();
//        }
//    } else if (columnIndex < object->getColumnCount()) {
//        columnIndex++;
//        if (columnIndex >= object->getColumnCount()) {
//            columnIndex = object->getColumnCount();
//        }
//    }
//}
//


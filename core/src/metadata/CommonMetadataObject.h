//---------------------------------------------------------------------------

#ifndef CommonMetadataObjectH
#define CommonMetadataObjectH

#include "MetaObject.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>
#include <functional>


//---------------------------------------------------------------------------


class CommonMetadataObject : public MetaObject {
public:
    // Конструкторы и деструктор
    CommonMetadataObject();
	CommonMetadataObject(const std::string& name, const std::string& synonym = "", const std::string& comment = "");
    virtual ~CommonMetadataObject() = default;

//    // Запрет копирования, разрешение перемещения
//    CommonMetadataObject(const CommonMetadataObject&) = delete;
//    CommonMetadataObject& operator=(const CommonMetadataObject&) = delete;
//    CommonMetadataObject(CommonMetadataObject&&) noexcept = default;
//    CommonMetadataObject& operator=(CommonMetadataObject&&) noexcept = default;
//
//    // === Методы управления реквизитами ===
//
//    /**
//     * @brief Добавить реквизит
//     * @param requisite Уникальный указатель на реквизит
//     * @return Ссылка на добавленный реквизит (для цепочки вызовов)
//     */
//    Requisite& addRequisite(std::unique_ptr<Requisite> requisite);
//
//    /**
//     * @brief Создать и добавить реквизит
//     * @param name Имя реквизита
//     * @param type Тип реквизита
//     * @param description Описание
//     * @param required Обязательность
//     * @return Ссылка на созданный реквизит
//     */
//    Requisite& createRequisite(const std::string& name,
//                              const std::string& type = "String",
//                              const std::string& description = "",
//                              bool required = false);
//
//    /**
//     * @brief Получить реквизит по имени
//     * @param name Имя реквизита
//     * @return Указатель на реквизит или nullptr, если не найден
//     */
//    Requisite* getRequisite(const std::string& name);
//    const Requisite* getRequisite(const std::string& name) const;
//
//    /**
//     * @brief Получить реквизит по индексу
//     */
//    Requisite* getRequisite(size_t index);
//    const Requisite* getRequisite(size_t index) const;
//
//    /**
//     * @brief Проверить наличие реквизита
//     */
//    bool hasRequisite(const std::string& name) const;
//
//    /**
//     * @brief Удалить реквизит
//     * @return true, если реквизит был удален
//     */
//    bool removeRequisite(const std::string& name);
//
//    /**
//     * @brief Получить количество реквизитов
//     */
//    size_t getRequisiteCount() const;
//
//    // === Методы управления формами ===
//
//    Form& addForm(std::unique_ptr<Form> form);
//    Form& createForm(const std::string& name,
//                    const std::string& formType = "Item",
//                    const std::string& fileName = "");
//    Form* getForm(const std::string& name);
//    const Form* getForm(const std::string& name) const;
//    Form* getFormByType(const std::string& formType);
//    bool hasForm(const std::string& name) const;
//    bool removeForm(const std::string& name);
//    size_t getFormCount() const;
//
//    // === Методы управления командами ===
//
//    Command& addCommand(std::unique_ptr<Command> command);
//    Command& createCommand(const std::string& name,
//                          const std::string& handler = "",
//                          const std::string& icon = "");
//    Command* getCommand(const std::string& name);
//    const Command* getCommand(const std::string& name) const;
//    bool hasCommand(const std::string& name) const;
//    bool removeCommand(const std::string& name);
//    size_t getCommandCount() const;
//
//    // === Методы управления макетами ===
//
//    Layout& addLayout(std::unique_ptr<Layout> layout);
//    Layout& createLayout(const std::string& name,
//                        const std::string& layoutType = "Spreadsheet",
//                        const std::string& fileName = "");
//    Layout* getLayout(const std::string& name);
//    const Layout* getLayout(const std::string& name) const;
//    Layout* getLayoutByType(const std::string& layoutType);
//    bool hasLayout(const std::string& name) const;
//    bool removeLayout(const std::string& name);
//    size_t getLayoutCount() const;
//
//    // === Методы управления табличными частями ===
//
//    TablePart& addTablePart(std::unique_ptr<TablePart> tablePart);
//    TablePart& createTablePart(const std::string& name,
//                              const std::string& description = "");
//    TablePart* getTablePart(const std::string& name);
//    const TablePart* getTablePart(const std::string& name) const;
//    bool hasTablePart(const std::string& name) const;
//    bool removeTablePart(const std::string& name);
//    size_t getTablePartCount() const;
//
//    // === Методы управления колонками (для списков) ===
//
//    Column& addColumn(std::unique_ptr<Column> column);
//    Column& createColumn(const std::string& name,
//                        const std::string& type = "String",
//                        int width = 100);
//    Column* getColumn(const std::string& name);
//    const Column* getColumn(const std::string& name) const;
//    bool hasColumn(const std::string& name) const;
//    bool removeColumn(const std::string& name);
//    size_t getColumnCount() const;
//
//    // === Методы сериализации/десериализации ===
//
//    /**
//     * @brief Сериализовать объект в XML
//     * @param parent Родительский XML-узел
//     */
//    virtual void toXML(tinyxml2::XMLElement* parent) const override;
//
//    /**
//     * @brief Десериализовать объект из XML
//     * @param element XML-элемент
//     */
//    virtual bool fromXML(const tinyxml2::XMLElement* element) override;
//
//    /**
//     * @brief Сериализовать объект в JSON
//     */
//    virtual nlohmann::json toJSON() const override;
//
//    /**
//     * @brief Десериализовать объект из JSON
//     */
//    virtual bool fromJSON(const nlohmann::json& json) override;
//
//    // === Методы для работы с UI ===
//
//    /**
//     * @brief Заполнить TreeView
//     * @param parent Родительский узел TreeView
//     * @param treeView Указатель на TreeView
//     */
//    virtual void populateTreeView(TTreeNode* parent, TTreeView* treeView) const override;
//
//    /**
//     * @brief Получить список свойств для отображения в PropertyGrid
//     * @return Список пар "ключ-значение"
//     */
//    virtual std::vector<std::pair<std::string, std::string>> getProperties() const override;
//
//    /**
//     * @brief Получить список реквизитов для отображения в таблице
//     */
//    std::vector<const Requisite*> getRequisitesForDisplay() const;
//
//    /**
//     * @brief Получить список форм для отображения
//     */
//    std::vector<const Form*> getFormsForDisplay() const;
//
//    /**
//     * @brief Получить список команд для отображения
//     */
//    std::vector<const Command*> getCommandsForDisplay() const;
//
//    /**
//     * @brief Получить список макетов для отображения
//     */
//    std::vector<const Layout*> getLayoutsForDisplay() const;
//
//    /**
//     * @brief Получить список табличных частей для отображения
//     */
//    std::vector<const TablePart*> getTablePartsForDisplay() const;
//
//    /**
//     * @brief Получить список колонок для отображения
//     */
//    std::vector<const Column*> getColumnsForDisplay() const;
//
//    // === Методы поиска и фильтрации ===
//
//    /**
//     * @brief Найти реквизит по имени (с поддержкой подстроки)
//     * @param searchText Текст для поиска
//     * @param caseSensitive Учитывать регистр
//     * @return Вектор найденных реквизитов
//     */
//    std::vector<const Requisite*> searchRequisites(const std::string& searchText,
//                                                  bool caseSensitive = false) const;
//
//    /**
//     * @brief Найти форму по имени или типу
//     */
//    std::vector<const Form*> searchForms(const std::string& searchText,
//                                        bool searchInType = true) const;
//
//    /**
//     * @brief Фильтровать реквизиты по типу
//     */
//    std::vector<const Requisite*> filterRequisitesByType(const std::string& type) const;
//
//    /**
//     * @brief Фильтровать обязательные реквизиты
//     */
//    std::vector<const Requisite*> getRequiredRequisites() const;
//
//    // === Валидация ===
//
//    /**
//     * @brief Проверить валидность объекта
//     * @param errors Вектор для записи ошибок
//     * @return true, если объект валиден
//     */
//    virtual bool validate(std::vector<std::string>& errors) const override;
//
//    /**
//     * @brief Проверить уникальность имен реквизитов
//     */
//    bool validateRequisiteNames(std::vector<std::string>& errors) const;
//
//    // === Паттерн Visitor ===
//
//    /**
//     * @brief Принять посетителя
//     * @param visitor Указатель на посетителя
//     */
//    virtual void accept(Visitor* visitor) override;
//
//    // === Методы клонирования ===
//
//    /**
//     * @brief Создать глубокую копию объекта
//     */
//    virtual std::unique_ptr<CommonMetadataObject> clone() const;
//
//    /**
//     * @brief Создать глубокую копию с новым именем
//     */
//    std::unique_ptr<CommonMetadataObject> cloneWithName(const std::string& newName) const;
//
//    // === Геттеры и сеттеры для статистики ===
//
//    size_t getTotalPropertiesCount() const;
//    size_t getTotalElementsCount() const;
//
//    // === Методы для работы с контейнерами ===
//
//    /**
//     * @brief Очистить все свойства
//     */
//    void clearAllProperties();
//
//    /**
//     * @brief Сортировать реквизиты по имени
//     * @param ascending По возрастанию (true) или убыванию (false)
//     */
//    void sortRequisitesByName(bool ascending = true);
//
//    /**
//     * @brief Сортировать формы по типу, затем по имени
//     */
//    void sortForms();
//
//    // === Операции импорта/экспорта ===
//
//    /**
//     * @brief Импортировать реквизиты из CSV
//     */
//    bool importRequisitesFromCSV(const std::string& filename);
//
//    /**
//     * @brief Экспортировать реквизиты в CSV
//     */
//    bool exportRequisitesToCSV(const std::string& filename) const;
//
//    // === Индексация для быстрого поиска ===
//
//    void rebuildIndexes();
//
//protected:
//    // Контейнеры для свойств
//    std::vector<std::unique_ptr<Requisite>> requisites;
//    std::vector<std::unique_ptr<Form>> forms;
//    std::vector<std::unique_ptr<Command>> commands;
//    std::vector<std::unique_ptr<Layout>> layouts;
//    std::vector<std::unique_ptr<TablePart>> tableParts;
//    std::vector<std::unique_ptr<Column>> columns;
//
//    // Индексы для быстрого поиска
//    std::unordered_map<std::string, Requisite*> requisiteIndex;
//    std::unordered_map<std::string, Form*> formIndex;
//    std::unordered_map<std::string, Command*> commandIndex;
//    std::unordered_map<std::string, Layout*> layoutIndex;
//    std::unordered_map<std::string, TablePart*> tablePartIndex;
//    std::unordered_map<std::string, Column*> columnIndex;
//
//    // Флаг изменения (для оптимизации)
//    mutable bool indexesDirty;
//
//    // Вспомогательные методы
//    void updateIndexes() const;
//    void addToIndexes();
//    void removeFromIndexes();
//
//    // Виртуальные методы для переопределения в потомках
//    virtual void afterRequisiteAdded(Requisite& requisite);
//    virtual void beforeRequisiteRemoved(Requisite& requisite);
//    virtual void afterFormAdded(Form& form);
//    virtual void beforeFormRemoved(Form& form);
//
//private:
//    // Приватные вспомогательные методы
//    template<typename T>
//    T* findInVector(const std::vector<std::unique_ptr<T>>& container,
//                   const std::string& name) const;
//
//    template<typename T>
//    bool removeFromVector(std::vector<std::unique_ptr<T>>& container,
//                         const std::string& name);
//
//    template<typename T>
//    void rebuildIndex(std::unordered_map<std::string, T*>& index,
//                     const std::vector<std::unique_ptr<T>>& container);
};


#endif

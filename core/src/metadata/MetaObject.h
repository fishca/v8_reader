//---------------------------------------------------------------------------

#ifndef METAOBJECT_H
#define METAOBJECT_H

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
#include <System.hpp>

// Forward declarations
class Visitor;
class Property;

/**
 * @enum ObjectType
 * @brief Типы объектов метаданных
 */
enum class ObjectType {
	Unknown = 0,
	Constant,                    // Константы
	Directory,                   // Справочники
	Document,                    // Документы
	DocumentJournal,             // Журналы документов
	Enum,                        // Перечисления
	Report,                      // Отчеты
	Processing,                  // Обработки
	CharacteristicPlan,          // Планы видов характеристик
	ChartOfAccounts,             // Планы счетов
	CalculationPlan,             // Планы видов расчета
	InformationRegister,         // Регистры сведений
	AccumulationRegister,        // Регистры накопления
	AccountingRegister,          // Регистры бухгалтерии
	CalculationRegister,         // Регистры расчета
	BusinessProcess,             // Бизнес-процессы
	Task,                        // Задачи
	ExternalDataSource,          // Внешние источники данных
	Custom                       // Пользовательский тип
};

/**
 * @enum ObjectState
 * @brief Состояние объекта
 */
enum class ObjectState {
    New,           // Новый объект
    Loaded,        // Загружен из файла
    Modified,      // Изменен
    Saved,         // Сохранен
    Deleted        // Помечен на удаление
};

/**
 * @class MetaObject
 * @brief Базовый абстрактный класс для всех объектов метаданных
 *
 * Предоставляет общий интерфейс и базовую функциональность для всех
 * объектов системы метаданных. Реализует паттерны:
 * - Composite (через Visitor)
 * - Prototype (через clone)
 * - Observer (через signals/slots)
 * - Strategy (через плагины валидации/сериализации)
 */
class MetaObject : public std::enable_shared_from_this<MetaObject> {
public:
    // ========== Конструкторы и деструктор ==========

	/**
	 * @brief Конструктор по умолчанию
	 */
	MetaObject();

	/**
	 * @brief Конструктор с параметрами
	 * @param name Имя объекта
	 * @param synonym Синоним
	 * @param comment Комментарий
	 */
	MetaObject(const String& name, const String& synonym = "", const String& comment = "");

	/**
	 * @brief Виртуальный деструктор
	 */
	virtual ~MetaObject();

	// Запрещаем копирование, разрешаем перемещение
	MetaObject(const MetaObject&) = delete;
	MetaObject& operator=(const MetaObject&) = delete;
	MetaObject(MetaObject&&) noexcept;
	MetaObject& operator=(MetaObject&&) noexcept;

	// ========== Идентификация и информация о типе ==========

	virtual ObjectType getType() const = 0;
	virtual String getTypeName() const = 0;
	virtual String getFullName() const;
	String getUUID() const;
	virtual bool isSameType(const MetaObject& other) const;

	template<typename T>
	bool isInstanceOf() const;

	template<typename T>
	T* as();

	template<typename T>
	const T* as() const;

	// ========== Основные свойства ==========
	void setName(const String& name);
	String getName() const;
	void setSynonym(const String& synonym);
	String getSynonym() const;
	void setComment(const String& comment);
	String getComment() const;
	// ========== Паттерн Prototype ==========

	/**
	 * @brief Создать глубокую копию объекта
	 * @return Уникальный указатель на копию
	 */
	virtual std::unique_ptr<MetaObject> clone() const = 0;

	/**
	 * @brief Создать глубокую копию с новым именем
	 * @param newName Новое имя для копии
	 * @return Уникальный указатель на копию
	 */
	virtual std::unique_ptr<MetaObject> cloneWithName(const std::string& newName) const;
	// ========== Сравнение объектов ==========

	/**
	 * @brief Сравнить объекты по содержимому
	 * @param other Другой объект
	 * @param differences Вектор для записи различий
	 * @return true, если объекты идентичны
	 */
	virtual bool compare(const MetaObject& other,
						std::vector<std::string>& differences) const;

	/**
	 * @brief Сравнить имена объектов
	 * @param other Другой объект
	 * @return true, если имена совпадают
	 */
	bool compareByName(const MetaObject& other) const;

	/**
	 * @brief Оператор сравнения (по имени)
	 * @param other Другой объект
	 * @return true, если имена совпадают
	 */
	bool operator==(const MetaObject& other) const;

	bool operator!=(const MetaObject& other) const;

	/**
	 * @brief Оператор сравнения для сортировки (по имени)
	 * @param other Другой объект
	 * @return true, если текущий объект меньше другого
	 */
	bool operator<(const MetaObject& other) const;

	// ========== Управление зависимостями ==========

	/**
	 * @brief Добавить зависимость от другого объекта
	 * @param object Объект-зависимость
	 */
	void addDependency(const std::shared_ptr<MetaObject>& object);

	/**
	 * @brief Удалить зависимость
	 * @param object Объект-зависимость
	 */
	void removeDependency(const std::shared_ptr<MetaObject>& object);

	/**
	 * @brief Получить список зависимых объектов
	 * @return Вектор слабых указателей на зависимости
	 */
	std::vector<std::weak_ptr<MetaObject>> getDependencies() const;

	/**
	 * @brief Получить список объектов, которые зависят от текущего
	 * @return Вектор слабых указателей
	 */
	std::vector<std::weak_ptr<MetaObject>> getDependents() const;

	/**
	 * @brief Проверить наличие циклических зависимостей
	 * @param errors Вектор для записи ошибок
	 * @return true, если циклических зависимостей нет
	 */
	bool checkCircularDependencies(std::vector<std::string>& errors) const;

	// ========== Расширяемые свойства ==========

	/**
	 * @brief Установить расширенное свойство
	 * @param key Ключ свойства
	 * @param value Значение (строка, число, bool, etc.)
	 */
	void setExtendedProperty(const std::string& key,
							const std::variant<std::string, int, double, bool>& value);

	/**
	 * @brief Получить расширенное свойство
	 * @param key Ключ свойства
	 * @return optional с значением свойства
	 */
	std::optional<std::variant<std::string, int, double, bool>>
	getExtendedProperty(const std::string& key) const;

	/**
	 * @brief Удалить расширенное свойство
	 * @param key Ключ свойства
	 * @return true, если свойство было удалено
	 */
	bool removeExtendedProperty(const std::string& key);

	/**
	 * @brief Получить все расширенные свойства
	 * @return Словарь расширенных свойств
	 */
	std::map<std::string, std::variant<std::string, int, double, bool>>
	getAllExtendedProperties() const;

	// ========== Сигналы и события ==========

	using PropertyChangedSignal = std::function<void(const std::string& propertyName)>;
	using StateChangedSignal = std::function<void(ObjectState oldState, ObjectState newState)>;

	/**
	 * @brief Подписаться на изменение свойства
	 * @param callback Функция обратного вызова
	 * @return Идентификатор подписки
	 */
	size_t subscribeToPropertyChanged(PropertyChangedSignal callback);

	/**
	 * @brief Подписаться на изменение состояния
	 * @param callback Функция обратного вызова
	 * @return Идентификатор подписки
	 */
	size_t subscribeToStateChanged(StateChangedSignal callback);

	/**
	 * @brief Отписаться от события
	 * @param subscriptionId Идентификатор подписки
	 */
	void unsubscribe(size_t subscriptionId);

	// ========== Статические методы фабрики ==========

	/**
	 * @brief Создать объект по типу
	 * @param type Тип объекта
	 * @param name Имя объекта
	 * @return Уникальный указатель на созданный объект
	 */
	static std::unique_ptr<MetaObject> create(ObjectType type,
											 const std::string& name = "");

	/**
	 * @brief Создать объект по имени типа
	 * @param typeName Имя типа
	 * @param name Имя объекта
	 * @return Уникальный указатель на созданный объект
	 */
	static std::unique_ptr<MetaObject> createByName(const std::string& typeName,
												   const std::string& name = "");

	/**
	 * @brief Получить список всех поддерживаемых типов
	 * @return Вектор пар "тип-имя типа"
	 */
	static std::vector<std::pair<ObjectType, std::string>> getSupportedTypes();

	/**
	 * @brief Зарегистрировать пользовательский тип
	 * @tparam T Тип объекта
	 * @param typeName Имя типа
	 * @return true, если регистрация успешна
	 */
	template<typename T>
	static bool registerType(const std::string& typeName);

protected:
	// Основные свойства
	String name;
	String synonym;
	String comment;
	std::chrono::system_clock::time_point created;
	std::chrono::system_clock::time_point modified;

	// Идентификатор
	String uuid;

	// Состояние
	ObjectState state;

	// Зависимости
	std::vector<std::weak_ptr<MetaObject>> dependencies;
	mutable std::vector<std::weak_ptr<MetaObject>> dependents; // Кэш

	// Расширенные свойства
	std::map<std::string, std::variant<std::string, int, double, bool>> extendedProperties;

	// Сигналы
	struct SignalData {
		size_t nextId = 1;
		std::map<size_t, PropertyChangedSignal> propertyChangedCallbacks;
		std::map<size_t, StateChangedSignal> stateChangedCallbacks;
	};
	std::shared_ptr<SignalData> signalData;

	// Вспомогательные методы
	void notifyPropertyChanged(const std::string& propertyName);
	void notifyStateChanged(ObjectState oldState, ObjectState newState);

	// Генерация UUID
	static String generateUUID();

	// Проверка и нормализация имени
	static String normalizeName(const String& name);

private:
	// Фабрика типов
	using CreatorFunc = std::function<std::unique_ptr<MetaObject>(const std::string&)>;
	static std::map<ObjectType, CreatorFunc>& getTypeRegistry();
	static std::map<std::string, ObjectType>& getNameRegistry();

	// Инициализация объекта
	void initialize();
};

// ========== Вспомогательные шаблоны ==========

/**
 * @brief Вспомогательный класс для регистрации типов
 */
template<typename T>
class MetaObjectRegistrar {
public:
	MetaObjectRegistrar(const std::string& typeName) {
		MetaObject::registerType<T>(typeName);
	}
};

// Макрос для удобной регистрации типов
#define REGISTER_METAOBJECT_TYPE(ClassName, TypeName) \
	static MetaObjectRegistrar<ClassName> ClassName##Registrar(TypeName)

#endif // METAOBJECT_H

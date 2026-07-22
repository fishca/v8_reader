# Подробный план рефакторинга v8_reader_refactoring

> **Цель:** Убрать повторяющийся код (дублирование) из проекта.
> **Для кого этот план:** Для разработчика начального уровня.
> **Как пользоваться:** Выполняйте шаги строго по порядку, не пропускайте проверки.

---

## 1. Что такое дублирование и зачем его убирать

Дублирование кода — это когда один и тот же код встречается в нескольких файлах.
Пример:
```cpp
// В файле Catalogs.cpp:
__fastcall TCatalogs::~TCatalogs() { }

// В файле Documents.cpp:
__fastcall TDocuments::~TDocuments() { }
```
Это дублирование. Если мы захотим изменить логику destructor, придётся менять её в двух местах. А если классов 12 — легко ошибиться.

**Цель рефакторинга:** вынести общий код в одно место, чтобы он использовался всеми классами.

---

## 2. Структура проекта (сокращённо)

```
src/
  BaseMetadataObject.h / .cpp                — базовый класс для всех объектов метаданных
  MetadataObjectWithSections.h / .cpp        — для объектов с реквизитами, табличными частями, формами
  MetadataObjectInformationRegister.h / .cpp — для регистров сведений
  Common.h / Common.cpp                      — общие вспомогательные функции
  ModuleTextStorage.h / .cpp                 — работа с текстом модулей и форм
  Parse_tree.h / .cpp                        — парсинг дерева 1С
  ConfigStorage.cpp                          — чтение файлов конфигурации
  MetaDataManager.h / .cpp                   — главный менеджер метаданных
  Catalogs.cpp / .h                          — справочники
  Documents.cpp / .h                         — документы
  Journals.cpp / .h                          — журналы
  Reports.cpp / .h                           — отчёты
  DataProcessors.cpp / .h                    — обработки
  BusinessProceses.cpp / .h                  — бизнес-процессы
  Enums.cpp / .h                             — перечисления
  ChartOfAccounts.cpp / .h                   — план счетов
  ChartOfCharacteristicTypes.cpp / .h        — типы характеристик
  InformationRegisters.cpp / .h              — регистры сведений
  AccumulationRegisters.cpp / .h             — регистры накопления
  CalculationRegisters.cpp / .h              — регистры расчёта
  AccountingRegisters.cpp / .h               — бухгалтерские регистры
  WebServices.cpp / .h                       — веб-сервисы (пустая обёртка)
  CommonTemplates.cpp / .h                   — общие макеты (пустая обёртка)
  CommonPictures.cpp / .h                    — общие картинки (пустая обёртка)
  CommonCommands.cpp / .h                    — общие команды (пустая обёртка)
  CommonForms.cpp / .h                       — общие формы
  HTTPServices                               — HTTP-сервисы (файл без расширения)
```

---

## 3. Как компилировать и проверять работоспособность

### 3.1. Компиляция

1. Откройте `v8reader.cbproj` в C++Builder.
2. Вверху IDE выберите конфигурацию **Debug** и платформу **Win32**.
3. Нажмите **Build** (Ctrl+F9) или **Run** (F9).
4. Готовый exe будет в `Compile/build/Win32/Debug/v8reader.exe`.

### 3.2. Проверка после изменений

После КАЖДОГО изменения:
1. Соберите проект (Ctrl+F9). Если есть ошибки — исправьте их перед продолжением.
2. Запустите `v8reader.exe`.
3. Откройте любую конфигурацию 1С (файл `.cf` или `.cfu`).
4. Убедитесь, что дерево метаданных отображается корректно.
5. Откройте несколько объектов разных типов (справочник, документ, регистр, модуль, форму).
6. Если всё работает — переходите к следующему шагу.

---

## 4. Правила безопасности

1. **Не удаляйте код, который не понимаете.** Если unsure — спросите.
2. **Сначала добавьте новый код, только потом удаляйте старый.** Никогда не делайте наоборот.
3. **Каждую фазу делайте в отдельной ветке git.**
   ```bash
   git checkout -b refactor-phase1
   ```
4. **После каждой фазы делайте коммит.**
   ```bash
   git add .
   git commit -m "refactor: phase 1 - утилитарные функции"
   ```
5. **Не меняйте логику работы кода.** Мы только перемещаем код, не изменяя его поведение.

---

## Фаза 1. Утилитарные функции (самая безопасная, начинаем с неё)

**Цель:** Убрать 4+ одинаковых копий функций из анонимных `namespace`.
**Объём:** ~80 строк.

---

### Шаг 1.1. Функция `FindFirstGuid`

#### 1.1.1. Добавить объявление в `Common.h`

1. Откройте `src/Common.h`.
2. Найдите место среди других объявлений функций.
3. Добавьте строку:
   ```cpp
   String FindFirstGuid(tree* node);
   ```
4. Сохраните файл.

#### 1.1.2. Добавить реализацию в `Common.cpp`

1. Откройте `src/Common.cpp`.
2. Добавьте в конец файла:

   ```cpp
   String FindFirstGuid(tree* node)
   {
       if (!node) return L"";
       String value = Trim(node->get_value());
       if (ModuleTextStorage::IsGuidLike(value)) return value;
       for (int i = 0; i < node->get_num_subnode(); i++)
       {
           String found = FindFirstGuid(node->get_subnode(i));
           if (!found.IsEmpty()) return found;
       }
       return L"";
   }
   ```

3. Убедитесь, что вверху `Common.cpp` подключены нужные заголовки:
   ```cpp
   #include "Common.h"
   #include "ModuleTextStorage.h"
   #include "Parse_tree.h"
   ```
   Если какого-то нет — добавьте.

#### 1.1.3. Удалить дубликаты из 4 файлов

Ищите в каждом файле блок:
```cpp
namespace {
String FindFirstGuid(tree* node) {
    if (!node) return L"";
    String value = Trim(node->get_value());
    if (ModuleTextStorage::IsGuidLike(value)) return value;
    for (int i = 0; i < node->get_num_subnode(); i++) {
        String found = FindFirstGuid(node->get_subnode(i));
        if (!found.IsEmpty()) return found;
    }
    return L"";
}}
```

**Файл 1: `src/MetadataObjectWithSections.cpp`**
- Найдите `FindFirstGuid` (обычно в начале файла).
- Удалите весь блок `namespace { ... }`.
- Добавьте `#include "Common.h"` если его нет.

**Файл 2: `src/MetadataObjectInformationRegister.cpp`**
- То же самое.

**Файл 3: `src/ChartOfAccounts.cpp`**
- То же самое.

**Файл 4: `src/ChartOfCharacteristicTypes.cpp`**
- То же самое.

#### 1.1.4. Проверка

1. Соберите проект.
2. Запустите `v8reader.exe`.
3. Откройте конфигурацию с планом счетов и типами характеристик.
4. Убедитесь, что нет ошибок компиляции и программа не вылетает.

> **Частая ошибка:** Осталась закрывающая `}` или дублируется функция после удаления namespace. Если компилятор ругается — проверьте, что блок удалён полностью.

---

### Шаг 1.2. Функции `LooksLike1CModuleText` и `FindEmbeddedModuleText`

#### 1.2.1. Добавить объявления в `ModuleTextStorage.h`

1. Откройте `src/ModuleTextStorage.h`.
2. Найдите класс `ModuleTextStorage`.
3. Добавьте в `public` секцию:
   ```cpp
   static bool LooksLike1CModuleText(const String& value);
   static String FindEmbeddedModuleText(tree* node);
   ```
   Если методы уже не статические — уберите `static`.

#### 1.2.2. Проверить реализацию в `ModuleTextStorage.cpp`

1. Откройте `src/ModuleTextStorage.cpp`.
2. Найдите методы `LooksLike1CModuleText` и `FindEmbeddedModuleText`.
3. Убедитесь, что они реализованы там. Если да — объявлений в `.h` достаточно для доступа из других файлов.

#### 1.2.3. Удалить дубликаты из `CommonModules.cpp`

1. Откройте `src/CommonModules.cpp`.
2. Ищите `LooksLike1CModuleText` в анонимном namespace (в начале файла).
3. Удалите весь блок с этой функцией.
4. В местах вызова замените на доступ через класс:
   ```cpp
   // Было (внутри анонимного namespace):
   if (LooksLike1CModuleText(value)) ...

   // Стало (внутри метода класса):
   if (ModuleTextStorage::LooksLike1CModuleText(value)) ...
   ```
   Или если функция стала глобальной (не статическая):
   ```cpp
   if (LooksLike1CModuleText(value)) ...
   ```
5. То же самое для `FindEmbeddedModuleText`.

#### 1.2.4. Удалить дубликаты из `CommonForms.cpp`

Аналогично шагу 1.2.3.

#### 1.2.5. Проверка

1. Сборка.
2. Запуск.
3. Откройте модуль или форму — текст должен загружаться.

---

### Шаг 1.3. Функции `ReadV8FileAsText` и `ReadDiskFileAsText`

#### 1.3.1. Добавить объявления в `ModuleTextStorage.h`

```cpp
String ReadV8FileAsText(v8file* file);
String ReadDiskFileAsText(const String& fileName);
```

#### 1.3.2. Реализовать в `ModuleTextStorage.cpp`

Скопируйте точные тела функций из `CommonModules.cpp` (примерно строки 157–202) в `ModuleTextStorage.cpp`.

#### 1.3.3. Удалить из `CommonModules.cpp`

Удалите дубликаты и замените вызовы.

#### 1.3.4. Проверка

Сборка + запуск + открытие модуля с текстом.

---

## Фаза 2. Тривиальные геттеры `MetaDataManager` (очень просто)

**Цель:** Переместить 18 однотипных методов из `.cpp` в `.h` как inline-функции.

### Шаг 2.1. Найти дубликаты

1. Откройте `src/MetaDataManager.cpp`.
2. Ищите методы, начинающиеся с `get`. Вы увидите блок:

   ```cpp
   std::vector<std::shared_ptr<TSessionParameters>>& MetaDataManager::getSessionParameters()
   {
       return SessionParameters;
   }
   std::vector<std::shared_ptr<TRoles>>& MetaDataManager::getRoles()
   {
       return Roles;
   }
   // ... ещё 16 похожих
   ```

### Шаг 2.2. Перенести в заголовок

1. Откройте `src/MetaDataManager.h`.
2. Найдите класс `MetaDataManager`.
3. В `public:` секции добавьте эти методы как inline:

   ```cpp
   inline std::vector<std::shared_ptr<TSessionParameters>>& getSessionParameters() { return SessionParameters; }
   inline std::vector<std::shared_ptr<TRoles>>& getRoles() { return Roles; }
   inline std::vector<std::shared_ptr<TScheduledJobs>>& getScheduledJobs() { return ScheduledJobs; }
   inline std::vector<std::shared_ptr<TExternalDataSources>>& getExternalDataSources() { return ExternalDataSources; }
   inline std::vector<std::shared_ptr<TFunctionalOptions>>& getFunctionalOptions() { return FunctionalOptions; }
   inline std::vector<std::shared_ptr<TDefinedTypes>>& getDefinedTypes() { return DefinedTypes; }
   inline std::vector<std::shared_ptr<TEventSubscriptions>>& getEventSubscriptions() { return EventSubscriptions; }
   inline std::vector<std::shared_ptr<TSubsystem>>& getSubsystems() { return Subsystems; }
   inline std::vector<std::shared_ptr<TCommonAttributes>>& getCommonAttributes() { return CommonAttributes; }
   inline std::vector<std::shared_ptr<TCommonTables>>& getCommonTables() { return CommonTables; }
   inline std::vector<std::shared_ptr<TFilterCriteria>>& getFilterCriteria() { return FilterCriteria; }
   inline std::vector<std::shared_ptr<TFunctionalOptionsParameters>>& getFunctionalOptionsParameters() { return FunctionalOptionsParameters; }
   inline std::vector<std::shared_ptr<TSettingsStorages>>& getSettingsStorages() { return SettingsStorages; }
   inline std::vector<std::shared_ptr<TCodeLists>>& getCodeLists() { return CodeLists; }
   inline std::vector<std::shared_ptr<TInterfaces>>& getInterfaces() { return Interfaces; }
   ```

   > **Важно:** Скопируйте точные имена методов из вашего `.cpp`! Не удаляйте другие методы.

4. Вернитесь в `MetaDataManager.cpp` и удалите старые определения этих методов.

### Шаг 2.3. Проверка

1. Сборка.
2. Если компилятор ругается на `multiple definition` — вы не удалили старые методы из `.cpp`.
3. Если компилятор ругается на `unknown symbol` — имена не совпадают.

---

## Фаза 3. Пустые обёртки и векторы-члены (самый большой эффект)

**Цель:** Создать шаблон `EmptyMetadataObject` и использовать его для 6 классов-пустышек.

---

### Шаг 3.1. Создать `EmptyMetadataObject.h`

1. В папке `src/` создайте новый файл `EmptyMetadataObject.h`.
2. Вставьте в него:

   ```cpp
   //---------------------------------------------------------------------------
   #ifndef EmptyMetadataObjectH
   #define EmptyMetadataObjectH
   //---------------------------------------------------------------------------

   #include "BaseMetadataObject.h"
   #include <vector>
   #include <memory>
   #include "Requisite.h"
   #include "Comand.h"
   #include "Moxel.h"
   #include "Tabular.h"
   #include "Form.h"

   //---------------------------------------------------------------------------
   template<typename Derived>
   class EmptyMetadataObject : public BaseMetadataObject
   {
   protected:
       std::vector<std::unique_ptr<TRequisite>> attributes;
       std::vector<std::unique_ptr<TComand>> commands;
       std::vector<std::unique_ptr<TMoxel>> layouts;
       std::vector<std::unique_ptr<TTabular>> tabularSections;
       std::vector<std::unique_ptr<TForm1C>> forms;

   public:
       using BaseMetadataObject::BaseMetadataObject;
       ~EmptyMetadataObject() = default;

       std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
       std::vector<std::unique_ptr<TComand>>& getCommands() override { return commands; }
       std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return layouts; }
       std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabularSections; }
       std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

       void __fastcall initializeFromTree() override {}
   };

   //---------------------------------------------------------------------------
   #endif
   ```

3. Добавьте в `src/v8readerPCH1.h`:
   ```cpp
   #include "EmptyMetadataObject.h"
   ```

---

### Шаг 3.2. Мигрировать 6 классов

#### 3.2.1. `TWebServices`

**`src/WebServices.h`**
1. Найдите `class TWebServices : public BaseMetadataObject` и замените на `class TWebServices : public EmptyMetadataObject<TWebServices>`.
2. Удалите 5 векторов (`attributes`, `commands`, `layouts`, `tabularSections`, `forms`).
3. Удалите 5 геттеров.
4. Удалите `void __fastcall initializeFromTree();`.

**`src/WebServices.cpp`**
1. Удалите 3 конструктора.
2. Удалите деструктор.
3. Удалите 5 геттеров.
4. Удалите `initializeFromTree()`.
5. Оставьте только `GetWebServiceName()` и `SetWebServiceName(...)`.

#### 3.2.2. `TCommonTemplates`

Повторите шаги 3.2.1 для `CommonTemplates.h` / `CommonTemplates.cpp`.

#### 3.2.3. `TCommonPictures`

Повторите для `CommonPictures.h` / `CommonPictures.cpp`.

#### 3.2.4. `TCommonCommands`

Повторите для `CommonCommands.h` / `CommonCommands.cpp`.

#### 3.2.5. `TCommonForms`

**`src/CommonForms.h`**
1. Замените базовый класс на `EmptyMetadataObject<TCommonForms>`.
2. Удалите 5 векторов.
3. Удалите 5 геттеров-секций.
4. **Не удаляйте** методы модульного текста (`LoadTextIfNeeded`, `GetText`, `SetText` и т.д.).

**`src/CommonForms.cpp`**
1. Удалите 3 конструктора и деструктор.
2. Удалите 5 геттеров-секций.

#### 3.2.6. `THTTPServices`

**`src/HTTPServices`** (файл без расширения)
1. Найдите `class THTTPServices : public BaseMetadataObject` и замените на `class THTTPServices : public EmptyMetadataObject<THTTPServices>`.
2. Удалите 5 векторов, 5 геттеров, `initializeFromTree()`.
3. Оставьте специфичные методы, если есть.

### Проверка после миграции 6 классов

1. Сборка.
2. Запуск.
3. В дереве найдите: Веб-сервисы, Макеты, Картинки, Команды, Формы, HTTP-сервисы.
4. Они должны отображаться без вылетов.

---

### Шаг 3.3. Очистка векторов из других заголовков

#### Что искать

В каждом заголовке найдите блок:
```cpp
std::vector<std::unique_ptr<TRequisite>> attributes;
std::vector<std::unique_ptr<TComand>> commands;
std::vector<std::unique_ptr<TMoxel>> layouts;
std::vector<std::unique_ptr<TTabular>> tabularSections;
std::vector<std::unique_ptr<TForm1C>> forms;
```

Если он есть внутри класса — удалите его.

#### Список файлов для проверки

- `src/WebSocketClients.h`
- `src/XDTOPackages.h`
- `src/WSReferences.h`
- `src/IntegrationServices.h`
- `src/StyleItems.h`
- `src/Styles.h`
- `src/TConstants.h`
- `src/SettingsStorages.h`
- `src/Roles.h`
- `src/ScheduledJobs.h`
- `src/ExternalDataSources.h`
- `src/FilterCriteria.h`
- `src/FunctionalOptions.h`
- `src/FunctionalOptionsParameters.h`
- `src/DefinedTypes.h`
- `src/EventSubscriptions.h`
- `src/SessionParameters.h`
- `src/Subsystem.h`
- `src/Interfaces.h`
- `src/Bots.h`
- `src/Langs.h`

#### Проверка

1. Сборка.
2. Если компилятор ругается `undeclared identifier` для `attributes`/`commands` — проверьте:
   - Удаляли ли вы векторы из класса, который НЕ наследует `EmptyMetadataObject`.
   - Нет ли прямого доступа к полям (`this->attributes`) вместо вызова `getAttributes()`.
3. Правило доступа: используйте только геттеры.

---

## Фаза 4. CRTP для `MetadataObjectWithSections`

**Цель:** Убрать ~240 строк boilerplate в 12+ файлах.

---

### Шаг 4.1. Создать шаблон `MetadataObjectWithSectionsT`

Откройте `src/MetadataObjectWithSections.h` и добавьте перед `#endif`:

```cpp
template<typename Derived, MetadataTreePaths (*GetPathsFunc)()>
class MetadataObjectWithSectionsT : public MetadataObjectWithSections
{
public:
    using MetadataObjectWithSections::MetadataObjectWithSections;

    void __fastcall initializeFromTree() override
    {
        MetadataObjectWithSections::initializeFromTreeWithPaths(GetPathsFunc());
    }
};
```

Затем создайте аналогичный шаблон для регистров в `src/MetadataObjectInformationRegister.h`:

```cpp
template<typename Derived, InfoRegisterTreePaths (*GetPathsFunc)()>
class MetadataObjectInformationRegisterT : public MetadataObjectInformationRegister
{
public:
    using MetadataObjectInformationRegister::MetadataObjectInformationRegister;

    void __fastcall initializeFromTree() override
    {
        MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetPathsFunc());
    }
};
```

---

### Шаг 4.2. Мигрировать 12+ классов

Для каждого класса из таблицы ниже сделайте 2 операции: измените `.h`, удалите метод из `.cpp`.

| Файл | Что заменить в .h | Что удалить в .cpp |
|------|-------------------|--------------------|
| `Catalogs.cpp/.h` | `MetadataObjectWithSections` -> `MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>` | `initializeFromTree()` |
| `Documents.cpp/.h` | -> `MetadataObjectWithSectionsT<TDocuments, GetDocumentsPaths>` | `initializeFromTree()` |
| `Journals.cpp/.h` | -> `MetadataObjectWithSectionsT<TJournals, GetJournalsPaths>` | `initializeFromTree()` |
| `Reports.cpp/.h` | -> `MetadataObjectWithSectionsT<TReports, GetReportsPaths>` | `initializeFromTree()` |
| `DataProcessors.cpp/.h` | -> `MetadataObjectWithSectionsT<TDataProcessors, GetDataProcessorsPaths>` | `initializeFromTree()` |
| `BusinessProceses.cpp/.h` | -> `MetadataObjectWithSectionsT<TBusinessProceses, GetBusinessProcesesPaths>` | `initializeFromTree()` |
| `ChartOfCalculationTypes.cpp/.h` | -> `MetadataObjectWithSectionsT<TChartOfCalculationTypes, GetChartOfCalculationTypesPaths>` | `initializeFromTree()` |
| `ExchangePlans.cpp/.h` | -> `MetadataObjectWithSectionsT<TExchangePlans, GetExchangePlansPaths>` | `initializeFromTree()` |
| `InformationRegisters.cpp/.h` | `MetadataObjectInformationRegister` -> `MetadataObjectInformationRegisterT<TInformationRegisters, GetInformationRegistersPaths>` | `initializeFromTree()` |
| `AccumulationRegisters.cpp/.h` | -> `MetadataObjectInformationRegisterT<TAccumulationRegisters, GetAccumulationRegistersPaths>` | `initializeFromTree()` |
| `CalculationRegisters.cpp/.h` | -> `MetadataObjectInformationRegisterT<TCalculationRegisters, GetCalculationRegistersPaths>` | `initializeFromTree()` |
| `AccountingRegisters.cpp/.h` | -> `MetadataObjectInformationRegisterT<TAccountingRegisters, GetAccountingRegistersPaths>` | `initializeFromTree()` |

#### Пример для Catalogs.h

**Было:**
```cpp
class TCatalogs : public MetadataObjectWithSections
```

**Стало:**
```cpp
class TCatalogs : public MetadataObjectWithSectionsT<TCatalogs, GetCatalogsPaths>
```

#### Пример для Catalogs.cpp

**Найдите и удалите:**
```cpp
void __fastcall TCatalogs::initializeFromTree()
{
    MetadataObjectWithSections::initializeFromTreeWithPaths(GetCatalogsPaths());
}
```

> **Важно:** Имена функций `GetXxxPaths()` могут отличаться в вашем проекте. Используйте именно те, которые есть в коде.

### Проверка

1. Сборка.
2. Запуск.
3. Откройте конфигурацию 1С.
4. Проверьте все типы метаданных — они должны отображаться.
5. Откройте модуль/форму каждого типа.

---

## Фаза 5. Парсинг ConfigStorage (средний риск)

**Цель:** Убрать 3 копии 90-строчного блока разбора `DynamicallyUpdated`.

---

### Шаг 5.1. Создать `ParseDynamicallyUpdated`

1. Откройте `src/ConfigStorage.cpp`.
2. Найдите первый дублирующийся блок (конструктор `ConfigStorageTableConfig`, строки ~619–709).
3. Скопируйте этот блок в отдельную статическую функцию вверху файла:

   ```cpp
   struct DynUpdateResult
   {
       int ndynup;
       TGUID* dynup;
   };

   static DynUpdateResult ParseDynamicallyUpdated(container_file* file, const String& path, const String& label)
   {
       DynUpdateResult result = {0, nullptr};

       try
       {
           // СКОпИРУЙТЕ СЮДА ВЕСЬ КОД РАЗБОРА из ConfigStorage.cpp:619-709
           // Не меняйте логику, просто перенесите код.
           // В конце установите:
           result.ndynup = ndynup;
           result.dynup = dynup;
       }
       catch (...)
       {
           // обработка ошибок
       }

       return result;
   }
   ```

4. **Не удаляйте старый код сразу!** Сначала убедитесь, что новая функция работает.

### Шаг 5.2. Заменить первый дубликат

1. Вернитесь в конструктор `ConfigStorageTableConfig` (строки ~619–709).
2. Замените весь блок разбора на:
   ```cpp
   DynUpdateResult result = ParseDynamicallyUpdated(file, path, "DynamicallyUpdated");
   ndynup = result.ndynup;
   dynup = result.dynup;
   ```
3. Соберите проект.
4. Убедитесь, что `ndynup` и `dynup` заполняются корректно.

### Шаг 5.3. Заменить второй и третий дубликат

1. Найдите конструктор `ConfigStorageTableConfigSave` (строки ~786–928).
2. Замените блок на вызов `ParseDynamicallyUpdated`.
3. Найдите конструктор `ConfigStorageTableConfigCas` (строки ~1032+).
4. Замените аналогичный блок.

### Проверка

1. Сборка.
2. Запуск с конфигурацией 1С, которая имеет историю изменений.
3. Проверьте, что информация о версиях отображается корректно.

---

## Фаза 6. Циклы парсинга (низкий риск)

**Цель:** Убрать ~150 строк повторяющихся шаблонов `Count-Delta` и перечисления детей.

---

### Шаг 6.1. Добавить утилиты в `Parse_tree.h` / `Parse_tree.cpp`

1. Откройте `src/Parse_tree.h`. Добавьте:
   ```cpp
   std::vector<String> ExtractNamesByCountDelta(tree* root, int baseIdx);
   void ForEachChild(tree* parent, std::function<void(tree*)> callback);
   ```

2. Откройте `src/Parse_tree.cpp`. Добавьте:
   ```cpp
   std::vector<String> ExtractNamesByCountDelta(tree* root, int baseIdx)
   {
       std::vector<String> result;
       if (!root) return result;

       try
       {
           tree* node_att = root;
           int CountAtt = (*node_att)[baseIdx][1]->get_value().ToInt();
           int Delta = CountAtt - 2;
           for (int i = 0; i < CountAtt; i++)
           {
               try
               {
                   tree* node_att_att = root;
                   node_att_att = &(*node_att_att)[baseIdx][7][i + CountAtt - Delta][0][1][1][1][2];
                   result.push_back(node_att_att->get_value());
               }
               catch (...)
               {
                   // Пропускаем элемент
               }
           }
       }
       catch (...)
       {
           // Игнорируем ошибки разбора
       }

       return result;
   }

   void ForEachChild(tree* parent, std::function<void(tree*)> callback)
   {
       if (!parent || !callback) return;
       tree* node = parent->get_next();
       while (node)
       {
           callback(node);
           node = node->get_next();
       }
   }
   ```

### Шаг 6.2. Заменить дубликаты

В файлах:
- `src/Enums.cpp`
- `src/ChartOfAccounts.cpp`
- `src/ChartOfCharacteristicTypes.cpp`
- `src/MetadataObjectInformationRegister.cpp`
- `src/MetadataObjectWithSections.cpp`

Найдите inline-циклы вида:
```cpp
int CountAtt = node_att->get_value().ToInt();
int Delta = CountAtt - 2;
for (int i = 0; i < CountAtt; i++)
{
    try
    {
        // ...
        attributes.push_back(...);
    }
    catch (...) { }
}
```

Замените на:
```cpp
std::vector<String> names = ExtractNamesByCountDelta(root_data.get(), 0);
for (const String& name : names)
{
    attributes.push_back(...);
}
```

### Проверка

1. Сборка.
2. Запуск.
3. Проверьте списки реквизитов, форм, макетов — они должны отображаться без изменений.

---

## Фаза 7. `ModuleTextMixin` (средний риск)

**Цель:** Убрать 12 одинаковых методов из `TCommonModules` и `TCommonForms`.

---

### Шаг 7.1. Создать `ModuleTextMixin.h`

Создайте `src/ModuleTextMixin.h`:

```cpp
//---------------------------------------------------------------------------
#ifndef ModuleTextMixinH
#define ModuleTextMixinH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "ModuleTextStorage.h"

//---------------------------------------------------------------------------
template<typename Derived>
class ModuleTextMixin : public BaseMetadataObject
{
protected:
    ModuleTextDocument textDocument;

    void LoadTextIfNeeded();
    void RefreshEditableTextIfNeeded();

public:
    String __fastcall GetText();
    void __fastcall SetText(const String& value);
    ModuleTextDocument __fastcall GetTextDocument();
    bool __fastcall SaveTextToSource();
    bool __fastcall HasEditableModuleText();
    String __fastcall GetEditableModuleText();
    void __fastcall SetEditableModuleText(const String& value);
    bool __fastcall SaveEditableModuleText(const String& value, String& errorText);
    ModuleTextLocation __fastcall GetEditableModuleLocation();
    bool __fastcall HasEditableModuleText(ModuleTextKind kind);
    String __fastcall GetEditableModuleText(ModuleTextKind kind);
    void __fastcall SetEditableModuleText(ModuleTextKind kind, const String& value);
    bool __fastcall SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText);
    ModuleTextLocation __fastcall GetEditableModuleLocation(ModuleTextKind kind);
};

//---------------------------------------------------------------------------
#endif
```

Создайте `src/ModuleTextMixin.cpp` и скопируйте реализации методов из `CommonModules.cpp` и `CommonForms.cpp` (они идентичны).

### Шаг 7.2. Мигрировать `TCommonModules` и `TCommonForms`

**`src/CommonModules.h`**
1. Найдите `class TCommonModules : public BaseMetadataObject` и замените на `class TCommonModules : public ModuleTextMixin<TCommonModules>` (или оставьте оба базовых класса, если нужна множественность).

**`src/CommonForms.h`**
1. Аналогично для `TCommonForms`.

### Проверка

1. Сборка.
2. Запуск.
3. Проверьте открытие модуля и формы, сохранение текста.

---

## Фаза 7 (альтернатива проще). Если mixin через template не работает

В C++Builder иногда шаблоны дают ошибки. В этом случае используйте композицию:

1. Создайте класс `ModuleTextHelper` (не шаблон) с всеми методами модульного текста.
2. В `TCommonModules` и `TCommonForms` добавьте поле:
   ```cpp
   ModuleTextHelper moduleTextHelper;
   ```
3. Делегируйте вызовы:
   ```cpp
   String __fastcall TCommonModules::GetText()
   {
       return moduleTextHelper.GetText();
   }
   ```
4. Это дольше, но надёжнее для C++Builder.

---

## Сводная таблица

| Фаза | Название | Файлов | Строк | Риск |
|------|----------|--------|-------|------|
| 1 | Утилитарные функции | 4-5 | 80 | Низкий |
| 2 | Inline-геттеры | 2 | 60 | Низкий |
| 3 | EmptyMetadataObject | 31+ | 500 | Средний |
| 4 | CRTP MetadataObjectWithSections | 12+ | 240 | Средний |
| 5 | ParseDynamicallyUpdated | 1 | 180 | Средний |
| 6 | ExtractNamesByCountDelta | 5 | 150 | Низкий |
| 7 | ModuleTextMixin | 2 | 150 | Средний |
| **ИТОГО** | | **~55 файлов** | **~1,435 строк** | |

---

## Критические рекомендации

1. Фазы 1, 2, 6 можно делать немедленно без риска сломать проект.
2. Фаза 3 даёт максимальный эффект (~500 строк), но затрагивает 31+ заголовок. Делать после Фаз 1 и 2.
3. Фаза 4 зависит от Фазы 3.
4. Git: отдельный коммит на каждую фазу. Перед каждой фазой — отдельная ветка.
5. Тестирование: после каждой фазы — полная перекомпиляция + запуск v8reader.exe с тестовой конфигурацией 1С.
6. Опечатка `comands` vs `commands` в `MetadataObjectInformationRegister.h:33-37` не исправляется в рамках этого рефакторинга.

---

## Чек-лист перед завершением фазы

- [ ] Код компилируется без ошибок.
- [ ] v8reader.exe запускается.
- [ ] Конфигурация 1С открывается.
- [ ] Все типы метаданных отображаются в дереве.
- [ ] Модули и формы открываются, текст загружается.
- [ ] Дублирующийся код удалён из старых мест.
- [ ] Новый код добавлен в общие заголовки/файлы.
- [ ] Git-коммит сделан с понятным сообщением.

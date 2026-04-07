# План рефакторинга построения дерева метаданных

## Контекст

В `src/MainUnit.cpp` есть группа процедур, которые вручную строят дерево метаданных в `VirtualStringTreeValue1C`:

- `fillInformationRegisterTree`
- `fillAccumulationRegisterTree`
- `fillAccountingRegisterTree`
- `fillCalculationRegisterTree`
- `fillCatalogsTree`
- `fillChartAccTree`
- `fillJournalTree`
- частично `fillEnumTree`

Наиболее показательная функция — `fillInformationRegisterTree`: она почти полностью повторяет шаблон, уже встречающийся в других `fill*Tree`-процедурах.

## Основные проблемы текущей реализации

### 1. Сильное дублирование кода

Почти каждая процедура содержит один и тот же сценарий:

1. Инициализация корневого узла:
   - `Name`
   - `Age`
   - `ImgIndex`
2. Создание секции:
   - `Измерения`
   - `Ресурсы`
   - `Реквизиты`
   - `Формы`
   - `Команды`
   - `Макеты`
3. Цикл по коллекции и создание дочерних узлов.

Отличается в основном только набор секций, текст заголовка и индекс иконки.

### 2. Слишком низкий уровень абстракции

В каждой функции вручную повторяются вызовы:

- `AddChild(...)`
- `GetNodeData(...)`
- присваивание `Name/Age/ImgIndex`

Из-за этого бизнес-структура дерева теряется в техническом шуме.

### 3. Длинные сигнатуры функций

Например, `fillAccountingRegisterTree` принимает длинный список параметров:

- `name`
- `attributes`
- `dimensions`
- `resources`
- `accountingFlags`
- `dimensionAccountingFlags`
- `forms`
- `comands`
- `moxels`

Такие сигнатуры трудно читать, сопровождать и безопасно вызывать.

### 4. Магические числа

В коде напрямую используются значения иконок и дефолтного возраста:

- `83`
- `82`
- `86`
- `98`
- `79`
- `10`
- `11`
- `118`
- `119`
- `30`

Это ухудшает читаемость и делает код менее самодокументируемым.

### 5. Смешение ответственности

`MainUnit.cpp` одновременно отвечает за:

- знание структуры метаданных;
- знание текстов секций;
- знание иконок;
- непосредственный рендеринг узлов VCL-дерева.

Из-за этого `TMainForm` перегружен логикой, которую лучше вынести в отдельный builder/helper-модуль.

### 6. Неунифицированная работа с коллекциями

В части случаев элементы представлены объектами с полем `name`, в части — строками (`fillEnumTree`).
Это мешает переиспользовать общий код без дополнительного уровня абстракции.

---

## Цель рефакторинга

Сделать построение дерева:

- менее дублирующимся;
- декларативным;
- расширяемым;
- удобным для поддержки;
- меньше связанным с `TMainForm`.

---

## Предлагаемая стратегия рефакторинга

## Этап 1. Вынести базовые helper-функции

### Задача

Спрятать низкоуровневые операции работы с деревом за небольшим API.

### Целевые функции

```cpp
void initNode(VirtualTreeData* data, const String& name, int imageIndex, int age = DefaultTreeNodeAge);

PVirtualNode addChildNode(TVirtualStringTree* tree,
                          PVirtualNode parent,
                          const String& name,
                          int imageIndex,
                          int age = DefaultTreeNodeAge);
```

### Что это даст

- уберёт повторяющиеся присваивания `Name/Age/ImgIndex`;
- упростит чтение кода в `fill*Tree`;
- создаст основу для следующего этапа.

---

## Этап 2. Вынести общую логику добавления секции

### Задача

Унифицировать код вида:

- создать секцию;
- пройти по коллекции;
- для каждого элемента добавить дочерний узел.

### Целевой API

Практический и наиболее удобный вариант — шаблонная функция:

```cpp
template <typename Collection, typename NameGetter>
void addSection(TVirtualStringTree* tree,
                PVirtualNode parent,
                const String& sectionName,
                int sectionImageIndex,
                int itemImageIndex,
                const Collection& items,
                NameGetter getName,
                int age = DefaultTreeNodeAge)
{
    PVirtualNode sectionNode = addChildNode(tree, parent, sectionName, sectionImageIndex, age);

    for (const auto& item : items)
        addChildNode(tree, sectionNode, getName(item), itemImageIndex, age);
}
```

### Что это даст

- устранит основной объём копипасты;
- позволит одинаково обрабатывать коллекции объектов и коллекции строк;
- сделает функции `fill*Tree` декларативными.

---

## Этап 3. Ввести именованные константы для иконок и стандартных значений

### Задача

Заменить магические числа понятными именами.

### Целевой эскиз

```cpp
namespace TreeImage {
    constexpr int Root = 72;
    constexpr int Attributes = 83;
    constexpr int TabularSections = 82;
    constexpr int Forms = 86;
    constexpr int Commands = 98;
    constexpr int Layouts = 79;
    constexpr int Dimensions = 10;
    constexpr int Resources = 11;
    constexpr int AccountingFlags = 118;
    constexpr int SubcontoFlags = 119;
    constexpr int JournalColumns = 6;
}

constexpr int DefaultTreeNodeAge = 30;
```

### Что это даст

- код станет понятнее без поиска по проекту;
- исчезнет зависимость от “неочевидных” чисел;
- будет проще менять отображение централизованно.

---

## Этап 4. Объединить однотипные процедуры в общую реализацию

### Кандидаты на объединение

Практически идентичны:

- `fillInformationRegisterTree`
- `fillAccumulationRegisterTree`
- `fillCalculationRegisterTree`

Близки по структуре:

- `fillAccountingRegisterTree`
- `fillChartAccTree`

### Предлагаемый общий API

#### Вариант через декларативное описание секций

```cpp
struct TreeSectionDescriptor {
    String sectionName;
    int sectionImageIndex;
    int itemImageIndex;
    std::function<void(PVirtualNode sectionNode)> renderItems;
};
```

```cpp
void fillRegisterTreeCommon(TVirtualStringTree* tree,
                            PVirtualNode objectNode,
                            VirtualTreeData* objectData,
                            const String& objectName,
                            int objectImageIndex,
                            const std::vector<TreeSectionDescriptor>& sections);
```

### Базовая реализация

```cpp
void fillRegisterTreeCommon(TVirtualStringTree* tree,
                            PVirtualNode objectNode,
                            VirtualTreeData* objectData,
                            const String& objectName,
                            int objectImageIndex,
                            const std::vector<TreeSectionDescriptor>& sections)
{
    initNode(objectData, objectName, objectImageIndex);

    for (const auto& section : sections)
    {
        PVirtualNode sectionNode = addChildNode(tree,
                                                objectNode,
                                                section.sectionName,
                                                section.sectionImageIndex);
        section.renderItems(sectionNode);
    }
}
```

### Комментарий

Этот вариант удобен там, где секции действительно различаются только набором данных и способом обхода.

Однако на практике в текущем проекте **шаблонный `addSection(...)` будет проще и легче внедряется поэтапно**, чем тотальный переход на `TreeSectionDescriptor` с `std::function`.

Поэтому рекомендуемый путь такой:

1. сначала внедрить `initNode` / `addChildNode` / `addSection`;
2. затем уже решать, нужен ли в проекте полноценный `TreeSectionDescriptor`.

---

## Этап 5. Сократить сигнатуры `fill*Tree`

### Проблема

Сейчас функции принимают слишком много параметров.

### Варианты улучшения

#### Вариант A. Передавать сам объект метаданных

Например:

```cpp
void fillInformationRegisterTree(PVirtualNode childNode,
                                 VirtualTreeData* childData,
                                 int imgIndex,
                                 const TInformationRegisters& reg);
```

#### Вариант B. Ввести адаптер/descriptor данных

```cpp
struct RegisterTreeData {
    String name;
    const std::vector<std::unique_ptr<TRequisite>>& attributes;
    const std::vector<std::unique_ptr<TRequisite>>& dimensions;
    const std::vector<std::unique_ptr<TRequisite>>& resources;
    const std::vector<std::unique_ptr<TForm1C>>& forms;
    const std::vector<std::unique_ptr<TComand>>& commands;
    const std::vector<std::unique_ptr<TMoxel>>& moxels;
};
```

### Что это даст

- меньше ошибок при вызове;
- понятнее зависимость функции от входных данных;
- проще переносить код в отдельный модуль.

---

## Этап 6. Вынести builder в отдельный модуль

### Цель

Разгрузить `MainUnit.cpp` и оставить в `TMainForm` только координацию UI.

### Возможные файлы

- `MetadataTreeBuilder.h`
- `MetadataTreeBuilder.cpp`

### Что вынести

- константы иконок;
- helper-функции построения узлов;
- `addSection(...)`;
- `fillRegisterTreeCommon(...)`;
- при необходимости — адаптеры для разных типов метаданных.

---

## Целевой эскиз API

Ниже приведён рекомендуемый набор интерфейсов, который можно взять как основу.

### Константы

```cpp
namespace TreeImage {
    constexpr int Root = 72;
    constexpr int Attributes = 83;
    constexpr int TabularSections = 82;
    constexpr int Forms = 86;
    constexpr int Commands = 98;
    constexpr int Layouts = 79;
    constexpr int Dimensions = 10;
    constexpr int Resources = 11;
    constexpr int AccountingFlags = 118;
    constexpr int SubcontoFlags = 119;
    constexpr int JournalColumns = 6;
}

constexpr int DefaultTreeNodeAge = 30;
```

### Базовые операции

```cpp
void initNode(VirtualTreeData* data,
              const String& name,
              int imageIndex,
              int age = DefaultTreeNodeAge);

PVirtualNode addChildNode(TVirtualStringTree* tree,
                          PVirtualNode parent,
                          const String& name,
                          int imageIndex,
                          int age = DefaultTreeNodeAge);
```

### Универсальная секция

```cpp
template <typename Collection, typename NameGetter>
void addSection(TVirtualStringTree* tree,
                PVirtualNode parent,
                const String& sectionName,
                int sectionImageIndex,
                int itemImageIndex,
                const Collection& items,
                NameGetter getName,
                int age = DefaultTreeNodeAge);
```

### Декларативный descriptor (опциональный следующий шаг)

```cpp
struct TreeSectionDescriptor {
    String sectionName;
    int sectionImageIndex;
    int itemImageIndex;
    std::function<void(PVirtualNode sectionNode)> renderItems;
};
```

### Общий builder для регистров

```cpp
void fillRegisterTreeCommon(TVirtualStringTree* tree,
                            PVirtualNode objectNode,
                            VirtualTreeData* objectData,
                            const String& objectName,
                            int objectImageIndex,
                            const std::vector<TreeSectionDescriptor>& sections);
```

---

## Пример целевой `fillInformationRegisterTree`

После первого этапа рефакторинга функция должна стать близкой к такой форме:

```cpp
void __fastcall TMainForm::fillInformationRegisterTree(
    PVirtualNode childNode,
    VirtualTreeData* childData,
    int imgIndex,
    String name,
    const std::vector<std::unique_ptr<TRequisite>>& attributes,
    const std::vector<std::unique_ptr<TRequisite>>& dimensions,
    const std::vector<std::unique_ptr<TRequisite>>& resources,
    const std::vector<std::unique_ptr<TForm1C>>& forms,
    const std::vector<std::unique_ptr<TComand>>& commands,
    const std::vector<std::unique_ptr<TMoxel>>& moxels)
{
    initNode(childData, name, imgIndex);

    addSection(VirtualStringTreeValue1C, childNode,
               L"Измерения", TreeImage::Dimensions, TreeImage::Dimensions,
               dimensions,
               [](const auto& item) { return item->name; });

    addSection(VirtualStringTreeValue1C, childNode,
               L"Ресурсы", TreeImage::Resources, TreeImage::Resources,
               resources,
               [](const auto& item) { return item->name; });

    addSection(VirtualStringTreeValue1C, childNode,
               L"Реквизиты", TreeImage::Attributes, TreeImage::Attributes,
               attributes,
               [](const auto& item) { return item->name; });

    addSection(VirtualStringTreeValue1C, childNode,
               L"Формы", TreeImage::Forms, TreeImage::Forms,
               forms,
               [](const auto& item) { return item->name; });

    addSection(VirtualStringTreeValue1C, childNode,
               L"Команды", TreeImage::Commands, TreeImage::Commands,
               commands,
               [](const auto& item) { return item->name; });

    addSection(VirtualStringTreeValue1C, childNode,
               L"Макеты", TreeImage::Layouts, TreeImage::Layouts,
               moxels,
               [](const auto& item) { return item->name; });
}
```

### Что это меняет

- исчезает ручная работа с каждым узлом секции;
- логика функции становится декларацией структуры дерева;
- поддержка и сравнение с другими `fill*Tree` становится проще.

---

## Пример использования `addSection` для строковых коллекций

Это особенно полезно для `fillEnumTree`, где элементы могут быть строками.

```cpp
addSection(VirtualStringTreeValue1C, childNode,
           L"Значения", TreeImage::Attributes, TreeImage::Attributes,
           CurCat->attributes,
           [](const auto& item) { return item; });
```

Таким образом один и тот же helper сможет работать и с:

- `vector<unique_ptr<TRequisite>>`
- `vector<unique_ptr<TForm1C>>`
- `vector<String>`

---

## Какие функции стоит переводить в первую очередь

### Приоритет 1 — почти идентичные

- `fillInformationRegisterTree`
- `fillAccumulationRegisterTree`
- `fillCalculationRegisterTree`

### Приоритет 2 — близкие по форме

- `fillAccountingRegisterTree`
- `fillChartAccTree`
- `fillJournalTree`

### Приоритет 3 — особые случаи

- `fillEnumTree`

---

## Рекомендуемый практический порядок работ

1. Вынести `TreeImage::*` и `DefaultTreeNodeAge`.
2. Реализовать `initNode(...)` и `addChildNode(...)`.
3. Реализовать шаблонный `addSection(...)`.
4. Перевести `fillInformationRegisterTree` как пилотный пример.
5. Перевести `fillAccumulationRegisterTree` и `fillCalculationRegisterTree`.
6. Перевести `fillAccountingRegisterTree` и `fillChartAccTree`.
7. Перевести `fillJournalTree` и `fillEnumTree`.
8. После стабилизации вынести builder в отдельный модуль.

---

## Минимально достаточный результат рефакторинга

Если нужен компромиссный вариант без большого архитектурного изменения, достаточно сделать следующие шаги:

- вынести helper-функции;
- убрать магические числа;
- внедрить `addSection(...)`;
- переписать `fillInformationRegisterTree` и 2–3 аналогичные функции.

Уже это даст:

- заметное снижение копипасты;
- лучшую читаемость;
- основу для дальнейшего поэтапного улучшения.

---

## Итог

Оптимальная стратегия для этого участка кода — **переход от ручного императивного построения дерева к небольшому декларативному API**.

Наиболее практичный первый шаг:

- `initNode(...)`
- `addChildNode(...)`
- `addSection(...)`

Наиболее логичный следующий шаг:

- `fillRegisterTreeCommon(...)`
- `TreeSectionDescriptor`
- вынос builder-логики из `MainUnit.cpp`.

Такой подход уменьшит дублирование, повысит читаемость и позволит развивать дерево метаданных без дальнейшего разрастания `MainUnit.cpp`.
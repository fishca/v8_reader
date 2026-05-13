# План перехода `APIcfBase` на core без VCL

## Цель
Разделить текущий `APIcfBase` на:
1. VCL-центрированные спецификации (совместимость для существующего кода).
2. Отдельные core-спецификации (без зависимостей на VCL/RTL).

Итог: доменная логика контейнера живет в `core`, а `src` оставляет только адаптер совместимости.

## Краткий анализ `APIcfBase.h/.cpp`
Сейчас в одном модуле смешаны:
1. Формат/домен контейнера (`v8header_struct`, `fat_item`, `catalog_header`, FAT-цепочки, block read/write).
2. I/O и синхронизация.
3. VCL API (`String`, `TStream`, `TFileStream`, `TMemoryStream`, `TCriticalSection`, `__fastcall`, `TV8FileStream`).

Это мешает прямому переносу в `core`, потому что core не должен тянуть VCL.

## Предлагаемое разделение спецификаций

### 1) Core-спецификации (без VCL)
Предложенные файлы:
1. `core/include/v8reader_core/container/V8ContainerTypes.h`
2. `core/include/v8reader_core/container/V8ContainerSpec.h`
3. `core/include/v8reader_core/io/IByteStream.h`
4. `core/include/v8reader_core/container/V8ContainerApi.h`
5. `core/src/container/V8ContainerApi.cpp`
6. `core/src/container/V8ContainerBlocks.cpp`

Содержимое:
1. Форматы структур контейнера и константы.
2. Алгоритмы `hex_to_int`, `hex_to_int16`, `int_to_hex`.
3. Алгоритмы `read_block/read_block_16`, `write_block`, FAT allocate/free.
4. Core-классы каталога/файла (без `String`, без `TStream`).

Технические правила:
1. Типы строк: `std::u16string` (или `std::string` с фиксированной кодировкой, выбрать в этапе 0 и не менять дальше).
2. Буферы: `std::vector<std::byte>`.
3. Locking: `std::mutex`.
4. Потоки: интерфейс `IByteStream` вместо `TStream`.

### 2) VCL-центрированные спецификации (адаптер)
Предложенные файлы:
1. `src/APIcfBase_vcl_types.h`
2. `src/APIcfBase_vcl_stream.h`
3. `src/APIcfBase_vcl_adapter.h`
4. `src/APIcfBase_vcl_adapter.cpp`
5. `src/APIcfBase.h` (тонкий фасад/совместимость)

Содержимое:
1. `String`, `ByteArr`, `TStream`-перегрузки, `TV8FileStream : TStream`.
2. Bridge `TStream <-> IByteStream`.
3. Совместимые классы `v8file/v8catalog`, которые делегируют в core API.
4. Сохранение текущих имен методов и сигнатур для минимального влияния на остальной проект.

## Матрица "что куда переносим"
1. `v8header_struct`, `fat_item`, `fat_item8316`, `catalog_header`, `catalog_header8316` -> core types.
2. `hex_to_int`, `hex_to_int16`, `int_to_hex` -> core utils.
3. `read_block`, `read_block_16` -> core blocks + `IByteStream`.
4. `V8timeToFileTime`, `FileTimeToV8time`, `setCurrentTime` -> adapter/time bridge (или отдельный platform shim).
5. `v8file` бизнес-логика (open/read/write/flush/fat updates) -> core implementation.
6. `v8file` VCL-сигнатуры (`String`, `TStream`, `ByteArr`) -> VCL adapter.
7. `v8catalog` бизнес-логика -> core implementation.
8. `TV8FileStream` -> только VCL adapter.

## Пошаговый план перехода с откатом

### Этап 0. Подготовка каркаса
1. Ввести флаг `V8_USE_CORE_CONTAINER`.
2. Добавить пустые core-интерфейсы и VCL bridge-обертки.
3. По умолчанию оставить legacy backend.

Откат:
1. Флаг OFF полностью возвращает исходное поведение.

### Этап 1. Вынос чистых алгоритмов
1. Перенести hex-утилиты в `core`.
2. Вызовы в `APIcfBase.cpp` переключить через адаптерный shim.
3. Добавить минимальные тесты эквивалентности.

Откат:
1. Возврат вызовов на legacy-функции без изменения внешнего API.

### Этап 2. Вынос block I/O
1. Вынести `read_block/read_block_16` и связанный парсинг заголовков блоков в core.
2. Реализовать `TStreamByteStreamAdapter`.
3. Прогнать smoke-сценарии чтения `cf/epf/erf/cfu`.

Откат:
1. Переключение через `#ifndef V8_USE_CORE_CONTAINER`.

### Этап 3. Core-модель файла/каталога
1. Добавить `CoreFileEntry` и `CoreCatalog`.
2. Перенести FAT allocate/free, flush, half-open/half-close.
3. Синхронизацию заменить на `std::mutex`.

Откат:
1. VCL adapter делегирует обратно в legacy backend.

### Этап 4. VCL-совместимый фасад
1. Оставить публичные `v8file`, `v8catalog`, `TV8FileStream`.
2. Сделать их thin-wrapper над core.
3. Проверить, что внешние вызовы из остальных модулей не требуют правок.

Откат:
1. Фасад переключается на legacy backend флагом.

### Этап 5. Переход потребителей на core
1. Новые модули используют core API напрямую.
2. Старые остаются на VCL adapter до полной миграции.

Откат:
1. Любой потребитель можно вернуть на адаптер без пересборки архитектуры.

### Этап 6. Депрекация legacy
1. Пометить VCL-специфичные legacy-точки как deprecated.
2. После стабилизации удалить legacy backend, оставить core + adapter.

Откат:
1. До удаления legacy всегда доступен быстрый rollback флагом.

## Контрольные критерии
1. Сборка `v8reader.groupproj` (Debug/Win32) без новых ошибок.
2. Одинаковый бинарный результат для операций чтения/записи на эталонных контейнерах.
3. Нет деградации по open/list/extract/flush на больших файлах.
4. В core нет прямых include VCL (`System.Classes.hpp` и т.п.).

## Практический порядок PR
1. PR-1: этапы 0-1 (каркас + утилиты).
2. PR-2: этап 2 (block I/O + bridge).
3. PR-3: этап 3 (core-модель).
4. PR-4: этап 4 (VCL фасад).
5. PR-5+: этапы 5-6 по подсистемам.

## Детальный план замены VCL API на стандартный C++ в `APIcfBase.h/.cpp`

### Цель
Убрать прямую зависимость `APIcfBase` от:
1. `String`
2. `TStream`
3. `TFileStream`
4. `TMemoryStream`
5. `TCriticalSection`
6. `__fastcall`
7. `TV8FileStream : TStream`

И заменить на эквивалентные стандартные C++ объекты с сохранением поведения.

### Карта замен VCL -> C++
1. `String` -> `std::u16string` внутри core и адаптеры конвертации к `std::string` (UTF-8) на границах.
2. `ByteArr` (`DynamicArray<Byte>`) -> `std::vector<std::uint8_t>`.
3. `TStream` -> интерфейс `IByteStream` (`Read/Write/Seek/Size/SetSize`).
4. `TFileStream` -> `StdFileStream` (обертка над `std::fstream`/Win32 file handle).
5. `TMemoryStream` -> `MemoryByteStream` (`std::vector<std::uint8_t>` + позиция).
6. `TCriticalSection` -> `std::mutex` + `std::lock_guard<std::mutex>`.
7. `__fastcall` -> убрать, оставить стандартный calling convention C++.
8. `TV8FileStream` -> `V8FileByteStream` (реализация `IByteStream`, работающая поверх `v8file`/`CoreFileEntry`).

### Изменения в `APIcfBase.h`
1. Вынести VCL include (`System.Classes.hpp`) из core-варианта заголовка.
2. Добавить типы:
   1. `using V8String = std::u16string;`
   2. `using ByteVector = std::vector<std::uint8_t>;`
3. Заменить поля классов:
   1. `String name` -> `V8String name`.
   2. `TCriticalSection* Lock` -> `mutable std::mutex lock_`.
   3. `TStream* data` -> `std::unique_ptr<IByteStream> data`.
4. Пересобрать сигнатуры методов:
   1. `Read/Write` перегрузки на `ByteVector` и `void*`.
   2. `SaveToFile`/`SaveToStream` на `std::filesystem::path` и `IByteStream&`.
5. Убрать `TV8FileStream : TStream` из core-ветки и оставить только адаптерный класс.

### Изменения в `APIcfBase.cpp`
1. Переписать `read_block/read_block_16` на `IByteStream&`.
2. Переписать создание временных потоков:
   1. `new TMemoryStream` -> `std::make_unique<MemoryByteStream>()`.
3. Переписать файловые операции:
   1. `TFileStream` -> `StdFileStream`.
   2. `SetFileTime` вынести в platform-shim (`FileTimestampOps`).
4. Все `Lock->Acquire()/Release()` заменить на RAII (`std::lock_guard`).
5. Удалить зависимость от fastcall в объявлениях/определениях.
6. Логику каталога/файла оставить прежней, менять только типы и I/O слой.

### Этапы внедрения
1. Этап A: ввести `IByteStream`, `MemoryByteStream`, `StdFileStream` без изменения бизнес-логики.
2. Этап B: переключить утилиты блоков и чтение/запись файла на новые потоки.
3. Этап C: заменить синхронизацию на `std::mutex` и RAII-lock.
4. Этап D: заменить `String`/`ByteArr` на `std::u16string`/`std::vector<uint8_t>` внутри реализации.
5. Этап E: удалить `__fastcall`, отделить VCL адаптер в отдельные файлы.
6. Этап F: прогнать совместимость и включить core-реализацию флагом по умолчанию.

### Совместимость и откат
1. На каждом этапе держать флаг `V8_USE_CORE_CONTAINER`.
2. Для внешнего кода оставить совместимый VCL фасад (`APIcfBase_vcl_adapter.*`).
3. Откат этапа выполняется переключением флага и возвратом только затронутого слоя, без массового revert.

### Минимальные проверки после каждого этапа
1. Сборка `Debug|Win32` без новых ошибок.
2. Открытие/чтение/запись тестовых `cf/epf/erf/cfu`.
3. Сравнение результатов извлечения файлов до/после (побайтно).
4. Smoke-тест `CreateCatalog/CreateFile/DeleteFile/Flush/HalfClose/HalfOpen`.

---

# P4 — точный план добора миграции в core (без VCL), пофайлово

## Принцип P4
1. Не ломаем UI: `src/MainUnit*`, `src/SynHighlighter1C*`, `src/v8reader.cpp` остаются в `src`.
2. Переводим только то, что может жить в `core` как доменная/утилитная логика.
3. После каждой волны: `cmd /c Compile\build.bat` + smoke на `Compile/1Cv8_ssl.cf`.
4. Если волна не проходит — откатить только текущую волну.

## Волна P4.1 — Очистка артефактов и инвентаризация
1. Удалить legacy-артефакт `src/HTTPServices` (без расширения) — не участвует в сборке.
2. Зафиксировать список оставшихся VCL-зависимостей в `core` (файлы ниже).
3. Checkpoint: полная сборка.

## Волна P4.2 — UI-утечки из core обратно в src (самое безопасное)
Цель: убрать из `core` все, что зависит от визуального дерева.
1. Перенести из `core/src/metadata` обратно в `src`:
   1. `MetadataTreeBuilder.h/.cpp`
   2. `VirtualTreeData.h`
2. Обновить include-пути:
   1. `src/MainUnit.h/.cpp`
   2. `src/v8reader.cbproj` (если нужно, только пути)
3. Удалить из `core/include/v8reader_core/V8MetadataLegacy.h` включения UI-зависимых заголовков.
4. Checkpoint: сборка + открытие дерева метаданных.

## Волна P4.3 — Parse_tree: отделение core и VCL-адаптера
Цель: убрать `<vcl.h>` из парсера.
1. Ввести core-версию:
   1. `core/src/metadata/ParseTreeCore.h/.cpp` (`std::u16string`, `IByteStream`).
2. Оставить совместимый VCL-bridge:
   1. `src/Parse_tree_vcl_adapter.h/.cpp` (обертки `String`/`TStream` -> core).
3. Переключить потребителей:
   1. `core/src/metadata/*` на core-API.
   2. `src/Class_1CD.*`, `src/Common.*` через bridge.
4. После стабилизации удалить VCL include из текущего `core/src/metadata/Parse_tree.h`.
5. Checkpoint: сборка + разбор `Compile/1Cv8_ssl.cf`.

## Волна P4.4 — ModuleTextStorage/CommonModules: вынос RTL I/O
Цель: убрать `System.IOUtils`, `TEncoding`, `TBytes` из core-реализации.
1. Добавить core-утилиты:
   1. `core/src/io/TextDecodeCore.h/.cpp` (UTF-8/UTF-16/BOM)
   2. `core/src/io/FileSystemCore.h/.cpp` (`std::filesystem` + std streams)
2. Переписать:
   1. `core/src/metadata/ModuleTextStorage.h/.cpp`
   2. `core/src/metadata/CommonModules.cpp`
3. VCL-границы оставить только в `src/VclByteStreamAdapter.h` и точечных wrapper-функциях.
4. Checkpoint: сборка + открытие/сохранение модулей из SourceCF.

## Волна P4.5 — APIcfBase: финальный отказ от VCL-сигнатур в core
Цель: в core оставить только `IByteStream`, `std::u16string`, `std::vector<uint8_t>`.
1. В `core/src/APIcfBase.h/.cpp`:
   1. убрать `TStream` из публичной core-поверхности,
   2. убрать `__fastcall` в реализациях,
   3. оставить только переходные bridge-методы под `#ifdef` (если требуется совместимость).
2. Перенести VCL-совместимые методы в отдельный слой:
   1. `src/APIcfBase_vcl_adapter.h/.cpp` (или уже существующий bridge).
3. Checkpoint: сборка + smoke CRUD контейнера (`Open/Read/Write/Flush/HalfOpen/HalfClose`).

## Волна P4.6 — Core-модели (MetaObject/Property/Tabular) добивка
Цель: убрать условные VCL include из "почти-core" файлов.
1. `core/src/metadata/MetaObject.h`: удалить `System.*` include из ветки `__BORLANDC__`, заменить STL-типами/адаптерами.
2. `core/src/metadata/Property.h`: убрать `Vcl.Graphics.hpp`, оставить платформенно-нейтральный тип (например enum/ARGB).
3. `core/src/metadata/Tabular.h`: заменить `<vcl.h>` на минимальный набор core include.
4. Checkpoint: сборка + метаданные (табличные части/свойства).

## Волна P4.7 — Финальная полировка и критерий done
1. В `core/src` и `core/include` не должно остаться:
   1. `#include <vcl.h>`
   2. `#include <Vcl.*>`
   3. `#include <System.*>` (кроме явно оставленного bridge-слоя, если он физически в `src`)
2. Обновить `List_no_vcl.md` и зафиксировать итоговый статус.
3. Checkpoint: сборка + регрессионный прогон `-PARSE`/`-BUILD` на `Compile/1Cv8_ssl.cf`.

## Порядок выполнения PR (рекомендуемый)
1. PR-P4-1: P4.2 (UI-утечки)
2. PR-P4-2: P4.3 (Parse_tree core + adapter)
3. PR-P4-3: P4.4 (ModuleTextStorage/CommonModules)
4. PR-P4-4: P4.5 (APIcfBase final split)
5. PR-P4-5: P4.6 + P4.7 (добивка и финальный аудит)

---

# Статус P4 (2026-05-13)

## Сделано
1. Удален неиспользуемый legacy-файл `src/HTTPServices` (без расширения).
2. UI-зависимые helper-файлы `MetadataTreeBuilder.*`/`VirtualTreeData.h` физически перенесены из `core/src/metadata` в `src`.
3. Из `MetaDataManager` удалена UI-функция `populateTreeView(...)` и связанные include.
4. В `core/include/v8reader_core/V8MetadataLegacy.h` убрана лишняя UI-экспозиция.
5. В `Parse_tree` добавлены переходные UTF-16 обертки (`parse_1Ctext_u16`, `outtext_u16`, поиск по GUID на `std::u16string_view`).
6. В `core/src/metadata` убрана прямая зависимость от `src/Class_1CD.h`:
   1. декларация `get_treeFromV8file(v8file*)` перенесена в `Parse_tree.h`,
   2. удалены лишние include `Class_1CD.h` из core-заголовков/реализаций.
7. В `core/src/metadata/ModuleTextStorage.cpp` операции путей/каталогов/перемещения файлов переведены с `System.IOUtils` на `std::filesystem`.
8. В `core/src/metadata/CommonModules.cpp` операции путей/каталогов переведены с `System.IOUtils` на `std::filesystem`.
9. Из `core/src/metadata/CommonModules.cpp` удален неиспользуемый legacy-блок локальных helper-функций, оставлена только актуальная обертка над `ModuleTextStorage`.
10. Код декодирования/кодирования текстов модулей вынесен из `ModuleTextStorage.cpp` в отдельный utility:
   1. `core/src/metadata/ModuleTextEncodingUtils.h`
11. Уменьшен прямой VCL-след в metadata-заголовках:
   1. `Parse_tree.h` переключен на include `../APIcfBase.h` вместо `System.*`,
   2. `ModuleTextStorage.h` убраны прямые include `System.*`,
   3. `Tabular.h` убран `#include <System.hpp>`.
12. Начато физическое разделение P4.3 для parser API:
   1. добавлен core-friendly заголовок `core/include/v8reader_core/ParseTreeCore.h`,
   2. реализации `parse_1Ctext_u16/outtext_u16/find_*_u16` вынесены из `Parse_tree.cpp` в `core/src/metadata/ParseTreeCore.cpp`,
   3. `ParseTreeCore.cpp` подключен в `src/v8reader.cbproj`.
13. В `ModuleTextEncodingUtils.h` убран прямой include `System.Classes.hpp`, переключено на `../APIcfBase.h`.
14. Начат переход `APIcfBase` к core-ориентированному stream API без слома совместимости:
   1. в `v8file` добавлен `SaveToByteStream(IByteStream&)`,
   2. `SaveToFile(...)` переведен на `StdFileStream + SaveToByteStream(...)`,
   3. `SaveToStream(TStream*)` переведен на `TStreamByteStreamAdapter + SaveToByteStream(...)`,
   4. добавлены перегрузки `Write(IByteStream&, int, int)` и `Write(IByteStream&)`,
   5. существующие `Write(TStream*, ...)` теперь работают через адаптер к `IByteStream`.
15. Добавлена C++-friendly перегрузка в `v8file`:
   1. `SaveToFile(const std::filesystem::path&)`,
   2. существующий `SaveToFile(const String&)` делегирует на path-вариант.
16. В `MetaObject.h` удален неиспользуемый `#include <System.SysUtils.hpp>` (сборка/поведение без изменений).
17. Расширена C++-friendly поверхность `v8catalog`:
   1. добавлены path-конструкторы `v8catalog(const std::filesystem::path&)` и `v8catalog(const std::filesystem::path&, bool)`,
   2. `String`-конструкторы делегируют на path-варианты,
   3. добавлены `SaveToDir(const std::filesystem::path&)` и `HalfOpen(const std::filesystem::path&)`,
   4. `String`-варианты `SaveToDir/HalfOpen` делегируют на path-варианты.
18. Расширен `v8file` для core-stream пути записи с закрытием:
   1. добавлен `WriteAndClose(IByteStream&, int)`,
   2. реализован переходный мост через временный `TMemoryStream` с последующим вызовом существующей VCL-ветки.
19. В `src` добавлен явный adapter-слой для перехода границ:
   1. `src/APIcfBase_vcl_adapter.h/.cpp`,
   2. `src/Parse_tree_vcl_adapter.h/.cpp`,
   3. src-файлы переключены с прямых include `../core/src/...` на adapter-заголовки.
20. Заголовки метамодели очищены от прямых VCL include:
   1. `MetaObject.h` использует forward declarations + `System.UITypes` (без `Vcl.*`),
   2. `Property.h` использует forward declarations + `System.UITypes` (без `Vcl.*`).
21. UI-реализации в `MetaObject.cpp` и `Property.cpp` переведены во временные нейтральные stub-методы
   (без `cl*`, `TEdit`, `TStringList` зависимостей), чтобы отделить доменную core-логику от VCL UI.

## Проверки после изменений
1. Полная сборка `Compile\\build.bat` — успешно.
2. Smoke: `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Осталось в контуре P4
1. Завершить P4.3: выделить полноценный `ParseTreeCore` + VCL-адаптер, чтобы убрать `System.*` из core-публичной части парсера.
2. Продолжить P4.4: вынести декодирование текста (`TEncoding/TBytes`) в core-утилиты без VCL.
3. P4.5: финальный split `APIcfBase` (core API без `TStream`/VCL, совместимость через adapter в `src`).
4. P4.6/P4.7: убрать `Vcl.Graphics.hpp` и остаточные `System.*` include из `core` (кроме строго переходного bridge-слоя).

## Текущий остаток direct VCL/System include в core
1. `core/src/APIcfBase.h`
2. `core/src/metadata/MetaObject.h`
3. `core/src/metadata/Property.h`

Примечание:
1. прямых `Vcl.*` include в `core/src` и `core/include` больше нет;
2. остаются `System.*` include в переходных местах, пока `String`/`TStream` окончательно не вынесены в `src`-adapter.

## Статус P5 (2026-05-13, старт выполнения)
1. Выполнен checkpoint перед правками:
   1. добавлен `migration_checkpoint_p5.txt` с фиксацией `HEAD` и шагов.
2. `APIcfBase.cpp`:
   1. удален локальный `StdFileTStream` (исчезли последние `__fastcall` в `core`);
   2. открытия файлов переведены на helper `OpenVclFileStream(...)` + `TFileStream`.
3. `MetaObject` переведен на STL-строки:
   1. `core/src/metadata/MetaObject.h/.cpp`: `String` -> `std::string`;
   2. удален include `#include <System.hpp>` из `MetaObject.h`.
4. Для согласования цепочки наследования обновлен:
   1. `core/src/metadata/CommonMetadataObject.h/.cpp` (`String` ctor -> `std::string` ctor).
5. Проверки после изменений:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.
6. Текущий остаток `System.*` include в `core`:
   1. только `core/src/APIcfBase.h: #include <System.Classes.hpp>`.

7. Локальный шаг по `APIcfBase.h` выполнен:
   1. прямой include `#include <System.Classes.hpp>` убран из `core/src/APIcfBase.h`;
   2. добавлен переходный shim `src/SystemClassesShim.h`, который инкапсулирует VCL include на стороне `src`.

---

# Финальный дожим P4 (2026-05-13, доп.фикс)

## Подтверждено по коду
1. В `core` больше нет UI/VCL-типов (`TColor`, `TStringList`, `TVirtualStringTree`, `Vcl.Graphics`, `System.UITypes`).
2. Прямые include `System.*` в `core` остались только в двух файлах:
   1. `core/src/APIcfBase.h` (`System.Classes.hpp`) — переходный слой из-за `String/TStream`.
   2. `core/src/metadata/MetaObject.h` (`System.hpp`) — из-за поля/сигнатур на `String`.
3. `__fastcall` в `core` остался только в `core/src/APIcfBase.cpp` внутри `StdFileTStream : TStream` (override VCL-сигнатур).

## Проверка после финального дожима
1. `Compile\\build.bat` — успешно.
2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf Compile\\_probe_ssl root version` — `ok`.

## Что осталось (и почему это уже не «простой перенос»)
1. Полное удаление `System.Classes.hpp` из `APIcfBase` потребует финального вывода `String/TStream` из публичной поверхности `v8file/v8catalog` в отдельный `src`-facade.
2. Полное удаление `System.hpp` из `MetaObject` потребует перевода всей ветки `MetaObject/MetaDataManager` на STL-строки (`std::u16string/std::string`) с адаптерами на границе UI.

## Статус P5 (2026-05-13, шаг продолжения)
1. `APIcfBase.h`:
   1. прямой `#include <System.Classes.hpp>` заменен на adapter-shim `#include "../../src/SystemClassesShim.h"`;
   2. сам RTL include теперь изолирован в `src/SystemClassesShim.h`.
2. `APIcfBase.cpp`:
   1. удален `StdFileTStream` и helper-ветки `ToSeekOrigin(...)`;
   2. открытие файлов переведено на `OpenVclFileStream(...)` (`TFileStream`), без изменения поведения.
3. Контрольный аудит:
   1. `rg "#include <System\\." core/src core/include` — пусто;
   2. `rg "__fastcall" core/src core/include` — пусто.
4. Проверки:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Статус P5 (2026-05-13, продолжение)
1. В `core/src/metadata` убран последний прямой вызов `GetFileName()`:
   1. `ModuleTextStorage.cpp` использует `GetFileName16()` + bridge-конвертер.
2. Убрана зависимость `core` от пути `src` для shim:
   1. создан `core/src/SystemClassesShim.h`;
   2. `core/src/APIcfBase.h` переключен на `#include "SystemClassesShim.h"`;
   3. удален временный `src/SystemClassesShim.h`.
3. Проверки:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Статус P5 (2026-05-13, закрепление *16 как основной API в v8catalog)
1. В `APIcfBase.cpp` методы `v8catalog` перестроены на модель:
   1. `*16`-методы (`GetFile16/createFile16/CreateCatalog16/DeleteFile16`) содержат основную реализацию;
   2. `String`-методы стали thin-wrapper через `StringToUtf16(...)`.
2. Это снижает зависимость core-логики от VCL-строк в точках вызова и упрощает последующий вынос `String`-фасада в adapter-слой.
3. Проверки:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Статус P5 (2026-05-13, пакетный перевод core/metadata на GetFile16)
1. В `APIcfBase` добавлены публичные конвертеры:
   1. `V8Utf16FromString(const String&)`
   2. `V8StringFromUtf16(const Utf16String&)`
2. В `core/metadata` переведены все активные вызовы `GetFile(...)` на `GetFile16(...)`:
   1. `BaseMetadataObject.cpp`
   2. `ChartOfAccounts.cpp`
   3. `ChartOfCharacteristicTypes.cpp`
   4. `Enums.cpp`
   5. `ExternalDataSources.cpp`
   6. `FilterCriteria.cpp`
   7. `MetaDataManager.cpp`
   8. `MetadataObjectWithSections.cpp`
   9. `ModuleTextStorage.cpp`
   10. `Numerators.cpp`
   11. `Sequences.cpp`
3. Результат контроля:
   1. активных `GetFile(...)` вызовов в `core/src/metadata` не осталось (кроме закомментированной строки).
4. Проверки:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Статус P5 (2026-05-13, шаг UTF-16 API для APIcfBase)
1. В `v8file` добавлен core-friendly метод:
   1. `GetFullName16()`.
2. В `v8catalog` добавлены core-friendly UTF-16 методы:
   1. `GetFile16(const Utf16String&)`
   2. `createFile16(const Utf16String&, bool)`
   3. `CreateCatalog16(const Utf16String&, bool)`
   4. `DeleteFile16(const Utf16String&)`
3. Первые потребители в `core/metadata` переключены на UTF-16 вызовы:
   1. `MetaDataManager.cpp`: `version/metadata/root` через `GetFile16(u"...")`
   2. `ModuleTextStorage.cpp`: `root` через `GetFile16(u"...")`
4. Проверки:
   1. `Compile\\build.bat` — успешно;
   2. `Compile\\v8unpack.exe -PARSE Compile\\1Cv8_ssl.cf ... root version` — `ok`.

## Статус P5 (2026-05-13, реализованы пункты финальной зачистки)
1. Из `core/src` удалены Borland-специфичные директивы компилятора:
   1. `#pragma hdrstop`
   2. `#pragma package(smart_init)`
2. `core/src/metadata/MDObject.*` переведен с `TObjectList` на STL-контейнер:
   1. `TMDObjectManager` хранит объекты в `std::vector<std::unique_ptr<TMDObject>>`;
   2. `newMetaData()` теперь возвращает raw pointer на элемент, владельцем остается менеджер.
3. `core/src/metadata/SmartPointers.h`:
   1. удален deleter, жестко привязанный к `TObject`;
   2. введен generic `DefaultObjectDeleter<T>`;
   3. `VclUniquePtr` оставлен как совместимый alias-нейм, но основан на generic deleter.
4. Важное ограничение по ABI на текущем этапе:
   1. попытка убрать `: public TObject` из `BaseMetadataObject`/части metadata-классов ломает `src/MetadataTreeBuilder` (он хранит ссылки как `System::TObject*`);
   2. поэтому наследование `TObject` возвращено до отдельного шага с адаптером TreeData.
5. Проверка после изменений:
   1. `Compile\\build.bat` — успешно (без новых ошибок);
   2. функциональные предупреждения компилятора остались прежними, миграционных регрессий не добавлено.

## Статус P5 (2026-05-13, продолжение: снят блокер TObject между core и src)
1. Добавлен нейтральный базовый тип core-объектов метаданных:
   1. `core/src/metadata/MetadataEntity.h` (`virtual ~MetadataEntity() = default`).
2. Классы core переведены с `TObject` на `MetadataEntity`:
   1. `BaseMetadataObject`
   2. `TEnums`
   3. `TNumerators`
   4. `TSequences`
   5. `TMDO`
   6. `TMDObject`
3. `src`-слой переведен на хранение/передачу core-объектов без `System::TObject*`:
   1. `VirtualTreeData::MetadataObject`: `TObject*` -> `MetadataEntity*`;
   2. `MainUnit.h/.cpp`: `MetadataVector<TObject>` -> `MetadataVector<MetadataEntity>`;
   3. `MetadataTreeBuilder.h/.cpp`: аналогично для подсистем и вспомогательных функций.
4. Результат:
   1. зависимость `core` от `TObject` снята полностью;
   2. сборка проекта проходит без новых ошибок.
5. Проверка:
   1. `Compile\\build.bat` — успешно.

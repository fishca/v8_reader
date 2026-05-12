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

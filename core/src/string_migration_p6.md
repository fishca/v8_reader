# P6 — Уход от `String` в core

## Текущее состояние
- Прямой VCL уже убран из `core/src`.
- Зависимость от RTL через `String` остаётся в 129 файлах.
- После последнего шага сборка проходит (`Compile/build.bat`).

## Стратегия
1. Сначала убрать `String` с границ API (публичные хедеры core).
2. Затем переводить доменные модули на `std::u16string` блоками.
3. VCL-совместимость оставлять только в `src` адаптерах.
4. После каждого блока — полная сборка.

## Порядок миграции (безболезненный)
1. `core/src/APIcfBase.h/.cpp`
- Перевод публичных сигнатур `String` -> `Utf16String` (или `std::u16string`).
- Сохранить временные обертки только в `src/APIcfBase_vcl_adapter.h`.

2. `core/src/metadata/ModuleTextStorage.h/.cpp`
- Поля/параметры `String` -> `std::u16string`.
- Внутренние утилиты пути/поиска тоже на `std::u16string` + конвертеры на границах файловой системы.

3. `core/src/metadata/Parse_tree.h/.cpp` + `ParseTreeCore.cpp`
- Перевести дерево и парсер на `std::u16string` как основной тип.
- Удалить зависимость на `TStringBuilder` в пользу std-контейнеров.

4. База метамодели
- `BaseMetadataObject.*`
- `MetadataObjectWithSections.*`
- `MetaObject.*`, `Property.*`
- Последовательно заменить `String` в полях/геттерах/сеттерах.

5. Остальные metadata-классы волнами
- По 10-15 файлов за итерацию с компиляцией.

## Критерии завершения
- `rg -n "\bString\b" core/src core/include` -> 0 (кроме явно разрешенных transitional-адаптеров в `src`).
- `APIcfBase.h` не тянет `System.hpp`.
- Проект стабильно собирается.

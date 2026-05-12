# v8reader_core

`v8reader_core` - слой чтения контейнеров и парсинга V8 Reader без зависимости от VCL.

Библиотека предоставляет небольшой C++17 API в `include/v8reader_core/V8ReaderCore.h`:

- получение списка файлов верхнего уровня внутри контейнера 1С;
- распаковка контейнера в каталог;
- разбор контейнера в исходные файлы;
- сборка CF-файла из разобранного каталога;
- упаковка и распаковка raw deflate-потоков 1С.

Этот слой намеренно не содержит UI-типы VCL/RTL: `String`, `TStream`, формы,
деревья, окна сообщений и т.п. Текущие классы дерева метаданных пока остаются
в VCL-слое приложения; их стоит переносить за стандартные C++-интерфейсы
отдельным этапом.

## Временная библиотека метаданных (P1/P2)

Для поэтапного выноса классов метаданных добавлена отдельная цель
`v8reader_metadata_legacy` (включается флагом CMake):

- `-DV8READER_BUILD_METADATA_LEGACY=ON`

Цель собирает кандидатов этапов P1/P2 (базовые metadata-классы и их первые
конкретные реализации) и остается VCL-зависимой.
Точка подключения заголовков: `include/v8reader_core/V8MetadataLegacy.h`.

## Сборка

Проект RAD Studio / C++Builder:

```bat
call "C:\Program Files (x86)\Embarcadero\Studio\37.0\bin\rsvars.bat"
msbuild ..\v8reader.groupproj /p:Config=Debug /p:Platform=Win32 /t:Build
```

Альтернативная сборка через CMake:

```bat
call "C:\Program Files (x86)\Embarcadero\Studio\37.0\bin\rsvars.bat"
cmake -S core -B core\build-bcc32c -G "Borland Makefiles" -DCMAKE_CXX_COMPILER=bcc32c
cmake --build core\build-bcc32c
```

Сборка с legacy metadata-целью:

```bat
call "C:\Program Files (x86)\Embarcadero\Studio\37.0\bin\rsvars.bat"
cmake -S core -B core\build-bcc32c-md -G "Borland Makefiles" -DCMAKE_CXX_COMPILER=bcc32c -DV8READER_BUILD_METADATA_LEGACY=ON
cmake --build core\build-bcc32c-md
```

Статическая библиотека использует существующие низкоуровневые исходники из
`src` и публичные заголовки zlib из `src/zlib`. Если CMake не найдёт zlib
автоматически, конечное приложение, использующее эту библиотеку, должно
подключить zlib самостоятельно.

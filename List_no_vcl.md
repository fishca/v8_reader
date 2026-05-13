# List_no_vcl

Проверены файлы в `src` (исходники `.cpp/.h`, без `OBJ`, `.dfm`, `.cbproj`).

## Кандидаты для простого переноса в `core` без VCL

1. `src/V8File.h`  
   - Использует STL/`std::filesystem`, без `vcl.h`, `String`, `TStream`.
2. `src/V8File.cpp`  
   - Алгоритмический код `v8unpack`, без VCL-типов.
3. `src/VersionFile.h`  
   - Чистый C++ (`std::string`, `istream`).
4. `src/VersionFile.cpp`  
   - Чистый C++, без VCL-зависимостей.
5. `src/utils.cpp`  
   - Работа с zlib и STL, без VCL API.
6. `src/v8_constants.h`  
   - Набор констант, без VCL.
7. `src/zlib/crc32.h`
8. `src/zlib/deflate.h`
9. `src/zlib/gzguts.h`
10. `src/zlib/inffast.h`
11. `src/zlib/inffixed.h`
12. `src/zlib/inflate.h`
13. `src/zlib/inftrees.h`
14. `src/zlib/trees.h`
15. `src/zlib/zconf.h`
16. `src/zlib/zlib.h`
17. `src/zlib/zutil.h`
   - Вендорные zlib-заголовки, VCL не используют.

## Не являются "простым переносом" без VCL

- UI/IDE/VCL-часть: `MainUnit.*`, `SynHighlighter1C.*`, `MetadataTreeBuilder.*`, `v8reader.cpp`, `v8readerPCH1.h`, `HTTPServices`.
- Потоки/строки VCL: `Class_1CD.*`, `ConfigStorage.*`, `Common.*`, `MessageRegistration.*`, `TempStream.*`, `VclByteStreamAdapter.h`, `UZLib.*`, `SmartPointers.h`.

Примечание: `db_ver.h` и `placeholder216.cpp` уже вынесены из `src` в `core` ранее.

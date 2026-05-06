# Инструкция по портированию v8_reader на wxWidgets

## 📋 Обзор проекта

**Цель:** Миграция приложения v8_reader с C++ Builder (VCL) на кроссплатформенный стек (GCC + wxWidgets) с сохранением функциональности чтения файлов 1С.

**Ориентировочные сроки:** 8-12 недель  
**Уровень сложности:** Высокий  
**Необходимые навыки:** C++17, wxWidgets, CMake, работа с бинарными данными

---

## 🎯 Этап 0: Подготовка окружения (Неделя 1)

### 0.1 Установка инструментов разработки

#### Windows
```bash
# Установить MSYS2 или MinGW-w64
# Скачать и установить wxWidgets 3.2+ (pre-built binaries или сборка из исходников)
# Установить CMake 3.20+
# Установить Git
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake git \
    libwxgtk3.2-dev wx-common \
    libz-dev libssl-dev
```

#### macOS
```bash
brew install cmake wxwidgets zlib openssl
```

### 0.2 Создание структуры проекта для миграции

```
v8_reader_port/
├── CMakeLists.txt              # Главный файл сборки
├── README.md                   # Документация
├── src/
│   ├── core/                   # Ядро парсинга (без изменений)
│   │   ├── Class_1CD.cpp
│   │   ├── Class_1CD.h
│   │   ├── Common.cpp
│   │   └── ...
│   ├── gui/                    # Новый GUI на wxWidgets
│   │   ├── main_frame.cpp
│   │   ├── main_frame.h
│   │   ├── data_view.cpp
│   │   └── ...
│   └── adapters/               # Адаптеры для совместимости
│       ├── stream_adapter.h
│       ├── string_adapter.h
│       └── vcl_compat.h
├── include/                    # Публичные заголовки
├── tests/                      # Unit-тесты
├── resources/                  # Иконки, файлы ресурсов
└── legacy/                     # Оригинальный код (для справки)
```

### 0.3 Инициализация репозитория

```bash
mkdir v8_reader_port
cd v8_reader_port
git init
git remote add origin <ваш_репозиторий>

# Скопировать ядро парсинга из оригинального проекта
cp -r ../v8_reader/source/core src/
cp -r ../v8_reader/source/common src/

# Создать начальную структуру
mkdir -p src/{gui,adapters} include tests resources
```

---

## 🔧 Этап 1: Создание слоя совместимости (Недели 1-2)

### 1.1 Адаптер строк (string_adapter.h)

Замена `AnsiString`/`UnicodeString` на `std::string`:

```cpp
// src/adapters/string_adapter.h
#pragma once
#include <string>
#include <cstdint>

// Базовый адаптер для совместимости типов
class TStringAdapter {
public:
    using StringType = std::string;
    
    static std::string AnsiToUTF8(const std::string& ansi_str);
    static std::string UTF8ToAnsi(const std::string& utf8_str);
    
    // Эмуляция методов AnsiString
    static size_t Length(const std::string& str) { return str.length(); }
    static std::string SubString(const std::string& str, size_t pos, size_t len);
    static int Pos(const std::string& substr, const std::string& str);
};

// Макросы для быстрой миграции
#define _T(str) str
#define __D(x) x
```

### 1.2 Адаптер потоков (stream_adapter.h)

Замена `TStream` на стандартные потоки:

```cpp
// src/adapters/stream_adapter.h
#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

class IStreamAdapter {
public:
    virtual ~IStreamAdapter() = default;
    
    virtual int64_t Read(void* buffer, int64_t count) = 0;
    virtual int64_t Write(const void* buffer, int64_t count) = 0;
    virtual int64_t Seek(int64_t offset, int origin) = 0;
    virtual int64_t Position() = 0;
    virtual int64_t Size() = 0;
    
    // Helper methods
    template<typename T>
    T ReadValue() {
        T value;
        Read(&value, sizeof(T));
        return value;
    }
};

class FileStreamAdapter : public IStreamAdapter {
private:
    std::fstream file;
    
public:
    explicit FileStreamAdapter(const std::string& filename, bool read_only = true);
    
    int64_t Read(void* buffer, int64_t count) override;
    int64_t Write(const void* buffer, int64_t count) override;
    int64_t Seek(int64_t offset, int origin) override;
    int64_t Position() override;
    int64_t Size() override;
};

class MemoryStreamAdapter : public IStreamAdapter {
private:
    std::vector<uint8_t> buffer;
    size_t position;
    
public:
    MemoryStreamAdapter() : position(0) {}
    explicit MemoryStreamAdapter(const std::vector<uint8_t>& data);
    
    int64_t Read(void* buffer, int64_t count) override;
    int64_t Write(const void* buffer, int64_t count) override;
    int64_t Seek(int64_t offset, int origin) override;
    int64_t Position() override;
    int64_t Size() override;
};
```

### 1.3 Удаление Borland-специфичных конструкций

Создать скрипт для автоматической замены:

```bash
#!/bin/bash
# scripts/remove_borland_pragmas.sh

find src -name "*.h" -o -name "*.cpp" | while read file; do
    # Удалить #pragma hdrstop
    sed -i '/#pragma hdrstop/d' "$file"
    
    # Заменить __fastcall на пустоту
    sed -i 's/__fastcall//g' "$file"
    
    # Удалить #pragma comment
    sed -i '/#pragma comment/d' "$file"
    
    # Заменить __property на комментарии (требует ручной доработки)
    sed -i 's/__property/\/\/ __property/g' "$file"
done
```

### 1.4 Исправление соглашений о вызовах

В заголовочных файлах заменить:
```cpp
// Было
void __fastcall ProcessData(char* buffer, int size);

// Стало
void ProcessData(char* buffer, int size);  // __fastcall удалён
```

**Важно:** Пересобрать все файлы после изменений, чтобы избежать проблем с линковкой.

---

## 🏗️ Этап 2: Настройка системы сборки CMake (Неделя 2)

### 2.1 Главный CMakeLists.txt

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(v8_reader VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Найти wxWidgets
find_package(wxWidgets 3.2 COMPONENTS core base REQUIRED)

# Найти zlib
find_package(ZLIB REQUIRED)

# Включить директорию с адаптерами
include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${wxWidgets_INCLUDE_DIRS}
)

# Исходники ядра (без изменений)
set(CORE_SOURCES
    src/core/Class_1CD.cpp
    src/core/Common.cpp
    src/core/V8File.cpp
    src/core/Database.cpp
    # ... добавить все файлы ядра
)

# Исходники GUI
set(GUI_SOURCES
    src/gui/main_frame.cpp
    src/gui/data_view.cpp
    src/gui/search_dialog.cpp
    src/gui/app.cpp
)

# Исходники адаптеров
set(ADAPTER_SOURCES
    src/adapters/stream_adapter.cpp
    src/adapters/string_adapter.cpp
)

# Создать библиотеку ядра
add_library(v8core STATIC ${CORE_SOURCES} ${ADAPTER_SOURCES})
target_link_libraries(v8core ZLIB::ZLIB)

# Создать исполняемый файл
add_executable(v8_reader WIN32 ${GUI_SOURCES})
target_link_libraries(v8_reader 
    v8core 
    ${wxWidgets_LIBRARIES}
)

# Настройки для Windows
if(WIN32)
    target_compile_definitions(v8_reader PRIVATE _UNICODE UNICODE)
endif()

# Unit тесты
enable_testing()
add_subdirectory(tests)
```

### 2.2 Конфигурация для разных платформ

Создать `cmake/config.cmake`:

```cmake
# Платформенные настройки
if(WIN32)
    set(PLATFORM_DEFINES _WIN32_WINNT=0x0601)
    set(PLATFORM_LIBS ws2_32)
elseif(APPLE)
    set(PLATFORM_DEFINES _DARWIN_C_SOURCE)
else()
    set(PLATFORM_DEFINES _LINUX)
endif()

target_compile_definitions(v8core PRIVATE ${PLATFORM_DEFINES})
target_link_libraries(v8core PRIVATE ${PLATFORM_LIBS})
```

### 2.3 Сборка проекта

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release

# Запустить тесты
ctest --verbose
```

---

## 🖼️ Этап 3: Разработка основного интерфейса (Недели 3-4)

### 3.1 Главное приложение (app.cpp)

```cpp
// src/gui/app.cpp
#include <wx/wx.h>
#include "main_frame.h"

class V8ReaderApp : public wxApp {
public:
    bool OnInit() override;
};

bool V8ReaderApp::OnInit() {
    if (!wxApp::OnInit())
        return false;
    
    // Инициализация изображений
    wxInitAllImageHandlers();
    
    // Создание главного окна
    auto* frame = new MainFrame(nullptr, wxID_ANY, "v8_reader");
    frame->Show(true);
    
    return true;
}

wxIMPLEMENT_APP(V8ReaderApp);
```

### 3.2 Главная форма (main_frame.h)

```cpp
// src/gui/main_frame.h
#pragma once
#include <wx/wx.h>
#include <wx/dataview.h>
#include <wx/stc/stc.h>
#include <wx/aui/aui.h>
#include "../core/Class_1CD.h"
#include "../adapters/stream_adapter.h"

class MainFrame : public wxFrame {
public:
    MainFrame(wxWindow* parent, wxWindowID id, const wxString& title);
    ~MainFrame();
    
private:
    // Компоненты интерфейса
    wxAuiManager m_aui;
    wxDataViewCtrl* m_dataView;
    wxStyledTextCtrl* m_hexView;
    wxStatusBar* m_statusBar;
    
    // Модели данных
    wxDataViewTreeCtrl* m_treeCtrl;
    
    // Данные 1С
    std::unique_ptr<Class_1CD> m_database;
    std::unique_ptr<FileStreamAdapter> m_stream;
    
    // Обработчики событий
    void OnOpenFile(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnSearch(wxCommandEvent& event);
    void OnItemActivated(wxDataViewEvent& event);
    void OnSelectionChanged(wxDataViewEvent& event);
    
    // Вспомогательные методы
    void LoadDatabase(const wxString& filename);
    void UpdateTreeView();
    void UpdateHexView(const std::vector<uint8_t>& data);
    void UpdateStatusBar(const wxString& message);
    
    DECLARE_EVENT_TABLE()
};

// ID команд
enum {
    ID_Menu_Open = wxID_HIGHEST + 1,
    ID_Menu_Search,
    ID_Menu_Export,
    ID_Menu_About
};
```

### 3.3 Реализация главной формы (main_frame.cpp)

```cpp
// src/gui/main_frame.cpp
#include "main_frame.h"
#include <wx/filename.h>
#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/busyinfo.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_Menu_Open, MainFrame::OnOpenFile)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU(ID_Menu_Search, MainFrame::OnSearch)
    EVT_DATAVIEW_ITEM_ACTIVATED(wxID_ANY, MainFrame::OnItemActivated)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title, wxDefaultPosition, wxSize(1200, 800)) {
    
    // Создание меню
    auto* menuBar = new wxMenuBar();
    
    auto* fileMenu = new wxMenu();
    fileMenu->Append(ID_Menu_Open, "&Открыть файл...\tCtrl+O");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "Выход\tAlt+F4");
    menuBar->Append(fileMenu, "&Файл");
    
    auto* editMenu = new wxMenu();
    editMenu->Append(ID_Menu_Search, "&Поиск...\tCtrl+F");
    menuBar->Append(editMenu, "&Правка");
    
    auto* helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&О программе");
    menuBar->Append(helpMenu, "&Справка");
    
    SetMenuBar(menuBar);
    
    // Создание AUI менеджера
    m_aui.SetManagedWindow(this);
    
    // Дерево объектов
    m_treeCtrl = new wxDataViewTreeCtrl(this, wxID_ANY);
    m_aui.AddPane(m_treeCtrl, wxAuiPaneInfo()
        .Name("ObjectTree")
        .Left()
        .Caption("Объекты базы")
        .BestSize(wxSize(300, -1))
        .CloseButton(false));
    
    // Таблица данных
    m_dataView = new wxDataViewCtrl(this, wxID_ANY);
    
    // Добавить колонки
    m_dataView->AppendTextColumn("Имя", 0, wxDATAVIEW_CELL_INERT, 200);
    m_dataView->AppendTextColumn("Тип", 1, wxDATAVIEW_CELL_INERT, 150);
    m_dataView->AppendTextColumn("Размер", 2, wxDATAVIEW_CELL_INERT, 100);
    
    m_aui.AddPane(m_dataView, wxAuiPaneInfo()
        .Name("DataView")
        .CenterPane()
        .Caption("Данные"));
    
    // Шестнадцатеричный просмотр
    m_hexView = new wxStyledTextCtrl(this, wxID_ANY);
    m_hexView->SetLexer(wxSTC_LEX_HEX);
    m_hexView->SetReadOnly(true);
    
    m_aui.AddPane(m_hexView, wxAuiPaneInfo()
        .Name("HexView")
        .Bottom()
        .Caption("HEX")
        .BestSize(wxSize(-1, 200))
        .CloseButton(false));
    
    m_aui.Update();
    
    // Строка состояния
    m_statusBar = CreateStatusBar(3);
    int widths[] = {-1, 150, 100};
    m_statusBar->SetStatusWidths(3, widths);
    
    UpdateStatusBar("Готов к работе");
}

MainFrame::~MainFrame() {
    m_aui.UnInit();
}

void MainFrame::OnOpenFile(wxCommandEvent& event) {
    wxFileDialog dlg(this, "Открыть файл 1С", "", "", 
        "Файлы 1С (*.1CD;*.cf)|*.1CD;*.cf|Все файлы (*)|*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (dlg.ShowModal() == wxID_OK) {
        wxString filename = dlg.GetPath();
        
        try {
            wxBusyInfo info("Загрузка файла...", this);
            LoadDatabase(filename);
            UpdateStatusBar(wxString::Format("Файл загружен: %s", filename));
        } catch (const std::exception& e) {
            wxMessageBox(wxString::Format("Ошибка загрузки: %s", e.what()), 
                "Ошибка", wxICON_ERROR);
        }
    }
}

void MainFrame::LoadDatabase(const wxString& filename) {
    // Очистка предыдущих данных
    m_database.reset();
    m_treeCtrl->DeleteAllItems();
    
    // Создание потока
    m_stream = std::make_unique<FileStreamAdapter>(filename.ToStdString(), true);
    
    // Инициализация базы данных
    m_database = std::make_unique<Class_1CD>();
    m_database->Initialize(m_stream.get());
    
    // Обновление дерева
    UpdateTreeView();
}

void MainFrame::UpdateTreeView() {
    if (!m_database)
        return;
    
    wxDataViewItem root = m_treeCtrl->AddRoot("База данных 1С");
    
    // Добавить основные разделы
    auto catalogs = m_treeCtrl->AppendItem(root, "Справочники");
    auto documents = m_treeCtrl->AppendItem(root, "Документы");
    auto registers = m_treeCtrl->AppendItem(root, "Регистры");
    
    // Заполнение данными из базы
    // Здесь нужно реализовать обход объектов базы
    // и добавление их в дерево
}

void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("v8_reader\nВерсия 1.0 (wxWidgets)\n\n"
                 "Инструмент для чтения файлов 1С",
                 "О программе", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnSearch(wxCommandEvent& event) {
    // Реализация диалога поиска
}

void MainFrame::OnItemActivated(wxDataViewEvent& event) {
    // Обработка двойного клика
}

void MainFrame::UpdateStatusBar(const wxString& message) {
    m_statusBar->SetStatusText(message, 0);
}
```

---

## 🌳 Этап 4: Миграция VirtualStringTree (Недели 5-7)

### 4.1 Анализ использования VirtualStringTree

Найти все места использования:
```bash
grep -r "VirtualStringTree\|TVirtualStringTree" src/
```

### 4.2 Замена на wxDataViewCtrl

Создать адаптер для эмуляции основных функций:

```cpp
// src/gui/vst_adapter.h
#pragma once
#include <wx/dataview.h>
#include <vector>
#include <memory>

class VSTDataAdapter : public wxDataViewVirtualListModel {
public:
    VSTDataAdapter();
    
    // Методы эмуляции VirtualStringTree
    void SetItemCount(size_t count);
    void AddItem(const std::vector<wxVariant>& data);
    void Clear();
    
    // Переопределённые методы
    unsigned int GetRowCount() const override;
    void GetValueByRow(wxVariant& variant, unsigned int row, 
                      unsigned int col) const override;
    
private:
    std::vector<std::vector<wxVariant>> m_data;
};
```

### 4.3 Кастомная отрисовка

Для сложной отрисовки использовать `wxDataViewCustomRenderer`:

```cpp
class HexDataRenderer : public wxDataViewCustomRenderer {
public:
    HexDataRenderer();
    
    bool Render(wxRect cell, wxDC dc, int state) override;
    bool Activate(wxRect cell, wxDataViewModel* model,
                 const wxDataViewItem& item, unsigned int col) override;
    
private:
    std::vector<uint8_t> m_hexData;
};
```

---

## 📝 Этап 5: Замена SynMemo (Неделя 7)

### 5.1 Использование wxStyledTextCtrl

```cpp
// src/gui/hex_viewer.cpp
#include <wx/stc/stc.h>

class HexViewer : public wxStyledTextCtrl {
public:
    HexViewer(wxWindow* parent);
    
    void SetData(const std::vector<uint8_t>& data);
    void HighlightBytes(size_t start, size_t length);
    
private:
    void FormatHexDisplay();
    
    std::vector<uint8_t> m_data;
};

HexViewer::HexViewer(wxWindow* parent)
    : wxStyledTextCtrl(parent, wxID_ANY) {
    
    // Настройка стиля для HEX
    SetLexer(wxSTC_LEX_HEX);
    StyleSetForeground(wxSTC_HEX_DEFAULT, *wxBLACK);
    StyleSetBackground(wxSTC_HEX_DEFAULT, *wxWHITE);
    StyleSetForeground(wxSTC_HEX_BYTE, wxColour(0, 0, 128));
    
    SetReadOnly(true);
    SetMarginWidth(0, 40);  // Поля адресов
}

void HexViewer::SetData(const std::vector<uint8_t>& data) {
    m_data = data;
    FormatHexDisplay();
}

void HexViewer::FormatHexDisplay() {
    ClearAll();
    
    wxString output;
    for (size_t i = 0; i < m_data.size(); i += 16) {
        // Адрес
        output += wxString::Format("%08X: ", i);
        
        // HEX байты
        for (size_t j = 0; j < 16 && (i + j) < m_data.size(); ++j) {
            output += wxString::Format("%02X ", m_data[i + j]);
        }
        
        // ASCII представление
        output += " |";
        for (size_t j = 0; j < 16 && (i + j) < m_data.size(); ++j) {
            char c = m_data[i + j];
            output += (c >= 32 && c < 127) ? wxString(c) : ".";
        }
        output += "|\n";
    }
    
    SetText(output);
}
```

---

## 🧪 Этап 6: Тестирование и отладка (Недели 8-9)

### 6.1 Создание unit-тестов

```cpp
// tests/test_parser.cpp
#include <gtest/gtest.h>
#include "../src/core/Class_1CD.h"
#include "../src/adapters/stream_adapter.h"

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Подготовка тестовых данных
    }
};

TEST_F(ParserTest, ParseValidFile) {
    MemoryStreamAdapter stream(test_data);
    Class_1CD db;
    
    EXPECT_NO_THROW(db.Initialize(&stream));
    EXPECT_GT(db.GetObjectCount(), 0);
}

TEST_F(ParserTest, DateConversion) {
    unsigned char time1CD[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    FILETIME ft;
    
    time1CD_to_FileTime(&ft, time1CD);
    
    EXPECT_EQ(ft.dwLowDateTime, 0);
    EXPECT_EQ(ft.dwHighDateTime, 0);
}
```

### 6.2 Интеграционное тестирование

Создать набор тестовых файлов 1С и проверить:
- Корректность чтения всех типов объектов
- Соответствие данных оригинальному C++ Builder приложению
- Производительность на больших файлах

---

## 🚀 Этап 7: Оптимизация и финализация (Недели 10-12)

### 7.1 Профилирование производительности

```bash
# Linux
perf record ./v8_reader test_file.1CD
perf report

# Windows
# Использовать Visual Studio Profiler или Intel VTune
```

### 7.2 Оптимизация памяти

- Использовать `reserve()` для векторов
- Применять move-семантику
- Избегать лишних копий строк

### 7.3 Создание инсталлятора

#### Windows (Inno Setup)
```ini
[Setup]
AppName=v8_reader
AppVersion=1.0
DefaultDirName={pf}\v8_reader

[Files]
Source: "build\Release\v8_reader.exe"; DestDir: "{app}"
Source: "resources\*"; DestDir: "{app}\resources"
```

#### Linux (AppImage/DEB/RPM)
```bash
# Создать AppImage
linuxdeployqt --appdir AppDir -executable v8_reader
```

---

## 📊 Чек-лист миграции

### Обязательные задачи
- [ ] Удалить все `#pragma hdrstop`
- [ ] Заменить `__fastcall` на стандартные вызовы
- [ ] Создать адаптеры для `TStream` и `AnsiString`
- [ ] Настроить CMake сборку
- [ ] Реализовать главное окно на wxWidgets
- [ ] Заменить VirtualStringTree на wxDataViewCtrl
- [ ] Заменить SynMemo на wxStyledTextCtrl
- [ ] Протестировать чтение всех типов объектов 1С
- [ ] Проверить работу на Windows/Linux/macOS

### Дополнительные улучшения
- [ ] Добавить тёмную тему
- [ ] Реализовать экспорт в CSV/JSON
- [ ] Добавить поиск с подсветкой
- [ ] Создать документацию пользователя
- [ ] Настроить CI/CD для кроссплатформенной сборки

---

## 🔧 Полезные команды

### Поиск Borland-специфичных конструкций
```bash
grep -rn "__fastcall\|#pragma hdrstop\|AnsiString\|UnicodeString" src/
```

### Автоматическая замена
```bash
find src -name "*.cpp" -o -name "*.h" | xargs sed -i 's/__fastcall//g'
```

### Сборка в разных конфигурациях
```bash
# Debug
cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build .

# Release
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .

# С включёнными предупреждениями
cmake -DCMAKE_CXX_FLAGS="-Wall -Wextra -Wpedantic" ..
```

---

## 🆘 Решение распространённых проблем

### Проблема: Ошибки компиляции из-за pack структур
**Решение:**
```cpp
#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#endif

struct MyStruct {
    // данные
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma GCC diagnostic pop
#endif
```

### Проблема: Различия в endianness
**Решение:**
```cpp
#include <bit>

template<typename T>
T byteswap_if_needed(T value) {
    if constexpr (std::endian::native == std::endian::little) {
        return value;  // 1С использует little-endian
    } else {
        return std::byteswap(value);
    }
}
```

### Проблема: Отсутствие некоторых функций wxWidgets
**Решение:** Использовать условную компиляцию или создать обёртки:
```cpp
#if wxCHECK_VERSION(3, 2, 0)
    // Использовать новую функцию
#else
    // Реализовать свою версию
#endif
```

---

## 📚 Дополнительные ресурсы

- [Официальная документация wxWidgets](https://docs.wxwidgets.org/)
- [wxWidgets Cookbook](https://wiki.wxwidgets.org/Category:Cookbook)
- [CMake Documentation](https://cmake.org/documentation/)
- [Примеры миграции с VCL](https://github.com/topics/vcl-to-wxwidgets)

---

## ✅ Критерии завершения миграции

1. ✅ Проект собирается без ошибок на всех целевых платформах
2. ✅ Все функции оригинального приложения работают корректно
3. ✅ Производительность не хуже оригинала (±10%)
4. ✅ Пройдены все unit-тесты
5. ✅ Документация обновлена
6. ✅ Создан инсталлятор для каждой платформы

---

**Дата создания:** 2024  
**Автор:** AI Assistant  
**Статус:** Готово к использованию

#ifndef SmartPointersH
#define SmartPointersH

#include <memory>
#include <vector>

// ============================================================================
// Кастомные deleters для умных указателей
// ============================================================================

// Кастомный deleter для VCL TObject
// Обеспечивает корректное удаление VCL-объектов
struct VclObjectDeleter {
    void operator()(TObject* obj) const {
        if (obj) {
            delete obj;
        }
    }
};

// Кастомный deleter для tree (парсинг метаданных 1С)
// Используется для безопасного освобождения дерева разбора
struct TreeDeleter {
    void operator()(tree* t) const {
        if (t) {
            delete t;
        }
    }
};

// Кастомный deleter для v8file (файлы 1С)
struct V8FileDeleter {
    void operator()(v8file* vf) const {
        if (vf) {
            delete vf;
        }
    }
};

// Кастомный deleter для v8catalog (каталог конфигурации 1С)
struct V8CatalogDeleter {
    void operator()(v8catalog* vc) const {
        if (vc) {
            delete vc;
        }
    }
};

// ============================================================================
// Типы умных указателей
// ============================================================================

// Умный указатель для VCL объектов (TObject и его наследники)
// Использует VclObjectDeleter для корректного удаления
template<typename T>
using VclUniquePtr = std::unique_ptr<T, VclObjectDeleter>;

// Умный указатель для дерева парсинга
using TreeUniquePtr = std::unique_ptr<tree, TreeDeleter>;

// Умный указатель для файлов 1С
using V8FileUniquePtr = std::unique_ptr<v8file, V8FileDeleter>;

// Умный указатель для каталога конфигурации 1С
using V8CatalogUniquePtr = std::unique_ptr<v8catalog, V8CatalogDeleter>;

// ============================================================================
// Векторы умных указателей
// ============================================================================

// Вектор уникальных указателей для метаданных
// Используется для объектов с единственным владельцем
// Пример: MetadataVector<TCatalogs> mdCatalogs;
template<typename T>
using MetadataVector = std::vector<std::unique_ptr<T>>;

// Вектор разделяемых указателей для метаданных
// Используется для объектов с общим владением
// Пример: SharedMetadataVector<TReport> mdReports;
template<typename T>
using SharedMetadataVector = std::vector<std::shared_ptr<T>>;

// ============================================================================
// Вспомогательные функции
// ============================================================================

// Создание умного указателя для VCL объекта
template<typename T, typename... Args>
VclUniquePtr<T> MakeVclUnique(Args&&... args) {
    return VclUniquePtr<T>(new T(std::forward<Args>(args)...));
}

// Создание вектора умных указателей с перемещением
template<typename T>
void AddToMetadataVector(MetadataVector<T>& vec, std::unique_ptr<T> item) {
    vec.push_back(std::move(item));
}

// ============================================================================
// Примеры использования
// ============================================================================
/*
// Пример 1: Замена голого указателя v8catalog*
// До:
v8catalog* GlobalCF = nullptr;
if (GlobalCF) {
    delete GlobalCF;
}
GlobalCF = new v8catalog(filename, true);

// После:
V8CatalogUniquePtr GlobalCF;
GlobalCF = std::make_unique<v8catalog>(filename, true);
// Автоматическое освобождение при выходе из области видимости


// Пример 2: Замена TObjectList* на MetadataVector
// До:
TObjectList* mdCatalogs = new TObjectList(true);
mdCatalogs->Add(new TCatalogs(...));
TCatalogs* cat = static_cast<TCatalogs*>(mdCatalogs->Items[i]);

// После:
MetadataVector<TCatalogs> mdCatalogs;
mdCatalogs.push_back(std::make_unique<TCatalogs>(...));
TCatalogs* cat = mdCatalogs[i].get();


// Пример 3: Замена tree* на TreeUniquePtr
// До:
tree* root_data = new tree();
delete root_data;

// После:
TreeUniquePtr root_data(new tree());
// Автоматическое освобождение


// Пример 4: Использование MetadataVector в методах
// До:
void FillTree(TObjectList* mdData) {
    for (int i = 0; i < mdData->Count; i++) {
        auto* item = static_cast<TCatalogs*>(mdData->Items[i]);
    }
}

// После:
void FillTree(const MetadataVector<TCatalogs>& mdData) {
    for (const auto& item : mdData) {
        TCatalogs* obj = item.get();
    }
}
*/

#endif

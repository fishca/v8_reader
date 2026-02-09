//---------------------------------------------------------------------------

#ifndef MetadataObjectWithSectionsH
#define MetadataObjectWithSectionsH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "Common.h"
#include <functional>

//---------------------------------------------------------------------------
// Конфигурация путей в дереве парсинга для разных типов метаданных 1С
struct MetadataTreePaths
{
    int attIdx;           // индекс: root[0][attIdx][1] = количество реквизитов
    std::vector<int> attItemPath;   // путь к имени реквизита от узла элемента
    int tabIdx;           // индекс для табличных частей
    std::vector<int> tabItemPath;   // путь к имени табличной части
    int formsIdx;         // индекс: root[0][formsIdx][0] = узел списка форм
    int cmdIdx;           // индекс: root[0][cmdIdx][1] = количество команд
    std::vector<int> cmdItemPath;   // путь к имени команды от узла элемента
    int moxIdx;           // индекс: root[0][moxIdx][0] = узел списка макетов
    std::function<String(v8catalog*, String&)> getFormNameFunc;
    bool hasTabulars = true;  // у журналов нет табличных частей
};

//---------------------------------------------------------------------------
// Базовый класс для объектов метаданных с реквизитами, ТЧ, формами, командами и макетами
class MetadataObjectWithSections : public BaseMetadataObject
{
protected:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TTabular>> tabulars;
    std::vector<std::unique_ptr<TForm1C>> forms;

    void initializeFromTreeWithPaths(const MetadataTreePaths& paths);

public:
    __fastcall MetadataObjectWithSections();
    __fastcall MetadataObjectWithSections(v8catalog* _parent, const String& _guid);
    __fastcall MetadataObjectWithSections(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~MetadataObjectWithSections();

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }
};

//---------------------------------------------------------------------------
#endif

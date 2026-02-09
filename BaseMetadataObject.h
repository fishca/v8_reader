//---------------------------------------------------------------------------

#ifndef BaseMetadataObjectH
#define BaseMetadataObjectH
//---------------------------------------------------------------------------

#include <vector>
#include "Class_1CD.h"
#include "APIcfBase.h"
#include "Parse_tree.h"
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"

//---------------------------------------------------------------------------
// Абстрактный базовый класс для всех объектов метаданных
// Предоставляет общий интерфейс и базовую функциональность
class BaseMetadataObject : public TObject
{
public:
    // Общие поля
    String name;
    String guid;
    tree* root_data;
    v8catalog* parent;

    // Конструкторы
    __fastcall BaseMetadataObject();
    __fastcall BaseMetadataObject(v8catalog* _parent, const String& _guid);
    __fastcall BaseMetadataObject(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~BaseMetadataObject() = 0; // Чисто виртуальный деструктор

    // Виртуальные методы для получения имени и GUID
    virtual String __fastcall GetName();
    virtual String __fastcall GetGUID();

    // Чисто виртуальные методы для получения списков элементов метаданных
    virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() = 0;
    virtual std::vector<std::unique_ptr<TComand>>& getCommands() = 0;
    virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() = 0;
    virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() = 0;
    virtual std::vector<std::unique_ptr<TForm1C>>& getForms() = 0;

    // Виртуальный метод для инициализации данных из root_data
    virtual void __fastcall initializeFromTree() = 0;
};


#endif

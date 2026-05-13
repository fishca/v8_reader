//---------------------------------------------------------------------------

#ifndef BaseMetadataObjectH
#define BaseMetadataObjectH
//---------------------------------------------------------------------------

#include <vector>
#include <memory>
#include "Class_1CD.h"
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"
#include "ModuleTextStorage.h"

//---------------------------------------------------------------------------
// Абстрактный базовый класс для всех объектов метаданных
// Предоставляет общий интерфейс и базовую функциональность
class BaseMetadataObject : public TObject
{
public:
    // Общие поля
    String name;
    String guid;
    std::unique_ptr<tree> root_data;
    v8catalog* parent;

    // Конструкторы
    BaseMetadataObject();
    BaseMetadataObject(v8catalog* _parent, const String& _guid);
    BaseMetadataObject(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~BaseMetadataObject() = 0; // Чисто виртуальный деструктор

    // Виртуальные методы для получения имени и GUID
    virtual String GetName();
    virtual String GetGUID();

    // Чисто виртуальные методы для получения списков элементов метаданных
    virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() = 0;
    virtual std::vector<std::unique_ptr<TComand>>& getCommands() = 0;
    virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() = 0;
    virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() = 0;
    virtual std::vector<std::unique_ptr<TForm1C>>& getForms() = 0;

    // Виртуальный метод для инициализации данных из root_data
    virtual void initializeFromTree() = 0;

	virtual bool HasEditableModuleText();
	virtual String GetEditableModuleText();
	virtual void SetEditableModuleText(const String& value);
	virtual bool SaveEditableModuleText(const String& value, String& errorText);
	virtual ModuleTextLocation GetEditableModuleLocation();
	virtual bool HasEditableModuleText(ModuleTextKind kind);
	virtual String GetEditableModuleText(ModuleTextKind kind);
	virtual void SetEditableModuleText(ModuleTextKind kind, const String& value);
	virtual bool SaveEditableModuleText(ModuleTextKind kind, const String& value, String& errorText);
	virtual ModuleTextLocation GetEditableModuleLocation(ModuleTextKind kind);
};


#endif


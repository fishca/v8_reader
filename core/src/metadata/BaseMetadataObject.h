//---------------------------------------------------------------------------

#ifndef BaseMetadataObjectH
#define BaseMetadataObjectH
//---------------------------------------------------------------------------

#include <vector>
#include <memory>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"
#include "ModuleTextStorage.h"
#include "MetadataEntity.h"

//---------------------------------------------------------------------------
// Абстрактный базовый класс для всех объектов метаданных
// Предоставляет общий интерфейс и базовую функциональность
class BaseMetadataObject : public MetadataEntity
{
public:
    // Общие поля
    Utf16String name;
    Utf16String guid;
	Utf16String guid16;
    std::unique_ptr<tree> root_data;
    v8catalog* parent;

    // Конструкторы
    BaseMetadataObject();
    BaseMetadataObject(v8catalog* _parent, const Utf16String& _guid);
    BaseMetadataObject(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    BaseMetadataObject(v8catalog* _parent, const TStringLike& _guid)
        : BaseMetadataObject(_parent, V8Utf16FromString(_guid))
    {
    }

    template <typename TStringLikeGuid, typename TStringLikeName>
    BaseMetadataObject(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : BaseMetadataObject(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
    {
    }
    virtual ~BaseMetadataObject() = 0; // Чисто виртуальный деструктор

    // Виртуальные методы для получения имени и GUID
    virtual Utf16String GetName();
    virtual Utf16String GetGUID();
	virtual Utf16String GetGUID16();

    // Чисто виртуальные методы для получения списков элементов метаданных
    virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() = 0;
    virtual std::vector<std::unique_ptr<TComand>>& getCommands() = 0;
    virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() = 0;
    virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() = 0;
    virtual std::vector<std::unique_ptr<TForm1C>>& getForms() = 0;

    // Виртуальный метод для инициализации данных из root_data
    virtual void initializeFromTree() = 0;

	virtual bool HasEditableModuleText();
	virtual Utf16String GetEditableModuleText();
	virtual void SetEditableModuleText(const Utf16String& value);
	virtual bool SaveEditableModuleText(const Utf16String& value, Utf16String& errorText);
	virtual ModuleTextLocation GetEditableModuleLocation();
	virtual bool HasEditableModuleText(ModuleTextKind kind);
	virtual Utf16String GetEditableModuleText(ModuleTextKind kind);
	virtual void SetEditableModuleText(ModuleTextKind kind, const Utf16String& value);
	virtual bool SaveEditableModuleText(ModuleTextKind kind, const Utf16String& value, Utf16String& errorText);
	virtual ModuleTextLocation GetEditableModuleLocation(ModuleTextKind kind);
};


#endif


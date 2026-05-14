//---------------------------------------------------------------------------

#ifndef MetadataObjectInformationRegisterH
#define MetadataObjectInformationRegisterH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "Common.h"
#include <functional>

//---------------------------------------------------------------------------
// Конфигурация путей в дереве парсинга для регистров сведений
struct InfoRegisterTreePaths
{
    int attIdx;
    std::vector<int> attItemPath;
    int dimIdx;           // индекс для измерений
    std::vector<int> dimItemPath;
    int resIdx;           // индекс для ресурсов
    std::vector<int> resItemPath;
    int formsIdx;
    int cmdIdx;
    std::vector<int> cmdItemPath;
    int moxIdx;
    std::function<Utf16String(v8catalog*, const Utf16String&)> getFormNameFunc;
};

//---------------------------------------------------------------------------
// Базовый класс для регистров сведений: реквизиты, измерения, ресурсы, формы, команды, макеты
// Табличных частей нет
class MetadataObjectInformationRegister : public BaseMetadataObject
{
protected:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TRequisite>> dimensions;   // измерения
    std::vector<std::unique_ptr<TRequisite>> resources;    // ресурсы
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TForm1C>> forms;
    std::vector<std::unique_ptr<TTabular>> tabulars;       // пустой, для совместимости с BaseMetadataObject

    void initializeFromTreeWithPaths(const InfoRegisterTreePaths& paths);

public:
    MetadataObjectInformationRegister();
    MetadataObjectInformationRegister(v8catalog* _parent, const Utf16String& _guid);
    MetadataObjectInformationRegister(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    MetadataObjectInformationRegister(v8catalog* _parent, const TStringLike& _guid)
        : MetadataObjectInformationRegister(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    MetadataObjectInformationRegister(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : MetadataObjectInformationRegister(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~MetadataObjectInformationRegister();

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

    std::vector<std::unique_ptr<TRequisite>>& getDimensions() { return dimensions; }
    std::vector<std::unique_ptr<TRequisite>>& getResources() { return resources; }
};

//---------------------------------------------------------------------------
#endif


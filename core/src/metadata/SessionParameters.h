//---------------------------------------------------------------------------

#ifndef SessionParametersH
#define SessionParametersH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSessionParameters
 * @brief Класс для хранения параметров сеанса (md_SessionParameters)
 *
 * Параметры сеанса - это объекты метаданных, которые содержат
 * параметры, доступные в текущем сеансе работы системы.
 */
class TSessionParameters : public BaseMetadataObject
{
private:
    // parameterName хранится в унаследованном поле name из BaseMetadataObject

public:
    TSessionParameters();
    TSessionParameters(v8catalog* _parent, const Utf16String& _guid);
    TSessionParameters(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TSessionParameters(v8catalog* _parent, const TStringLike& _guid)
        : TSessionParameters(_parent, V8Utf16FromString(_guid))
    {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TSessionParameters(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TSessionParameters(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name))
    {}
    virtual ~TSessionParameters();

    // Методы для получения имени параметра сеанса
    Utf16String GetParameterName();
    void SetParameterName(const Utf16String& _name);

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif


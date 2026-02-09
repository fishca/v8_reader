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
    __fastcall TSessionParameters();
    __fastcall TSessionParameters(v8catalog* _parent, const String& _guid);
    __fastcall TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TSessionParameters();

    // Методы для получения имени параметра сеанса
    String __fastcall GetParameterName();
    void __fastcall SetParameterName(String _name);

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void __fastcall initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif

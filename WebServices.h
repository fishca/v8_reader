//---------------------------------------------------------------------------
#ifndef WebServicesH
#define WebServicesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TWebServices
 * @brief Класс для хранения веб-сервисов (md_WebServices)
 *
 * Веб-сервисы - это объекты метаданных, которые предоставляют
 * SOAP и HTTP интерфейсы для интеграции с внешними системами.
 */
class TWebServices : public BaseMetadataObject
{
private:
    // data хранится в унаследованном поле root_data из BaseMetadataObject

public:
    __fastcall TWebServices();
    __fastcall TWebServices(v8catalog* _parent, const String& _guid);
    __fastcall TWebServices(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TWebServices();

    // Методы для получения имени веб-сервиса
    String __fastcall GetWebServiceName();
    void __fastcall SetWebServiceName(String _name);

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

//---------------------------------------------------------------------------
#endif

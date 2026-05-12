#ifndef HTTPServicesH
#define HTTPServicesH

#include "BaseMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class THTTPServices
 * @brief Класс для хранения HTTP-сервисов (md_HTTPServices)
 *
 * HTTP-сервисы - это объекты метаданных, которые предоставляют
 * REST интерфейсы для интеграции с внешними системами.
 */
class THTTPServices : public BaseMetadataObject
{
private:
    // data хранится в унаследованном поле root_data из BaseMetadataObject

public:
    __fastcall THTTPServices();
    __fastcall THTTPServices(v8catalog* _parent, const String& _guid);
    __fastcall THTTPServices(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~THTTPServices();

    // Методы для получения имени HTTP-сервиса
    String __fastcall GetHTTPServicesName();
    void __fastcall SetHTTPServicesName(String _name);

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

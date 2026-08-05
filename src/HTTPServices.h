#ifndef HTTPServicesH
#define HTTPServicesH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class THTTPServices
 * @brief Класс для хранения HTTP-сервисов (md_HTTPServices)
 *
 * HTTP-сервисы - это объекты метаданных, которые предоставляют
 * REST интерфейсы для интеграции с внешними системами.
 */
class THTTPServices : public EmptyMetadataObject<THTTPServices>
{
public:
    __fastcall THTTPServices();
    __fastcall THTTPServices(v8catalog* _parent, const String& _guid);
    __fastcall THTTPServices(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени HTTP-сервиса
    String __fastcall GetHTTPServicesName();
    void __fastcall SetHTTPServicesName(String _name);
};

//---------------------------------------------------------------------------

#endif

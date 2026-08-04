//---------------------------------------------------------------------------
#ifndef WebServicesH
#define WebServicesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TWebServices
 * @brief Класс для хранения веб-сервисов (md_WebServices)
 *
 * Веб-сервисы - это объекты метаданных, которые предоставляют
 * SOAP и HTTP интерфейсы для интеграции с внешними системами.
 */
class TWebServices : public EmptyMetadataObject<TWebServices>
{
public:
    __fastcall TWebServices();
    __fastcall TWebServices(v8catalog* _parent, const String& _guid);
    __fastcall TWebServices(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени веб-сервиса
    String __fastcall GetWebServiceName();
    void __fastcall SetWebServiceName(String _name);
};

//---------------------------------------------------------------------------
#endif

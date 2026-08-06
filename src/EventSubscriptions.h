//---------------------------------------------------------------------------

#ifndef EventSubscriptionsH
#define EventSubscriptionsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TEventSubscriptions
 * @brief Класс для хранения подписок на события (md_EventSubscriptions)
 *
 * Подписки на события - это объекты метаданных, которые содержат
 * настройки подписок на различные события системы.
 */
class TEventSubscriptions : public EmptyMetadataObject<TEventSubscriptions>
{
private:
    // eventSubscriptionName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TEventSubscriptions();
    __fastcall TEventSubscriptions(v8catalog* _parent, const String& _guid);
    __fastcall TEventSubscriptions(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени подписки на событие
    String __fastcall GetEventSubscriptionName();
    void __fastcall SetEventSubscriptionName(String _name);
};

#endif

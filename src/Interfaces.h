//---------------------------------------------------------------------------

#ifndef InterfacesH
#define InterfacesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TInterfaces
 * @brief Класс для хранения интерфейсов (md_Interfaces)
 *
 * Интерфейсы - это объекты метаданных, которые содержат
 * интерфейсы конфигурации 1С:Предприятие.
 */
class TInterfaces : public EmptyMetadataObject<TInterfaces>
{
private:
    // interfaceName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TInterfaces();
    __fastcall TInterfaces(v8catalog* _parent, const String& _guid);
    __fastcall TInterfaces(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени интерфейса
    String __fastcall GetInterfaceName();
    void __fastcall SetInterfaceName(String _name);
};

#endif

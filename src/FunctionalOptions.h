//---------------------------------------------------------------------------

#ifndef FunctionalOptionsH
#define FunctionalOptionsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptions
 * @brief Класс для хранения функциональных опций (md_FunctionalOptions)
 *
 * Функциональные опции - это объекты метаданных, которые содержат
 * настройки функциональности системы.
 */
class TFunctionalOptions : public EmptyMetadataObject<TFunctionalOptions>
{
private:
    // name хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TFunctionalOptions();
    __fastcall TFunctionalOptions(v8catalog* _parent, const String& _guid);
    __fastcall TFunctionalOptions(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени функциональной опции
    String __fastcall GetOptionName();
    void __fastcall SetOptionName(String _name);
};

#endif

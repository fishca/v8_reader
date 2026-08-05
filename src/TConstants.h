#ifndef TConstantsH
#define TConstantsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TConstants
 * @brief Класс для хранения констант (md_Constants)
 *
 * Константы - это объекты метаданных, которые содержат
 * постоянные значения, используемые в различных частях конфигурации.
 */
class TConstants : public EmptyMetadataObject<TConstants>
{
public:
    __fastcall TConstants();
    __fastcall TConstants(v8catalog* _parent, const String& _guid);
    __fastcall TConstants(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени константы
    String __fastcall GetConstantsName();
    void __fastcall SetConstantsName(String _name);
};

#endif

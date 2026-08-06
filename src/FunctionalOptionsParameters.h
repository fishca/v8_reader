//---------------------------------------------------------------------------

#ifndef FunctionalOptionsParametersH
#define FunctionalOptionsParametersH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TFunctionalOptionsParameters
 * @brief Класс для хранения параметров функциональных опций (md_FunctionalOptionsParameters)
 *
 * Параметры функциональных опций - это объекты метаданных, которые содержат
 * параметры, доступные для функциональных опций системы.
 */
class TFunctionalOptionsParameters : public EmptyMetadataObject<TFunctionalOptionsParameters>
{
private:
    // name хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TFunctionalOptionsParameters();
    __fastcall TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid);
    __fastcall TFunctionalOptionsParameters(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени параметра функциональной опции
    String __fastcall GetParameterName();
    void __fastcall SetParameterName(String _name);
};

#endif

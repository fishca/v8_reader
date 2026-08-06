//---------------------------------------------------------------------------

#ifndef SessionParametersH
#define SessionParametersH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TSessionParameters
 * @brief Класс для хранения параметров сеанса (md_SessionParameters)
 *
 * Параметры сеанса - это объекты метаданных, которые содержат
 * параметры, доступные в текущем сеансе работы системы.
 */
class TSessionParameters : public EmptyMetadataObject<TSessionParameters>
{
private:
    // parameterName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TSessionParameters();
    __fastcall TSessionParameters(v8catalog* _parent, const String& _guid);
    __fastcall TSessionParameters(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени параметра сеанса
    String __fastcall GetParameterName();
    void __fastcall SetParameterName(String _name);
};

#endif

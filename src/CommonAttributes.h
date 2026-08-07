//---------------------------------------------------------------------------

#ifndef CommonAttributesH
#define CommonAttributesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonAttributes
 * @brief Класс для хранения общих реквизитов (md_CommonAttributes)
 *
 * Общие реквизиты - это объекты метаданных, которые содержат
 * реквизиты, доступные для использования в различных элементах конфигурации.
 */
class TCommonAttributes : public EmptyMetadataObject<TCommonAttributes>
{
private:
    // attributeName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommonAttributes();
    __fastcall TCommonAttributes(v8catalog* _parent, const String& _guid);
    __fastcall TCommonAttributes(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени общего реквизита
    String __fastcall GetAttributeName();
    void __fastcall SetAttributeName(String _name);
};

#endif

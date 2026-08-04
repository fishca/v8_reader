//---------------------------------------------------------------------------

#ifndef CommonTemplatesH
#define CommonTemplatesH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class TCommonTemplates
 * @brief Класс для хранения общих макетов (md_CommonTemplates)
 *
 * Общие макеты - это объекты метаданных, которые содержат
 * макеты, доступные в различных частях конфигурации.
 */
class TCommonTemplates : public EmptyMetadataObject<TCommonTemplates>
{
public:
    __fastcall TCommonTemplates();
    __fastcall TCommonTemplates(v8catalog* _parent, const String& _guid);
    __fastcall TCommonTemplates(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени общего макета
    String __fastcall GetTemplateName();
    void __fastcall SetTemplateName(String _name);
};

#endif

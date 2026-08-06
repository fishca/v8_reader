//---------------------------------------------------------------------------

#ifndef DefinedTypesH
#define DefinedTypesH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TDefinedTypes
 * @brief Класс для хранения определяемых типов (md_DefinedTypes)
 *
 * Определяемые типы - это объекты метаданных, которые содержат
 * пользовательские типы данных, используемые в конфигурации.
 */
class TDefinedTypes : public EmptyMetadataObject<TDefinedTypes>
{
private:
    String typeName;  // Имя определяемого типа

public:
    __fastcall TDefinedTypes();
    __fastcall TDefinedTypes(v8catalog* _parent, const String& _guid);
    __fastcall TDefinedTypes(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени определяемого типа
    String __fastcall GetTypeName();
    void __fastcall SetTypeName(String _name);
};

#endif

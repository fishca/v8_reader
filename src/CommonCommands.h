//---------------------------------------------------------------------------

#ifndef CommonCommandsH
#define CommonCommandsH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class TCommonCommands
 * @brief Класс для хранения общих команд (md_CommonCommands)
 *
 * Общие команды - это объекты метаданных, которые содержат
 * команды, доступные в различных частях конфигурации.
 */
class TCommonCommands : public EmptyMetadataObject<TCommonCommands>
{
public:
    __fastcall TCommonCommands();
    __fastcall TCommonCommands(v8catalog* _parent, const String& _guid);
    __fastcall TCommonCommands(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени общей команды
    String __fastcall GetCommandName();
    void __fastcall SetCommandName(String _name);
};

#endif

//---------------------------------------------------------------------------

#ifndef BotsH
#define BotsH

#include "EmptyMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TBots
 * @brief Класс для хранения ботов (md_Bots)
 *
 * Боты - это объекты метаданных, которые содержат
 * автоматизированные процедуры для взаимодействия с внешними системами.
 */
class TBots : public EmptyMetadataObject<TBots>
{
private:
    String botName;  // Имя бота

public:
    __fastcall TBots();
    __fastcall TBots(v8catalog* _parent, const String& _guid);
    __fastcall TBots(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени бота
    String __fastcall GetBotName();
    void __fastcall SetBotName(String _name);
};

#endif

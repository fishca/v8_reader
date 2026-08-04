//---------------------------------------------------------------------------

#ifndef CommonPicturesH
#define CommonPicturesH

#include "EmptyMetadataObject.h"

//---------------------------------------------------------------------------

/**
 * @class TCommonPictures
 * @brief Класс для хранения общих картинок (md_CommonPictures)
 *
 * Общие картинки - это объекты метаданных, которые содержат
 * картинки, доступные в различных частях конфигурации.
 */
class TCommonPictures : public EmptyMetadataObject<TCommonPictures>
{
public:
    __fastcall TCommonPictures();
    __fastcall TCommonPictures(v8catalog* _parent, const String& _guid);
    __fastcall TCommonPictures(v8catalog* _parent, const String& _guid, const String& _name);

    // Методы для получения имени общей картинки
    String __fastcall GetPictureName();
    void __fastcall SetPictureName(String _name);
};

#endif

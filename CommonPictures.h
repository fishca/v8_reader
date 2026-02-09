//---------------------------------------------------------------------------

#ifndef CommonPicturesH
#define CommonPicturesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

/**
 * @class TCommonPictures
 * @brief Класс для хранения общих картинок (md_CommonPictures)
 *
 * Общие картинки - это объекты метаданных, которые содержат
 * картинки, доступные в различных частях конфигурации.
 */
class TCommonPictures : public BaseMetadataObject
{
private:
    // pictureName хранится в унаследованном поле name из BaseMetadataObject

public:
    __fastcall TCommonPictures();
    __fastcall TCommonPictures(v8catalog* _parent, const String& _guid);
    __fastcall TCommonPictures(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~TCommonPictures();

    // Методы для получения имени общей картинки
    String __fastcall GetPictureName();
    void __fastcall SetPictureName(String _name);

    // Реализация виртуальных методов BaseMetadataObject
    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void __fastcall initializeFromTree() override;

private:
    // Внутренние хранилища для совместимости с интерфейсом
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif

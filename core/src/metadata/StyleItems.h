//---------------------------------------------------------------------------

#ifndef StyleItemsH
#define StyleItemsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TStyleItems : public BaseMetadataObject
{
public:
    TStyleItems();
    TStyleItems(v8catalog* _parent, const Utf16String& _guid);
    TStyleItems(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TStyleItems(v8catalog* _parent, const TStringLike& _guid)
        : TStyleItems(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TStyleItems(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TStyleItems(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TStyleItems();

    Utf16String GetStyleItemName() const;
    void SetStyleItemName(const Utf16String& _name);

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
    std::vector<std::unique_ptr<TComand>>& getCommands() override;
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
    std::vector<std::unique_ptr<TForm1C>>& getForms() override;

    void initializeFromTree() override;

private:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TComand>> commands;
    std::vector<std::unique_ptr<TMoxel>> layouts;
    std::vector<std::unique_ptr<TTabular>> tabularSections;
    std::vector<std::unique_ptr<TForm1C>> forms;
};

#endif


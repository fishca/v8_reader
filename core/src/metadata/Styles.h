//---------------------------------------------------------------------------

#ifndef StylesH
#define StylesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TStyles : public BaseMetadataObject
{
public:
    TStyles();
    TStyles(v8catalog* _parent, const Utf16String& _guid);
    TStyles(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
    template <typename TStringLike>
    TStyles(v8catalog* _parent, const TStringLike& _guid)
        : TStyles(_parent, V8Utf16FromString(_guid)) {}
    template <typename TStringLikeGuid, typename TStringLikeName>
    TStyles(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
        : TStyles(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
    virtual ~TStyles();

    Utf16String GetStyleName() const;
    void SetStyleName(const Utf16String& _name);

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


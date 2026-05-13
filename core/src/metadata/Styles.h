//---------------------------------------------------------------------------

#ifndef StylesH
#define StylesH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TStyles : public BaseMetadataObject
{
private:
    String styleName;

public:
    TStyles();
    TStyles(v8catalog* _parent, const String& _guid);
    TStyles(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TStyles();

    String GetStyleName();
    void SetStyleName(String _name);

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


//---------------------------------------------------------------------------

#ifndef StyleItemsH
#define StyleItemsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TStyleItems : public BaseMetadataObject
{
private:
    String styleItemName;

public:
    TStyleItems();
    TStyleItems(v8catalog* _parent, const String& _guid);
    TStyleItems(v8catalog* _parent, const String& _guid, const String& _name);
    virtual ~TStyleItems();

    String GetStyleItemName();
    void SetStyleItemName(String _name);

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


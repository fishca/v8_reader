//---------------------------------------------------------------------------

#ifndef SubsystemH
#define SubsystemH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TSubsystem : public BaseMetadataObject
{
private:
	// subsystemName С…СЂР°РЅРёС‚СЃСЏ РІ СѓРЅР°СЃР»РµРґРѕРІР°РЅРЅРѕРј РїРѕР»Рµ name РёР· BaseMetadataObject

public:
	TSubsystem();
	TSubsystem(v8catalog* _parent, const String& _guid);
	TSubsystem(v8catalog* _parent, const String& _guid, const String& _name);
	virtual ~TSubsystem();

	String GetSubsystemName();
	void SetSubsystemName(String _name);

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

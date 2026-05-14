//---------------------------------------------------------------------------

#ifndef ChartOfCharacteristicTypesH
#define ChartOfCharacteristicTypesH
//---------------------------------------------------------------------------
#include <vector>
#include "../APIcfBase.h"
#include "Parse_tree.h"
#include "BaseMetadataObject.h"

//---------------------------------------------------------------------------
class TChartOfCharacteristicTypes : public BaseMetadataObject
{
private:
	std::vector<std::unique_ptr<TRequisite>> attributes; // список реквизитов
	std::vector<std::unique_ptr<TComand>> comands;       // список команд
	std::vector<std::unique_ptr<TMoxel>> moxels;         // список макетов
	std::vector<std::unique_ptr<TTabular>> tabulars;     // список табличных частей
	std::vector<std::unique_ptr<TForm1C>> forms;         // список форм

public:
	/* TODO : Реализовать класс */
	TChartOfCharacteristicTypes();
	TChartOfCharacteristicTypes(v8catalog *_parent, const Utf16String& _guid);
	TChartOfCharacteristicTypes(v8catalog *_parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TChartOfCharacteristicTypes(v8catalog *_parent, const TStringLike& _guid)
		: TChartOfCharacteristicTypes(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TChartOfCharacteristicTypes(v8catalog *_parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TChartOfCharacteristicTypes(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	~TChartOfCharacteristicTypes();

	// Реализация виртуальных методов
	virtual std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
	virtual std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
	virtual std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
	virtual std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
	virtual std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	virtual void initializeFromTree() override;

	void SetName();
	void SetGUID();
};

#endif


//---------------------------------------------------------------------------

#ifndef LangsH
#define LangsH

#include "BaseMetadataObject.h"
//---------------------------------------------------------------------------

class TLangs : public BaseMetadataObject
{
private:
	// interfaceName хранится в унаследованном поле name из BaseMetadataObject

public:
	TLangs();
	TLangs(v8catalog* _parent, const Utf16String& _guid);
	TLangs(v8catalog* _parent, const Utf16String& _guid, const Utf16String& _name);
	template <typename TStringLike>
	TLangs(v8catalog* _parent, const TStringLike& _guid)
		: TLangs(_parent, V8Utf16FromString(_guid)) {}
	template <typename TStringLikeGuid, typename TStringLikeName>
	TLangs(v8catalog* _parent, const TStringLikeGuid& _guid, const TStringLikeName& _name)
		: TLangs(_parent, V8Utf16FromString(_guid), V8Utf16FromString(_name)) {}
	virtual ~TLangs();

	// Методы для получения имени интерфейса
	Utf16String GetLangName() const;
	void SetLangName(const Utf16String& _name);

	// Реализация виртуальных методов BaseMetadataObject
	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override;
	std::vector<std::unique_ptr<TComand>>& getCommands() override;
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override;
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override;
	std::vector<std::unique_ptr<TForm1C>>& getForms() override;

	void initializeFromTree() override;

private:
	// Внутренние хранилища для совместимости с интерфейсом
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;
};


#endif


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
	__fastcall TLangs();
	__fastcall TLangs(v8catalog* _parent, const String& _guid);
	__fastcall TLangs(v8catalog* _parent, const String& _guid, const String& _name);
	virtual __fastcall ~TLangs();

	// Методы для получения имени интерфейса
	String __fastcall GetLangName();
	void __fastcall SetLangName(String _name);

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

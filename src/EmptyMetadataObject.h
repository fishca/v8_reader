//---------------------------------------------------------------------------

#ifndef EmptyMetadataObjectH
#define EmptyMetadataObjectH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include <vector>
#include <memory>
#include "Requisite.h"
#include "Comand.h"
#include "Moxel.h"
#include "Tabular.h"
#include "Form.h"

//---------------------------------------------------------------------------
// Шаблон для объектов метаданных без собственной логики парсинга.
// Наследует BaseMetadataObject и предоставляет 5 векторов-членов + 5 геттеров.
// Используется для: веб-сервисов, макетов, картинок, команд и прочих "пустых" обёрток.
template<typename Derived>
class EmptyMetadataObject : public BaseMetadataObject
{
protected:
	std::vector<std::unique_ptr<TRequisite>> attributes;
	std::vector<std::unique_ptr<TComand>> commands;
	std::vector<std::unique_ptr<TMoxel>> layouts;
	std::vector<std::unique_ptr<TTabular>> tabularSections;
	std::vector<std::unique_ptr<TForm1C>> forms;

public:
	__fastcall EmptyMetadataObject() : BaseMetadataObject() {}
	__fastcall EmptyMetadataObject(v8catalog* _parent, const String& _guid) : BaseMetadataObject(_parent, _guid) {}
	__fastcall EmptyMetadataObject(v8catalog* _parent, const String& _guid, const String& _name) : BaseMetadataObject(_parent, _guid, _name) {}
	virtual __fastcall ~EmptyMetadataObject() {}

	std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
	std::vector<std::unique_ptr<TComand>>& getCommands() override { return commands; }
	std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return layouts; }
	std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabularSections; }
	std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

	void __fastcall initializeFromTree() override {}
};

//---------------------------------------------------------------------------
#endif

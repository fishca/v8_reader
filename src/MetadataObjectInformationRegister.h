//---------------------------------------------------------------------------

#ifndef MetadataObjectInformationRegisterH
#define MetadataObjectInformationRegisterH
//---------------------------------------------------------------------------

#include "BaseMetadataObject.h"
#include "Common.h"
#include <functional>

//---------------------------------------------------------------------------
// Конфигурация путей в дереве парсинга для регистров сведений
struct InfoRegisterTreePaths
{
    int attIdx;
    std::vector<int> attItemPath;
    int dimIdx;           // индекс для измерений
    std::vector<int> dimItemPath;
    int resIdx;           // индекс для ресурсов
    std::vector<int> resItemPath;
    int formsIdx;
    int cmdIdx;
    std::vector<int> cmdItemPath;
    int moxIdx;
    std::function<String(v8catalog*, String&)> getFormNameFunc;
};

//---------------------------------------------------------------------------
// Базовый класс для регистров сведений: реквизиты, измерения, ресурсы, формы, команды, макеты
// Табличных частей нет
class MetadataObjectInformationRegister : public BaseMetadataObject
{
protected:
    std::vector<std::unique_ptr<TRequisite>> attributes;
    std::vector<std::unique_ptr<TRequisite>> dimensions;   // измерения
    std::vector<std::unique_ptr<TRequisite>> resources;    // ресурсы
    std::vector<std::unique_ptr<TComand>> comands;
    std::vector<std::unique_ptr<TMoxel>> moxels;
    std::vector<std::unique_ptr<TForm1C>> forms;
    std::vector<std::unique_ptr<TTabular>> tabulars;       // пустой, для совместимости с BaseMetadataObject

    void initializeFromTreeWithPaths(const InfoRegisterTreePaths& paths);

public:
    __fastcall MetadataObjectInformationRegister();
    __fastcall MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid);
    __fastcall MetadataObjectInformationRegister(v8catalog* _parent, const String& _guid, const String& _name);
    virtual __fastcall ~MetadataObjectInformationRegister();

    std::vector<std::unique_ptr<TRequisite>>& getAttributes() override { return attributes; }
    std::vector<std::unique_ptr<TComand>>& getCommands() override { return comands; }
    std::vector<std::unique_ptr<TMoxel>>& getLayouts() override { return moxels; }
    std::vector<std::unique_ptr<TTabular>>& getTabularSections() override { return tabulars; }
    std::vector<std::unique_ptr<TForm1C>>& getForms() override { return forms; }

    std::vector<std::unique_ptr<TRequisite>>& getDimensions() { return dimensions; }
	std::vector<std::unique_ptr<TRequisite>>& getResources() { return resources; }
};

//---------------------------------------------------------------------------
// CRTP-шаблон: наследник передает свою функцию GetPaths через параметр шаблона
template<typename Derived, InfoRegisterTreePaths (*GetPathsFunc)()>
class MetadataObjectInformationRegisterT : public MetadataObjectInformationRegister
{
public:
	__fastcall MetadataObjectInformationRegisterT() : MetadataObjectInformationRegister() {}
	__fastcall MetadataObjectInformationRegisterT(v8catalog* _parent, const String& _guid) : MetadataObjectInformationRegister(_parent, _guid) {}
	__fastcall MetadataObjectInformationRegisterT(v8catalog* _parent, const String& _guid, const String& _name) : MetadataObjectInformationRegister(_parent, _guid, _name) {}
	virtual __fastcall ~MetadataObjectInformationRegisterT() {}

	void __fastcall initializeFromTree() override
	{
		MetadataObjectInformationRegister::initializeFromTreeWithPaths(GetPathsFunc());
	}
};

//---------------------------------------------------------------------------
#endif

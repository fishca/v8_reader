//---------------------------------------------------------------------------

#ifndef TabularH
#define TabularH

#include <vcl.h>
#include <memory>
#include <vector>

#include "MDO.h"
#include "Parse_tree.h"
#include "Requisite.h"

//---------------------------------------------------------------------------
class TTabular : public TMDO
{
public:
	std::vector<std::unique_ptr<TRequisite>> attributes;

	__fastcall TTabular();
	__fastcall TTabular(String _name, String _guid);
	__fastcall ~TTabular();

	void __fastcall initializeFromTree(tree* root);
};
#endif

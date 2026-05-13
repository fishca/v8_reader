//---------------------------------------------------------------------------

#ifndef TabularH
#define TabularH

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

	TTabular();
	TTabular(String _name, String _guid);
	~TTabular();

	void initializeFromTree(tree* root);
};
#endif


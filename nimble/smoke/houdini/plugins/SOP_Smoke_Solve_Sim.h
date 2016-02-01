#ifndef __SOP_Smoke_Solve_Sim_h__
#define __SOP_Smoke_Solve_Sim_h__

#include <SOP/SOP_Node.h>

#include <smoke/lib/core/SimData.h>
#include <smoke/houdini/adapters/SolveSimAdapter.h>

namespace HDK_Sample
{
	class SOP_Smoke_Solve_Sim : public SOP_Node
	{
	public:
		SOP_Smoke_Solve_Sim(OP_Network *net, const char *name, OP_Operator *op);
		virtual ~SOP_Smoke_Solve_Sim();
		static PRM_Template myTemplateList[];
		static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
	protected:
		virtual const char *inputLabel(unsigned idx) const;
		virtual OP_ERROR cookMySop(OP_Context &context);
	private:
		fpreal myLastCookTime;	// Last cooked time
		smoke::core::SimData* simDataPtr;
	};
} // End HDK_Sample namespace
#endif

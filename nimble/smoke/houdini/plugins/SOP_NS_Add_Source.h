#ifndef __SOP_Solid_Create_Sim_h__
#define __SOP_Solid_Create_Sim_h__

#include <SOP/SOP_Node.h>

class SOP_NS_Add_Source: public SOP_Node
{
public:
	SOP_NS_Add_Source(OP_Network *net, const char *name,
			OP_Operator *op);
	virtual ~SOP_NS_Add_Source();
	static PRM_Template myTemplateList[];
	static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
protected:
	void initSystem();
	virtual OP_ERROR cookMySop(OP_Context &context);
};
#endif

#ifndef __SOP_Solid_Create_Sim_h__
#define __SOP_Solid_Create_Sim_h__

#include <SOP/SOP_Node.h>

#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);

class SOP_OpenVDB_Test_A: public SOP_Node
{
public:
	SOP_OpenVDB_Test_A(OP_Network *net, const char *name,
			OP_Operator *op);
	virtual ~SOP_OpenVDB_Test_A();
	static PRM_Template myTemplateList[];
	static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
protected:
	void initSystem();
	virtual OP_ERROR cookMySop(OP_Context &context);
private:
	int RESET()
	{
		return evalInt("reset", 0, 0);
	}
	int SUBSTEPS()
	{
		return evalInt("subSteps", 0, 0);
	}
	int MAX_SUBSTEPS()
	{
		return evalInt("maxSubSteps", 0, 0);
	}
	float SIM_TIME_SCALE()
	{
		return evalFloat("sim_time_scale", 0, 0);
	}
	float COLLISION_TOLERANCE()
	{
		return evalFloat("collision_tolerance", 0, 0);
	}
	fpreal myLastCookTime;	// Last cooked time
	static int *myOffsets;
};
#endif

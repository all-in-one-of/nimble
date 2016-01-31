#include "SOP_NS_Create_Sim.h"

#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>
#include <openvdb/openvdb.h>
#include <GU/GU_PrimVDB.h>
#include <smoke/houdini/utils/BlindDataManager.h>

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("ns_create_sim", "NS Create Sim",
					SOP_NS_Create_Sim::myConstructor,
					SOP_NS_Create_Sim::myTemplateList, 0, // Min required sources
					1,	// Maximum sources
					0));
}

static PRM_Name names[] =
{ PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name(
		"maxSubSteps", "Max Sub Steps"), PRM_Name("sim_time_scale",
		"Simulation Time Scale"), PRM_Name("collision_tolerance",
		"Collision Tolerance") };

static PRM_Default defaultSubSteps(1);
static PRM_Default defaultMaxSubSteps(200);
static PRM_Default defaultCollTolerance(0.01);

PRM_Template SOP_NS_Create_Sim::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J,
		1, &names[1], &defaultSubSteps), PRM_Template(PRM_INT_J, 1, &names[2],
		&defaultMaxSubSteps), PRM_Template(PRM_FLT, 1, &names[3],
		PRMoneDefaults), PRM_Template(PRM_FLT, 1, &names[4],
		&defaultCollTolerance), PRM_Template(), };

int * SOP_NS_Create_Sim::myOffsets = 0;

OP_Node *
SOP_NS_Create_Sim::myConstructor(OP_Network *net, const char *name,
		OP_Operator *op)
{
	return new SOP_NS_Create_Sim(net, name, op);
}

SOP_NS_Create_Sim::SOP_NS_Create_Sim(OP_Network *net, const char *name,
		OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_NS_Create_Sim::~SOP_NS_Create_Sim()
{
}

void SOP_NS_Create_Sim::initSystem()
{
	smoke::houdini::utils::BlindDataManager blindDataManager;
	gdp->clearAndDestroy();
	delete simDataPtr;

	const GU_Detail* bboxGdp = inputGeo(0);
	UT_BoundingBox bbox;
	bboxGdp->getBBox(&bbox);
	double voxel_size = 0.05;
	openvdb::CoordBBox bbox2(
			openvdb::Coord(bbox.minvec().x(), bbox.minvec().y(),
					bbox.minvec().z()),
			openvdb::Coord(bbox.maxvec().x(), bbox.maxvec().y(),
					bbox.maxvec().z()));
	simDataPtr = new smoke::core::SimData(bbox2, voxel_size);

	blindDataManager.insertSimDataPtr(gdp, simDataPtr);
	GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, simDataPtr->getDensityPtr(),
	NULL, "density");
}

OP_ERROR SOP_NS_Create_Sim::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	fpreal reset, currframe;
	CH_Manager *chman;
	OP_Node::flags().timeDep = 1;
	chman = OPgetDirector()->getChannelManager();
	currframe = chman->getSample(context.getTime());
	reset = RESET();
	if (currframe <= reset)
	{
		myLastCookTime = reset;
		initSystem();
	}

	return error();
}

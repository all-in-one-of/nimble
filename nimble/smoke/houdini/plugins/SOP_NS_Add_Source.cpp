#include "SOP_NS_Add_Source.h"

#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>
#include <openvdb/openvdb.h>
#include <openvdb/tools/Composite.h>
#include <openvdb/tools/GridTransformer.h>
#include <GU/GU_PrimVDB.h>

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("ns_add_source", "NS Add Source",
					SOP_NS_Add_Source::myConstructor,
					SOP_NS_Add_Source::myTemplateList, 2, // Min required sources
					2,	// Maximum sources
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

PRM_Template SOP_NS_Add_Source::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J,
		1, &names[1], &defaultSubSteps), PRM_Template(PRM_INT_J, 1, &names[2],
		&defaultMaxSubSteps), PRM_Template(PRM_FLT, 1, &names[3],
		PRMoneDefaults), PRM_Template(PRM_FLT, 1, &names[4],
		&defaultCollTolerance), PRM_Template(), };

int * SOP_NS_Add_Source::myOffsets = 0;

OP_Node *
SOP_NS_Add_Source::myConstructor(OP_Network *net, const char *name,
		OP_Operator *op)
{
	return new SOP_NS_Add_Source(net, name, op);
}

SOP_NS_Add_Source::SOP_NS_Add_Source(OP_Network *net, const char *name,
		OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_NS_Add_Source::~SOP_NS_Add_Source()
{
}

void SOP_NS_Add_Source::initSystem()
{
}

OP_ERROR SOP_NS_Add_Source::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	openvdb::initialize();

	duplicateSource(0, context);
	const GU_Detail* gdpB = inputGeo(1);

	GU_PrimVDB* vdb = (GU_PrimVDB*) gdp->getGEOPrimitiveByIndex(0);
	openvdb::GridBase::Ptr gridBaseA = vdb->getGridPtr();
	openvdb::FloatGrid::Ptr gridA = openvdb::gridPtrCast<openvdb::FloatGrid>(
			gridBaseA);
	openvdb::FloatGrid::Ptr copyOfGridA = gridA->deepCopy();
//	vdb->setGrid(*copyOfGridA);

	GU_PrimVDB* srcVdb = (GU_PrimVDB*) gdpB->getGEOPrimitiveByIndex(0);
	openvdb::GridBase::Ptr gridBaseB = srcVdb->getGridPtr();
	openvdb::FloatGrid::Ptr sourceGridB = openvdb::gridPtrCast<openvdb::FloatGrid>(
			gridBaseB);

	openvdb::FloatGrid::Ptr targetGridB = copyOfGridA->deepCopy();

		const openvdb::math::Transform
		    &sourceXform = sourceGridB->transform(),
		    &targetXform = targetGridB->transform();
		openvdb::Mat4R xform =
		    sourceXform.baseMap()->getAffineMap()->getMat4() *
		    targetXform.baseMap()->getAffineMap()->getMat4().inverse();
		openvdb::tools::GridTransformer transformer(xform);
		transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
		    *sourceGridB, *targetGridB);

//		openvdb::tools::compMax(*copyOfGridA, *targetGridB);
		openvdb::tools::compMax(*gridA, *targetGridB);

	return error();
}

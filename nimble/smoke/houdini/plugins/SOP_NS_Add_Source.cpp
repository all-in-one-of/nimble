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
#include <smoke/houdini/adapters/AddSourceAdapter.h>
#include <smoke/houdini/utils/BlindDataManager.h>

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("ns_add_source", "NS Add Source", SOP_NS_Add_Source::myConstructor,
					SOP_NS_Add_Source::myTemplateList, 2, // Min required sources
					2,	// Maximum sources
					0));
}

PRM_Template SOP_NS_Add_Source::myTemplateList[] =
{ PRM_Template(), };

OP_Node *
SOP_NS_Add_Source::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_NS_Add_Source(net, name, op);
}

SOP_NS_Add_Source::SOP_NS_Add_Source(OP_Network *net, const char *name, OP_Operator *op) :
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

	duplicateSource(0, context);
	const GU_Detail* gdpB = inputGeo(1);

	GU_PrimVDB* srcVdbDensity = (GU_PrimVDB*) gdpB->getGEOPrimitiveByIndex(0);
	openvdb::GridBase::Ptr gridBaseDensityB = srcVdbDensity->getGridPtr();
	openvdb::FloatGrid::Ptr sourceGridDensityB = openvdb::gridPtrCast<openvdb::FloatGrid>(gridBaseDensityB);

	GU_PrimVDB* srcVdbVelocity = (GU_PrimVDB*) gdpB->getGEOPrimitiveByIndex(1);
	openvdb::GridBase::Ptr gridBaseVelocityB = srcVdbVelocity->getGridPtr();
	openvdb::VectorGrid::Ptr sourceGridVelocityB = openvdb::gridPtrCast<openvdb::VectorGrid>(gridBaseVelocityB);

	smoke::houdini::utils::BlindDataManager blindDataManager;
	smoke::core::SimData* simDataPtr = blindDataManager.extractSimDataPtr(gdp);

	smoke::houdini::adapters::AddSourceAdapter adapter;
	adapter.addFloatSource(simDataPtr, sourceGridDensityB);
	adapter.addVectorSource(simDataPtr, sourceGridVelocityB);

	return error();
}

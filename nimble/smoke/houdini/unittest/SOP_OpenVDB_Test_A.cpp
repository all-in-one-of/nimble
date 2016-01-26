#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>
#include <openvdb/openvdb.h>
#include <openvdb/tools/GridTransformer.h>
#include <GU/GU_PrimVDB.h>
#include "SOP_OpenVDB_Test_A.h"

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("openvdb_test_a",
					"OpenVDB Test A", SOP_OpenVDB_Test_A::myConstructor,
					SOP_OpenVDB_Test_A::myTemplateList, 0, // Min required sources
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

PRM_Template SOP_OpenVDB_Test_A::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J,
		1, &names[1], &defaultSubSteps), PRM_Template(PRM_INT_J, 1, &names[2],
		&defaultMaxSubSteps), PRM_Template(PRM_FLT, 1, &names[3],
		PRMoneDefaults), PRM_Template(PRM_FLT, 1, &names[4],
		&defaultCollTolerance), PRM_Template(), };

int * SOP_OpenVDB_Test_A::myOffsets = 0;

OP_Node *
SOP_OpenVDB_Test_A::myConstructor(OP_Network *net, const char *name,
		OP_Operator *op)
{
	return new SOP_OpenVDB_Test_A(net, name, op);
}

SOP_OpenVDB_Test_A::SOP_OpenVDB_Test_A(OP_Network *net, const char *name,
		OP_Operator *op) :
		SOP_Node(net, name, op)
{
}

SOP_OpenVDB_Test_A::~SOP_OpenVDB_Test_A()
{
}

void SOP_OpenVDB_Test_A::initSystem()
{
}

OP_ERROR SOP_OpenVDB_Test_A::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
	if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	openvdb::initialize();

	openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create();

	GU_PrimVDB* vdb = GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, grid, NULL,
			"gridName");

	const GU_Detail* bboxGdp = inputGeo(0);
	UT_BoundingBox bbox;
	bboxGdp->getBBox(&bbox);
	UT_Vector3 min = bbox.minvec();
	openvdb::Coord min1(min.x(), min.y(), min.z());
	UT_Vector3 max = bbox.maxvec();
	openvdb::Coord max1(max.x(), max.y(), max.z());

    openvdb::CoordBBox bbox1(min1,max1);
    grid->fill(bbox1,1,1);
    openvdb::FloatGrid::Ptr srcGrid = grid->deepCopy();

    openvdb::math::Mat4d mat = openvdb::math::Mat4d::identity();
    openvdb::math::Transform::Ptr linearTransform =
        openvdb::math::Transform::createLinearTransform(mat);
    // Rotate the transform by 90 degrees about the X axis.
    // As a result the j-index will now map into the -z physical direction,
    // and the k-index will map to the +y physical direction.
    linearTransform->preRotate(M_PI/4, openvdb::math::Y_AXIS);
//    grid->setTransform(linearTransform);

//    openvdb::math::Transform& xform = grid->transform();
//    xform.postTranslate(openvdb::math::Vec3d(100,0,0));

    openvdb::tools::GridTransformer transformer(linearTransform->baseMap()->getAffineMap()->getMat4());
    // Resample using nearest-neighbor interpolation.
    transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
        *srcGrid, *grid);

	return error();
}

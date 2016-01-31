#include <UT/UT_DSOVersion.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <OP/OP_AutoLockInputs.h>
#include <iostream>
#include <openvdb/openvdb.h>
#include <openvdb/tools/GridTransformer.h>
#include <openvdb/tools/Composite.h>
#include <GU/GU_PrimVDB.h>
#include "SOP_OpenVDB_Test_A.h"

void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("openvdb_test_a", "OpenVDB Test A",
					SOP_OpenVDB_Test_A::myConstructor,
					SOP_OpenVDB_Test_A::myTemplateList, 0, // Min required sources
					0,	// Maximum sources
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

	//------------Grid 1----------------
//	openvdb::FloatGrid::Ptr grid1 = openvdb::FloatGrid::create();
//	grid1->setTransform(openvdb::math::Transform::createLinearTransform(0.1));
//	grid1->fill(
//			openvdb::CoordBBox(openvdb::Coord(-1, -1, -1),
//					openvdb::Coord(1, 1, 1)), 1, 1);
//
//	GU_PrimVDB* vdb1 = GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, grid1, NULL,
//			"grid1");
//	UT_Matrix4 mat1 = UT_Matrix4::getIdentityMatrix();
//	mat1.rotate(UT_Axis3::YAXIS, 45);
//	mat1.translate(4, 0, 0);
//	vdb1->setTransform4(mat1);
	//------------Grid 1----------------

	//------------Grid 2----------------
//	openvdb::FloatGrid::Ptr grid2 = openvdb::FloatGrid::create();
//	grid2->setTransform(openvdb::math::Transform::createLinearTransform(0.1));
//	grid2->fill(
//			openvdb::CoordBBox(openvdb::Coord(-1, -1, -1),
//					openvdb::Coord(1, 1, 1)), 1, 1);
//
//	GU_PrimVDB* vdb2 = GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, grid2, NULL,
//			"grid2");
//    openvdb::FloatGrid::Ptr srcGrid2 = grid2->deepCopy();
//
//    openvdb::math::Mat4d mat = openvdb::math::Mat4d::identity();
//    openvdb::math::Transform::Ptr linearTransform =
//        openvdb::math::Transform::createLinearTransform(mat);
//    linearTransform->preRotate(M_PI/4, openvdb::math::Y_AXIS);
//
//    openvdb::tools::GridTransformer transformer(linearTransform->baseMap()->getAffineMap()->getMat4());
//    transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
//        *srcGrid2, *grid2);
	//------------Grid 2----------------

	//------------Grid 3----------------
//	openvdb::FloatGrid::Ptr grid3A = openvdb::FloatGrid::create();
//	grid3A->fill(
//			openvdb::CoordBBox(openvdb::Coord(-1, -1, -1),
//					openvdb::Coord(1, 1, 1)), 1, 1);
//
//	openvdb::FloatGrid::Ptr grid3B = openvdb::FloatGrid::create();
//	grid3B->fill(
//			openvdb::CoordBBox(openvdb::Coord(1, 1, 1),
//					openvdb::Coord(3, 3, 3)), 1, 1);
//
//	openvdb::tools::compSum(*grid3A, *grid3B);
//	GU_PrimVDB* vdb3 = GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, grid3A,
//			NULL, "grid3");
	//------------Grid 3----------------

	//------------Grid 4----------------
	//------------Recipe for composition of two grids with different transforms.
	openvdb::FloatGrid::Ptr grid4A = openvdb::FloatGrid::create();
	grid4A->fill(
			openvdb::CoordBBox(openvdb::Coord(-10, -10, -10),
					openvdb::Coord(10, 10, 10)), 1, 1);
	openvdb::math::Transform::Ptr linearTransform4A =
			openvdb::math::Transform::createLinearTransform(1);
	linearTransform4A->postScale(0.1);
	linearTransform4A->postRotate(M_PI / 4, openvdb::math::Y_AXIS);
	linearTransform4A->postTranslate(openvdb::math::Vec3d(5, 0, 0));
	grid4A->setTransform(linearTransform4A);

	openvdb::FloatGrid::Ptr sourceGrid4B = openvdb::FloatGrid::create();
	sourceGrid4B->fill(
			openvdb::CoordBBox(openvdb::Coord(-10, -10, -10),
					openvdb::Coord(10, 10, 10)), 1, 1);
	openvdb::math::Transform::Ptr linearTransform4B =
			openvdb::math::Transform::createLinearTransform(1);
	linearTransform4B->postScale(0.1);
	linearTransform4B->postRotate(M_PI / 4, openvdb::math::Y_AXIS);
	linearTransform4B->postTranslate(openvdb::math::Vec3d(0, 0, 5));
	sourceGrid4B->setTransform(linearTransform4B);

	openvdb::FloatGrid::Ptr targetGrid4B = grid4A->deepCopy();

	const openvdb::math::Transform
	    &sourceXform = sourceGrid4B->transform(),
	    &targetXform = targetGrid4B->transform();
	openvdb::Mat4R xform =
	    sourceXform.baseMap()->getAffineMap()->getMat4() *
	    targetXform.baseMap()->getAffineMap()->getMat4().inverse();
	openvdb::tools::GridTransformer transformer(xform);
	transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
	    *sourceGrid4B, *targetGrid4B);

	openvdb::tools::compSum(*grid4A, *targetGrid4B);
	GU_PrimVDB::buildFromGrid((GU_Detail&) *gdp, grid4A,
	NULL, "grid4");
	//------------Grid 4----------------

	return error();
}

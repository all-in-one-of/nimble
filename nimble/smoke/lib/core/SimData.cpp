/*
 * SimData.cpp
 *
 *  Created on: 28-Jan-2016
 *      Author: user
 */

#include <smoke/lib/core/SimData.h>

namespace smoke
{
namespace core
{
SimData::SimData(openvdb::CoordBBox bbox, smoke::core::Scalar voxelSize, Scalar resetFrame,
		Scalar subSteps, Scalar maxSubSteps, Scalar simulationTimeScale) :
		resetFrame(resetFrame), subSteps(subSteps), maxSubSteps(maxSubSteps), simulationTimeScale(
				simulationTimeScale)
{
	openvdb::initialize();
	densityPtr = openvdb::FloatGrid::create();
	temperaturePtr = openvdb::FloatGrid::create();
	velocityPtr = openvdb::VectorGrid::create();

	openvdb::Coord min1(bbox.min().x() / voxelSize, bbox.min().y() / voxelSize,
			bbox.min().z() / voxelSize);
	openvdb::Coord max1(bbox.max().x() / voxelSize, bbox.max().y() / voxelSize,
			bbox.max().z() / voxelSize);

	openvdb::CoordBBox bbox1(min1, max1);
	densityPtr->fill(bbox1, 0.0, 1);
	temperaturePtr->fill(bbox1, 0.0, 1);
	velocityPtr->fill(bbox1, openvdb::math::Vec3<float>(0, 0, 0), 1);

	openvdb::math::Transform::Ptr linearTransform = openvdb::math::Transform::createLinearTransform(
			1);
	linearTransform->postScale(voxelSize);
	densityPtr->setTransform(linearTransform);
	temperaturePtr->setTransform(linearTransform);
	velocityPtr->setTransform(linearTransform);

//	resetFrame = 1;
//	subSteps = 1;
//	maxSubSteps = 10;
//	simulationTimeScale = 1;
}

SimData::~SimData()
{
}

}
}

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
SimData::SimData(openvdb::CoordBBox bbox, smoke::core::Scalar voxelSize)
{
	openvdb::initialize();
	densityPtr = openvdb::FloatGrid::create();

	openvdb::Coord min1(bbox.min().x() / voxelSize, bbox.min().y() / voxelSize,
			bbox.min().z() / voxelSize);
	openvdb::Coord max1(bbox.max().x() / voxelSize, bbox.max().y() / voxelSize,
			bbox.max().z() / voxelSize);

	openvdb::CoordBBox bbox1(min1, max1);
	densityPtr->fill(bbox1, 0.0, 1);
	openvdb::math::Transform::Ptr linearTransform =
			openvdb::math::Transform::createLinearTransform(1);
	linearTransform->postScale(voxelSize);
	densityPtr->setTransform(linearTransform);

	subSteps = 1;
	resetFrame = 1;
	maxSubSteps = 10;
	simulationTimeScale = 1;
}

SimData::~SimData()
{
}

const openvdb::FloatGrid::Ptr& SimData::getDensityPtr() const
{
	return densityPtr;
}

void SimData::setDensityPtr(const openvdb::FloatGrid::Ptr& densityGridPtr)
{
	this->densityPtr = densityGridPtr;
}
}
}

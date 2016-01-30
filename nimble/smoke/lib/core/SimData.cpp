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
SimData::SimData()
{
	openvdb::initialize();
	densityGridPtr = openvdb::FloatGrid::create();
}

SimData::~SimData()
{
	// TODO Auto-generated destructor stub
}

const openvdb::FloatGrid::Ptr& SimData::getDensityGridPtr() const
{
	return densityGridPtr;
}

void SimData::setDensityGridPtr(const openvdb::FloatGrid::Ptr& densityGridPtr)
{
	this->densityGridPtr = densityGridPtr;
}
}
}

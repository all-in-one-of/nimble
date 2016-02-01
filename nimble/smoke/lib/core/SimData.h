/*
 * SimData.h
 *
 *  Created on: 28-Jan-2016
 *      Author: user
 */

#ifndef SMOKE_LIB_CORE_SIMDATA_H_
#define SMOKE_LIB_CORE_SIMDATA_H_

#include <openvdb/openvdb.h>
#include <smoke/lib/core/CommonTypes.h>
#include <smoke/lib/sources/VdbSource.h>

namespace smoke
{
namespace core
{
class SimData
{
public:
	SimData(openvdb::CoordBBox bbox, smoke::core::Scalar voxelSize, Scalar resetFrame,
			Scalar subSteps, Scalar maxSubSteps, Scalar simulationTimeScale);
	virtual ~SimData();
	const openvdb::FloatGrid::Ptr& getDensityPtr() const
	{
		return densityPtr;
	}
	void setDensityPtr(const openvdb::FloatGrid::Ptr& densityPtr)
	{
		this->densityPtr = densityPtr;
	}
	const openvdb::FloatGrid::Ptr& getTemperaturePtr() const
	{
		return temperaturePtr;
	}
	void setTemperaturePtr(const openvdb::FloatGrid::Ptr& temperaturePtr)
	{
		this->temperaturePtr = temperaturePtr;
	}
	const openvdb::VectorGrid::Ptr& getVelocityPtr() const
	{
		return velocityPtr;
	}
	void setVelocityPtr(const openvdb::VectorGrid::Ptr& velocityPtr)
	{
		this->velocityPtr = velocityPtr;
	}
	Scalar getResetFrame() const
	{
		return resetFrame;
	}

	Scalar getSimulationTimeScale() const
	{
		return simulationTimeScale;
	}

	Scalar getSubSteps() const
	{
		return subSteps;
	}

	Scalar getMaxSubSteps() const
	{
		return maxSubSteps;
	}

	void setMaxSubSteps(Scalar maxSubSteps)
	{
		this->maxSubSteps = maxSubSteps;
	}

	std::vector<smoke::sources::VdbSource*> sources;
private:
	openvdb::FloatGrid::Ptr densityPtr;
	openvdb::FloatGrid::Ptr temperaturePtr;
	openvdb::VectorGrid::Ptr velocityPtr;
	Scalar resetFrame;
	Scalar subSteps;
	Scalar maxSubSteps;
	Scalar simulationTimeScale;
};
}
}

#endif /* SMOKE_LIB_CORE_SIMDATA_H_ */

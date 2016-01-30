/*
 * SimData.h
 *
 *  Created on: 28-Jan-2016
 *      Author: user
 */

#ifndef SMOKE_LIB_CORE_SIMDATA_H_
#define SMOKE_LIB_CORE_SIMDATA_H_

#include <openvdb/openvdb.h>

namespace smoke
{
namespace core
{
class SimData
{
public:
	SimData();
	virtual ~SimData();
	const openvdb::FloatGrid::Ptr& getDensityGridPtr() const;
	void setDensityGridPtr(const openvdb::FloatGrid::Ptr& densityGridPtr);

private:
	openvdb::FloatGrid::Ptr densityGridPtr;
};
}
}

#endif /* SMOKE_LIB_CORE_SIMDATA_H_ */

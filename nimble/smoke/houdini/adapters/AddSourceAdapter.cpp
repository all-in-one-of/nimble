/*
 * AddSourceAdapter.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#include <smoke/houdini/adapters/AddSourceAdapter.h>
#include <smoke/lib/sources/VdbFloatSource.h>
#include <smoke/lib/sources/VdbVectorSource.h>

namespace smoke
{
namespace houdini
{
namespace adapters
{

AddSourceAdapter::AddSourceAdapter()
{
//	smoke::sources::VdbVectorSource* velocity_src = new smoke::sources::VdbVectorSource(grid);
}

AddSourceAdapter::~AddSourceAdapter()
{
	// TODO Auto-generated destructor stub
}

void AddSourceAdapter::addFloatSource(smoke::core::SimData* simDataPtr,
		smoke::core::FloatGridPtr grid)
{
	smoke::sources::VdbFloatSource* density_src = new smoke::sources::VdbFloatSource(grid);
	simDataPtr->density_sources.push_back(density_src);
	smoke::sources::VdbFloatSource* temperature_src = new smoke::sources::VdbFloatSource(grid);
	simDataPtr->temperature_sources.push_back(temperature_src);
}

void AddSourceAdapter::addVectorSource(smoke::core::SimData* simDataPtr,
		smoke::core::VectorGridPtr grid)
{
	smoke::sources::VdbVectorSource* velocity_src = new smoke::sources::VdbVectorSource(grid);
	simDataPtr->velocity_sources.push_back(velocity_src);
}

} /* namespace adapters */
} /* namespace houdini */
} /* namespace smoke */

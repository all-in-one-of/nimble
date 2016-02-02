/*
 * AddSourceAdapter.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#include <smoke/houdini/adapters/AddSourceAdapter.h>
#include <smoke/lib/sources/VdbSource.h>

namespace smoke
{
namespace houdini
{
namespace adapters
{

AddSourceAdapter::AddSourceAdapter(smoke::core::SimData* simDataPtr,smoke::core::FloatGridPtr grid)
{
//	std::cout <<"AddSourceAdapter::AddSourceAdapter CALLED" << std::endl;
	smoke::sources::VdbSource* density_src = new smoke::sources::VdbSource(grid);
	simDataPtr->density_sources.push_back(density_src);
	smoke::sources::VdbSource* temperature_src = new smoke::sources::VdbSource(grid);
	simDataPtr->temperature_sources.push_back(temperature_src);
}

AddSourceAdapter::~AddSourceAdapter()
{
	// TODO Auto-generated destructor stub
}

} /* namespace adapters */
} /* namespace houdini */
} /* namespace smoke */

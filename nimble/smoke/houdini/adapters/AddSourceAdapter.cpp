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
	smoke::sources::VdbSource* vdb_src = new smoke::sources::VdbSource(grid);
	simDataPtr->sources.push_back(vdb_src);
}

AddSourceAdapter::~AddSourceAdapter()
{
	// TODO Auto-generated destructor stub
}

} /* namespace adapters */
} /* namespace houdini */
} /* namespace smoke */

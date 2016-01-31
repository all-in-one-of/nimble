/*
 * SourceManager.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#include <smoke/lib/solver/SourceManager.h>
#include <smoke/lib/core/SimData.h>
#include <openvdb/tools/Composite.h>
#include <openvdb/tools/GridTransformer.h>

namespace smoke
{
namespace solver
{

SourceManager::SourceManager()
{
	// TODO Auto-generated constructor stub

}

SourceManager::~SourceManager()
{
	// TODO Auto-generated destructor stub
}

} /* namespace solver */
} /* namespace smoke */

void smoke::solver::SourceManager::accumulateSources(smoke::core::SimData* simDataPtr)
{
	smoke::core::FloatGridPtr gridA = simDataPtr->getDensityPtr();
	for (std::vector<smoke::sources::VdbSource*>::iterator source =
			simDataPtr->sources.begin(); source != simDataPtr->sources.end(); ++source)
	{
//		std::cout << "SourceManager::accumulateSources START" << std::endl;
		smoke::core::FloatGridPtr sourceGridB = (*source)->getFloatGridPtr();

		openvdb::FloatGrid::Ptr targetGridB = gridA->deepCopy();

			const openvdb::math::Transform
			    &sourceXform = sourceGridB->transform(),
			    &targetXform = targetGridB->transform();
			openvdb::Mat4R xform =
			    sourceXform.baseMap()->getAffineMap()->getMat4() *
			    targetXform.baseMap()->getAffineMap()->getMat4().inverse();
			openvdb::tools::GridTransformer transformer(xform);
			transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
			    *sourceGridB, *targetGridB);

			openvdb::tools::compMax(*gridA, *targetGridB);
	}
	simDataPtr->sources.clear();
}

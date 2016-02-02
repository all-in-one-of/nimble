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

void smoke::solver::SourceManager::accumulateField(const smoke::core::FloatGridPtr& gridA,
		std::vector<smoke::sources::VdbFloatSource*>& sources)
{
	for (std::vector<smoke::sources::VdbFloatSource*>::iterator source = sources.begin();
			source != sources.end(); ++source)
	{
		smoke::core::FloatGridPtr sourceGridB = (*source)->getFloatGridPtr();
		openvdb::FloatGrid::Ptr targetGridB = gridA->deepCopy();
		const openvdb::math::Transform &sourceXform = sourceGridB->transform(), &targetXform =
				targetGridB->transform();
		openvdb::Mat4R xform = sourceXform.baseMap()->getAffineMap()->getMat4()
				* targetXform.baseMap()->getAffineMap()->getMat4().inverse();
		openvdb::tools::GridTransformer transformer(xform);
		transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::FloatGrid>(
				*sourceGridB, *targetGridB);
		openvdb::tools::compMax(*gridA, *targetGridB);
	}
	sources.clear();
}

void smoke::solver::SourceManager::accumulateSources(smoke::core::SimData* simDataPtr)
{
	accumulateField(simDataPtr->getDensityPtr(), simDataPtr->density_sources);

	accumulateField(simDataPtr->getTemperaturePtr(), simDataPtr->temperature_sources);

	//---------------
	openvdb::VectorGrid::Ptr gridA = simDataPtr->getVelocityPtr();
	std::vector<smoke::sources::VdbVectorSource*>& sources = simDataPtr->velocity_sources;

	for (std::vector<smoke::sources::VdbVectorSource*>::iterator source = sources.begin();
			source != sources.end(); ++source)
	{
		smoke::core::VectorGridPtr sourceGridB = (*source)->getVectorGridPtr();
		openvdb::VectorGrid::Ptr targetGridB = gridA->deepCopy();
		const openvdb::math::Transform &sourceXform = sourceGridB->transform(), &targetXform =
				targetGridB->transform();
		openvdb::Mat4R xform = sourceXform.baseMap()->getAffineMap()->getMat4()
				* targetXform.baseMap()->getAffineMap()->getMat4().inverse();
		openvdb::tools::GridTransformer transformer(xform);
		transformer.transformGrid<openvdb::tools::QuadraticSampler, openvdb::VectorGrid>(
				*sourceGridB, *targetGridB);
		openvdb::tools::compMax(*gridA, *targetGridB);
	}
	sources.clear();

}

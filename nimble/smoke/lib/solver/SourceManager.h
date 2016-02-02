/*
 * SourceManager.h
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#ifndef LIB_SOLVER_SOURCEMANAGER_H_
#define LIB_SOLVER_SOURCEMANAGER_H_

#include <smoke/lib/core/CommonTypes.h>
#include <smoke/lib/core/SimData.h>
#include <smoke/lib/sources/VdbSource.h>

namespace smoke
{
namespace solver
{

class SourceManager
{
public:
	SourceManager();
	virtual ~SourceManager();
//	void addSource(smoke::sources::VdbSource* s)
//	{
//		sources.push_back(s);
//	}
	void accumulateSources(smoke::core::SimData* simDataPtr);
private:
	smoke::core::SimData* simDataPtr;
//	std::vector<smoke::sources::VdbSource*> sources;

	void accumulateField(const smoke::core::FloatGridPtr& gridA,
			std::vector<smoke::sources::VdbSource*>& sources);
};

} /* namespace solver */
} /* namespace smoke */

#endif /* LIB_SOLVER_SOURCEMANAGER_H_ */

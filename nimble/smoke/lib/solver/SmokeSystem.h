/*
 * SmokeSystem.h
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#ifndef LIB_SOLVER_SMOKESYSTEM_H_
#define LIB_SOLVER_SMOKESYSTEM_H_

#include <smoke/lib/core/SimData.h>
#include <smoke/lib/core/CommonTypes.h>
#include <smoke/lib/solver/SourceManager.h>
namespace smoke
{
namespace solver
{

class SmokeSystem
{
public:
	SmokeSystem(smoke::core::SimData* simDataPtr);
	virtual ~SmokeSystem();
	void stepForward(smoke::core::Scalar timeStep);
//	void addSource(smoke::sources::VdbSource* source)
//	{
//		sourceManger.addSource(source);
//	}
private:
	smoke::core::SimData* simDataPtr;
	SourceManager sourceManger;
};

} /* namespace solver */
} /* namespace smoke */

#endif /* LIB_SOLVER_SMOKESYSTEM_H_ */

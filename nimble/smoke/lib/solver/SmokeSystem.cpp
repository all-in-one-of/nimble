/*
 * SmokeSystem.cpp
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#include <smoke/lib/solver/SmokeSystem.h>
#include <iostream>

namespace smoke
{
namespace solver
{
using namespace smoke::core;

SmokeSystem::SmokeSystem(smoke::core::SimData* simDataPtr) :
		simDataPtr(simDataPtr)
{
	// TODO Auto-generated constructor stub

}

SmokeSystem::~SmokeSystem()
{
	// TODO Auto-generated destructor stub
}

void SmokeSystem::stepForward(Scalar fullTimeStep)
{
	sourceManger.accumulateSources(simDataPtr);
}

} /* namespace solver */
} /* namespace smoke */

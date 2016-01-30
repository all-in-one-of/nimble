/*
 * SolveSimAdapter.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "SolveSimAdapter.h"

namespace smoke
{
	namespace houdini
	{
		namespace adapter
		{

			SolveSimAdapter::SolveSimAdapter(smoke::core::SimData* simDataPtr) :
					smokeSystem(simDataPtr)
			{
			}

			SolveSimAdapter::~SolveSimAdapter()
			{
				// TODO Auto-generated destructor stub
			}

			void SolveSimAdapter::stepForward(double fps, int subSteps)
			{
				for (int i = 0; i < subSteps; i++)
				{
					smokeSystem.stepForward(1 / (fps * float(subSteps)));
				}
			}

		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */

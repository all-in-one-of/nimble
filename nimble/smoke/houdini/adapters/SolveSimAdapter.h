#ifndef SOLVESIMADAPTER_H_
#define SOLVESIMADAPTER_H_

#include "smoke/lib/solver/SmokeSystem.h"
#include "smoke/lib/core/SimData.h"

namespace smoke
{
	namespace houdini
	{
		namespace adapter
		{
			class SolveSimAdapter
			{
			public:
				SolveSimAdapter(smoke::core::SimData* simDataPtr);
				virtual ~SolveSimAdapter();
				void stepForward(double fps, int subSteps);
			private:
				smoke::solver::SmokeSystem smokeSystem;
			};
		} /* namespace adapter */
	} /* namespace houdini */
} /* namespace solid */
#endif /* SOLVESIMADAPTER_H_ */

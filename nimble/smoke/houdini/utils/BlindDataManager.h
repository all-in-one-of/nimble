/*
 * BlindDataManager.h
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#ifndef BLINDDATAMANAGER_H_
#define BLINDDATAMANAGER_H_

#include "GU/GU_Detail.h"
#include <openvdb/openvdb.h>


namespace solid
{
	namespace houdini
	{
		class BlindDataManager
		{
		public:
			BlindDataManager();
			virtual ~BlindDataManager();
			openvdb::FloatGrid::Ptr extractGridPtr(GU_Detail* gdp);
			void insertGridPtr(GU_Detail* gdp, openvdb::FloatGrid::Ptr gridPtr);
		};

	} /* namespace houdini */
} /* namespace solid */
#endif /* BLINDDATAMANAGER_H_ */

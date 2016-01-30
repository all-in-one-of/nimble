/*
 * BlindDataManager.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "BlindDataManager.h"

#include "GA/GA_AIFBlindData.h"

namespace smoke
{
	namespace houdini
	{

		BlindDataManager::BlindDataManager()
		{
			// TODO Auto-generated constructor stub

		}

		BlindDataManager::~BlindDataManager()
		{
			// TODO Auto-generated destructor stub
		}

		core::SimData* BlindDataManager::extractSimDataPtr(GU_Detail* gdp)
		{
			const GA_ROAttributeRef attrRef = gdp->findAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC,
																	"SimData");
			const GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData *blindData = attr->getAIFBlindData();
			return blindData->getValue<smoke::core::SimData*>(attr, 0);
		}

		void BlindDataManager::insertSimDataPtr(GU_Detail* gdp, smoke::core::SimData* simDataPtr)
		{
			GA_RWAttributeRef attrRef = gdp->createAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC, "SimData",
																NULL, NULL, "blinddata");
			GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData* blindData = attr->getAIFBlindData();
			blindData->setDataSize(attr, sizeof(smoke::core::SimData*), &simDataPtr);
		}

	} /* namespace houdini */
} /* namespace solid */

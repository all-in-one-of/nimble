/*
 * BlindDataManager.cpp
 *
 *  Created on: 03-May-2014
 *      Author: jaideep
 */

#include "BlindDataManager.h"

#include "GA/GA_AIFBlindData.h"

namespace solid
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

		openvdb::FloatGrid::Ptr BlindDataManager::extractGridPtr(GU_Detail* gdp)
		{
			const GA_ROAttributeRef attrRef = gdp->findAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC,
																	"Grid");
			const GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData *blindData = attr->getAIFBlindData();
			return blindData->getValue<openvdb::FloatGrid::Ptr>(attr, 0);
		}

		void BlindDataManager::insertGridPtr(GU_Detail* gdp, openvdb::FloatGrid::Ptr gridPtr)
		{
			GA_RWAttributeRef attrRef = gdp->createAttribute(GA_ATTRIB_DETAIL, GA_SCOPE_PUBLIC, "Grid",
																NULL, NULL, "blinddata");
			GA_Attribute *attr = attrRef.getAttribute();
			const GA_AIFBlindData* blindData = attr->getAIFBlindData();
			blindData->setDataSize(attr, sizeof(openvdb::FloatGrid::Ptr), &gridPtr);
		}

	} /* namespace houdini */
} /* namespace solid */

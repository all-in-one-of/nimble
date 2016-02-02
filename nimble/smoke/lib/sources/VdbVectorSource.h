/*
 * VdbSource.h
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#ifndef LIB_SOURCES_VDBVECTORSOURCE_H_
#define LIB_SOURCES_VDBVECTORSOURCE_H_

#include <smoke/lib/core/CommonTypes.h>
namespace smoke
{
namespace sources
{

class VdbVectorSource
{
public:
	VdbVectorSource(smoke::core::VectorGridPtr vectorGridPtr) :
			vectorGridPtr(vectorGridPtr)
	{

	}
	virtual ~VdbVectorSource();

	const smoke::core::VectorGridPtr& getVectorGridPtr() const
	{
		return	vectorGridPtr;
	}

	void setFloatGridPtr(const smoke::core::VectorGridPtr& vectorGridPtr)
	{
		this->vectorGridPtr = vectorGridPtr;
	}

private:
	smoke::core::VectorGridPtr vectorGridPtr;
};

} /* namespace sources */
} /* namespace smoke */

#endif /* LIB_SOURCES_VDBVECTORSOURCE_H_ */

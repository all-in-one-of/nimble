/*
 * AddSourceAdapter.h
 *
 *  Created on: 30-Jan-2016
 *      Author: user
 */

#ifndef HOUDINI_ADAPTERS_ADDSOURCEADAPTER_H_
#define HOUDINI_ADAPTERS_ADDSOURCEADAPTER_H_

#include <smoke/lib/core/SimData.h>
#include <smoke/lib/core/CommonTypes.h>
namespace smoke
{
namespace houdini
{
namespace adapters
{

class AddSourceAdapter
{
public:
	AddSourceAdapter();
	virtual ~AddSourceAdapter();
	void addFloatSource(smoke::core::SimData* simDataPtr,smoke::core::FloatGridPtr grid);
	void addVectorSource(smoke::core::SimData* simDataPtr,smoke::core::VectorGridPtr grid);
};

} /* namespace adapters */
} /* namespace houdini */
} /* namespace smoke */

#endif /* HOUDINI_ADAPTERS_ADDSOURCEADAPTER_H_ */

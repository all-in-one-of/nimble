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
	AddSourceAdapter(smoke::core::SimData* simDataPtr,smoke::core::FloatGridPtr source);
	virtual ~AddSourceAdapter();
};

} /* namespace adapters */
} /* namespace houdini */
} /* namespace smoke */

#endif /* HOUDINI_ADAPTERS_ADDSOURCEADAPTER_H_ */

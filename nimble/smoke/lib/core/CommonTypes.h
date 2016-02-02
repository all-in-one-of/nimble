#ifndef COMMONTYPES_H_
#define COMMONTYPES_H_

#include <openvdb/openvdb.h>
namespace smoke
{
namespace core
{
typedef double Scalar;
typedef openvdb::FloatGrid::Ptr FloatGridPtr;
typedef openvdb::VectorGrid::Ptr VectorGridPtr;
}
}
#endif /* COMMONTYPES_H_ */

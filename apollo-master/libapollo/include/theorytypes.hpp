/**
 * @file    theorytypes.hpp
 * @brief   Types returned as a result of the theory functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#ifndef apollo_theorytypes_hpp_
#define apollo_theorytypes_hpp_

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "sequenceinterface.hpp"
#include "types.hpp"

namespace apollo {

typedef boost::geometry::model::point<types::mz_store_t, 1, boost::geometry::cs::cartesian> Point1D;

typedef boost::geometry::model::box<Point1D> Box1D;

typedef boost::geometry::index::rtree< std::pair<Box1D, SequenceI::shp>, boost::geometry::index::rstar<16> > MhSequenceTree;

} /* namespace apollo */

#endif /* apollo_theorytypes_hpp_ */

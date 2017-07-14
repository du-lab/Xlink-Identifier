/**
 * @file    locset.hpp
 * @brief   A set of locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#ifndef apollo_locset_hpp
#define apollo_locset_hpp

#include <ostream>

#include <boost/container/flat_set.hpp>
#include "sequenceinterface.hpp"

namespace apollo {

/**
 * A set of locations on a sequence. 
 *	@note Primarily used in multimodlocgen to hold modification locations
 */
typedef boost::container::flat_set<SequenceI::size_type> LocSet;

std::ostream& operator<<(std::ostream &out, LocSet const &rhs);

} /* namespace apollo */

#endif /* apollo_locset_hpp */
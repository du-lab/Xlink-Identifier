/**
 * @file    locresiduemap.hpp
 * @brief   A map of locations and modofications or residues
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */


#ifndef apollo_locresiduemap_hpp
#define apollo_locresiduemap_hpp

#include <ostream>
#include <boost/container/flat_map.hpp>

#include "sequenceinterface.hpp"
#include "types.hpp"

namespace apollo {

typedef boost::container::flat_map<SequenceI::size_type, types::residue_t> LocResidueMap;

std::ostream& operator<<(std::ostream &out, LocResidueMap const &rhs);

} /* namespace apollo */

#endif /* apollo_locresiduemap_hpp */
/**
 * @file    residueset.hpp
 * @brief   A flat set of residues
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/09
 * @copyright 2012
 */

#ifndef apollo_residueset_hpp_
#define apollo_residueset_hpp_

#include <ostream>
#include <boost/container/flat_set.hpp>

#include "types.hpp"

namespace apollo {

typedef boost::container::flat_set<types::residue_t> ResidueSet;

std::ostream& operator<<(std::ostream &out, ResidueSet const &rSet);

} /* namespace apollo */

#endif /* apollo_residueset_hpp_ */

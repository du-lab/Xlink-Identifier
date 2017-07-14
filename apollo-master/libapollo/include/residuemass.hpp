/**
 * @file    residuemass.hpp
 * @brief   Defines ResidueMass container
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */
#ifndef apollo_residuemass_hpp_
#define apollo_residuemass_hpp_

#include <ostream>
#include <boost/container/flat_map.hpp>
#include "types.hpp"

namespace apollo {

/**
 * @typedef ResidueMass
 * @brief Map between a residue and its mass or mass modification
 */
typedef boost::container::flat_map<types::residue_t,
    types::dalton_t> ResidueMass;

std::ostream& operator<<(std::ostream &out, ResidueMass const &rMass);

} /* namespace apollo */

#endif /* apollo_residuemass_hpp_ */

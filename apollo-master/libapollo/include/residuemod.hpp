/**
 * @file    residuemod.hpp
 * @brief   Association between a residue and its modifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/23
 * @copyright 2012
 */

#ifndef apollo_residuemod_hpp_
#define apollo_residuemod_hpp_

#include <ostream>
#include <boost/container/flat_set.hpp>
#include <boost/container/flat_map.hpp>
#include "residuecount.hpp"
#include "residueset.hpp"

namespace apollo {

typedef boost::container::flat_map< ResidueCount::key_type, 
    ResidueSet > ResidueMod;

std::ostream& operator<<(std::ostream &out, ResidueMod const &rMod);

} /* namespace apollo */



#endif /* apollo_residuemod_hpp_ */

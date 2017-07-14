/**
 * @file    multirefresiduecount.hpp
 * @brief   Defines MultiRefResidueCount
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/24
 * @copyright 2012
 */

#ifndef apollo_multirefresiduecount_hpp_
#define apollo_multirefresiduecount_hpp_

#include <ostream>
#include <boost/container/flat_map.hpp>
#include "refutil.hpp"
#include "residuecount.hpp"

namespace apollo {

/**
 * A map between a mod and the counts per residue
 *  @note Primarily used in multimodcountgen. This simplifies modification 
        calculations immensely
 */

typedef boost::container::flat_map< ResidueCount::key_type,
    ResidueCount::cref >
    MultiRefResidueCount;

std::size_t hash_value(MultiRefResidueCount const &mrCount);

} /* namespace apollo */


std::ostream& operator<<(std::ostream &out, apollo::MultiRefResidueCount const &rhs);



#endif /* apollo_multirefresiduecount_hpp_ */

/**
 * @file    multireflocset.hpp
 * @brief   Map between mods and their locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */


#ifndef apollo_multireflocset_hpp
#define apollo_multireflocset_hpp

#include <functional>
#include <ostream>
 
#include <boost/container/flat_map.hpp>

#include "refutil.hpp"
#include "residuecount.hpp"
#include "locset.hpp"

namespace apollo {

/**
 * A map between a mod and its sequence locations
 *  @note Primarily used in multimodlocgen. This simplifies location 
        calculations immensely
 */

typedef boost::container::flat_map< ResidueCount::key_type,
    std::reference_wrapper<LocSet const> >
    MultiRefLocSet;

std::ostream& operator<<(std::ostream &out, MultiRefLocSet const &mrLocSet);

} /* namespace apollo */

#endif /* apollo_multireflocset_hpp */
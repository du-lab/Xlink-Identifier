/**
 * @file    f_multimodloc.hpp
 * @brief   A filter for use when iterating through multimodlocations, 
    removing ones with duplicate locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/03
 * @copyright 2013
 */

#ifndef apollo_filter_f_multimodloc_hpp_
#define apollo_filter_f_multimodloc_hpp_

#include "filterinterface.hpp"
#include "../core/multireflocset.hpp"

namespace apollo {

namespace filter {

class unique_MultiModLoc : public FilterI<MultiRefLocSet> {
public:

    unique_MultiModLoc() {}

    bool operator()(filter_type const &multiRefLoc) const;

    ~unique_MultiModLoc() {}
};

} /* namespace filter*/
} /* namespace apollo */

#endif /* apollo_filter_f_multimodloc_hpp_ */

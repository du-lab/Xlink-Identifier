/**
 * @file    f_multimodcount.cpp
 * @brief   Predicates for filtering multi mod counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/30
 * @copyright 2012
 */

#include "../core/residuecalc.hpp"
#include "f_multimodcount.hpp"

namespace apollo {
namespace filter {

bool range_MultiModCount::operator()(filter_type const &multiModCount) const {

    ResidueCount aggregateCount = fn::aggregateMultiResidueCount(multiModCount);
    
    for(auto const &aggPair : aggregateCount) {
        auto const aa = aggPair.first;
        auto const count = aggPair.second;
        auto const lower_bound = _lowerRange[aa];
        auto const upper_bound = _upperRange[aa];
        if ((count < lower_bound) ||
            (count >= upper_bound)) {
            return false;
        } 
    }
    return true;
}

} /* namespace filter */
} /* namespace filter */

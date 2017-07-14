/**
 * @file    f_modcount.cpp
 * @brief   Predicates for filtering mod counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#include "f_modcount.hpp"

namespace apollo {

namespace filter {

bool range_ModCount::operator()(filter_type const &modCount) const {
    count_t count = 0;
    for(auto const &modPair : modCount) {
        count += modPair.second;
    }
    if ((count >= _lowerCount) &&
    	(count < _upperCount)) {
        return true;
    } else {
        return false;
    }
}

} /* namespace filter */
} /* namespace apollo */

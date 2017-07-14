/**
 * @file    f_multimodloc.cpp
 * @brief   A filter for use when iterating through multimodlocations, 
    removing ones with duplicate locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/03
 * @copyright 2013
 */

#include <iterator>
#include "f_multimodloc.hpp"

namespace apollo {

namespace filter {

bool unique_MultiModLoc::operator()(filter_type const &multiRefLoc) const {
    // shortcut if there's nothing to check
    if (multiRefLoc.empty() || multiRefLoc.size() < 2) {
        return true;
    } 

    auto currentIt = multiRefLoc.begin();
    auto checkIt = std::next(currentIt);
    auto const endIt = multiRefLoc.end();

    for(; currentIt != endIt; ++currentIt) {
        for(auto checkIt = std::next(currentIt); checkIt != endIt; ++checkIt) {
            for(auto const &loc : currentIt->second.get()) {
                auto locFoundIt = checkIt->second.get().find(loc);
                if (locFoundIt != checkIt->second.get().end()) {
                    // We found a duplicate: locations are not unique
                    return false;
                }
            }
        }
    }
    return true;
}

} /* namespace filter */
} /* namespace apollo */
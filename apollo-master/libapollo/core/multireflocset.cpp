/**
 * @file    multirefLocSet.cpp
 * @brief   Map between mods and their locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#include "multireflocset.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, MultiRefLocSet const &mrLocSet) {
    for (auto const &mLocPair : mrLocSet) {
        out << "{" << mLocPair.first << ":" << mLocPair.second << "}";
    }
    return out;
}

} /* namespace apollo */
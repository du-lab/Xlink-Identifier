/**
 * @file    locset.cpp
 * @brief   A set of locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#include "locset.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, LocSet const &rhs) {
    bool afterFirst = false;
    out << "[";
    for( auto const &loc : rhs ) {
        if (afterFirst) {
            out << ", ";
        }
        out << loc;
        afterFirst = true;
    }
    out << "]";
    return out;
}

} /* namespace apollo */
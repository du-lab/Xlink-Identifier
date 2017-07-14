/**
 * @file    residuemass.cpp
 * @brief   Defines ResidueMass << operator
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/10
 * @copyright 2012
 */


#include <iostream>

#include "residuemass.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, ResidueMass const &rMass) {
    using std::endl;
    bool afterFirst = false;
    for(auto const &rMassPair : rMass) {
        if (afterFirst) {
            out << endl;
        }
        out << "(" << rMassPair.first << ":" << rMassPair.second << ")";
        afterFirst = true;
    }
    return out;
}

} /* namespace apollo */

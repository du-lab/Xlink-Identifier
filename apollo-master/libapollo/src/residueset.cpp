/**
 * @file    residueset.cpp
 * @brief   Operator for sending residue set to ostream
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/9
 * @copyright 2012
 */


#include "residueset.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, ResidueSet const &rhs) {
    bool afterFirst = false;
    out << "(";
    for(auto const &residue : rhs) {
        if (afterFirst) {
            out << ", ";
        }
        out << residue;
        afterFirst = true;
    }
    out << ")";
    return out;
}

} /* namespace apollo */

/**
 * @file    locresiduemap.cpp
 * @brief   A map of locations and modofications or residues
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#include "locresiduemap.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, LocResidueMap const &rhs) {

    for (auto const &lrPair : rhs) {
        out << "{" << lrPair.first << ":" << lrPair.second << "}";
    }

    return out;
}


} /* namespace apollo */
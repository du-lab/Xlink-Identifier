/**
 * @file    residuemod.cpp
 * @brief   Association between a residue and its modifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/30
 * @copyright 2012
 */

#include "residuemod.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, ResidueMod const &rMod) {
    out << "{";
    bool afterFirst = false;
    for(auto const &rModPair : rMod) {
        if (afterFirst) {
            out << ", ";
        }
        ResidueMod::key_type const residue = rModPair.first;
        out << residue << ":" << rModPair.second;
        afterFirst = true;
    }
    out << "}";
    return out;
}
} /* namespace apollo */

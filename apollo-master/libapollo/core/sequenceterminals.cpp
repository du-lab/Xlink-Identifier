/**
 * @file    sequenceterminals.cpp
 * @brief   A simple bitset to hold Nh2 and C Terminus info
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#include "sequenceterminals.hpp"

namespace apollo {

SequenceTerminals::SequenceTerminals(bool const hasNh2Terminus,
    bool const hasCTerminus) {
        _term[Terminal::Nh2] = hasNh2Terminus;
        _term[Terminal::C] = hasCTerminus;
}

bool SequenceTerminals::hasNh2Terminus() const {
    if (_term.any()) {
        return _term[Terminal::Nh2];
    }
    return false;
}

bool SequenceTerminals::hasCTerminus() const {
    if (_term.any()) {
        return _term[Terminal::C];
    }
    return false;
}

std::ostream& operator<<(std::ostream &out, SequenceTerminals const &rhs) {
    out << "NH2:" << rhs.hasNh2Terminus() << 
        ", C:" << rhs.hasCTerminus();
    return out;
}

bool SequenceTerminals::operator==(SequenceTerminals const &rhs) const {
    return (_term == rhs._term);
}
} /* namespace apollo */

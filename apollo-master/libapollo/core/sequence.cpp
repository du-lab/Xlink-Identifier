/**
 * @file    sequence.cpp
 * @brief   Simple sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#include "sequence.hpp"

namespace apollo {

Sequence::Sequence(string_type sequenceString,
            bool const hasNh2Terminus,
            bool const hasCTerminus) :
    _sequenceString(sequenceString),
    _seqTerminals(hasNh2Terminus, hasCTerminus) {}

SequenceI::size_type Sequence::length() const {
    return _sequenceString.length();
}

SequenceI::string_type Sequence::toString() const {
    return _sequenceString;
}

SequenceI::const_iterator Sequence::begin() const {
    return _sequenceString.begin();
}

SequenceI::const_iterator Sequence::end() const {
    return _sequenceString.end();
}

bool Sequence::hasNh2Terminus() const {
    return _seqTerminals.hasNh2Terminus();
}

bool Sequence::hasCTerminus() const {
    return _seqTerminals.hasCTerminus();
}

void Sequence::print(std::ostream &out) const {
    out << toString();
}

void Sequence::debugPrint(std::ostream &out) const {
    out << toString();
}

SequenceI::shp Sequence::rootProtein() const {
    return shared_from_this();
}

} /* namespace apollo */


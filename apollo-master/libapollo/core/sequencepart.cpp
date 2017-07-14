/**
 * @file    sequencepart.cpp
 * @brief   A sub-sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#include <iterator>
#include "sequencepart.hpp"

namespace apollo {

SequencePart::SequencePart(SequenceI::shp parent,
    size_type from,
    size_type length) :
    _parent(parent),
    _from(from),
    _length(length) {

    //TODO: Check to make sure our parent exists!
    //TODO: It would behoove us to check for legal lengths

    // If the length is 0, assume they want the rest of the sequence
    if (_length ==  0) {
        _length = parent->length();
    }

    bool hasNh2Terminus = false;
    bool hasCTerminus = false;
        // If the from location is not 0, it cannot have an NH2 terminus
    if ((_from == 0) && _parent->hasNh2Terminus()) {
        hasNh2Terminus = true;
    }
    // If the length does not include the parent's end, it cannot have a C terminus
    if (((_from + _length) == parent->length())
        && _parent->hasCTerminus()) {
        hasCTerminus = true;
    }
    _seqTerminals = SequenceTerminals(hasNh2Terminus, hasCTerminus);
}

SequenceI::size_type SequencePart::length() const {
    return _length;
}

SequenceI::string_type SequencePart::toString() const {
    return string_type(begin(), end());
}

SequenceI::const_iterator SequencePart::begin() const {
    return boost::next(_parent->begin(), _from);
}

SequenceI::const_iterator SequencePart::end() const {
    return boost::next(begin(), _length);
}

bool SequencePart::hasNh2Terminus() const {
return _seqTerminals.hasNh2Terminus();
}

bool SequencePart::hasCTerminus() const {
return _seqTerminals.hasCTerminus();
}

void SequencePart::print(std::ostream &out) const {
    out << toString();
}

void SequencePart::debugPrint(std::ostream &out) const {
    out << toString();
}

SequenceI::shp SequencePart::rootProtein() const {
    return _parent->rootProtein();
}

} /* namespace apollo */

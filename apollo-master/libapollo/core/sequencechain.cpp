/**
 * @file    sequencechain.cpp
 * @brief   A chain of sequences
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#include <iterator>

#include "sequencechain.hpp"

namespace apollo {

SequenceI::size_type SequenceChain::length() const {
    return std::distance(begin(), end());
}

SequenceI::string_type SequenceChain::toString() const {
    return string_type(begin(), end());
}

SequenceI::const_iterator SequenceChain::begin() const {
    return _seqVector.front()->begin();
}

SequenceI::const_iterator SequenceChain::end() const {
    return _seqVector.back()->end();
}

bool SequenceChain::hasNh2Terminus() const {
    return _seqVector.front()->hasNh2Terminus();
}

bool SequenceChain::hasCTerminus() const {
    return _seqVector.back()->hasCTerminus();
}

void SequenceChain::print(std::ostream &out) const {
    out << toString();
}

void SequenceChain::debugPrint(std::ostream &out) const {
    bool notFirst = false;
    for(auto const &sequenceShp : _seqVector ) {
        if (notFirst) {
            out << ", ";
        } else {
            notFirst = true;
        }
        sequenceShp->debugPrint(out);
    }
}

SequenceI::shp SequenceChain::rootProtein() const {
    return _seqVector.front()->rootProtein();
}

} /* namespace apollo */

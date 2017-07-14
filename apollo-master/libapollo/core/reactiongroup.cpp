/**
 * @file    reactiongroup.cpp
 * @brief   Represents the logic of a reaction group
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#include "reactiongroup.hpp"

namespace apollo {

using types::count_t;
using types::residue_t;

ReactionGroup::ReactionGroup(residue_t target,
    bool const linkableToNh2Terminus,
    bool const linkableToCTerminus) :
    _seqTerminals(linkableToNh2Terminus, linkableToCTerminus) {
    _targets.insert(target);
}

bool ReactionGroup::operator()(residue_t const residue) const {
    if (_targets.find(residue) != _targets.end()) {
        return true;
    } else {
        return false;
    }
}

bool ReactionGroup::operator()(SequenceI const &seq) const {
    if (reactionSites(seq) >= 1) {
        return true;
    } else {
        return false;
    }
}

bool ReactionGroup::canBindToNh2Terminus(SequenceI const &seq) const {
    if (bindsToNh2Terminus() && seq.hasNh2Terminus() ) {
        return true;
    } else {
        return false;
    }
}

bool ReactionGroup::canBindToCTerminus(SequenceI const &seq) const {
    if (bindsToCTerminus() && seq.hasCTerminus()) {
        return true;
    } else {
        return false;
    }
}

count_t ReactionGroup::reactionSites(SequenceI const &seq) const {
    using types::sequence_string_t;

    count_t siteCount = 0;
    for(sequence_string_t::const_iterator it = seq.begin();
        it != seq.end();
        ++it) {

        if (_targets.find(*it) != _targets.end()) {
            siteCount += 1;
        }
    }

    if (canBindToNh2Terminus(seq)) {
        siteCount += 1;
    }
    if (canBindToCTerminus(seq)) {
        siteCount += 1;
    }
    return siteCount;
}

bool ReactionGroup::bindsToNh2Terminus() const {
    return _seqTerminals.hasNh2Terminus();
}

bool ReactionGroup::bindsToCTerminus() const {
    return _seqTerminals.hasCTerminus();
}

bool ReactionGroup::operator==(ReactionGroup const &rhs) const {
    return ((_seqTerminals == rhs._seqTerminals) &&
        (_targets == rhs._targets));
}

bool ReactionGroup::operator!=(ReactionGroup const &rhs) const {
    return !operator==(rhs);
}

void ReactionGroup::operator+=(ReactionGroup const &rhs) {
    bool linkToNh2Term = bindsToNh2Terminus() | rhs.bindsToNh2Terminus();
    bool linkToCTerm = bindsToCTerminus() | rhs.bindsToCTerminus();
    _seqTerminals = SequenceTerminals(linkToNh2Term, linkToCTerm);
    _targets.insert(rhs._targets.begin(), rhs._targets.end());
}

std::ostream& operator<<(std::ostream &out, ReactionGroup const &rhs) {
    out << "Targets:" << rhs._targets << 
        ", " << rhs._seqTerminals;
    return out;
}

ReactionGroup operator+(ReactionGroup lhs, ReactionGroup const &rhs) {
    lhs += rhs;
    return lhs;
}


} /* namespace apollo */

/**
 * @file    intrareactiongroup.cpp
 * @brief   Represents the logic of 2 reaction groups connecting to a 
 *  single sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/23
 * @copyright 2012
 */

#include "residueset.hpp"
#include "intrareactiongroup.hpp"

namespace apollo {

IntraReactionGroup::IntraReactionGroup() :
    _group1_cref(_shared), _group2_cref(_shared) {}

IntraReactionGroup::IntraReactionGroup(ReactionGroup const &group1, ReactionGroup const &group2) :
    _super(group1 + group2), 
    _group1_cref(group1), _group2_cref(group2) {

    bool sharedNh2Term = (group1.bindsToNh2Terminus() &&
            group2.bindsToNh2Terminus());
    bool sharedCTerm = (group1.bindsToCTerminus() &&
            group2.bindsToCTerminus());

    ResidueSet sharedResidues;

    for(auto const &aa : _targets) {
        if (group1(aa) && group2(aa)) {
            sharedResidues.emplace(aa);
        }
    }

    _shared = ReactionGroup(sharedResidues.begin(), sharedResidues.end(),
        sharedNh2Term, sharedCTerm);

}

bool IntraReactionGroup::operator()(SequenceI const &seq) const {
    count_t group1Count = _group1_cref.get().reactionSites(seq);
    count_t group2Count = _group2_cref.get().reactionSites(seq);
    count_t sharedCount = _shared.reactionSites(seq);

    // If group1 can bind to the sequence
    if (group1Count > 0) {

        // And if all of group1 can be taken up by some of group2,
        // then at least one space must be taken up by group1
        if (group1Count == sharedCount) {
            group2Count -= 1;
        }

        // If group2 has any remaining spaces, then both groups can bind
        if (group2Count > 0) {
            return true;
        }
    }

    return false;
}

} /* namespace apollo */

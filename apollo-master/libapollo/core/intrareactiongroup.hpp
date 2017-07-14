/**
 * @file    intrareactiongroup.hpp
 * @brief   Represents the logic of 2 reaction groups connecting to a 
 *  single sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/23
 * @copyright 2012
 */

#ifndef apollo_intrareactiongroup_hpp_
#define apollo_intrareactiongroup_hpp_

#include "sequenceinterface.hpp"
#include "reactiongroup.hpp"


namespace apollo {

/**
 *	@class IntraReactionGroup intrareactiongroup.hpp "intrareactiongroup.hpp"
 * A simplification of logic for two reaction groups binding to the same sequence
 */

class IntraReactionGroup : public ReactionGroup {
public:
    IntraReactionGroup();

    IntraReactionGroup(ReactionGroup const &group1, ReactionGroup const &group2);
    
    /**
     * Check if the reaction group would bind to a residue
     *
     *  @param[in] residue  The residue to check
     *
     *  @return True if residue would be bound, otherwise false
     */
    bool operator()(residue_t const residue) const;
    
    /** 
     * Check if the reaction would bind to the sequence
     *
     *  @param[in] seq  The sequence to check
     *
     *  @return True if the sequence would be bound, otherwise false
     */
    bool operator()(SequenceI const &seq) const;

    ~IntraReactionGroup() {}

private:
    typedef ReactionGroup _super;
    ReactionGroup::cref _group1_cref;
    ReactionGroup::cref _group2_cref;
    ReactionGroup _shared;
};


} /* namespace apollo */

#endif /* apollo_intrareactiongroup_hpp_ */

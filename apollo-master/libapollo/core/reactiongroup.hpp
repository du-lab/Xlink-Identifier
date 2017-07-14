/**
 * @file    reactiongroup.hpp
 * @brief   Represents the logic of a reaction group
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#ifndef apollo_reactiongroup_hpp_
#define apollo_reactiongroup_hpp_

#include <ostream>
#include <vector>
#include <functional>

#include "types.hpp"
#include "residueset.hpp"
#include "sequenceinterface.hpp"
#include "sequenceterminals.hpp"

namespace apollo {
/**
 * @class   ReactionGroup reactiongroup.h "reactiongroup.h"
 * @brief   A linker's reaction group
 */
class ReactionGroup {
public:

    typedef types::residue_t residue_t;

    typedef types::count_t count_t;

    typedef std::reference_wrapper<ReactionGroup const> cref;

    typedef std::vector<ReactionGroup> vec;

    // Default ctor
    ReactionGroup() {}

    /**
     * A reaction group that binds to a single residue
     */
    ReactionGroup(residue_t residue,
        bool const linkableToNh2Terminus = false,
        bool const linkableToCTerminus = false);

    /**
     * A reaction group that binds to multiple residues
     */
    template <typename IteratorT>
    ReactionGroup(IteratorT begin, IteratorT end,
        bool const linkableToNh2Terminus = false,
        bool const linkableToCTerminus = false) :
        _targets(begin, end),
        _seqTerminals(linkableToNh2Terminus, linkableToCTerminus) {}

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

    bool canBindToNh2Terminus(SequenceI const &seq) const;

    bool canBindToCTerminus(SequenceI const &seq) const;

    /**
     * @brief Determines the number of reaction sites available on a fragment
     * @param[in] fragment  The fragment to be checked
     * @return  The number of sites on the fragment available for binding
     */
    count_t reactionSites(SequenceI const &seq) const;

    /**
     * @return If this reaction group binds to the amine terminus
     */
    bool bindsToNh2Terminus() const;

    /**
     * @return If this reaction group binds to the c terminus
     */
    bool bindsToCTerminus() const;

    bool operator==(ReactionGroup const &rhs) const;

    bool operator!=(ReactionGroup const &rhs) const;

    /**
     * Combine the effects of two reaction groups
     */
    void operator+=(ReactionGroup const &rhs);

    friend std::ostream& operator<<(std::ostream &out, ReactionGroup const &rhs);

    virtual ~ReactionGroup() {}

protected:
    ResidueSet _targets;
    SequenceTerminals _seqTerminals;
};

/**
 * Combine the effects of two reaction groups
 */
ReactionGroup operator+(ReactionGroup lhs, ReactionGroup const &rhs);

} /* namespace apollo */

#endif /* apollo_reactiongroup_hpp_ */

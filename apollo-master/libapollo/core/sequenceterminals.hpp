/**
 * @file    sequenceterminals.hpp
 * @brief   A simple bitset to hold Nh2 and C Terminus info
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */
#ifndef apollo_sequenceterminals_hpp_
#define apollo_sequenceterminals_hpp_

#include <ostream>
#include <bitset>

namespace apollo {

/**
 *  @class SequenceTerminals sequenceterminals.hpp "sequenceterminals.hpp"
 * A bitset that represents the Nh2 and C terminus of a sequence.
    Also used by ReactionGroup to determine which terminal the group binds
 */
class SequenceTerminals {
public:
    SequenceTerminals(bool const hasNh2Terminus = true,
        bool const hasCTerminus = true);

    bool hasNh2Terminus() const;

    bool hasCTerminus() const;

    bool operator==(SequenceTerminals const &rhs) const;

    friend std::ostream& operator<<(std::ostream &out, 
        SequenceTerminals const &rhs);

    ~SequenceTerminals() {}
private:
    enum Terminal{Nh2, C, numOfTerms};
    typedef std::bitset<numOfTerms> terminal_bitset;
    terminal_bitset _term;
};

} /* namespace apollo */
#endif /* apollo_sequenceterminals_hpp_ */

/**
 * @file    sequence.hpp
 * @brief   A sub-sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_sequencepart_hpp_
#define apollo_sequencepart_hpp_

#include "sequenceinterface.hpp"
#include "sequenceterminals.hpp"

namespace apollo {

class SequencePart : virtual public SequenceI {
public:
        /**
     * @brief   Constructor by making a sub-sequence
     * @param[in] parent    The parent sequence
     * @param[in] from      The start of the sub sequence
     * @param[in] length        The length of the subsequence
     */
    SequencePart(SequenceI::shp parent,
        size_type from,
        size_type length = 0);

    ~SequencePart() {}

private:
    //Variables
    SequenceI::shp _parent; ///< The sequence parent
    size_type _from; ///< The sub-sequence from
    size_type _length; ///< The sub-sequence length
    SequenceTerminals _seqTerminals;

    // Functions
    string_type toString() const; ///< Defined by sequence interface
    const_iterator begin() const; ///< Defined by sequence interface
    const_iterator end() const; ///< Defined by sequence interface
    size_type length() const; ///< Defined by sequence interface
    bool hasNh2Terminus() const; ///< Defined by sequence interface
    bool hasCTerminus() const; ///< Defined by sequence interface
    void print(std::ostream &out) const; ///< Defined by sequence interface
    void debugPrint(std::ostream &out) const; ///< Defined by sequence interface
    shp rootProtein() const; ///< Defined by sequence interface
    SequencePart() {} ///< No default constructor
};


} /* namespace apollo */
#endif /* apollo_sequencepart_hpp_ */

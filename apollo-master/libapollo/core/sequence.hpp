/**
 * @file    sequence.hpp
 * @brief   Simple sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_sequence_hpp_
#define apollo_sequence_hpp_

#include "sequenceinterface.hpp"
#include "sequenceterminals.hpp"

namespace apollo {

class Sequence : public std::enable_shared_from_this<SequenceI>, public virtual SequenceI {
public:
    /**
     * @brief   Constructor via sequence information
     * @param[in] sequenceString    The new sequence's string
     * @param[in] hasNh2Terminus  Whether the sequence has an amino terminus
     * @param[in] hasCTerminus  Whether the sequence has a C Terminus
     */
    template <class IteratorT>
    Sequence(IteratorT begin, IteratorT end,
            bool const hasNh2Terminus = true,
            bool const hasCTerminus = true) :
        _sequenceString(begin, end),
        _seqTerminals(hasNh2Terminus, hasCTerminus) {}

    Sequence(string_type sequenceString,
        bool const hasNh2Terminus = true,
        bool const hasCTerminus = true);

    ~Sequence() {}
private:
    //Variables
    string_type _sequenceString;
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
    Sequence() {} ///< No default constructor
};

} /* namespace apollo */
#endif /* apollo_sequence_hpp_ */

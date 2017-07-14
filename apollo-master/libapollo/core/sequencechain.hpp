/**
 * @file    sequencechain.hpp
 * @brief   A chain of sequences
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_sequencechain_hpp_
#define apollo_sequencechain_hpp_

#include "sequenceinterface.hpp"

namespace apollo {

class SequenceChain : virtual public SequenceI {
public:
    template<typename IteratorT>
    SequenceChain(IteratorT begin, IteratorT end) :
        _seqVector(begin, end) {}

    ~SequenceChain() {}
private:
    // Variables
    SequenceI::shp_vec _seqVector; ///< Vector of sequence

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
    SequenceChain() {} ///< No default constructor
};

}
#endif /* apollo_sequencechain_hpp_ */

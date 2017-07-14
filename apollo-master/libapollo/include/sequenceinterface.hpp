/**
 * @file    sequenceinterface.hpp
 * @brief   Sequence interface
 *
 * @author  Adam Baxter
 * @version 2.0
 * @since    2012/07/10
 * @copyright 2012
 */

#ifndef apollo_sequencei_hpp_
#define apollo_sequencei_hpp_

#include <memory>
#include <ostream>
#include <deque>
#include <vector>
#include <functional>

#include <boost/utility.hpp>

#include "types.hpp"
#include "aggregateset.hpp"

namespace apollo {
    
/**
 * @class   SequenceI sequenceinterface.hpp "sequenceinterface.hpp"
 * @brief   Defines a standard interface for all Sequence classes
 * @note    Sequences must not contain mass or charge calculation capabilities.
 *          They are strictly for determining sequence information.
 *          Non-copyable
 */


class SequenceI : boost::noncopyable {
public:

    typedef std::reference_wrapper<SequenceI const> cref;

    /**
     * @brief   A shared pointer to any sequence interface
     */
    typedef std::shared_ptr<SequenceI const> shp;

    /**
     * @brief   A vector of SequenceI shared pointers
     */
    typedef std::vector<SequenceI::shp> shp_vec;

    /**
     * @brief   A deque of SequenceI shared pointers
     */
    typedef std::deque<SequenceI::shp> shp_deque;

    /**
     * @brief   A set with an additional += operator
     */
    typedef aggregate_set<SequenceI::shp> shp_set;

    /**
     * @brief   string representation type
     */
    typedef types::sequence_string_t string_type;

    /**
     * @brief   string representation type
     */
    typedef string_type::value_type value_type;


    /**
     * @brief   type received from length()
     */
    typedef string_type::size_type size_type;

    /**
     * @brief   type received from begin(), end()
     */

    typedef string_type::const_iterator const_iterator;
    
    /**
     * @return The number of residues in the sequence
     */
    virtual size_type length() const = 0;

    /**
     * @return The sequence as a string
     */
    virtual string_type toString() const = 0;

    /**
     * @return The begin iterator of the sequence
     */
    virtual const_iterator begin() const = 0;

    /**
     * @return The end iterator of the sequence
     */
    virtual const_iterator end() const = 0;


    /**
     * @return Whether the sequence has an amino terminus or not
     */
    virtual bool hasNh2Terminus() const = 0;

    /**
     * @return Whether the sequence has a C terminus or not
     */
    virtual bool hasCTerminus() const = 0;

    /**
     * @brief Print sequence to ostream
     * @param[in] out
     *      The ostream to print to
     */
    virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Print debug information to ostream
     * @param[in] out
     *      ostream to print to
     */
    virtual void debugPrint(std::ostream &out) const = 0;

    /**
     * @return The root protein this sequence is from
     */
    virtual shp rootProtein() const = 0;

    virtual ~SequenceI() {}
};

inline std::ostream& operator<<(std::ostream &out, SequenceI const &seq) {
    seq.print(out);
    return out;
}

inline std::ostream& operator<<(std::ostream &out, SequenceI::shp_set const & shpSet) {
    bool afterFirst = false;
    for(auto const &seqShp : shpSet) {
        if (afterFirst) {
            out << ", ";
        }
        out << *seqShp;
        afterFirst = true;
    }
    return out;
}

inline std::size_t hash_value(SequenceI::shp const &seqShp) {
    std::hash<SequenceI::shp> shp_fn;
    return shp_fn(seqShp);
}

} /* namespace apollo */

#endif /* apollo_sequencei_hpp_ */

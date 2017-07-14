/**
 * @file    residuecount.hpp
 * @brief   Defines ResidueCount
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#ifndef apollo_residuecount_hpp_
#define apollo_residuecount_hpp_

#include <ostream>
#include <utility>
#include <functional>

#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>


#include "types.hpp"

namespace apollo {
/**
 * @class   ResidueCount
 * @brief   Map associating Residue->Count
 * @details Represents the number of times each residue occurs in a sequence
 */
class ResidueCount {
public:
    typedef std::reference_wrapper<ResidueCount const> cref;
    
    typedef boost::container::flat_map<types::residue_t,
    types::count_t> impl_type;

    typedef impl_type::key_type key_type;

    typedef impl_type::mapped_type mapped_type;

    typedef impl_type::value_type value_type;

    typedef impl_type::const_iterator const_iterator;

    typedef impl_type::const_pointer const_pointer;

    typedef impl_type::const_reference const_reference;

    typedef impl_type::const_reverse_iterator const_reverse_iterator;

    typedef impl_type::iterator iterator;

    typedef impl_type::pointer pointer;

    typedef impl_type::reference reference;

    typedef impl_type::reverse_iterator reverse_iterator;

    typedef impl_type::difference_type difference_type;

    typedef impl_type::size_type size_type;

    /**
     * @brief   ResidueCount constructor from sequence
     * @param[in] sequence  The sequence to be counted
     */
    explicit ResidueCount(types::sequence_string_t const &sequenceStr);

    /**
     * @brief   default constructor
     */
    ResidueCount(void) {}

    /**
     * @brief   Iterator constructor
     */
    template<class Iterator>
    ResidueCount(Iterator begin, Iterator end) {
        for( ; begin != end; ++begin) {
            _rCount.emplace(*begin);        }
    }

    /* Copy constructor */
    ResidueCount(ResidueCount const &rhs);

    /* Move constructor */
    ResidueCount(ResidueCount &&rhs);

    ResidueCount& operator=(ResidueCount const &rhs);

    ResidueCount& operator=(ResidueCount &&rhs);

    mapped_type aggregateCount() const;

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

    void clear();

    bool empty() const;

    size_type size() const;

    void shrink_to_fit() {
        _rCount.shrink_to_fit();
    }

    template<typename... Args>
    std::pair<iterator, bool> emplace(Args&&... args) {
        return _rCount.emplace(std::forward<Args>(args)...);
    }
    template<typename... Args>
    iterator emplace_hint(const_iterator hint, Args&&... args) {
        return _rCount.emplace_hint(hint, std::forward<Args>(args)...);
    }

    std::pair<iterator, bool> insert(value_type const &x);

    mapped_type const& at(key_type const &key) const;

    bool operator==(ResidueCount const &rhs) const;

    bool operator<(ResidueCount const &rhs) const;

    mapped_type& operator[](key_type const residue);

    // Overload to use [] as a const operation
    mapped_type operator[](key_type const residue) const;

    void operator+=(ResidueCount const &rhs);

    void operator-=(ResidueCount const &rhs);

    friend std::ostream& operator<<(std::ostream &out, ResidueCount const &rhs);

    ~ResidueCount() {}
private:
    impl_type _rCount;

    void clearZeroes();
};

std::size_t hash_value(ResidueCount const &rCount);

ResidueCount operator-(ResidueCount lhs, ResidueCount const &rhs);

ResidueCount operator+(ResidueCount lhs, ResidueCount const &rhs);

} /* namespace apollo */

#endif /* apollo_residuecount_hpp_ */

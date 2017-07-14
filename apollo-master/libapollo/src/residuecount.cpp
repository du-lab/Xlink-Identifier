/**
 * @file    residuecount.cpp
 * @brief   Defines ResidueCount
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#include "residuecount.hpp"

#include <boost/functional/hash.hpp>

namespace apollo {

ResidueCount::ResidueCount(types::sequence_string_t const &sequenceStr) {
    using types::sequence_string_t;
    // Add up each amino acid's count in a sequence
    for(auto const &residue : sequenceStr) {
        _rCount[residue] += 1;
    }
}

/* Copy constructor */
ResidueCount::ResidueCount(ResidueCount const &rhs) {
    _rCount =  rhs._rCount;
}

/* Move constructor */
ResidueCount::ResidueCount(ResidueCount &&rhs) :
    _rCount(std::move(rhs._rCount)) {}

ResidueCount& ResidueCount::operator=(ResidueCount &&rhs) {
    if (this != &rhs) {
        _rCount = std::move(rhs._rCount);
    }
    return *this;
}

ResidueCount& ResidueCount::operator=(ResidueCount const &rhs) {
    if (this != &rhs) {
        _rCount = rhs._rCount;
    }
    return *this;
}

ResidueCount::mapped_type ResidueCount::aggregateCount() const {
    mapped_type aggCount = 0;
    for(auto const &kvPair : _rCount) {
        aggCount += kvPair.second;
    }
    return aggCount;
}

ResidueCount::iterator ResidueCount::begin() {
    return _rCount.begin();
}

ResidueCount::const_iterator ResidueCount::begin() const {
    return _rCount.begin();
}

ResidueCount::const_iterator ResidueCount::cbegin() const {
    return _rCount.cbegin();
}

ResidueCount::iterator ResidueCount::end() {
    return _rCount.end();
}

ResidueCount::const_iterator ResidueCount::end() const {
    return _rCount.end();
}

ResidueCount::const_iterator ResidueCount::cend() const {
    return _rCount.cend();
}

void ResidueCount::clear() {
    _rCount.clear();
}

bool ResidueCount::empty() const {
    if (!_rCount.empty() &&
        (aggregateCount() > 0)) {
        return false;
    }
    return true;
}

ResidueCount::size_type ResidueCount::size() const {
    return _rCount.size();
}

std::pair<ResidueCount::iterator, bool> ResidueCount::insert(value_type const &x) {
    return _rCount.insert(x);
}

ResidueCount::mapped_type const& ResidueCount::at(key_type const &key) const {
    return _rCount.at(key);
}

bool ResidueCount::operator==(ResidueCount const &rhs) const {
    if(_rCount == rhs._rCount) {
        return true;
    }
    return false;
}

bool ResidueCount::operator<(ResidueCount const &rhs) const {
    if(_rCount < rhs._rCount) {
        return true;
    }
    return false;
}

ResidueCount::mapped_type& ResidueCount::operator[](key_type const residue) {
    return _rCount[residue];
}

ResidueCount::mapped_type ResidueCount::operator[](key_type const residue) const {
    const_iterator it = _rCount.find(residue);
    if (it != end()) {
        return it->second;
    } else {
        return 0;
    }
}

void ResidueCount::operator+=(ResidueCount const &rhs) {
    for(auto const &rCountPair :  rhs) {
        operator[](rCountPair.first) += rCountPair.second;
    }
    clearZeroes();
}

void ResidueCount::operator-=(ResidueCount const &rhs) {
    for(auto const &rCountPair :  rhs) {
        operator[](rCountPair.first) -= rCountPair.second;
    }
    clearZeroes();
}

void ResidueCount::clearZeroes() {
    ResidueCount::iterator it = begin();
    while(it != end()) {
        if (it->second == 0) {
            it = _rCount.erase(it);
        } else {
            ++it;
        }
    }
}

// hash_value was originally implemented as:
// return boost::hash_range(rCount.begin(), rCount.end());

// However, in Boost 1.51.0, changes done to the hash library caused
// the compiler to freak out the dimensionless units. I may be able to fix it later
// but I'm busy finishing the product.
// - Adam

std::size_t hash_value(apollo::ResidueCount const &rCount) {
    std::size_t seed = 0;
    for(auto const &rCountPair : rCount) {
        boost::hash_combine(seed, rCountPair.first);
        boost::hash_combine(seed, rCountPair.second.value());
    }
    return 0;
}

ResidueCount operator-(ResidueCount lhs, ResidueCount const &rhs) {
    lhs -= rhs;
    return lhs;
}

ResidueCount operator+(ResidueCount lhs, ResidueCount const &rhs) {
    lhs += rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream &out, ResidueCount const &rhs) {
    for(auto const &rCountPair :  rhs) {
        ResidueCount::key_type const residue = rCountPair.first;
        ResidueCount::mapped_type const count = rCountPair.second;
        out << "(" << residue << ":" << count.value() << ")";
    }
    return out;
}



} /* namespace apollo */


/**
 * @file    modlocgen.cpp
 * @brief   Generates all possible dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */
#include <iostream>
#include <algorithm>
#include <iterator>

#include <boost/combination.hpp>
#include "modlocgen.hpp"

namespace apollo {

LocSet residueLocations(SequenceI const &seq, ResidueSet const &rSet) {
    using std::distance;

    LocSet lVector;
    auto seqBegin = seq.begin();
    auto seqIt = seqBegin;
    auto seqEnd = seq.end();

    for(; seqIt != seqEnd; ++seqIt) {
        ResidueSet::const_iterator rSetIt = rSet.find(*seqIt);
        if (rSetIt != rSet.end()) {
            lVector.emplace(distance(seqBegin, seqIt));
        }
    }
    return lVector;
}


ModLocGen::ModLocGen(SequenceI const &seq, types::count_t locCount, ResidueSet const &rSet) :
    _super(),
    _locCount(locCount),
    _locations(residueLocations(seq, rSet)) {}

ModLocGen::ModLocGen(ModLocGen const &rhs) :
    _super(rhs),
    _locCount(rhs._locCount),
    _locations(rhs._locations) {}

ModLocGen::ModLocGen(ModLocGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _locCount(rhs._locCount),
    _locations(std::move(rhs._locations)) {}

ModLocGen& ModLocGen::operator=(ModLocGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _locCount = rhs._locCount;
        _locations = rhs._locations;

    }
    return *this;
}

ModLocGen& ModLocGen::operator=(ModLocGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _locCount = rhs._locCount;
        _locations = std::move(rhs._locations);
    }
    return *this;
}

bool ModLocGen::operator()(value_type &rv) {
    using boost::next_combination;

    $gen_start;

    // Only yield locations if there are locations to yield
    if (_locCount > 0 && _locations.size() > 0) {
        $yield(rv);
    
        while (next_combination(_locations.begin(),
            std::next(_locations.begin(), _locCount),
            _locations.end())) {
            
            $yield(rv);
        }
    }
    $gen_stop;
}

void ModLocGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

bool ModLocGen::operator==(ModLocGen const &rhs) const {
    if (_super::operator==(rhs) &&
        _locCount == rhs._locCount &&
        _locations == rhs._locations
        ) {
        return true;
    } else {
        return false;
    }
}

LocSet ModLocGen::genReturn() const {
    LocSet lVector(_locations.begin(), std::next(_locations.begin(), _locCount));
    return lVector;
}

} /* namespace apollo */

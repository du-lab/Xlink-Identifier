/**
 * @file    multimodcountgen.cpp
 * @brief   Generates all possible dynamic modifications
 *      with multiple mods possible
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/23
 * @copyright 2012
 */

#include <algorithm>
#include <utility>
#include <iostream>
#include "multimodcountgen.hpp"


namespace apollo {

MultiModCountGen::MultiModCountGen(ResidueMod const &rmMap, 
    ResidueCount const &upper_rCount,
    ResidueCount const &lower_rCount) {

    typedef ResidueCount::key_type aa_t;
    typedef ResidueCount::mapped_type count_t;
    using filter::range_ModCount;
    iter_type const fModEnd;
    for(auto const &upperCountPair : upper_rCount) {
        aa_t const aa = upperCountPair.first;
        count_t const upperCount = upperCountPair.second;
        count_t const lowerCount = lower_rCount[aa];

        if (upperCount > 0) {
            ResidueCount subModCount;
            count_t const upperRange = upperCount + 1;
            for(auto const &mod : rmMap.at(aa)) {
                subModCount.emplace(mod, upperCount);
            }
            range_ModCount filter(upperRange, lowerCount);
            ModCountIter modCountIter = make_geniter<ModCountGen>(subModCount);
            iter_type fModIter = iter_type(filter, modCountIter);
            range_iter_type fRangeIter = range_iter_type(fModIter, fModEnd);
            _rangeMap.emplace(aa, fRangeIter);
        }
    }
    if(!_rangeMap.empty()) {
        _rangeIt = _rangeMap.begin();
    }
}

MultiModCountGen::MultiModCountGen(MultiModCountGen const &rhs) :
    _super(rhs){
        using std::distance;
	_rangeMap = rhs._rangeMap;
        range_map_type::difference_type dist =
            distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt);
        _rangeIt = std::next(_rangeMap.begin(), dist);
}

MultiModCountGen::MultiModCountGen(MultiModCountGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _rangeMap(std::move(rhs._rangeMap)),
    _rangeIt(std::move(rhs._rangeIt)) {}

MultiModCountGen& MultiModCountGen::operator=(MultiModCountGen const &rhs) {
    if (this != &rhs) {
        using std::distance;
        _super::operator=(static_cast<_super const&>(rhs));
        _rangeMap = rhs._rangeMap;
        range_map_type::difference_type dist =
            distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt);
        _rangeIt = std::next(_rangeMap.begin(), dist);
    }
    return *this;
}

MultiModCountGen& MultiModCountGen::operator=(MultiModCountGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _rangeMap = std::move(rhs._rangeMap);
        _rangeIt = std::move(rhs._rangeIt);
    }
    return *this;
}


bool MultiModCountGen::operator()(value_type &rv) {
    $gen_start;
    $yield(rv);
    if (!_rangeMap.empty()) {
        for(_rangeIt = _rangeMap.begin(); ;) {
            ++(_rangeIt->second);
            if (_rangeIt->second.atEnd()) {
                if (std::next(_rangeIt) == _rangeMap.end()) {
                    break;
                } else {
                    _rangeIt->second.restart();
                    ++_rangeIt;
                }
            } else {
                $yield(rv);
                _rangeIt = _rangeMap.begin();
            }
        }
    }
    $gen_stop;
}

void MultiModCountGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

MultiRefResidueCount MultiModCountGen::genReturn() const {
    MultiRefResidueCount returnValue;
    for(auto const &rangeMapPair : _rangeMap) {
        if (!rangeMapPair.second->empty()) {
            range_map_type::key_type const aa = rangeMapPair.first;
            returnValue.emplace(aa, std::cref(*(rangeMapPair.second)));
        }
    }
    return returnValue;
}

bool MultiModCountGen::operator==(MultiModCountGen const &rhs) const {
    using std::distance;
    if (_super::operator==(rhs) &&
        (_rangeMap == rhs._rangeMap) &&
        (distance<range_map_type::const_iterator>(_rangeMap.begin(), _rangeIt)
         == distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt))) {

        return true;
    } else {
        return false;
    }
}

} /* namespace apollo */

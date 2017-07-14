/**
 * @file    modcountgen.cpp
 * @brief   Generates all possible dynamic modifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#include <algorithm>
#include <iterator>

#include "modcountgen.hpp"

 namespace apollo {

ModCountGen::ModCountGen(ResidueCount const &rCount) {
    for (auto const &rCountPair : rCount) {
        ResidueCount::key_type const aa = rCountPair.first;
        ResidueCount::mapped_type const aaCount = rCountPair.second;
        if (aaCount > 0) {
            range_type countRange(0, aaCount +  1);
            range_iter_type countRangeIter(countRange);
            _rangeMap.emplace(aa, countRangeIter);
        }
    }
}

ModCountGen::ModCountGen(ModCountGen const &rhs) :
    _super(rhs) {
        using std::distance;
        _rangeMap = rhs._rangeMap;
        range_map_type::difference_type dist =
            distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt);
        _rangeIt = std::next(_rangeMap.begin(), dist);
}

ModCountGen::ModCountGen(ModCountGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _rangeMap(std::move(rhs._rangeMap)),
    _rangeIt(std::move(rhs._rangeIt)) {}

ModCountGen& ModCountGen::operator=(ModCountGen const &rhs) {
    if (this != &rhs) {
        using std::distance;
        _super::operator=(rhs);
        _rangeMap = rhs._rangeMap;
        range_map_type::difference_type dist =
            distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt);
        _rangeIt = std::next(_rangeMap.begin(), dist);
    }
    return *this;
}

ModCountGen& ModCountGen::operator=(ModCountGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _rangeMap = std::move(rhs._rangeMap);
        _rangeIt = std::move(rhs._rangeIt);
    }
    return *this;
}

bool ModCountGen::operator()(ResidueCount &rv) {
    $gen_start
    $yield(rv);
    if (_rangeMap.size() > 0) {
        for (_rangeIt = _rangeMap.begin(); ; ) {
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
    $gen_stop
}

void ModCountGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

bool ModCountGen::operator==(ModCountGen const &rhs) const {
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

ResidueCount ModCountGen::genReturn() const {
    ResidueCount returnValue;
    for(auto const &rangePair : _rangeMap ) {
        ResidueCount::key_type const aa = rangePair.first;
        ResidueCount::mapped_type const aaCount = *(rangePair.second);
        if (aaCount > 0) {
            returnValue[aa] = aaCount;
        }
    }
    return returnValue;
}

 } /* namespace apollo */

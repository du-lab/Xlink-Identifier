/**
 * @file    multimodlocgen.cpp
 * @brief   Generates all possible multiple dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#include <algorithm>
#include <utility>
#include <iostream>

#include <boost/log/trivial.hpp>

#include "multimodlocgen.hpp"

namespace apollo {

MultiModLocGen::MultiModLocGen(SequenceI const &seq, ResidueCount const &dynamicModCount, ResidueMod const &iDynamicMod) {
    for (auto const &modCountPair : dynamicModCount) {
        auto const mod = modCountPair.first;
        auto const modCount = modCountPair.second;

        _rangeMap.emplace(mod, make_geniter<ModLocGen>(seq, modCount, iDynamicMod.at(mod)));
    }
}

MultiModLocGen::MultiModLocGen(MultiModLocGen const &rhs) :
    _super(rhs) {
    using std::distance;
    _rangeMap = rhs._rangeMap;

    range_map_type::difference_type dist = 
        distance<range_map_type::const_iterator>(rhs._rangeMap.begin(), rhs._rangeIt);
    _rangeIt = std::next(_rangeMap.begin(), dist);

}

MultiModLocGen::MultiModLocGen(MultiModLocGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _rangeMap(std::move(rhs._rangeMap)),
    _rangeIt(std::move(rhs._rangeIt)) {}

MultiModLocGen& MultiModLocGen::operator=(MultiModLocGen const &rhs) {
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

MultiModLocGen& MultiModLocGen::operator=(MultiModLocGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _rangeMap = std::move(rhs._rangeMap);
        _rangeIt = std::move(rhs._rangeIt);
    }
    return *this;
}

bool MultiModLocGen::operator()(value_type &rv) {
    $gen_start;
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
    $gen_stop;
}

void MultiModLocGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool MultiModLocGen::operator==(MultiModLocGen const &rhs) const {
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

MultiRefLocSet MultiModLocGen::genReturn() const {
    MultiRefLocSet returnValue;
    for (auto const &rangeMapPair : _rangeMap) {
        if (!rangeMapPair.second->empty()) {
            range_map_type::key_type const aa = rangeMapPair.first;
            returnValue.emplace(aa, std::cref(*(rangeMapPair.second)));
        }
    }
    return returnValue;
}

} /* namespace apollo */

/**
 * @file    ntrypticgen.cpp
 * @brief   Generator and iterator for n tryptic
 *  theoretical digestion
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/16
 * @copyright 2012
 */

#include <iterator>
#include <algorithm>
#include <iostream>
#include <vector>
#include <boost/container/container_fwd.hpp>

#include "../core/sequencepart.hpp"
#include "ntrypticgen.hpp"

namespace apollo {

typedef std::vector<NTrypticGen::size_type> LocationVector;

NTrypticGen::NTrypticGen(SequenceI::shp parentShp,
        size_type trypticity,
        regex_type const digestRegex,
        tolerance_type tolerance) :
    _parentShp(parentShp),
    _trypticity(trypticity),
    _tolerance(tolerance) {
    using std::sort;
    using std::unique;
    using boost::container::ordered_unique_range;

    regex_iter_type regexCurrent(_parentShp->begin(),
        _parentShp->end(),
        digestRegex);
    regex_iter_type regexEnd;

    LocationVector lVector;
    for( ; regexCurrent != regexEnd; ++regexCurrent) {
        lVector.emplace_back(regexCurrent->position());
    }
    sort(lVector.begin(), lVector.end());
    unique(lVector.begin(), lVector.end());
    PositionSet tempTrypticPositions(ordered_unique_range,
        std::make_move_iterator(lVector.begin()),
        std::make_move_iterator(lVector.end()));
    _trypticPositions = std::move(tempTrypticPositions);
}

NTrypticGen::NTrypticGen(NTrypticGen const &other) :
    _super(other),
    _currentLength(other._currentLength),
    _currentNmc(other._currentNmc),
    _tolerance(other._tolerance),
    _parentShp(other._parentShp),
    _trypticity(other._trypticity),
    _currentTrypticity(other._currentTrypticity),
    _trypticPositions(other._trypticPositions),
    _first(other._first),
    _last(other._last) {}

NTrypticGen::NTrypticGen(NTrypticGen &&other) :
    _super(std::forward<_super>(other)),
    _currentLength(other._currentLength),
    _currentNmc(other._currentNmc),
    _tolerance(other._tolerance),
    _parentShp(std::move(other._parentShp)),
    _trypticity(other._trypticity),
    _currentTrypticity(other._currentTrypticity),
    _trypticPositions(std::move(other._trypticPositions)),
    _first(other._first),
    _last(other._last) {}

NTrypticGen& NTrypticGen::operator=(NTrypticGen const &other) {
    if (this != &other) {
        _super::operator=(other);
        _currentLength = other._currentLength;
        _currentNmc = other._currentNmc;
        _tolerance = other._tolerance;
        _parentShp = other._parentShp;
        _trypticity = other._trypticity;
        _currentTrypticity = other._currentTrypticity;
        _trypticPositions = other._trypticPositions;
        _first = other._first;
        _last = other._last;
    }
    return *this;
}

NTrypticGen& NTrypticGen::operator=(NTrypticGen &&other) {
    if (this != &other) {
        _super::operator=(std::forward<_super>(other));
        _currentLength = other._currentLength;
        _currentNmc = other._currentNmc;
        _tolerance = other._tolerance;
        _parentShp = std::move(other._parentShp);
        _trypticity = other._trypticity;
        _currentTrypticity = other._currentTrypticity;
        _trypticPositions = std::move(other._trypticPositions);
        _first = other._first;
        _last = other._last;
    }
    return *this;
}


bool NTrypticGen::operator()(value_type &rv) {
    $gen_start;
    _first = 0;
    while (_first < _parentShp->length()) {
        _currentLength = 0;
        _currentNmc = 0;
        while ((_first + _currentLength) < _parentShp->length()) {
            _last = _first + _currentLength;
            _currentLength += 1;
            _currentTrypticity = 0;
            if (firstIsTryptic()) {
                _currentTrypticity += 1;
            }
            if (lastIsTryptic()) {
                _currentTrypticity += 1;
            }
            if ((_currentTrypticity == _trypticity) &&
                _tolerance.withinTolerance(_currentLength, _currentNmc)) {

                $yield(rv);
            } else if (_tolerance.isTooLarge(_currentLength, _currentNmc)) {
                break;
            }
            if (lastIsTryptic()) {
                _currentNmc += 1;
            }
        }
        _first += 1;
    }
    $gen_stop;
}

void NTrypticGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

bool NTrypticGen::operator==(NTrypticGen const &other) const {
    if (_super::operator==(other)) {
        return (
            (_currentLength == other._currentLength) &&
            (_currentNmc == other._currentNmc) &&
            (_tolerance == other._tolerance) &&
            (_parentShp == other._parentShp) &&
            (_trypticity == other._trypticity) &&
            (_currentTrypticity == other._currentTrypticity) &&
            (_first == other._first) &&
            (_last == other._last) &&
            (_trypticPositions == other._trypticPositions)
            );
    } else {
        return false;
    }
}

bool NTrypticGen::firstIsTryptic() const {
    if (_first == 0) {
        if (Nh2TerminusIsTryptic) {
            return true;
        } else {
            return false;
        }
    } else {
        if (_trypticPositions.find(_first - 1) != _trypticPositions.end()) {
            return true;
        } else {
            return false;
        }
    }
}

bool NTrypticGen::lastIsTryptic() const {
    if ((_first + _currentLength) == _parentShp->length()) {
        if (CTerminusIsTryptic) {
            return true;
        } else {
            return false;
        }
    } else {
        if (_trypticPositions.find(_last) != _trypticPositions.end()) {
            return true;
        } else {
            return false;
        }
    }
}

SequenceI::shp NTrypticGen::genReturn() const {
    using std::make_shared;
    return make_shared<SequencePart>(_parentShp,
        _first,
        _currentLength);
}

}

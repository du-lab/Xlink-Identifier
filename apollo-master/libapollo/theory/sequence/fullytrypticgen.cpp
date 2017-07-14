/**
 * @file    fullytrypticgen.cpp
 * @brief   Generator for fully tryptic theoretical digestion
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */

#include <algorithm>
#include <iterator>
#include <iostream>
#include <boost/utility.hpp>
#include <boost/assert.hpp>
#include <boost/log/trivial.hpp>
#include "../core/sequencepart.hpp"
#include "../core/sequencechain.hpp"
#include "fullytrypticgen.hpp"

namespace apollo {

typedef FullyTrypticGen::value_type value_type;

FullyTrypticGen::FullyTrypticGen(SequenceI::shp parentShp,
    regex_type const digestRegex,
    tolerance_type tolerance) :
    _tolerance(tolerance) {

    using namespace boost::xpressive;
    using std::make_shared;

    //BOOST_LOG_TRIVIAL(info) << *parentShp;
    regex_type const fullyTrypticRegex = -*_w >> digestRegex | *_w;

    regex_iter_type regexCurrent(parentShp->begin(),
        parentShp->end(),
        fullyTrypticRegex);

    regex_iter_type regexEnd;
    size_type processedLength = 0;

    for( ; regexCurrent != regexEnd; ++regexCurrent) {
        // Ignore any empty matches, as at the end point
        if (regexCurrent->length() > 0) {
            SequenceI::shp digestedSeq =
                make_shared<SequencePart>(parentShp,
                    regexCurrent->position(),
                    regexCurrent->length());

            processedLength += regexCurrent->length();

            //BOOST_LOG_TRIVIAL(info) << *digestedSeq ;
            _digestDeq.emplace_back(digestedSeq);
        }
    }
    _digestIter = _digestDeq.cbegin();
    // If the total length of the subsequences and the original sequence do not match
    // then the program is missing information. DO NOT COMMENT OUT THIS NEXT LINE!!! EVER!!!
    //BOOST_LOG_TRIVIAL(info) << "Parent Length: " << processedLength;
    //BOOST_LOG_TRIVIAL(info) << "Processed Length: " << parentShp->length();

    BOOST_ASSERT_MSG(processedLength == parentShp->length(),
        "Subsequence lengths do not match parent length");
}

FullyTrypticGen::FullyTrypticGen(FullyTrypticGen const &rhs) :
    _super(rhs),
    _digestDeq(rhs._digestDeq),
    _currentLength(rhs._currentLength),
    _currentNmc(rhs._currentNmc),
    _tolerance(rhs._tolerance) {
    using std::distance;
    deque_type::difference_type iterDistance =
        distance(rhs._digestDeq.cbegin(), rhs._digestIter);
    _digestIter = std::next(_digestDeq.cbegin(), iterDistance);
}


FullyTrypticGen::FullyTrypticGen(FullyTrypticGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _currentLength(rhs._currentLength),
    _currentNmc(rhs._currentNmc),
    _tolerance(rhs._tolerance),
    _digestIter(std::move(rhs._digestIter)),
    _digestDeq(std::move(rhs._digestDeq)) {}

FullyTrypticGen& FullyTrypticGen::operator=(FullyTrypticGen const &rhs) {
    using std::distance;
    if (this != &rhs) {
        _super::operator=(rhs);
        _currentLength = rhs._currentLength;
        _currentNmc = rhs._currentNmc;
        _tolerance = rhs._tolerance;
        _digestDeq = rhs._digestDeq;
        deque_type::difference_type iterDistance =
            distance(rhs._digestDeq.cbegin(), rhs._digestIter);
        _digestIter = std::next(_digestDeq.cbegin(), iterDistance);
    }
    return *this;
}

FullyTrypticGen& FullyTrypticGen::operator=(FullyTrypticGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _currentLength = rhs._currentLength;
        _currentNmc = rhs._currentNmc;
        _tolerance = rhs._tolerance;
        _digestIter = std::move(rhs._digestIter);
        _digestDeq = std::move(rhs._digestDeq);
    }
    return *this;
}

bool FullyTrypticGen::operator==(FullyTrypticGen const &rhs) const{
    if (_super::operator==(rhs)) {
        return (
            (_currentLength == rhs._currentLength) &&
            (_currentNmc == rhs._currentNmc) &&
            (_tolerance == rhs._tolerance) &&
            (_digestIter == rhs._digestIter) &&
            (_digestDeq == rhs._digestDeq)
            );
    } else {
        return false;
    }
}

bool FullyTrypticGen::operator()(value_type &rv) {
    $gen_start;
    while (!_digestDeq.empty()) {
        _digestIter = _digestDeq.cbegin();
        _currentLength = 0;
        _currentNmc = 0;
        while (_digestIter != _digestDeq.cend()) {
            _currentLength += (*_digestIter)->length();
            ++_digestIter;
            if (_tolerance.withinTolerance(_currentLength, _currentNmc)) {
                $yield(rv);
            } else if (_tolerance.isTooLarge(_currentLength, _currentNmc)) {
                break;
            }
            _currentNmc += 1;
        }
        _digestDeq.pop_front();
    }
    $gen_stop;
}

void FullyTrypticGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

value_type FullyTrypticGen::genReturn() const {
    using std::make_shared;
    return make_shared<SequenceChain>(_digestDeq.cbegin(), _digestIter);
}

} /* namespace apollo */

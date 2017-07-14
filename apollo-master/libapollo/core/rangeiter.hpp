/**
 * @file    rangeiter.hpp
 * @brief   Represents begin, end, and current iter as a group
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#ifndef apollo_rangeiter_hpp_
#define apollo_rangeiter_hpp_

#include <utility>
#include <iterator>
#include <boost/iterator/iterator_traits.hpp>

namespace apollo {

template <typename IteratorT>
class RangeIter {
public:
    typedef typename boost::iterator_value<IteratorT>::type value_type;
    typedef typename boost::iterator_reference<IteratorT>::type reference_type;
    typedef typename boost::iterator_pointer<IteratorT>::type pointer_type;
    typedef typename boost::iterator_difference<IteratorT>::type difference_type;

    RangeIter() {}

    RangeIter(IteratorT begin, IteratorT end = IteratorT()) :
        _begin(begin), _current(_begin), _end(end) {}

    RangeIter(RangeIter const &rhs) :
        _begin(rhs._begin), _end(rhs._end) {
        if (rhs.atBegin()) {
            _current = _begin;
        } else if (rhs.atEnd()) {
            _current = _end;
        } else {
            _current = std::next(_begin, rhs.distance());
        }
    }

    RangeIter(RangeIter &&rhs) :
        _begin(std::move(rhs._begin)),
        _current(std::move(rhs._current)),
        _end(std::move(rhs._end)) {}

    template <typename RangeT>
    RangeIter(RangeT const &range) :
    _begin(range.begin()), _current(_begin), _end(range.end()) {}
    
    RangeIter& operator=(RangeIter const &rhs) {
        if (this != &rhs) {
            _begin = rhs._begin;
            _end = rhs._end;
            if (rhs.atBegin()) {
                _current = _begin;
            } else if (rhs.atEnd()) {
                _current = _end;
            } else {
                _current = std::next(_begin, rhs.distance());
            }
        }
        return *this;
    }

    RangeIter& operator=(RangeIter &&rhs) {
        if (this != &rhs) {
            _begin = std::move(rhs._begin);
            _current = std::move(rhs._current);
            _end = std::move(rhs._end);
        }
        return *this;
    }

    bool atBegin() const {
        return _current == _begin;
    }

    bool atEnd() const {
        return _current == _end;
    }

    difference_type distance() const {
        using std::distance;
        difference_type diff =
            distance(_begin, _current);
        return diff;
    }
    void restart() {
        _current = _begin;
    }

    IteratorT const& base() const {
        return _current;
    }

    reference_type operator*() const {
        return *_current;
    }

    pointer_type operator->() const {
        return &(*_current);
    }

    void operator++(void) {
        ++_current;
    }

    bool operator==(RangeIter const &other) const {
        if ((_current == other._current) &&
            (_begin == other._begin) &&
            (_end == other._end)) {
            return true;
        } else {
            return false;
        }
    }

    ~RangeIter() {}
private:
    IteratorT _begin;
    IteratorT _current;
    IteratorT _end;
};



} /* namespace apollo */

#endif /* apollo_rangeiter_hpp_ */

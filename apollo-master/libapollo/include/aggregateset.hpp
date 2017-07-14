/**
 * @file    aggregateflatset.hpp
 * @brief   A flat set with the += operator. Used for ICL
 *  Necessary to work around a compiler bug in clang
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */


#ifndef apollo_aggregateset_hpp_
#define apollo_aggregateset_hpp_

#include <utility>

#include <boost/container/flat_set.hpp>

namespace apollo {

template <typename V>
class aggregate_set : public boost::container::flat_set<V> {
public:

aggregate_set(void) : _super() {}

aggregate_set(aggregate_set const &rhs) : _super(rhs) {}

aggregate_set(aggregate_set &&rhs) :
    _super(std::forward<_super>(rhs)) {}

aggregate_set& operator=(aggregate_set const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
    }
    return *this;
}

aggregate_set& operator=(aggregate_set &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
    }
    return *this;
}

using boost::container::flat_set<V>::emplace;

void operator+=(aggregate_set const &rhs) {
    for(auto const &val : rhs) {
        emplace(val);
    }
}

private:
    typedef boost::container::flat_set<V> _super;
};

} /* namespace apollo */

#endif /* apollo_aggregateset_hpp_ */

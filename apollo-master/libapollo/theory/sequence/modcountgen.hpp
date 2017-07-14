/**
 * @file    modcountgen.hpp
 * @brief   Generates all possible dynamic modification counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#ifndef apollo_modcountgen_hpp_
#define apollo_modcountgen_hpp_

#include <utility>

#include <boost/container/flat_map.hpp>
#include <boost/range/irange.hpp>

#include "residuecount.hpp"
#include "../core/generator.hpp"
#include "../core/rangeiter.hpp"

namespace apollo {

namespace detail {
typedef boost::integer_range<types::count_store_t> CountRange;
typedef RangeIter<CountRange::const_iterator> CountRangeIter;
typedef boost::container::flat_map<ResidueCount::key_type, CountRangeIter> ModCountRange;
}

class ModCountGen : public Generator<ResidueCount> {
public:
    typedef detail::CountRange range_type;
    typedef detail::CountRangeIter range_iter_type;
    typedef detail::ModCountRange range_map_type;

    ModCountGen() : _super() {}

    ModCountGen(ResidueCount const &rCount);

    ModCountGen(ModCountGen const &rhs);

    ModCountGen(ModCountGen &&rhs);

    ModCountGen& operator=(ModCountGen const &rhs);

    ModCountGen& operator=(ModCountGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(ModCountGen const &rhs) const;

    ~ModCountGen() {}
private:
    typedef Generator<ResidueCount> _super;
    range_map_type _rangeMap;
    range_map_type::iterator _rangeIt;

    ResidueCount genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_modcountgen_hpp_ */

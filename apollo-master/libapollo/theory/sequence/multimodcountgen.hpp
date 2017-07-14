/**
 * @file    multimodcountgen.hpp
 * @brief   Generates all possible dynamic modifications
 *      with multiple mods possible
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */


#ifndef apollo_multimodcountgen_hpp_
#define apollo_multimodcountgen_hpp_

#include <boost/iterator/filter_iterator.hpp>
#include <boost/container/flat_map.hpp>

#include "sequenceinterface.hpp"
#include "residuecount.hpp"
#include "residuemod.hpp"

#include "../core/generator.hpp"
#include "../core/rangeiter.hpp"
#include "../core/multirefresiduecount.hpp"
#include "../filter/f_modcount.hpp"
#include "modcountiter.hpp"

namespace apollo {

namespace detail {

typedef boost::filter_iterator<filter::range_ModCount, ModCountIter> FModIter;
typedef RangeIter<FModIter> FModRangeIter;
typedef boost::container::flat_map<ResidueCount::key_type, FModRangeIter> FModCountRange;
} /* namespace detail */

class MultiModCountGen : public Generator<MultiRefResidueCount> {
public:
    MultiModCountGen() : _super() {}

    MultiModCountGen(ResidueMod const &rmMap, 
        ResidueCount const &upper_rCount,
        ResidueCount const &lower_rCount = ResidueCount());

    MultiModCountGen(MultiModCountGen const &rhs);

    MultiModCountGen(MultiModCountGen &&rhs);

    MultiModCountGen& operator=(MultiModCountGen const &rhs);

    MultiModCountGen& operator=(MultiModCountGen && rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(MultiModCountGen const &rhs) const;

    ~MultiModCountGen() {}
private:
    typedef Generator<MultiRefResidueCount> _super;
    typedef detail::FModIter iter_type;
    typedef detail::FModRangeIter range_iter_type;
    typedef detail::FModCountRange range_map_type;

    range_map_type _rangeMap;
    range_map_type::iterator _rangeIt;

    MultiRefResidueCount genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_multimodcountgen_hpp_ */

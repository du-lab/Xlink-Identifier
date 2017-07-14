/**
 * @file    multimodlocgen.hpp
 * @brief   Generates all possible multiple dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#ifndef apollo_multimodlocgen_hpp_
#define apollo_multimodlocgen_hpp_

#include <boost/container/flat_map.hpp>

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "residuecount.hpp"
#include "residuemod.hpp"

#include "../core/generator.hpp"
#include "../core/rangeiter.hpp"
#include "../core/multireflocset.hpp"
#include "modlociter.hpp"

namespace apollo {

namespace detail {

typedef RangeIter<ModLocIter> ModLocRangeIter;

typedef boost::container::flat_map<ResidueCount::key_type, ModLocRangeIter> ModLocRangeMap;
} /* namespace detail */

class MultiModLocGen : public Generator<MultiRefLocSet> {

public:
    MultiModLocGen() : _super() {}

    MultiModLocGen(SequenceI const &seq, ResidueCount const &dynamicModCount, ResidueMod const &iDynamicMod);

    MultiModLocGen(MultiModLocGen const &rhs);

    MultiModLocGen(MultiModLocGen &&rhs);

    MultiModLocGen& operator=(MultiModLocGen const &rhs);

    MultiModLocGen& operator=(MultiModLocGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(MultiModLocGen const &rhs) const;

    ~MultiModLocGen() {}
private:
    typedef Generator<MultiRefLocSet> _super;

    typedef detail::ModLocRangeIter range_iter_type;
    typedef detail::ModLocRangeMap range_map_type;

    range_map_type _rangeMap;
    range_map_type::iterator _rangeIt;
    
    MultiRefLocSet genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_multimodlocgen_hpp_ */

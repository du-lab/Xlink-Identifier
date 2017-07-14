/**
 * @file    sequencemhgen.hpp
 * @brief   Generates all possible mods and mod masses given a sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/14
 * @copyright 2012
 */

#ifndef apollo_sequencemhgen_hpp_
#define apollo_sequencemhgen_hpp_

#include <utility>
#include <functional>

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "residuecount.hpp"
#include "residuemod.hpp"
#include "residuemass.hpp"
#include "options.hpp"
#include "sequenceconfig.hpp"

#include "../core/generator.hpp"
#include "../core/rangeiter.hpp"

#include "multimodcountiter.hpp"

namespace apollo {

class SequenceMhGen : public Generator<types::mz_t> {
public:
    typedef types::mz_t mz_t;
    typedef types::dalton_t dalton_t;
    typedef MultiModCountIter mmod_iter_t;
    typedef std::reference_wrapper<ResidueMass const> residue_mass_cref;
    typedef RangeIter<mmod_iter_t> mmod_range_t;

    SequenceMhGen();

    SequenceMhGen(SequenceI const &seq, 
        SequenceOptions const &sOptions);

    SequenceMhGen(SequenceMhGen const &rhs);

    SequenceMhGen(SequenceMhGen &&rhs);

    SequenceMhGen& operator=(SequenceMhGen const &rhs);

    SequenceMhGen& operator=(SequenceMhGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    dalton_t mass() const;

    dalton_t hydralizedMass() const;

    dalton_t residueMass() const;

    dalton_t hydralizedResidueMass() const;

    dalton_t staticMass() const;

    ResidueCount staticMods() const;

    dalton_t dynamicMass() const;

    ResidueCount dynamicMods() const;

    SequenceConfig config() const;

    bool operator==(SequenceMhGen const &rhs) const;

    ~SequenceMhGen() {}
private:
    typedef Generator<mz_t> _super;
    residue_mass_cref _staticModMasses;
    residue_mass_cref _dynamicModMasses;
    mmod_range_t _staticModRange;
    mmod_range_t _dynamicModRange;
    dalton_t _residueMass;
    dalton_t _staticMass;
    dalton_t _dynamicMass;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_sequencemassgen_hpp_ */

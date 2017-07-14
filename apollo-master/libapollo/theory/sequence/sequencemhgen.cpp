/**
 * @file    SequenceMhGen.cpp
 * @brief   Generates all possible mods and mod masses given a sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/14
 * @copyright 2012
 */

#include <algorithm>

#include "mz.hpp"
#include "units.hpp"
#include "../core/stdmass.hpp"
#include "../core/residuecalc.hpp"
#include "sequencemhgen.hpp"


namespace apollo {

using units::dalton_mass;

typedef SequenceMhGen::dalton_t dalton_t;

namespace detail {
    ResidueMass const emptyRMass;
}

SequenceMhGen::SequenceMhGen(): 
    _super(),
    _staticModMasses(detail::emptyRMass),
    _dynamicModMasses(detail::emptyRMass),
    _residueMass(0.0f * dalton_mass),
    _staticMass(0.0f * dalton_mass),
    _dynamicMass(0.0f * dalton_mass) {}

SequenceMhGen::SequenceMhGen(SequenceI const &seq, 
    SequenceOptions const &sOptions) : 
    _super(),
    _staticModMasses(sOptions.staticModMasses),
    _dynamicModMasses(sOptions.dynamicModMasses),
    _residueMass(0.0f * dalton_mass),
    _staticMass(0.0f * dalton_mass),
    _dynamicMass(0.0f * dalton_mass) {

    using fn::massFromSequence;
    using fn::rCountFromSequence;

    // calculating the bare mass -> just total mass
    _residueMass = massFromSequence(seq, sOptions.stdResidueMass);

    ResidueCount staticModCount = rCountFromSequence(seq, sOptions.staticMods);

    // QUESTION make sure this is correct becuase static mods are ALWAYS modified
    _staticModRange = 
        mmod_range_t(
            make_geniter<MultiModCountGen>(sOptions.staticMods, 
                staticModCount, 
                staticModCount)
        );

    ResidueCount dynamicModCount = rCountFromSequence(seq, sOptions.dynamicMods);
    _dynamicModRange =
        mmod_range_t(
            make_geniter<MultiModCountGen>(sOptions.dynamicMods, 
                dynamicModCount)
        );
}

SequenceMhGen::SequenceMhGen(SequenceMhGen const &rhs) :
    _super(rhs),
    _staticModMasses(rhs._staticModMasses),
    _dynamicModMasses(rhs._dynamicModMasses),
    _staticModRange(rhs._staticModRange),
    _dynamicModRange(rhs._dynamicModRange),
    _residueMass(rhs._residueMass),
    _staticMass(rhs._staticMass),
    _dynamicMass(rhs._dynamicMass) {}

SequenceMhGen::SequenceMhGen(SequenceMhGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _staticModMasses(rhs._staticModMasses),
    _dynamicModMasses(rhs._dynamicModMasses),
    _staticModRange(std::move(rhs._staticModRange)),
    _dynamicModRange(std::move(rhs._dynamicModRange)),
    _residueMass(rhs._residueMass),
    _staticMass(rhs._staticMass),
    _dynamicMass(rhs._dynamicMass) {}

SequenceMhGen& SequenceMhGen::operator=(SequenceMhGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _staticModMasses = rhs._staticModMasses;
        _dynamicModMasses = rhs._dynamicModMasses;
        _staticModRange = rhs._staticModRange;
        _dynamicModRange = rhs._dynamicModRange;
        _residueMass = rhs._residueMass;
        _staticMass = rhs._staticMass;
        _dynamicMass = rhs._dynamicMass;
    }
    return *this;
}

SequenceMhGen& SequenceMhGen::operator=(SequenceMhGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _staticModMasses = rhs._staticModMasses;
        _dynamicModMasses = rhs._dynamicModMasses;
        _staticModRange = std::move(rhs._staticModRange);
        _dynamicModRange = std::move(rhs._dynamicModRange);
        _residueMass = rhs._residueMass;
        _staticMass = rhs._staticMass;
        _dynamicMass = rhs._dynamicMass;
    }
    return *this;
}

bool SequenceMhGen::operator()(value_type &rv) {
    using fn::massFromMultiResidueCount;
    $gen_start;
    for( ; !_staticModRange.atEnd(); ++_staticModRange) {
        _staticMass = 
            massFromMultiResidueCount(*_staticModRange, _staticModMasses);
        _dynamicModRange.restart();
        for( ; !_dynamicModRange.atEnd(); ++_dynamicModRange) {
            _dynamicMass = 
                massFromMultiResidueCount(*_dynamicModRange, _dynamicModMasses);
            $yield(rv);
        }
    }
    $gen_stop;
}

void SequenceMhGen::generate(value_type &rv) const {
    rv = genReturn();
}

dalton_t SequenceMhGen::mass() const {
return residueMass() + staticMass() + dynamicMass();
}

dalton_t SequenceMhGen::hydralizedMass() const {
    return hydralizedResidueMass() + staticMass() + dynamicMass(); 
}

dalton_t SequenceMhGen::residueMass() const {
    return _residueMass;
}

dalton_t SequenceMhGen::hydralizedResidueMass() const {
    using stdmass::H2O_da;
    return _residueMass + H2O_da;
}

dalton_t SequenceMhGen::staticMass() const {
    return _staticMass;
}

ResidueCount SequenceMhGen::staticMods() const {
    using fn::aggregateMultiResidueCount;
    return aggregateMultiResidueCount(*_staticModRange);
}

dalton_t SequenceMhGen::dynamicMass() const {
    return _dynamicMass;
}

ResidueCount SequenceMhGen::dynamicMods() const {
    using fn::aggregateMultiResidueCount;
    return aggregateMultiResidueCount(*_dynamicModRange);
}

SequenceConfig SequenceMhGen::config() const {
    return SequenceConfig(genReturn(), staticMods(), dynamicMods());
}

bool SequenceMhGen::operator==(SequenceMhGen const &rhs) const {
    if (
        _super::operator==(rhs) &&
        (_staticModMasses == rhs._staticModMasses) &&
        (_dynamicModMasses == rhs._dynamicModMasses) &&
        (_residueMass == rhs._residueMass) && 
        (_staticMass == rhs._staticMass) &&
        (_dynamicMass == rhs._dynamicMass) &&
        (_staticModRange == rhs._staticModRange) &&
        (_dynamicModRange == rhs._dynamicModRange) 
    ) {
        return true;
    } else {
        return false;
    }
}

SequenceMhGen::value_type SequenceMhGen::genReturn() const {
    return Mz::MhFromM(hydralizedMass());
}


} /* namespace apollo */

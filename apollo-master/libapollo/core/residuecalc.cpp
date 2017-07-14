/**
 * @file    residuecalc.cpp
 * @brief   Various residue calculation functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/29
 * @copyright 2012
 */

#include "units.hpp"
#include "residuecalc.hpp"


namespace apollo {
namespace fn {

ResidueCount rCountToLoc(LocResidueMap const &lrMap, SequenceI::size_type const to) {
    ResidueCount rCount;
    auto const lrTo = lrMap.lower_bound(to);
    for(auto lrIt = lrMap.begin(); lrIt != lrTo; ++lrIt) {
        rCount[lrIt->second] += 1;
    }
    return rCount;
}

ResidueCount rCountFromLoc(LocResidueMap const &lrMap, SequenceI::size_type const from) {
    ResidueCount rCount;
    for(auto lrIt = lrMap.lower_bound(from); lrIt != lrMap.end(); ++lrIt) {
        rCount[lrIt->second] += 1;
    }
    return rCount;
}

ResidueMod invertResidueMod(ResidueMod const &rmMap) {
    ResidueMod iRMMap;
    for (auto const &rmPair : rmMap) {
        auto const &residue = rmPair.first;
        for (auto const &mod : rmPair.second) {
            iRMMap[mod].emplace(residue);
        }
    }
    return iRMMap;
}

LocResidueMap aggregateMultiLocSet(MultiRefLocSet const &mrls) {
    LocResidueMap lrMap;
    for(auto const &mLocSetPair : mrls) {
        for(auto const &loc : mLocSetPair.second.get()) {
            lrMap.emplace(loc, mLocSetPair.first);
        }
    }
    return lrMap;
}

ResidueCount rCountFromSequence(SequenceI const &seq, ResidueMod const &rmMap) {
    typedef ResidueCount::key_type aa_t;
    typedef ResidueCount::mapped_type count_t;

    using types::sequence_string_t;
    ResidueCount seqResidues;

    for(sequence_string_t::const_iterator it = seq.begin();
        it != seq.end();
        ++it) {

        if (rmMap.find(*it) != rmMap.end()) {
            seqResidues[*it] += 1;
        }
    }

    return seqResidues;
}

ResidueCount aggregateMultiResidueCount(MultiRefResidueCount const & mrrc) {
    ResidueCount aggregateCount;
    for(auto const &mrrPair : mrrc) {
        for(auto const &rCountPair : mrrPair.second.get()) {
            ResidueCount::key_type const aa = rCountPair.first;
            ResidueCount::mapped_type const aaCount = rCountPair.second;
            aggregateCount[aa] += aaCount;
        }
    }
    return aggregateCount;
}

types::dalton_t massFromSequence(SequenceI const &seq, 
    ResidueMass const &rmMap) {
    
    using types::sequence_string_t;
    using types::dalton_t;
    using units::dalton_mass;

    dalton_t mass = 0.0f * dalton_mass;

    for(sequence_string_t::const_iterator it = seq.begin();
        it != seq.end();
        ++it) {

        ResidueMass::const_iterator rmIt = rmMap.find(*it);
        if (rmIt != rmMap.end()) {
            mass += rmIt->second;
        }
    }
    return mass;
}

types::dalton_t massFromResidueCount(ResidueCount const &rCount, 
    ResidueMass const &rmMap) {

    using types::dalton_t;
    using units::dalton_mass;

    dalton_t mass = 0.0f * dalton_mass;

    for(auto const &rmPair : rmMap) {
        ResidueMass::key_type const aa = rmPair.first;
        ResidueMass::mapped_type const aaMass = rmPair.second;
        mass += dalton_t(rCount[aa] * aaMass);
    }
    return mass;
}

types::dalton_t massFromMultiResidueCount(MultiRefResidueCount const &mrrc,
    ResidueMass const &rmMap) {

    using types::dalton_t;
    using units::dalton_mass;

    dalton_t mass = 0.0f * dalton_mass;

    ResidueCount aggRCount = aggregateMultiResidueCount(mrrc);

    mass = massFromResidueCount(aggRCount, rmMap);

    return mass;
}

} /* namespace fn */
} /* namespace apollo */

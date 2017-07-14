/**
 * @file    residuecalc.hpp
 * @brief   Various residue calculation functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/29
 * @copyright 2012
 */

#ifndef apollo_residuecalc_hpp_
#define apollo_residuecalc_hpp_

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "sequenceconfig.hpp"
#include "residuecount.hpp"
#include "residuemod.hpp"
#include "residuemass.hpp"
#include "multirefresiduecount.hpp"
#include "locresiduemap.hpp"
#include "multireflocset.hpp"

// TODO: Rename residuecalc to coreutils
namespace apollo {
namespace fn {

ResidueCount rCountToLoc(LocResidueMap const &lrMap, SequenceI::size_type const to);

ResidueCount rCountFromLoc(LocResidueMap const &lrMap, SequenceI::size_type const from);

ResidueMod invertResidueMod(ResidueMod const &rmMap);

LocResidueMap aggregateMultiLocSet(MultiRefLocSet const &mrls);

ResidueCount rCountFromSequence(SequenceI const &seq, ResidueMod const &rmMap);

ResidueCount aggregateMultiResidueCount(MultiRefResidueCount const & mrrc);

types::dalton_t massFromSequence(SequenceI const &seq, ResidueMass const &rmMap);

types::dalton_t massFromResidueCount(ResidueCount const &rCount,
    ResidueMass const &rmMap);

types::dalton_t massFromMultiResidueCount(MultiRefResidueCount const &mrrc,
    ResidueMass const &rmMap);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_residuecalc_hpp_ */

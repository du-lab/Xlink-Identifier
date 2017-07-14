/**
 * @file    sequenceconfig.hpp
 * @brief   Types to represent sequence configuration
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/28
 * @copyright 2012
 */

#ifndef apollo_sequenceconfig_hpp_
#define apollo_sequenceconfig_hpp_

#include <ostream>
#include <utility>
#include <tuple>

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "residuecount.hpp"

namespace apollo {

typedef std::tuple<
    types::mz_t,            // get<0> is the hydralized mh for sequence + mods
    ResidueCount,           // get<1> is the static mod count
    ResidueCount            // get<2> is the dynamic mod count
    > SequenceConfig;

std::size_t hash_value(SequenceConfig const &sConfig);

std::ostream& operator<<(std::ostream &out, SequenceConfig const &rhs);

typedef std::pair<SequenceI::shp, SequenceConfig> SequenceMotif;

std::size_t hash_value(SequenceMotif const &sMotif);

std::ostream& operator<<(std::ostream &out, SequenceMotif const &rhs);

} /* namespace apollo */

#endif /* apollo_sequenceconfig_hpp_ */

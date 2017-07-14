/**
 * @file    locationutil.hpp
 * @brief   A set of utilities to simplify generating location information
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/12/08
 * @copyright 2013
 */

#ifndef apollo_locationutil_hpp
#define apollo_locationutil_hpp

#include <vector>

#include "locresiduemap.hpp"
#include "linkloc.hpp"
#include "residuemod.hpp"
#include "../core/linker.hpp"
#include "sequenceconfig.hpp"
#include "enums.hpp"

namespace apollo {

namespace fn {

LocResidueMap staticLocations(SequenceI const &seq, ResidueMod const staticMods);

std::vector<LocResidueMap> dynamicLocations(SequenceMotif const &seqMotif,
                                            ResidueMod const &iDynamicMods);

std::vector<LinkLoc> linkLocations(SequenceMotif const &seqMotif,
                                   Linker::shp const linkerShp,
                                   enums::LinkerConfig linkerConfig);

} /* namespace fn */

} /* namespace apollo */

#endif // apollo_locationutil_hpp

#include "locationutil.hpp"

#include "../filter/f_multimodloc.hpp"
#include "multimodlociter.hpp"
#include "linklociter.hpp"
#include "../core/residuecalc.hpp"

namespace apollo {

namespace fn {

LocResidueMap staticLocations(SequenceI const &seq, ResidueMod const staticMods) {
    using std::distance;

    LocResidueMap lrMap;

    for (auto seqIt = seq.begin(); seqIt != seq.end(); ++seqIt) {
        auto const staticModIt = staticMods.find(*seqIt);
        if (staticModIt != staticMods.end()) {
            lrMap.emplace(distance(seq.begin(), seqIt), *(staticModIt->second.begin()));
        }
    }
    return lrMap;
}

std::vector<LocResidueMap> dynamicLocations(SequenceMotif const &seqMotif,
                                            ResidueMod const &iDynamicMods) {

    typedef boost::filter_iterator<filter::unique_MultiModLoc, MultiModLocIter> FMultiModLocIter;

    using std::get;
    using fn::aggregateMultiLocSet;

    FMultiModLocIter const fmmLocEnd;
    LocResidueMap const emptyModMap;
    filter::unique_MultiModLoc const unique_filter;

    std::vector<LocResidueMap> lrVector;

    FMultiModLocIter fmmLocIter(unique_filter,
                                make_geniter<MultiModLocGen>(
                                    *(seqMotif.first),
                                    get<2>(seqMotif.second),
                                    iDynamicMods
                                    )
                                );

    for( ; fmmLocIter != fmmLocEnd; ++fmmLocIter) {
        lrVector.emplace_back(aggregateMultiLocSet(*fmmLocIter));
    }

    if (lrVector.empty()) {
        lrVector.emplace_back(emptyModMap);
    }

    return lrVector;
}

std::vector<LinkLoc> linkLocations(SequenceMotif const &seqMotif,
                                   Linker::shp const linkerShp,
                                   enums::LinkerConfig linkerConfig) {

    LinkLocIter const llEnd;

    auto llIter = make_geniter<LinkLocGen>(linkerShp, seqMotif.first, linkerConfig);

    return std::vector<LinkLoc>(llIter, llEnd);
}

} /* namespace fn */

} /* namespace apollo */

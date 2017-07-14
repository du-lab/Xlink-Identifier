/**
 * @file    theory.hpp
 * @brief   Run theoretical generation 
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/10
 * @copyright 2012
 */

#include <utility>
#include <vector>

#include <boost/log/trivial.hpp>

#include "../core/rangeiter.hpp"
#include "theory.hpp"
#include "enums.hpp"
#include "types.hpp"
#include "mz.hpp"
#include "../core/residuecalc.hpp"
#include "../theory/sequence/fullytrypticiter.hpp"
#include "../theory/sequence/ntrypticiter.hpp"
#include "../theory/sequence/sequencemhiter.hpp"

namespace apollo {

namespace fn {

template <class D>
SequenceI::shp_vec iterDigest(D digest) {
    D const digestEnd;
    SequenceI::shp_vec digestVec;
    for (; digest != digestEnd; ++digest) {
        digestVec.emplace_back(*digest);
    }
    return digestVec;
}

SequenceI::shp_vec digest(SequenceI::shp seqShp, 
    DigestOptions const &dOptions) {

    using types::count_store_t;

    FullyTrypticIter ftIter;
    NTrypticIter nIter;
    SequenceI::shp_vec digestVec;

    const count_store_t partial = 1;
    const count_store_t none = 0;

    switch(dOptions.digestType) {
    case enums::Digest::Full:
        ftIter = make_geniter<FullyTrypticGen>(seqShp, 
            dOptions.digestRegex,
            dOptions.digestTolerance);
        digestVec = iterDigest(ftIter);
    break;
    case enums::Digest::Partial:
        nIter = make_geniter<NTrypticGen>(seqShp,
            partial,
            dOptions.digestRegex,
            dOptions.digestTolerance);
        digestVec = iterDigest(nIter);
    break;
    case enums::Digest::None:
        nIter = make_geniter<NTrypticGen>(seqShp,
            none,
            dOptions.digestRegex,
            dOptions.digestTolerance);
        digestVec = iterDigest(nIter);
    break;
    default:
    break;
    }
    return digestVec;
}

MhSequenceTree::value_type mhInterval(SequenceI::shp &seqShp,
    SequenceOptions const &sOptions) {

    using types::mz_store_t;
    using types::mz_t;
    using units::mass_charge;
    using std::make_pair;


    mz_store_t const intervalThreashold = 0.001f;

    bool lowerRangeNotSet = true;
    mz_t lowerRange;
    bool upperRangeNotSet = true;
    mz_t upperRange;

    SequenceMhIter mhIter = make_geniter<SequenceMhGen>(*seqShp, sOptions);
    SequenceMhIter const mhEnd;

    for(; mhIter != mhEnd; ++mhIter) {
        /*
        BOOST_LOG_TRIVIAL(debug) << *seqShp <<
            ":" << (*mhIter).value() <<
            ", std+H2O:" << mhIter.gen().hydralizedResidueMass().value() <<
            ", static:" << mhIter.gen().staticMass().value() << 
                "-" << mhIter.gen().staticMods() <<
            ", dynamic:" << mhIter.gen().dynamicMass().value() << 
                "-" << mhIter.gen().dynamicMods();
                */
        if (lowerRangeNotSet) {
            lowerRange = *mhIter;
            lowerRangeNotSet = false;
        } else if (*mhIter < lowerRange) {
            lowerRange = *mhIter;
        }
        if (upperRangeNotSet) {
            upperRange = *mhIter;
            upperRangeNotSet = false;
        } else if (*mhIter > upperRange) {
            upperRange = *mhIter;
        }
    }

    mz_store_t lowerBound = lowerRange.value();
    lowerBound -= intervalThreashold;
    mz_store_t upperBound = upperRange.value();
    upperBound += intervalThreashold;

    return make_pair(
                Box1D(Point1D(lowerBound), Point1D(upperBound)),
        seqShp);
}

std::vector<MhSequenceTree::value_type> calcIntervals(
        SequenceI::shp seqShp,
        DigestOptions const &dOptions,
        SequenceOptions const &sOptions) {

    std::vector<MhSequenceTree::value_type> treeNodes;

    SequenceI::shp_vec digestVec = digest(seqShp, dOptions);
    for (SequenceI::shp &digestedSeq : digestVec) {
        treeNodes.emplace_back(mhInterval(digestedSeq, sOptions));
    }
    return treeNodes;
}

MhSequenceTree calcPeptides(
    ThreadPool &threadpool,
    SequenceIdMap const &seqIdMap, Options const &options) {


    typedef std::vector<
        std::future< std::vector<MhSequenceTree::value_type> >
        > future_mh_segment_vec;

    using types::count_store_t;

    MhSequenceTree msTree;

    future_mh_segment_vec mhSegmentFutures;

    for(auto const &seqIdPair : seqIdMap) {
        mhSegmentFutures.emplace_back(
                    threadpool.enqueue(
                        calcIntervals, seqIdPair.first, std::cref(options.digest()), std::cref(options.sequence())
            )
        );
    }

    for(auto &segmentFuture : mhSegmentFutures) {
        segmentFuture.wait();
        std::vector<MhSequenceTree::value_type> segmentVec = segmentFuture.get();
        for (MhSequenceTree::value_type segment: segmentVec) {
            /*
            BOOST_LOG_TRIVIAL(debug) << "Inserting: " << *segment.second
                                     << " [" << segment.first.min_corner().get<0>() << "-" <<segment.first.max_corner().get<0>() << "]";
*/
            msTree.insert(segment);
        }
    }

    return msTree;

}

} /* namespace fn */

} /* namespace apollo */

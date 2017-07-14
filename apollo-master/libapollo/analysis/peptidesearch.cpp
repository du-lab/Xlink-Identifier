/**
 * @file    peptidesearch.cpp
 * @brief   Searches through theoretical peptide possibilities to find
 *      potentially matching sequence and modification combinations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/17
 * @copyright 2012
 */
#include <algorithm>
#include <iterator>
#include <utility>
#include <unordered_set>

#include <boost/log/trivial.hpp>

#include <boost/iterator/filter_iterator.hpp>

#include "units.hpp"
#include "types.hpp"
#include "../core/stdmass.hpp"
#include "mz.hpp"
#include "theory.hpp"
#include "enums.hpp"
#include "peptidesearch.hpp"
#include "../filter/f_mz.hpp"

#include "../theory/sequence/sequencemhiter.hpp"

namespace apollo {

types::mz_t const zeroMz(0.0f * units::mass_charge);


filter::range_Mz rangeFromSearchTolerance(types::mz_t const experimentalMh,
    MzSearchTolerance const searchTolerance) {

    using enums::Tolerance;
    using filter::range_Mz;

    switch(searchTolerance.type) {

    case Tolerance::Mz:
        return range_Mz::FromMhAndTolerance(experimentalMh,
            searchTolerance.mzTolerance);
    break;

    case Tolerance::Ppm:
        return range_Mz::FromPpm(experimentalMh, searchTolerance.ppmTolerance);
    break;

    }
}

typedef boost::filter_iterator<filter::range_Mz, SequenceMhIter> FSequenceMhIter;

namespace fn {

SequenceMotifs peptideSearch(MhSequenceTree const& mhTree,
    types::mz_t const experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions) {
    
    using types::mz_t;
    using filter::range_Mz;
    using std::make_pair;

    range_Mz mzRange = 
        rangeFromSearchTolerance(experimentalMh, aOptions.precursorSearch);

    FSequenceMhIter const mhEnd;
    SequenceMotifs sMotifs;

    MhSequenceTree::const_query_iterator treeIt =
            mhTree.qbegin(boost::geometry::index::intersects(mzRange.toBox()));

    for(; treeIt != mhTree.qend(); ++treeIt) {

        FSequenceMhIter mhIter(mzRange,
                               make_geniter<SequenceMhGen>(*(treeIt->second),
                                                           sOptions));
        for(; mhIter != mhEnd; ++mhIter) {
/*
            BOOST_LOG_TRIVIAL(debug) << "Range Match: " << experimentalMh <<
                ": " << *mhIter << "-" << *seqShp;
                */
            sMotifs.emplace(treeIt->second, mhIter.base().gen().config());

        }
    }
    return sMotifs;
}

SequenceMotifs peptideSearchUsingGroup(MhSequenceTree const& mhTree,
    filter::range_Mz const mzRange,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions,
    ReactionGroup const &group) {
    /*
        BOOST_LOG_TRIVIAL(info) << "Group Range: " << experimentalMh <<
                ":[" << mzRange.lower().value() << "-" << mzRange.upper().value() << "]";
    */
        FSequenceMhIter const mhEnd;

        SequenceMotifs sMotifs;

        MhSequenceTree::const_query_iterator treeIt =
                mhTree.qbegin(boost::geometry::index::intersects(mzRange.toBox()));

        for(; treeIt != mhTree.qend(); ++treeIt) {

            if(!group(*(treeIt->second))) {
                continue;
            }

            /*
            BOOST_LOG_TRIVIAL(debug) << "Group Candidate: " << *(treeIt->second)
                    << " [" << treeIt->first.min_corner().get<0>() << "-" << treeIt->first.max_corner().get<0>() << "]";
    */
            FSequenceMhIter mhIter(mzRange,
                                   make_geniter<SequenceMhGen>(*(treeIt->second),
                                                               sOptions));
            for(; mhIter != mhEnd; ++mhIter) {

                /*
                BOOST_LOG_TRIVIAL(debug) << "Range Match: " << experimentalMh <<
                    ": " << *mhIter << "-" << *(treeIt->second);
                    */
                sMotifs.emplace(treeIt->second, mhIter.base().gen().config());

            }
        }

        return sMotifs;
}

SequenceMotifs peptideSearchUsingGroup(MhSequenceTree const& mhTree,
    types::mz_t experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions, 
    ReactionGroup const &group) {

    using filter::range_Mz;
    using std::make_pair;

    range_Mz mzRange = 
        rangeFromSearchTolerance(experimentalMh, aOptions.precursorSearch);

    // ICL cannot handle negative values, apparently
    if (mzRange.upper() < zeroMz) {
        mzRange = range_Mz(zeroMz, zeroMz);
    } else if (mzRange.lower() < zeroMz) {
        mzRange = range_Mz(zeroMz, mzRange.upper());
    }
    return peptideSearchUsingGroup(mhTree, mzRange, sOptions, aOptions, group);
}

LinkedSequenceMotifs peptideSearchUsingInterlink(MhSequenceTree const& mhTree,
    types::mz_t experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions,
    Linker const &linker) {

    using types::mz_t;
    using types::dalton_t;
    using units::mass_charge;
    using units::dalton_mass;
    using filter::range_Mz;
    using std::make_pair;
    using stdmass::H_da;
    using std::get;

    dalton_t const interlinkMass = linker.interlinkedMass();

    dalton_t const experimentalM = Mz::MFromMh(experimentalMh);

    dalton_t const targetM = experimentalM -
            interlinkMass;

    mz_t const targetMh = Mz::MhFromM(targetM);

    range_Mz targetRange =
        rangeFromSearchTolerance(targetMh, aOptions.precursorSearch);

    /*BOOST_LOG_TRIVIAL(info) << std::fixed << std::setprecision(5);

    BOOST_LOG_TRIVIAL(info) << "Target Range: [" << targetRange.lower() << "-" << targetRange.upper() << "]";
*/
    range_Mz group1Range(zeroMz, targetRange.upper());
/*
    BOOST_LOG_TRIVIAL(info) << "Group 1 Range: [" << group1Range.lower() << "-" << group1Range.upper() << "]";
    */
    FSequenceMhIter const mhEnd;
    LinkedSequenceMotifs lsMotifs;

    MhSequenceTree::const_query_iterator treeIt =
            mhTree.qbegin(boost::geometry::index::intersects(group1Range.toBox()));

    for(; treeIt != mhTree.qend(); ++treeIt) {
        if(!linker.group1()(*(treeIt->second))) {
            continue;
        }

        /*

        BOOST_LOG_TRIVIAL(debug) << "Group 1 Candidate: " << *(treeIt->second)
                << " [" << treeIt->first.min_corner().get<0>() << "-" << treeIt->first.max_corner().get<0>() << "]";
*/

        FSequenceMhIter mhIter(group1Range,
                               make_geniter<SequenceMhGen>(*(treeIt->second),
                                                           sOptions));
        for(; mhIter != mhEnd; ++mhIter) {

            //BOOST_LOG_TRIVIAL(debug) << "Group 1 Searched From: " << *mhIter;

            dalton_t const peptide1MWithoutProton = mhIter.base().gen().hydralizedMass();

            dalton_t const lowerTarget = Mz::MFromMh(targetRange.lower());

            dalton_t const upperTarget = Mz::MFromMh(targetRange.upper());


            range_Mz const group2Range( Mz::MhFromM(lowerTarget - peptide1MWithoutProton),
                                              Mz::MhFromM(upperTarget - peptide1MWithoutProton));

            SequenceMotifs group2Motifs = peptideSearchUsingGroup(
                mhTree, group2Range, sOptions, aOptions, linker.group2()
                );

            /*
            if(!group2Motifs.empty()) {
                BOOST_LOG_TRIVIAL(info) << "Peptide 1 Without Proton: " << peptide1MWithoutProton;

            }
*/
            /*
            for(auto const & motif : group2Motifs) {
                dalton_t const peptide2MWithoutProton = Mz::MFromMh(get<0>(motif.second));
//                BOOST_LOG_TRIVIAL(info) << "Peptide 2 Without Proton: " << peptide2MWithoutProton;
                dalton_t const entireMass = peptide1MWithoutProton +
                        peptide2MWithoutProton +
                        interlinkMass;
                mz_t const entireMh = Mz::MhFromM(entireMass);
//                BOOST_LOG_TRIVIAL(info) << "Experimental " << experimentalMh << " vs " << entireMh;
            }
*/
            if(!group2Motifs.empty()) {
                lsMotifs.emplace(
                    make_pair(treeIt->second, mhIter.base().gen().config()),
                    std::move(group2Motifs)
                );
            }
        }
    }


    return lsMotifs;

}

} /* namespace fn */
} /* namespace apollo */

/**
 * @file    reports.cpp
 * @brief   A map between a sequence structure and its report
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */
#include <sstream>
#include <iterator>
#include <tuple>
#include <atomic>
#include <cmath>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/log/trivial.hpp>

#include "../core/residuecalc.hpp"
#include "../core/stdmass.hpp"
#include "../theory/sequence/multimodlociter.hpp"
#include "../filter/f_multimodloc.hpp"
#include "../filter/f_mz.hpp"
#include "../theory/sequence/linklociter.hpp"

#include "units.hpp"
#include "enums.hpp"
#include "../experiment/denoise.hpp"
#include "../experiment/normalize.hpp"
#include "../analysis/xcorrelation.hpp"
#include "../theory/sequence/locationutil.hpp"
#include "../theory/ion/ulinkioncfgiter.hpp"
#include "../theory/ion/linkioncfgiter.hpp"
#include "../theory/ion/intralinkioncfgiter.hpp"
#include "../theory/ion/interlinkioncfgiter.hpp"
#include "sequencescore.hpp"

#include "reports.hpp"

namespace apollo {

void createDirectory(boost::filesystem::path const &directory) {
    using boost::filesystem::exists;
    using boost::filesystem::create_directory;
    if (!exists(directory)) {
        create_directory(directory);
    }
}

std::string idString(long l) {
    using std::stringstream;
    using std::setw;
    using std::setfill;
    stringstream ss;
    ss << setw(10) << setfill('0') << l;
    return ss.str();
}

std::ostream& operator<<(std::ostream &out, SequenceId const &seqId) {
    using std::endl;
    out << "Sequence Id: " << seqId.first << ", Description: " << seqId.second;
}

void printUnlinkedHeader(std::ostream &out,
                         SequenceIdMap const &seqIdMap,
                         SequenceMotif const &candidate,
                         LocResidueMap const &staticModMap,
                         LocResidueMap const &dynamicModMap) {
    using std::endl;
    SequenceI::shp seqParent = candidate.first->rootProtein();
    //out << "Parent - " << seqIdMap.at(seqParent) << endl;
    auto it = seqIdMap.find(seqParent);
    if( it != seqIdMap.end()) {
        out << "Parent - " << (*it).second.first << endl;
    }
    out << "Sequence: " << *candidate.first << endl;
    out << "Static Mods: " << staticModMap << endl;
    out << "DynamicMods: " << dynamicModMap << endl;

}

void printDeadendHeader(std::ostream &out,
                        SequenceIdMap const &seqIdMap,
                        SequenceMotif const &candidate,
                        LinkLoc const linkLoc,
                        LocResidueMap const &staticModMap,
                        LocResidueMap const &dynamicModMap) {
    using std::endl;
    SequenceI::shp seqParent = candidate.first->rootProtein();
    //out << "Parent - " << seqIdMap.at(seqParent) << endl;
    auto it = seqIdMap.find(seqParent);
    if( it != seqIdMap.end()) {
        out << "Parent - " << (*it).second.first << endl;
    }
    out << "Sequence: " << *candidate.first << endl;
    out << "Link At: " << linkLoc << endl;
    out << "Static Mods: " << staticModMap << endl;
    out << "DynamicMods: " << dynamicModMap << endl;
}

void printIntraHeader(std::ostream &out,
                      SequenceIdMap const &seqIdMap,
                      SequenceMotif const &candidate,
                      LinkLoc const linkLoc1,
                      LinkLoc const linkLoc2,
                      LocResidueMap const &staticModMap,
                      LocResidueMap const &dynamicModMap) {
    using std::endl;
    SequenceI::shp seqParent = candidate.first->rootProtein();
    //out << "Parent - " << seqIdMap.at(seqParent) << endl;
    auto it = seqIdMap.find(seqParent);
    if( it != seqIdMap.end()) {
        out << "Parent - " << (*it).second.first << endl;
    }
    
    out << "Sequence: " << *candidate.first << endl;
    out << "Link At: " << linkLoc1 << ", " << linkLoc2 << endl;
    out << "Static Mods: " << staticModMap << endl;
    out << "DynamicMods: " << dynamicModMap << endl;
}

// This is generating too much output. Suppress it for now. HERE
void printInterHeader(std::ostream &out,
                      SequenceIdMap const &seqIdMap,
                      SequenceMotif const &candidate1,
                      LinkLoc const linkLoc1,
                      LocResidueMap const &staticModMap1,
                      LocResidueMap const &dynamicModMap1,
                      SequenceMotif const &candidate2,
                      LinkLoc const linkLoc2,
                      LocResidueMap const &staticModMap2,
                      LocResidueMap const &dynamicModMap2) {
    using std::endl;
    out << "First sequence: " << endl;
    SequenceI::shp seqParent1 = candidate1.first->rootProtein();
    //out << "Parent - " << (seqIdMap.at(seqParent1)).second.first << endl;
    //out << "Parent - " << seqIdMap[seqParent1] << endl;
    auto it = seqIdMap.find(seqParent1);
    if( it != seqIdMap.end()) {
        out << "Parent - " << (*it).second.first << endl;
    }
    out << "Sequence: " << *candidate1.first << endl;
    out << "Link At: " << linkLoc1 << endl;
    out << "Static Mods: " << staticModMap1 << endl;
    out << "DynamicMods: " << dynamicModMap1 << endl;
    out << endl;
    out << "Second sequence: " << endl;
    SequenceI::shp seqParent2 = candidate2.first->rootProtein();
    //out << "Parent - " << (seqIdMap.at(seqParent2)).second.first << endl;
    auto it2 = seqIdMap.find(seqParent2);
    if( it2 != seqIdMap.end()) {
        out << "Parent - " << (*it2).second.first << endl;
    }
    out << "Sequence: " << *candidate2.first << endl;
    out << "Link At: " << linkLoc2 << endl;
    out << "Static Mods: " << staticModMap2 << endl;
    out << "DynamicMods: " << dynamicModMap2 << endl;
}

// This is generating too much output. Suppress it for now. HERE
void printSequenceScore(std::ostream &out, SequenceScore const &sequenceScore) {
    using std::endl;
    using std::string;
    string const tabStr("\t");

    out <<"X Correlation Score: " << sequenceScore.xCorrelation() << endl;
    out <<"Sp Score: " << sequenceScore.sp().first << endl;
    out << "Matches: " << endl;
    out << "Dta" << tabStr <<"Theoretical" << tabStr << "IonConfig" << endl;
    for (MatchedSpectrumVector::value_type const &msPair : sequenceScore.sp().second) {
        out << (*msPair.first) << tabStr << (*msPair.second).first << tabStr << (*msPair.second).second << endl;
    }
}

// This is generating too much output. Suppress it for now. HERE
void printSpectrum(std::ostream &out, IonSpectrum const &ionSpectrum) {
    using std::endl;
    using std::string;
    string const tabStr("\t");
    out << "Theoretical" << tabStr << "ionConfig" << endl;
    for (IonSpectrum::value_type const &isPair : ionSpectrum) {
        out << isPair.first << tabStr << isPair.second << endl;
    }
}

std::string decorateCandidate(SequenceMotif const &candidate,
                           LocResidueMap const &staticLocations,
                           LocResidueMap const &dynamicLocations,
                           types::residue_t const linkerSymbol,
                           LinkLoc const linkLoc1 = LinkLoc::Unlinked(),
                           LinkLoc const linkLoc2 = LinkLoc::Unlinked()
                           ) {
    using std::string;
    using std::stringstream;

    stringstream decoratedCandidate;

    if ((linkLoc1 == LinkLoc::OnNh2Terminus() || linkLoc2 == LinkLoc::OnNh2Terminus())) {
        decoratedCandidate << linkerSymbol << " ";
    }

    SequenceI::shp sequence = candidate.first;
    string const strCandidate = sequence->toString();
    for(SequenceI::size_type i = 0; i < sequence->length(); i++) {
        decoratedCandidate << strCandidate[i];
        LocResidueMap::const_iterator staticDecorator = staticLocations.find(i);
        if(staticDecorator != staticLocations.end()) {
            decoratedCandidate << staticDecorator->second;
        }
        LocResidueMap::const_iterator dynamicDecorator = dynamicLocations.find(i);
        if(dynamicDecorator != dynamicLocations.end()) {
            decoratedCandidate << dynamicDecorator->second;
        }
        if ((linkLoc1.loc() == i) || (linkLoc2.loc() == i)) {
            decoratedCandidate << linkerSymbol;
        }
    }

    if((linkLoc1 == LinkLoc::OnCTerminus()) || (linkLoc2 == LinkLoc::OnCTerminus())) {
        decoratedCandidate << " " << linkerSymbol;
    }


    return decoratedCandidate.str();
}

void printScore(std::ostream &out,
                SequenceIdMap const &seqIdMap,
                ScoreReport_vec const &scores) {
    using std::endl;
    using std::get;
    using std::string;
    string const tabStr("\t");
    out << "XCor" << tabStr <<
           //"SP" << tabStr <<
           "MassError" << tabStr <<
           "DTA" << tabStr <<
           "Linker Config"<< tabStr <<
           "Linker" << tabStr <<
           "ID" << tabStr <<
           "Sequence 1" << tabStr <<
           "Decorated 1" << tabStr <<
           "Parent 1" << tabStr <<
           "Sequence 2" << tabStr <<
           "Decorated 2" << tabStr <<
           "Parent 2" << endl;

    for(ScoreReport const &score : scores) {
        out << get<0>(score) << tabStr << // xcor
              // get<1>(score) << tabStr <<
               get<10>(score).value() << tabStr << // mass error
               get<2>(score) << tabStr << // dta
               get<3>(score) << tabStr; // Linker Config
        if (get<3>(score) == enums::LinkerConfig::Unlinked) {
            out << tabStr;
        } else {
            out << get<4>(score)->name() << tabStr; // Linker
        }
        out << get<5>(score) << tabStr; // unique ID
        out << *get<6>(score) << tabStr; // Sequence 1
        out << get<8>(score) << tabStr; // Sequence 1 Decorated

        SequenceI::shp seqParent1 = get<6>(score)->rootProtein();
        out << seqIdMap.at(seqParent1).first << tabStr; // Sequence 1 Parent

        if (get<3>(score) == enums::LinkerConfig::Interlinked) {
            out << *get<7>(score) << tabStr; // Sequence 2
            out << get<9>(score) << tabStr; // Sequence 2 Decorated

            SequenceI::shp seqParent2 = get<7>(score)->rootProtein();
            out << seqIdMap.at(seqParent2).first << tabStr; // Sequence 2 Parent
        } else {
            out << tabStr << tabStr;
        }
        out << endl;
    }
}

types::mz_t mhFromUnlinked(SequenceMotif const &candidate) {
    using std::get;
    return get<0>(candidate.second);
}

types::mz_t mhFromDeadend(SequenceMotif const &candidate, Linker const &linker) {
    using units::mass_charge;
    return mhFromUnlinked(candidate) + (linker.deadendMass().value() * mass_charge);
}

types::mz_t mhFromIntra(SequenceMotif const &candidate, Linker const &linker) {
    using units::mass_charge;
    return mhFromUnlinked(candidate) + (linker.intralinkedMass().value() * mass_charge);
}

types::mz_t mhFromInter(SequenceMotif const &candidate1, SequenceMotif const &candidate2,
                        Linker const &linker) {
    using units::mass_charge;
    return mhFromUnlinked(candidate1) +
            mhFromUnlinked(candidate2) +
            (linker.interlinkedMass().value() * mass_charge) -
            (stdmass::H_da.value() * mass_charge);

}

types::ppm_t ppmFromMassError(types::mz_t const measuredMz, types::mz_t const theoreticalMz) {
    return (
                ((measuredMz - theoreticalMz)/ theoreticalMz)
                * 1000000.0f
            );
}

ScoreReport_vec produceReport(CandidatePeptides const &candidates,
                              boost::filesystem::path const &resultsPath,
                              SequenceIdMap const &seqIdMap,
                              Options const &options,
                              std::atomic_long &candidateCount
                              ) {
    using std::ios_base;
    using std::string;
    using std::get;
    using std::endl;
    using std::vector;
    using boost::filesystem::path;


    using boost::filesystem::ofstream;

    using types::mz_t;
    using units::mass_charge;

    using types::intensity_t;
    using units::intensity;

    using filter::range_Mz;

    using fn::kMostIntensePeaks;
    using fn::minimumIntensity;
    using fn::normalize;
    using fn::binNormalize;
    using fn::binMzSpectrum;
    using fn::staticLocations;
    using fn::dynamicLocations;
    using fn::linkLocations;

    ScoreReport_vec scoreReport;
    Linker::shp const unlinkedLinker;

    SequenceI::shp const emptySequence;
    std::string const emptyCandidate2;

    // General strings
    string const tabStr("\t");
    string const dotStr(".");
    string const dtaStr("dta");
    string const txtStr("txt");
    string const cndStr("candidates");

    // Folder structures
    string const processedStr("processed");
    string const unlinkedStr("unlinked");
    string const deadendStr("deadend");
    string const intraStr("intra");
    string const interStr("inter");


    // Processed file names
    string const originalSpectrumStr("original");
    string const mostIntenseStr("mostintense");
    string const normalizedStr("normalized");
    string const binNormalizedStr("binnormalize");
    string const binXCorrelationStr("binxcorrelation");

    mz_t const binStepSize(100.0f * mass_charge);

    // For french photo
    intensity_t minIntensity(2.0 * intensity);

    //Kansas = 20.0f
    // French = 0.0f
    types::intensity_store_t const minXScore = options.analysis().scoringOptions.xcorrCutoff;

    types::mz_t const measuredMh = get<1>(candidates.dta().first);

    path const & dtaPath = get<3>(candidates.dta().first);
    path const dtaStem = dtaPath.stem();
    path const outputDir = resultsPath / dtaStem;

    MzSpectrum const &dtaSpectrum = candidates.dta().second;
    types::charge_t dtaCharge = get<2>(candidates.dta().first);
    // Default
    //MzSpectrum const mostIntense = kMostIntensePeaks(dtaSpectrum, 50);
    //MzSpectrum const normalized = normalize(dtaSpectrum);
    //MzSpectrum const denoisedNormalized = normalize(mostIntense);

    //Photo
    MzSpectrum const normalized = normalize(dtaSpectrum);
    MzSpectrum const mostIntense = minimumIntensity(normalized, minIntensity);

    MzSpectrum const binNormalized = binNormalize(mostIntense, binStepSize);
    BinnedSpectrum const xCorrelationSpectrum = binMzSpectrum(binNormalized,
                                                              options.analysis().xCorrelation.binStepSize,
                                                              options.analysis().xCorrelation.binSumIntensities);

    BOOST_LOG_TRIVIAL(info) << "Processing: " << dtaPath.stem();


    bool createdOutput = false;
    bool createdUnlinked = false;

    // Iter end points
    UlinkIonCfgIter const ulinkIonCfgEnd;
    LinkIonCfgIter const linkIonCfgEnd;
    IntralinkIonCfgIter const intralinkIonCfgEnd;
    InterlinkIonCfgIter const interlinkIonCfgEnd;

    long currentCount = 0;

//    if (!candidates.unlinked().empty()) {
//        path const unlinkedDir = outputDir / unlinkedStr;
//
//        // Score unlinked
//        for (SequenceMotif const &candidate : candidates.unlinked()) {
//            //Generate location information
//
//            types::mz_t const theoreticalMh = mhFromUnlinked(candidate);
//            types::ppm_t const massError = ppmFromMassError(measuredMh, theoreticalMh);
//
//            LocResidueMap staticModMap = staticLocations(*candidate.first, options.sequence().staticMods);
//            vector<LocResidueMap> dynamicModMaps = dynamicLocations(candidate, options.sequence().iDynamicMods);
//            for(LocResidueMap const &dynamicModMap : dynamicModMaps) {
//                UlinkIonCfgIter ionIter =
//                        make_geniter<UlinkIonCfgGen>(candidate, staticModMap, dynamicModMap, options.sequence());
//                CandidateIons ulinkIons(ionIter, ulinkIonCfgEnd, dtaCharge, options.analysis().theoreticalSpectrum);
//                SequenceScore ulinkScore(options.analysis(), std::move(ulinkIons), mostIntense, xCorrelationSpectrum);
//
//                if (ulinkScore.xCorrelation() <= minXScore) {
//                    continue;
//                }
//                if (!createdOutput) {
//                    createDirectory(outputDir);
//                    createdOutput = true;
//                }
//                if (!createdUnlinked) {
//                    createDirectory(unlinkedDir);
//                    createdUnlinked = true;
//                }
//                currentCount = candidateCount++;
//                //BOOST_LOG_TRIVIAL(info) << "Candidate: " << currentCount;
//
//                std::string decoratedCandidate1 = decorateCandidate(candidate, staticModMap, dynamicModMap, ' ');
//
//                // This is generating too much output. Suppress it for now. HERE
//                //path candidatesPath = unlinkedDir;
//                //candidatesPath /=(idString(currentCount) + "_" + cndStr + dotStr + txtStr);
//                //ofstream cndOut(candidatesPath, ios_base::trunc & ios_base::out);
//                //printSpectrum(cndOut, ulinkScore.candidates().spectrum());
//                //cndOut.flush();
//                //cndOut.close();
//
//                // This is generating too much output. Suppress it for now. HERE
//                //path unlinkedPath = unlinkedDir;
//                //unlinkedPath /= (idString(currentCount) + dotStr + txtStr);
//                //ofstream unlinkedOut(unlinkedPath, ios_base::trunc & ios_base::out);
//                //printUnlinkedHeader(unlinkedOut, seqIdMap,candidate, staticModMap, dynamicModMap);
//                //printSequenceScore(unlinkedOut, ulinkScore);
//                //unlinkedOut.flush();
//                //unlinkedOut.close();
//
//
//                scoreReport.emplace_back(ulinkScore.xCorrelation(),
//                                         ulinkScore.sp().first,
//                                         dtaStem.string(),
//                                         enums::LinkerConfig::Unlinked,
//                                         unlinkedLinker,
//                                         currentCount,
//                                         candidate.first,
//                                         emptySequence,
//                                         decoratedCandidate1,
//                                         emptyCandidate2,
//                                         massError,
//                                         theoreticalMh
//                                         );
//            }
//
//        }
//    }
//
//
//
    for( LinkerCandidateMap::value_type const &linkerCandidatesPair : candidates.linkable()) {
        Linker::shp const &linkerShp = linkerCandidatesPair.first;
        LinkedCandidates const &linkedCandidates = linkerCandidatesPair.second;

        if (linkedCandidates.deadend.empty() &&
                linkedCandidates.intralinked.empty() &&
                linkedCandidates.interlinked.empty()) {
            continue;
        }

        path const linkerDirectory = outputDir / linkerShp->name();
        bool createdLinker = false;
        bool createdDeadend = false;
       bool createdIntra = false;
        bool createdInter = false;

//
//        if (!linkedCandidates.deadend.empty()) {
//
//            path const deadendDir = linkerDirectory / deadendStr;
//
//
//            // Score deadend
//            for(SequenceMotif const &deCandidate : linkedCandidates.deadend) {
//                //Generate location information
//
//                types::mz_t const theoreticalMh = mhFromDeadend(deCandidate, *linkerShp);
//                types::ppm_t const massError = ppmFromMassError(measuredMh, theoreticalMh);
//
//                LocResidueMap staticModMap = staticLocations(*deCandidate.first, options.sequence().staticMods);
//                vector<LocResidueMap> dynamicModMaps = dynamicLocations(deCandidate, options.sequence().iDynamicMods);
//                vector<LinkLoc> linkLocs = linkLocations(deCandidate, linkerShp, enums::LinkerConfig::Deadend);
//
//                for(LocResidueMap const &dynamicModMap : dynamicModMaps) {
//                    for(LinkLoc const linkLoc : linkLocs) {
//
//                        LinkIonCfgIter deIonCfgIter = make_geniter<LinkIonCfgGen>(deCandidate, linkLoc, staticModMap, dynamicModMap, options.sequence());
//                        CandidateIons deIons(deIonCfgIter, linkIonCfgEnd, dtaCharge,  options.analysis().theoreticalSpectrum, linkerShp);
//                        SequenceScore deScore(options.analysis(), std::move(deIons), mostIntense, xCorrelationSpectrum);
//
//                        if (deScore.xCorrelation() <= minXScore) {
//                            continue;
//                        }
//                        if (!createdOutput) {
//                            createDirectory(outputDir);
//                            createdOutput = true;
//                        }
//                        if (!createdLinker) {
//                            createDirectory(linkerDirectory);
//                            createdLinker = true;
//                        }
//                        if (!createdDeadend) {
//                            createDirectory(deadendDir);
//                            createdDeadend = true;
//                        }
//                        currentCount = candidateCount++;
//                        //BOOST_LOG_TRIVIAL(info) << "Candidate: " << currentCount;
//
//                        std::string decoratedCandidate1 = decorateCandidate(deCandidate, staticModMap, dynamicModMap, linkerShp->symbol(), linkLoc);
//
//                        // This is generating too much output. Suppress it for now. HERE
//                        //path candidatesPath = deadendDir;
//                        //candidatesPath /=(idString(currentCount) + "_" + cndStr + dotStr + txtStr);
//                        //ofstream cndOut(candidatesPath, ios_base::trunc & ios_base::out);
//                        //printSpectrum(cndOut, deScore.candidates().spectrum());
//                        //cndOut.flush();
//                        //cndOut.close();
//
//
//                        // This is generating too much output. Suppress it for now. HERE
//                        //path dePath = deadendDir;
//                        //dePath /= (idString(currentCount) + dotStr + txtStr);
//                        //ofstream deOut(dePath, ios_base::trunc & ios_base::out);
//                        //printDeadendHeader(deOut, seqIdMap, deCandidate, linkLoc, staticModMap, dynamicModMap);
//                        //printSequenceScore(deOut, deScore);
//                        //deOut.flush();
//                        //deOut.close();
//
//                        scoreReport.emplace_back(deScore.xCorrelation(),
//                                                 deScore.sp().first,
//                                                 dtaStem.string(),
//                                                 enums::LinkerConfig::Deadend,
//                                                 linkerShp,
//                                                 currentCount,
//                                                 deCandidate.first,
//                                                 emptySequence,
//                                                 decoratedCandidate1,
//                                                 emptyCandidate2,
//                                                 massError,
//                                                 theoreticalMh
//                                                 );
//                    }
//                }
//            }
//        }
//
//        if (!linkedCandidates.intralinked.empty()) {
//
//            path const intraDir = linkerDirectory / intraStr;
//
//
//            // Score intralinked
//            for(SequenceMotif const &intraCandidate : linkedCandidates.intralinked) {
//
//                types::mz_t const theoreticalMh = mhFromIntra(intraCandidate, *linkerShp);
//                types::ppm_t const massError = ppmFromMassError(measuredMh, theoreticalMh);
//
//                //Generate location information
//                LocResidueMap staticModMap = staticLocations(*intraCandidate.first, options.sequence().staticMods);
//                vector<LocResidueMap> dynamicModMaps = dynamicLocations(intraCandidate, options.sequence().iDynamicMods);
//                vector<LinkLoc> linkLocs = linkLocations(intraCandidate, linkerShp, enums::LinkerConfig::Intralinked);
//
//                for(LocResidueMap const & dynamicModMap : dynamicModMaps) {
//                    vector<LinkLoc>::iterator linkFirst = linkLocs.begin();
//                    vector<LinkLoc>::iterator linkSecond = std::next(linkFirst);
//                    for(; ((std::next(linkSecond) != linkLocs.end()) && (std::next(linkFirst) != linkSecond)); ++linkFirst) {
//                        for(; linkSecond != linkLocs.end(); ++linkSecond) {
//                            IntralinkIonCfgIter intralinkIonCfgIter = make_geniter<IntralinkIonCfgGen>(intraCandidate, *linkFirst, *linkSecond, staticModMap, dynamicModMap, options.sequence());
//                            CandidateIons intraIons(intralinkIonCfgIter, intralinkIonCfgEnd, dtaCharge, options.analysis().theoreticalSpectrum, linkerShp);
//                            SequenceScore intraScore(options.analysis(), std::move(intraIons), mostIntense, xCorrelationSpectrum);
//
//                            if (intraScore.xCorrelation() <= minXScore) {
//                                continue;
//                            }
//                            if (!createdOutput) {
//                                createDirectory(outputDir);
//                                createdOutput = true;
//                            }
//                            if (!createdLinker) {
//                                createDirectory(linkerDirectory);
//                                createdLinker = true;
//                            }
//                            if (!createdIntra) {
//                                createDirectory(intraDir);
//                                createdIntra = true;
//                            }
//                            currentCount = candidateCount++;
//                            //BOOST_LOG_TRIVIAL(info) << "Candidate: " << currentCount;
//
//                            std::string decoratedCandidate1 = decorateCandidate(intraCandidate, staticModMap, dynamicModMap, linkerShp->symbol(), *linkFirst, *linkSecond);
//
//                            // This is generating too much output. Suppress it for now. HERE
//                            //path candidatesPath = intraDir;
//                            //candidatesPath /=(idString(currentCount) + "_" + cndStr + dotStr + txtStr);
//                            //ofstream cndOut(candidatesPath, ios_base::trunc & ios_base::out);
//                            //printSpectrum(cndOut, intraScore.candidates().spectrum());
//                            //cndOut.flush();
//                            //cndOut.close();
//
//                            // This is generating too much output. Suppress it for now. HERE
//                            //path intraPath = intraDir;
//                            //intraPath /= (idString(currentCount) + dotStr + txtStr);
//                            //ofstream intraOut(intraPath, ios_base::trunc & ios_base::out);
//                            //printIntraHeader(intraOut, seqIdMap, intraCandidate, *linkFirst, *linkSecond, staticModMap, dynamicModMap);
//                            //printSequenceScore(intraOut, intraScore);
//                            //intraOut.flush();
//                            //intraOut.close();
//
//                            scoreReport.emplace_back(intraScore.xCorrelation(),
//                                                     intraScore.sp().first,
//                                                     dtaStem.string(),
//                                                     enums::LinkerConfig::Intralinked,
//                                                     linkerShp,
//                                                     currentCount,
//                                                     intraCandidate.first,
//                                                     emptySequence,
//                                                     decoratedCandidate1,
//                                                     emptyCandidate2,
//                                                     massError,
//                                                     theoreticalMh
//                                                     );
//                        }
//                        linkSecond = std::next(linkFirst);
//                        ++linkSecond;
//                    }
//                }
//            }
//        }

        if (!linkedCandidates.interlinked.empty()) {
            path const interDir = linkerDirectory / interStr;
            // Score interlinked
            for(LinkedSequenceMotifs::value_type const &interCandidatesPair : linkedCandidates.interlinked) {
                //Generate location information for first sequence
                SequenceMotif const &linkedCandidate1 = interCandidatesPair.first;
                LocResidueMap staticModMap1 = staticLocations(*linkedCandidate1.first, options.sequence().staticMods);
                vector<LocResidueMap> dynamicModMaps1 = dynamicLocations(linkedCandidate1, options.sequence().iDynamicMods);
                vector<LinkLoc> linkLocs1 = linkLocations(linkedCandidate1, linkerShp, enums::LinkerConfig::Interlinked);

                for(SequenceMotif const &linkedCandidate2 : interCandidatesPair.second) {
                    types::mz_t const theoreticalMh = mhFromInter(linkedCandidate1, linkedCandidate2, *linkerShp);
                    types::ppm_t const massError = ppmFromMassError(measuredMh, theoreticalMh);



                    //Generate location information for second sequence
                    LocResidueMap staticModMap2 = staticLocations(*linkedCandidate2.first, options.sequence().staticMods);
                    vector<LocResidueMap> dynamicModMaps2 = dynamicLocations(linkedCandidate2, options.sequence().iDynamicMods);
                    vector<LinkLoc> linkLocs2 = linkLocations(linkedCandidate2, linkerShp, enums::LinkerConfig::Interlinked);

                    for(LocResidueMap const &dynamicModMap1 : dynamicModMaps1) {
                        for(LinkLoc const linkLoc1 : linkLocs1) {
                            for(LocResidueMap const &dynamicModMap2 : dynamicModMaps2) {
                                for(LinkLoc const linkLoc2 : linkLocs2) {
                                    InterlinkIonCfgIter interlinkIonCfgIter = make_geniter<InterlinkIonCfgGen>(linkedCandidate1, linkLoc1, staticModMap1, dynamicModMap1, linkedCandidate2, linkLoc2, staticModMap2, dynamicModMap2, options.sequence());
                                    CandidateIons interIons(interlinkIonCfgIter, interlinkIonCfgEnd, dtaCharge, options.analysis().theoreticalSpectrum, linkerShp);
                                    SequenceScore interScore(options.analysis(), std::move(interIons), mostIntense, xCorrelationSpectrum);

                                    if (interScore.xCorrelation() <= minXScore) {
                                        continue;
                                    }
                                    if (!createdOutput) {
                                        createDirectory(outputDir);
                                        createdOutput = true;
                                    }
                                    if (!createdLinker) {
                                        createDirectory(linkerDirectory);
                                        createdLinker = true;
                                    }
                                    if (!createdInter) {
                                        createDirectory(interDir);
                                        createdInter = true;
                                    }
                                    currentCount = candidateCount++;
                                    //BOOST_LOG_TRIVIAL(info) << "Candidate: " << currentCount;
                                    range_Mz theoRange = range_Mz::FromPpm(measuredMh, options.analysis().precursorSearch.ppmTolerance);
                                    //BOOST_LOG_TRIVIAL(info) << std::fixed << std::setprecision(5);
                                    //BOOST_LOG_TRIVIAL(info) << "Measured: " << measuredMh << ", Theoretical: " << theoreticalMh << ", Lower: " << theoRange.lower() << ", Upper: " << theoRange.upper();

                                    std::string decoratedCandidate1 = decorateCandidate(linkedCandidate1, staticModMap1, dynamicModMap1, linkerShp->symbol(), linkLoc1);
                                    std::string decoratedCandidate2 = decorateCandidate(linkedCandidate2, staticModMap2, dynamicModMap2, linkerShp->symbol(), linkLoc2);

                                    // This is generating too much output. Suppress it for now. HERE
                                    //path candidatesPath = interDir;
                                    //candidatesPath /=(idString(currentCount) + "_" + cndStr + dotStr + txtStr);
                                    //ofstream cndOut(candidatesPath, ios_base::trunc & ios_base::out);
                                    //printSpectrum(cndOut, interScore.candidates().spectrum());
                                    //cndOut.flush();
                                    //cndOut.close();

                                    // This is generating too much output. Suppress it for now. HERE
                                    //path interPath = interDir;
                                    //interPath /= (idString(currentCount) + dotStr + txtStr);
                                    //ofstream interOut(interPath, ios_base::trunc & ios_base::out);
                                    //printInterHeader(interOut, seqIdMap,
                                    //                 linkedCandidate1, linkLoc1, staticModMap1, dynamicModMap1,
                                    //                 linkedCandidate2, linkLoc2, staticModMap2, dynamicModMap2);
                                    // This is generating too much output. Suppress it for now. HERE
                                    //printSequenceScore(interOut, interScore);
                                    //interOut.flush();
                                    //interOut.close();

                                    scoreReport.emplace_back(interScore.xCorrelation(),
                                                             interScore.sp().first,
                                                             dtaStem.string(),
                                                             enums::LinkerConfig::Interlinked,
                                                             linkerShp,
                                                             currentCount,
                                                             linkedCandidate1.first,
                                                             linkedCandidate2.first,
                                                             decoratedCandidate1,
                                                             decoratedCandidate2,
                                                             massError,
                                                             theoreticalMh
                                                             );
                                }
                            }
                        }
                    }
                }
            }

        }
    }

    return scoreReport;
}

// This is going to be much longer than I want. I'm sorry
void produceReports(ThreadPool &threadpool,
                    boost::filesystem::path const &resultsPath,
                    SequenceIdMap const &seqIdMap,
                    DtaCandidates const &dtaCandidates,
                    Options const &options) {

    using std::ios_base;

    using boost::filesystem::path;
    using boost::filesystem::ofstream;
    using fn::invertResidueMod;

    typedef std::vector<
        std::future<ScoreReport_vec>
        > score_report_future_vec;

    std::atomic_long candidateCount(0);

    createDirectory(resultsPath);

    ScoreReport_vec scoreReport;

    score_report_future_vec scoreReportFutures;
    for(CandidatePeptides const &candidates : dtaCandidates) {

        if(!candidates.hasCandidates()) {
            continue;
        }

        scoreReportFutures.emplace_back(
                    threadpool.enqueue(
                        produceReport,
                        std::cref(candidates),
                        std::cref(resultsPath),
                        std::cref(seqIdMap),
                        std::cref(options),
                        std::ref(candidateCount))
                    );
    }

    for(auto &reportFuture : scoreReportFutures) {
        reportFuture.wait();
        ScoreReport_vec newReports = std::move(reportFuture.get());
        for(ScoreReport & report : newReports) {
            scoreReport.emplace_back(report);
        }
    }

    path const overviewPath = resultsPath / "results.csv";
    ofstream overviewOut(overviewPath, ios_base::trunc & ios_base::out);
    printScore(overviewOut, seqIdMap, scoreReport);
    overviewOut.flush();
    overviewOut.close();

}

} /* namespace apollo */

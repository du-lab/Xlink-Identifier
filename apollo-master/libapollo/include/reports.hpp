/**
 * @file    reports.hpp
 * @brief   A map between a sequence structure and its report
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#ifndef apollo_reports_hpp_
#define apollo_reports_hpp_

#include <tuple>
#include <vector>
#include <functional>
#include <atomic>

#include "ThreadPool.hpp"

#include <boost/filesystem.hpp>

#include "analysistypes.hpp"
#include "fastatypes.hpp"

#include "linkloc.hpp"
#include "locresiduemap.hpp"
#include "options.hpp"
#include "sequenceconfig.hpp"

namespace apollo {

typedef std::tuple<types::intensity_store_t, // XCorrelation Score
    types::intensity_store_t, // SP Score
    std::string, // DTA Candidate
    enums::LinkerConfig, // LinkerConfig
    Linker::shp, // linker
    long, // Candidate count
    SequenceI::shp, // sequence 1
    SequenceI::shp, // sequence 2
    std::string, // decoratedCandidate1,
    std::string, // decoratedCandidate2
    types::ppm_t, // mass error in ppm
    types::mz_t // theoretical mh
> ScoreReport;

typedef std::vector<ScoreReport> ScoreReport_vec;

void printScore(std::ostream &out,
                SequenceIdMap const &seqIdMap,
                ScoreReport_vec const &scores);

ScoreReport_vec produceReport(CandidatePeptides const &candidates,
                              boost::filesystem::path const &resultsPath,
                              SequenceIdMap const &seqIdMap,
                              Options const &options,
                              std::atomic_long &candidateCount
                              );

void produceReports(ThreadPool &threadpool,
                    boost::filesystem::path const &resultsPath,
                    SequenceIdMap const &seqIdMap,
                    DtaCandidates const &dtaCandidates,
                    Options const &options);

} /* namespace apollo */

#endif /* apollo_reports_hpp_ */

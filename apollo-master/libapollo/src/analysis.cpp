/**
 * @file    analysis.cpp
 * @brief   Determine candidate peptides and ions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/17
 * @copyright 2012
 */

#include <utility>
#include <vector>
#include <future>

#include <boost/container/flat_map.hpp>
#include <boost/log/trivial.hpp>

#include "units.hpp"
#include "analysis.hpp"
#include "../analysis/xcorrelation.hpp"
#include "../analysis/sp.hpp"
#include "candidateions.hpp"
#include "candidatepeptides.hpp"

namespace apollo {

namespace fn {

CandidatePeptides candidates(MhSequenceTree const &mhTree,
    DtaFile const &dtaFile,
    Options const &options) {
    return CandidatePeptides(mhTree, dtaFile, options);
}

DtaCandidates determineCandidates(ThreadPool &threadpool,
    MhSequenceTree const &mhTree,
    DtaFiles const &dtaFiles,
    Options const &options) {

    typedef std::vector<
        std::future<DtaCandidates::value_type>
        > future_dta_candidate_vec;

    typedef boost::container::flat_map<types::scanCount_store_t, types::count_t> ScanCountCount;


    using std::get;

    ScanCountCount scCountMap;

    future_dta_candidate_vec candidateFutures;

    // Determine how many files each scan count has
    for (auto const &dtaFile : dtaFiles) {
        scCountMap[get<0>(dtaFile.first)] += 1;
    }

    // Process the files
    for (auto const &dtaFile : dtaFiles) {

        // assume the only good scans have a single dta
        if (scCountMap[get<0>(dtaFile.first)] == 1) {
            candidateFutures.emplace_back(
                threadpool.enqueue(
                    candidates, std::cref(mhTree), std::cref(dtaFile), std::cref(options)
                )
            );
        }
    }

    DtaCandidates dtaCandidates;

    for (auto &candidateFuture : candidateFutures) {
        candidateFuture.wait();
        CandidatePeptides cPeptide = std::move(candidateFuture.get());
        if (cPeptide.hasCandidates()) {
            dtaCandidates.emplace_back(std::move(cPeptide));
        }
    }

    return dtaCandidates;

}


} /* namespace fn */
} /* namespace apollo */

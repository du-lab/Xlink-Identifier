#ifndef apollo_stdrun_hpp_
#define apollo_stdrun_hpp_

#include "ThreadPool.hpp"
#include "options.hpp"
#include "pathvector.hpp"
#include "theory.hpp"
#include "analysis.hpp"
#include "reports.hpp"

namespace apollo {

namespace fn {

void stdrun(
        ThreadPool &threadpool,
        PathVector const &dtaPaths,
        boost::filesystem::path const &resultsPath,
        SequenceIdMap const &seqIdMap,
        MhSequenceTree const &mhSeqTree,
        Options const &options
        );
} /* namespace fn */
} /* namespace apollo */

#endif // apollo_stdrun_hpp_

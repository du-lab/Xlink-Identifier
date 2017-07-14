/**
 * @file    analysis.hpp
 * @brief   Determine candidate peptides and ions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/17
 * @copyright 2012
 */


#ifndef apollo_analysis_hpp_
#define apollo_analysis_hpp_

#include "ThreadPool.hpp"

#include "types.hpp"
#include "analysistypes.hpp"
#include "options.hpp"
#include "readdtas.hpp"
#include "theorytypes.hpp"

namespace apollo {

namespace fn {

DtaCandidates determineCandidates(ThreadPool &threadpool,
    MhSequenceTree const &mhTree,
    DtaFiles const &dtaFiles,
    Options const &options);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_analysis_hpp_ */

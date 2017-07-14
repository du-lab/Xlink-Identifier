/**
 * @file    theory.hpp
 * @brief   Run theoretical generation 
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/10
 * @copyright 2012
 */


#ifndef apollo_theory_hpp_
#define apollo_theory_hpp_

#include "ThreadPool.hpp"
#include "theorytypes.hpp"
#include "fastatypes.hpp"
#include "options.hpp"

namespace apollo {

namespace fn {

MhSequenceTree calcPeptides(ThreadPool &threadpool,
    SequenceIdMap const &seqIdMap, Options const &options);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_theory_hpp_ */

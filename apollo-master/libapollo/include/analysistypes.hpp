/**
 * @file    analysistypes.hpp
 * @brief   Types returned as a result of the analysis functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/28
 * @copyright 2012
 */

#ifndef apollo_analysistypes_hpp_
#define apollo_analysistypes_hpp_

#include <vector>

#include "types.hpp"
#include "dtatypes.hpp"
#include "candidatepeptides.hpp"

namespace apollo {

typedef std::vector<CandidatePeptides> DtaCandidates;

} /* namespace apollo */

#endif /* apollo_analysistypes_hpp_ */

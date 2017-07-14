/**
 * @file    peptidesearch.hpp
 * @brief   Searches through theoretical peptide possibilities to find
 *      potentially matching sequence and modification combinations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/17
 * @copyright 2012
 */

#ifndef apollo_peptidesearch_hpp_
#define apollo_peptidesearch_hpp_

#include <utility>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "options.hpp"
#include "theory.hpp"
#include "sequenceconfig.hpp"
#include "candidatepeptides.hpp"
#include "../core/reactiongroup.hpp"

/**
 * @namespace apollo
 * @brief Apollo library
 */
namespace apollo {

/**
 * @namespace fn
 * @brief Functions that follow functional programming
 */
namespace fn {

SequenceMotifs peptideSearch(MhSequenceTree const& mhTree,
    types::mz_t experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions);

SequenceMotifs peptideSearchUsingGroup(MhSequenceTree const& mhTree,
    types::mz_t experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions, 
    ReactionGroup const &group);

LinkedSequenceMotifs peptideSearchUsingInterlink(MhSequenceTree const& mhTree,
    types::mz_t experimentalMh,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions,  
    Linker const &linker);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_peptidesearch_hpp_ */

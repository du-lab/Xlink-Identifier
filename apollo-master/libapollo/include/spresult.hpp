/**
 * @file    spresult.hpp
 * @brief   SP Result types
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */


#ifndef apollo_spresult_hpp_
#define apollo_spresult_hpp_

#include <vector>
#include <utility>

#include <boost/container/vector.hpp>

#include "spectrumtypes.hpp"

namespace apollo {

typedef std::pair<MzSpectrum::const_iterator, IonSpectrum::const_iterator> MatchedSpectrumPair;

typedef std::vector<MatchedSpectrumPair> MatchedSpectrumVector;

typedef std::pair<types::intensity_store_t, MatchedSpectrumVector> SpResult;

} /* namespace apollo */

#endif /* apollo_spresult_hpp_ */

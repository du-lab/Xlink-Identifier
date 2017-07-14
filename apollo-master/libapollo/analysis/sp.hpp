/**
 * @file    sp.hpp
 * @brief   SP Calculation function
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#ifndef apollo_sp_hpp_
#define apollo_sp_hpp_

#include "types.hpp"
#include "spectrumtypes.hpp"
#include "spresult.hpp"

/**
 * @namespace apollo
 * @brief Apollo library
 */
namespace apollo {

/**
 * @namespace fn
 * @brief Functions that follow functional programming ideology
 */
namespace fn {

SpResult spCalculation(MzSpectrum const &expSpectrum, 
    IonSpectrum const &theoSpectrum,
    types::mz_t const halfWindow);

} /* namespace fn*/
} /* namespace apollo */

#endif /* apollo_sp_hpp_ */
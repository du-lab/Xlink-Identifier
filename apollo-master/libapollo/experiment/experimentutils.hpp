/**
 * @file    experimentutils.hpp
 * @brief   Misc. utilities for use in experiment related functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#ifndef apollo_experimentutils_hpp_
#define apollo_experimentutils_hpp_

#include "spectrumtypes.hpp"

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

/**
 * @fn bool lesserIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2)
 * @brief Determins if the intensity of one mz,int pair is smaller than another
 * @param mzIntPair1 First mz,int pair
 * @param mzIntPair2 Second mz,int pair
 * @return true if intensity of pair 1 is smaller than pair 2, otherwise false
 */
bool smallerIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2);

/**
 * @fn bool greaterIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2)
 * @brief Determins if the intensity of one mz,int pair is greater than another
 * @param mzIntPair1 First mz,int pair
 * @param mzIntPair2 Second mz,int pair
 * @return true if intensity of pair 1 is greater than pair 2, otherwise false
 */
bool greaterIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_experimentutils_hpp_ */

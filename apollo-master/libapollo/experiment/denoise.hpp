/**
 * @file    denoise.hpp
 * @brief   Various denoise functions for experimental datasets
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#ifndef apollo_denoise_hpp_
#define apollo_denoise_hpp_

#include "types.hpp"
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
 * @fn MzSpectrum kMostIntensePeaks(MzSpectrum const &mzSpectrum,
    types::count_store_t const k)
 * @brief Returns a new spectrum of the k most intense peaks
 * @note Spectrum returned unmodified if spectrum size <= k
 * @param mzSpectrum The MzSpectrum to be denoised
 * @param k The size the spectrum is to be trimmed to (default is 100)
 * @return The trimmed spectrum
 */

MzSpectrum kMostIntensePeaks(MzSpectrum const &mzSpectrum, 
    types::count_store_t const k = 100);

MzSpectrum minimumIntensity(MzSpectrum const &mzSpectrum, types::intensity_t intensity);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_denoise_hpp_ */

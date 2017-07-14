/**
 * @file    normalize.hpp
 * @brief   Various normalization functions for experimental datasets
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#ifndef apollo_normalize_hpp_
#define apollo_normalize_hpp_

#include "units.hpp"
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

MzSpectrum normalize(MzSpectrum const &mzSpectrum,
    types::intensity_t const normalizeTo = 
        types::intensity_t(100.0f * units::intensity));

/**
 * @fn MzSpectrum binNormalize(MzSpectrum const &mzSpectrum,
    types::mz_bin_t const step,
    types::intensity_t const normalizeTo)
 * @brief Normalizes the spectrum to a defined height
 * @note Bins always start at 0
 * @param mzSpectrum The experimental spectrum
 * @param step The size of the bins normalization should occur in
 * @param normalizeTo The intensity height to normalize to
 * @return Normalized spectrum
 *
 */
MzSpectrum binNormalize(MzSpectrum const &mzSpectrum,
    types::mz_t const step,
    types::intensity_t const normalizeTo = 
        types::intensity_t(100.0f * units::intensity));
} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_normalize_hpp_ */

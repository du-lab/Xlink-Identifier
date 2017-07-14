/**
 * @file    xcorrelation.hpp
 * @brief   Utility functions for xcorrelation related functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/03
 * @copyright 2012
 */

#ifndef apollo_xcorrelation_hpp_
#define apollo_xcorrelation_hpp_

#include "types.hpp"
#include "dtatypes.hpp"
#include "ionconfig.hpp"
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
 * @brief Converts an IonSpectrum into an MzSpectrum, losing all
 *  ion information.
 * @param ionSpectrum The Ion Spectrum to be converted
 * @return The converted spectrum
 */
MzSpectrum ionToMzSpectrum(IonSpectrum const &ionSpectrum);

/**
 * @brief Bins a spectrum to int values
 * @note Bins always start at 0
 * @param mzSpectrum The MzSpectrum to be converted
 * @param step The step size to bin the spectrum in
 * @param sumIntensities Whether intensities should be summed (default=true),
 *  or choose only the largest intensity
 * @return The binned spectrum
 */

 // Step size must be floating. Must be able to be lower than 1
BinnedSpectrum binMzSpectrum(MzSpectrum const &mzSpectrum,
    types::mz_t const step,
    bool const sumIntensities = true);

/**
 * @brief Calculates the xcorrelation score between two spectrum
 * @param expSpectrum The experimental binned spectrum to be compared
 * @param theoSpectrum The theoretical binned spectrum to be compared
 * @param step The step size (an int) the spectrums are binned in
 * @param halfWindow The half window (an int) for the xcorrelation
 */

types::intensity_store_t xCorrelation(BinnedSpectrum const &expSpectrum,
    BinnedSpectrum const &theoSpectrum,
    types::mz_bin_t const halfWindow);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_xcorrelation_hpp_ */

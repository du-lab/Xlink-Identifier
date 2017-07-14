/**
 * @file    spectrumtypes.hpp
 * @brief   Different types to represent spectrums
 *
 * @author  Adam Baxter
 * @version 2.0
 * @since    2012/10/03
 * @copyright 2012
 */


#ifndef apollo_spectrumtypes_hpp_
#define apollo_spectrumtypes_hpp_


#include <boost/container/flat_map.hpp>
#include "types.hpp"
#include "ionconfig.hpp"

/**
 * @namespace apollo
 * @brief Apollo library
 */
namespace apollo {

/**
 * @typedef MzSpectrum
 * @brief Map between an mz and its intensity
 */
typedef boost::container::flat_map<
    types::mz_t,   // mz
    types::intensity_t   // intensity
    > MzSpectrum;

std::ostream& operator<<(std::ostream &out, MzSpectrum const &mzSpectrum);

typedef MzSpectrum::value_type MzIntPair;

std::ostream& operator<<(std::ostream &out, MzIntPair const &mzIntPair);

/**
 * @typed IonSpectrum
 * @brief Map between an Mz (Mz & Z) and its ion specification
 */
typedef boost::container::flat_multimap<Mz, IonSpec> IonSpectrum;

/**
 * @fn std::ostream& operator<<(std::ostream &out, IonSpectrum const &ionSpectrum)
 * @brief outputs the IonSpectrum
 */
std::ostream& operator<<(std::ostream &out, IonSpectrum const &ionSpectrum);

/**
 * @typed MzIonSpecPair
 * @brief A pair of an Mz (Mz & Z) and its ion specification
 */
typedef IonSpectrum::value_type MzIonSpecPair;

/**
 * @fn std::ostream& operator<<(std::ostream &out, MzIonSpecPair const &mzIonSpecPair)
 * @brief outputs the MzIonSpecPair
 */
std::ostream& operator<<(std::ostream &out, MzIonSpecPair const &mzIonSpecPair);

/**
 * @typed FlooredSpectrum
 * @brief Map between floored mz values and its intensity
 */
typedef boost::container::flat_map<types::mz_bin_t, types::intensity_t> BinnedSpectrum;

std::ostream& operator<<(std::ostream &out, BinnedSpectrum const &bmzSpectrum);

typedef BinnedSpectrum::value_type BMzIntPair;

std::ostream& operator<<(std::ostream &out, BMzIntPair const &bmzIntPair);


} /* namespace apollo */

#endif /* apollo_spectrumtypes_hpp_ */

/**
 * @file    types.hpp
 * @brief   apollo typedefs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#ifndef apollo_types_hpp_
#define apollo_types_hpp_

#include <string>
#include <boost/functional/hash.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <boost/cstdint.hpp>
#include "units.hpp"

/**
 * @namespace apollo
 * @brief Apollo library
 */
namespace apollo {

/**
 * @namespace types
 * @brief Defines basic types used throughout the apollo library
 */
namespace types {
using boost::units::quantity;
using boost::units::si::dimensionless;

/**
 * @typedef mass_store_t
 * @brief Storage unit for mass
 */
typedef float mass_store_t;

/**
 * @typedef dalton_t
 * @brief Dalton quantity
 */
typedef quantity<units::dalton_unit, mass_store_t> dalton_t;

/**
 * @typedef ppm_t
 * @brief PPM quantity
 */
typedef quantity<dimensionless, mass_store_t> ppm_t;

/**
 * @typedef mz_store_t
 * @brief Storage unit for mass charge
 */
typedef float mz_store_t;

/**
 * @typedef mz_t
 * @brief Mass charge quantity
 */

typedef quantity<units::mass_charge_unit, mz_store_t> mz_t;

/**
 * @typedef intensity_store_t
 * @brief Storage unit for intensity
 */
typedef float intensity_store_t;

/**
 * @typedef intensity_t
 * @brief Intensity quantity
 */
typedef quantity<units::ms_intensity_unit, intensity_store_t> intensity_t;

/**
 * @typedef count_store_t
 * @brief Storage unit for counts (so many of x item)
 * @note This is signed on purpose. -WHEN- numerical overflows occur,
 *  they will be very obvious. NEVER change these to be unsigned, ever.
 *  Simply increase the storage size to the next largest size
 */
typedef boost::int16_t count_store_t;

/**
 * @typedef count_t
 * @brief Count quantity
 */
typedef quantity<dimensionless, count_store_t> count_t;

/**
 * @typedef charge_store_t
 * @brief Storage unit for charge
 * @note This is signed on purpose. -WHEN- numerical overflows occur,
 *  they will be very obvious. NEVER change these to be unsigned, ever.
 *  Simply increase the storage size to the next largest size
 */
typedef boost::int16_t charge_store_t;

/**
 * @typedef charge_t
 * @brief Charge quantity
 */
typedef quantity<units::charge_unit, charge_store_t> charge_t;


/**
 * @typedef mz_floor_store_t
 * @brief Storage unit for mass charge after its been floored
 * @note We use integer for sanity reasons. Dragons lay in wait when doing 
 *  == comparisons with float
 * @note This is signed on purpose. -WHEN- numerical overflows occur,
 *  they will be very obvious. NEVER change these to be unsigned, ever.
 *  Simply increase the storage size to the next largest size
 */
typedef boost::int32_t mz_bin_t;

/**
 * @typedef scanCount_store_t
 * @brief storage unit for dta scan count
 * @note This is signed on purpose. -WHEN- numerical overflows occur,
 *  they will be very obvious. NEVER change these to be unsigned, ever.
 *  Simply increase the storage size to the next largest size
 */
typedef boost::int32_t scanCount_store_t;

/**
 * @typedef residue_t
 * @brief Storage unit for residue characters
 */
typedef char residue_t;

/**
 * @typedef io_string_t
 * @brief String type for accessing file io
 */
typedef std::string io_string_t;

/**
 * @typedef sequence_string_t
 * @brief String type for storing sequences
 */
typedef std::basic_string<residue_t> sequence_string_t;

/**
 * @typedef regex_t
 * @brief Xpressive regex string type
 */
typedef boost::xpressive::sregex regex_t;

/**
 * @typedef regex_it_t
 * @brief Xpressive regex string iterator type
 */
typedef boost::xpressive::sregex_iterator regex_it_t;

} /* namespace types */

} /* namespace apollo */

#endif /* apollo_types_hpp_ */

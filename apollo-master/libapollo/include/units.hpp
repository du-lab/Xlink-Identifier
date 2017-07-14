/**
 * @file    units.hpp
 * @brief   Defines dalton as a boost unit
 *      to prevent stupid mistakes in calculations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#ifndef apollo_units_hpp_
#define apollo_units_hpp_

#include <boost/units/conversion.hpp>
#include <boost/units/io.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/prefixes.hpp>

/**
 * @namespace apollo
 * @brief Apollo library
 */

namespace apollo {

/**
 * @namespace units
 * @brief Defines units used throughout calculations to prevent incorrect math
 *  from occurring
 */

namespace units {

using boost::units::base_unit;
using boost::units::mass_dimension;
using boost::units::luminous_intensity_dimension;
using boost::units::electric_charge_dimension;
using boost::units::unit;
using boost::units::make_system;

/* Dalton */

/**
 * @struct dalton_mass_base_unit
 * @brief Boost::units definition for dalton
 */
struct dalton_mass_base_unit :
    base_unit<dalton_mass_base_unit, mass_dimension, 1> {
        static std::string name() { return "dalton"; }
        static std::string symbol() { return "Da"; }
    };

/**
 * @typedef dalton_system
 * @brief Boost::units system for dalton
 */
typedef make_system<dalton_mass_base_unit>::type dalton_system;

/**
 * @typedef dalton_unit
 * @brief Binding the dalton_system to the mass dimension
 */
typedef unit<mass_dimension, dalton_system> dalton_unit;

/**
 * @var dalton_mass
 * @brief A single instance of a dalton
 */
static const dalton_unit dalton_mass;

/* Intensity */

/**
 * @struct ms_intensity_base_unit
 * @brief Boost::units definition for intensity
 */
struct ms_intensity_base_unit :
    base_unit<ms_intensity_base_unit, luminous_intensity_dimension, 2> {
        static std::string name() { return "intensity"; }
        static std::string symbol() { return "int"; }
    };

/**
 * @typedef ms_intensity_system
 * @brief Boost::units system for intensity
 */
typedef make_system<ms_intensity_base_unit>::type ms_intensity_system;

/**
 * @typedef ms_intensity_unit
 * @brief Binding the ms_intensity_system to the luminous intensity dimension
 */
typedef unit<luminous_intensity_dimension, ms_intensity_system> ms_intensity_unit;

/**
 * @var inensity
 * @brief A single instance of intensity
 */
static const ms_intensity_unit intensity;

/* Charge */

/**
 * @struct charge_state_base_unit
 * @brief Boost::units definition for charge
 */
struct charge_state_base_unit :
    base_unit<charge_state_base_unit, electric_charge_dimension, 3> {
        static std::string name() { return "charge"; }
        static std::string symbol() { return "z"; }
    };

/**
 * @typedef charge_system
 * @brief Boost::units system for charge
 */
typedef make_system<charge_state_base_unit>::type charge_system;

/**
 * @typedef charge_unit
 * @brief Binding the charge_system to the electric charge dimension
 */
typedef unit<electric_charge_dimension, charge_system> charge_unit;

/**
 * @var charge
 * @brief A single instance of charge
 */
static const charge_unit charge;

/* Mass Charge */

/**
 * @typedef mass_charge_unit
 * @brief Defining that a mass charge is Da/z
 */
typedef boost::units::divide_typeof_helper<dalton_unit, charge_unit>::type mass_charge_unit;

/**
 * @var mass_charge
 * @brief A single instance of mass charge
 */
static const mass_charge_unit mass_charge;
} /* namespace units */
} /* namespace apollo */


/**
 * @brief Tells boost::units how to convert between a dalton and a kg, and,
 *  therefore, any other mass available in boost::units
 */

BOOST_UNITS_DEFINE_CONVERSION_FACTOR(apollo::units::dalton_mass_base_unit,
    boost::units::si::kilogram_base_unit,
    double, 1.66053892173e-27);

#endif /* apollo_units_hpp_ */

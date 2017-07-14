/**
 * @file    stdmass.hpp
 * @brief   Defines oft used masses in dalton
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */
#ifndef apollo_stdmass_hpp_
#define apollo_stdmass_hpp_

#include <boost/units/static_constant.hpp>
#include "types.hpp"
#include "residuemass.hpp"

namespace apollo {

namespace stdmass {

using units::dalton_mass;
using types::dalton_t;

dalton_t const zero_da(0.0f * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(zero_da, dalton_t);

// Atoms, ordered by mass
dalton_t const H_da(1.00782 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(H_da, dalton_t);

dalton_t const O_da(15.9949141 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(O_da, dalton_t);

dalton_t const Na_da(22.98976928 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(Na_da, dalton_t);

dalton_t const K_da(39.0983 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(K_da, dalton_t);

// Chemicals, ordered by mass
dalton_t const CH2_da(14.01565 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(CH2_da, dalton_t);

dalton_t const NH3_da(17.02655 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(NH3_da, dalton_t);

dalton_t const H2O_da(18.01056 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(H2O_da, dalton_t);

dalton_t const CO_da(27.99492 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(CO_da, dalton_t);

dalton_t const H3PO4_da(97.9769 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(H3PO4_da, dalton_t);

namespace residue {

/**
 * @brief Map of the standard average masses for all 20 amino acids
 */
extern ResidueMass const AvgMap_da;

/**
 * @brief Map of the standard monoisotopic masses for all 20 amino acids
 */
extern ResidueMass const MonoisotopicMap_da;

namespace mod {
// Single amino acid mod
dalton_t const Cys_da(57.0215 * dalton_mass);
BOOST_UNITS_STATIC_CONSTANT(Cys_da, dalton_t);


} /* namespace mod */


} /* namespace residue */

} /* namespace stdmass */

} /* namespace apollo*/

#endif /* apollo_stdmass_hpp_ */

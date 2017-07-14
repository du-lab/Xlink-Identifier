/**
 * @file    stdcharge.hpp
 * @brief   Defines oft used charges in z
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/13
 * @copyright 2012
 */
#ifndef apollo_stdcharge_hpp_
#define apollo_stdcharge_hpp_

#include <boost/units/static_constant.hpp>
#include "types.hpp"

namespace apollo {

namespace stdcharge {

types::charge_t const singleCharge(1 * units::charge);
BOOST_UNITS_STATIC_CONSTANT(singleCharge, types::charge_t);

} /* */

} /* namespace apollo */

#endif /* apollo_stdcharge_hpp_ */
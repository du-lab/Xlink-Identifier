/**
 * @file    f_mz.cpp
 * @brief   A filter for use when iterating through masses using 
 *  mz as a determinant
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/21
 * @copyright 2012
 */

#include "f_mz.hpp"
#include "../core/geometryutil.hpp"

namespace apollo {

namespace filter {

types::mz_store_t const intervalThreshold = 0.001f;

bool range_Mz::operator()(filter_type const &theoreticalMh) const {
    if ((theoreticalMh >= _lowerMh) && 
        (theoreticalMh < _upperMh)) {
        return true;
    } else {
        return false;
    }
}

types::mz_t range_Mz::lower() const {
    return _lowerMh;
}

types::mz_t range_Mz::upper() const {
    return _upperMh;
}

Box1D range_Mz::toBox() const {
    return boxFrom(_lowerMh.value() - intervalThreshold,
            _upperMh.value() + intervalThreshold);
}

range_Mz range_Mz::FromMhAndTolerance(types::mz_t const mh, types::mz_t const tolerance) {
    return range_Mz(mh - tolerance, mh + tolerance);
}

const types::ppm_t exp = 1000000;

range_Mz range_Mz::FromPpm(types::mz_t const mh, types::ppm_t const ppm) {
    using types::mz_t;
    using types::ppm_t;
    ppm_t const basePpm = ppm /exp;
    mz_t const upperRange = mh/(1 - basePpm);
    mz_t const lowerRange = mh/(basePpm + 1);
    return range_Mz(lowerRange, upperRange);

}

} /* namespace filter */
} /* namespace apollo */

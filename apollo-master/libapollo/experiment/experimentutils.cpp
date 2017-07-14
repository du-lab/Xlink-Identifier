/**
 * @file    experimentutils.cpp
 * @brief   Misc. utilities for use in experiment related functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#include "experimentutils.hpp"

namespace apollo {

namespace fn {

bool smallerIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2) {
    if (mzIntPair1.second < mzIntPair2.second) {
        return true;
    } else {
        return false;
    }
}


bool greaterIntensity(MzSpectrum::value_type const &mzIntPair1,
    MzSpectrum::value_type const &mzIntPair2) {
    if (mzIntPair1.second > mzIntPair2.second) {
        return true;
    } else {
        return false;
    }
}

} /* namespace fn */
} /* namespace apollo */

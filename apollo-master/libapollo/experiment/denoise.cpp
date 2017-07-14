/**
 * @file    denoise.cpp
 * @brief   Various denoise functions for experimental datasets
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#include <algorithm>
#include <vector>
#include "experimentutils.hpp"
#include "denoise.hpp"


namespace apollo {

namespace fn {

MzSpectrum kMostIntensePeaks(MzSpectrum const &mzSpectrum, 
    types::count_store_t const k) {
    using std::sort;
    if (mzSpectrum.size() <= k) {
        return mzSpectrum;
    }

    std::vector<MzSpectrum::value_type> 
        mzVector(mzSpectrum.begin(), mzSpectrum.end());

    // greaterIntensity function from experimentutils.hpp
    sort(mzVector.begin(), mzVector.end(), greaterIntensity);

    return MzSpectrum(mzVector.begin(), mzVector.begin() + k);
}

MzSpectrum minimumIntensity(MzSpectrum const &mzSpectrum, types::intensity_t intensity) {
    MzSpectrum fSpectrum;
    for(MzSpectrum::value_type const & mzIntPair : mzSpectrum) {
        if (mzIntPair.second >= intensity) {
            fSpectrum.insert(mzIntPair);
        }
    }
    return fSpectrum;
}

} /* namespace fn */
} /* namespace apollo */

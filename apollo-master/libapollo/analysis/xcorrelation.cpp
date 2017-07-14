/**
 * @file    xcorrelation.cpp
 * @brief   Utility functions for converting spectrums
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/03
 * @copyright 2012
 */

#include <cmath>

#include "units.hpp"
#include "xcorrelation.hpp"


namespace apollo {

namespace fn {

MzSpectrum ionToMzSpectrum(IonSpectrum const &ionSpectrum) {
    using types::intensity_t;
    using units::intensity;
    intensity_t const default_Intensity(50.0f * intensity);

    MzSpectrum mzSpectrum;
    for(auto const &ionSpecPair : ionSpectrum) {
       mzSpectrum[ionSpecPair.first.mz()] += default_Intensity; 
    }
    return mzSpectrum;
}

BinnedSpectrum binMzSpectrum(MzSpectrum const &mzSpectrum,
    types::mz_t const step,
    bool const sumIntensities) {
    using types::mz_bin_t;
    using units::mass_charge;

    BinnedSpectrum bSpectrum;
    for(auto const &mzSpecPair : mzSpectrum) {

        mz_bin_t bin = (mz_bin_t)(mzSpecPair.first/step);

        if (sumIntensities) {
            bSpectrum[bin] += mzSpecPair.second;
        } else {
            if (bSpectrum[bin] < mzSpecPair.second) {
                bSpectrum[bin] = mzSpecPair.second;
            }
        }
    }
    return bSpectrum;
}

// Owen Edit
// Find the number of experimental spectal lines that are within a given tolerance of a theoretical
// line
//int FindNumMatches(MzSpectrum const &theoSpectrum, 
//    MzSpectrum const &expSpectrum, mzTol){
//
//    int count = 0;
//
//    for (auto const &curTheo: theoSpectrum)
//    {
//        for (auto const &curExp: expSpectrum)
//        {
//            if (((curTheo.first + mzTol)>curExp.first)
//                    &&((curTheo.first - mzTol)<curExp.first))
//            {
//                count++;
//            }
//        }
//    }
//    return count
//}

BinnedSpectrum::mapped_type bFind(BinnedSpectrum const &bSpectrum,
    BinnedSpectrum::key_type const key) {

    using types::intensity_t;
    using units::intensity;
    
    intensity_t const zeroInt(0 * intensity);

    BinnedSpectrum::const_iterator it = bSpectrum.find(key);
    if (it != bSpectrum.end()) {
        return it->second;
    } else {
        return zeroInt;
    }
}

// halfWindow comes from options. Hard set in optiontypes.cpp. halfWindow = 75
types::intensity_store_t xCorrelation(BinnedSpectrum const &expSpectrum,
    BinnedSpectrum const &theoSpectrum,
    types::mz_bin_t const halfWindow) {

    using types::intensity_store_t;
    using types::mz_bin_t;
    using units::mass_charge;

    intensity_store_t scoreAtZero = 0.0f;
    intensity_store_t otherScores = 0.0f;

    for(mz_bin_t shift = -halfWindow; 
        shift <= halfWindow; 
        shift += 1) {

        intensity_store_t stepScore = 0.0f;
        for(auto const &expPair : expSpectrum) {
            mz_bin_t shiftedBin = expPair.first + shift;
            stepScore += 
                (expPair.second.value() * 
                    bFind(theoSpectrum, shiftedBin).value());
        }
        if (shift == 0) {
            scoreAtZero = stepScore;
        } else {
            otherScores += stepScore;
        }

    }


    mz_bin_t const windowSize = 2 * halfWindow; 
    intensity_store_t const avgOtherScores = otherScores/windowSize;

    return (scoreAtZero - avgOtherScores)/1000.0f;
}

} /* namespace fn */
} /* namespace apollo */

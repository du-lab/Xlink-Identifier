/**
 * @file    normalize.cpp
 * @brief   Various normalization functions for experimental datasets
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <vector>


#include "normalize.hpp"
#include "experimentutils.hpp"

namespace apollo {

namespace fn {

MzSpectrum normalize(MzSpectrum const &mzSpectrum,
    types::intensity_t const normalizeTo) {
    
    using std::make_pair;
    using std::max_element;
    using types::intensity_t;
    using types::intensity_store_t;

    MzSpectrum normalizedSpectrum(mzSpectrum);

    intensity_t const maxInt = (max_element(mzSpectrum.begin(), 
        mzSpectrum.end(),
        smallerIntensity))->second;

    // The spectrum's max intensity 
    intensity_store_t const maxScale = normalizeTo/maxInt;
    
    for(auto &mzSpecPair : normalizedSpectrum) {
        mzSpecPair.second = mzSpecPair.second * maxScale;

    }

    return normalizedSpectrum;
}

//TODO: Do this without making a vector, use iterator
// that way we can just copy in the spectrum without having to make a new one
MzSpectrum binNormalize(MzSpectrum const &mzSpectrum,
    types::mz_t const step,
    types::intensity_t const normalizeTo) {

    using std::make_pair;
    using types::intensity_t;
    using types::intensity_store_t;
    using units::intensity;

    using types::mz_bin_t;
    using units::mass_charge;

    intensity_t const zero_int(0.0f * intensity);

    MzSpectrum normalizedSpectrum;

    // @note We make copies of the mz,int pairs here, instead of references.
    //  This is because the size of the pairs is equal to the size of the reference.
    //  Thusly, the function is faster not having to dereference the pointers
    //  each time.
    std::vector<MzSpectrum::value_type> binVector;




    bool firstBin = true;
    mz_bin_t currentBin;
    intensity_t largestInt = zero_int;

    for(auto const &mzSpecPair : mzSpectrum) {
        // Round the mz to the nearest int, keeping it in mass charge units
        mz_bin_t bin = (mz_bin_t)(mzSpecPair.first/step);

        if (firstBin) {
            currentBin = bin;
            firstBin = false;
        } else {
            if (currentBin != bin) {
                intensity_store_t binScale = 
                    normalizeTo/largestInt;

                for(auto const &binPair : binVector) {
                    normalizedSpectrum.emplace(
                        binPair.first, 
                        binPair.second * binScale
                    );
                }

                binVector.clear();
                currentBin = bin;
                largestInt = zero_int;
            }
        }
        
        if (largestInt < mzSpecPair.second) {
            largestInt = mzSpecPair.second;
        }

        binVector.emplace_back(mzSpecPair);
    }

    // Run through the vector for the last bin
    intensity_store_t scale = 
        normalizeTo.value()/largestInt.value();
    for(auto const &binPair : binVector) {
        normalizedSpectrum.emplace(
            binPair.first, 
            binPair.second.value() * scale * intensity
        );
    }
    return normalizedSpectrum;
}

} /* namespace fn*/
} /* namespace apollo */

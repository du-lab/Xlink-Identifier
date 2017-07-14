/**
 * @file    spectrumtypes.cpp
 * @brief   Different types to represent spectrums
 *
 * @author  Adam Baxter
 * @version 2.0
 * @since    2012/10/03
 * @copyright 2012
 */

#include "spectrumtypes.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, IonSpectrum const &ionSpectrum) {
    using std::endl;
    for(auto const &mzSpecPair : ionSpectrum) {
        out << mzSpecPair << endl;
    }
    return out;
}


std::ostream& operator<<(std::ostream &out, MzIonSpecPair const &mzIonSpecPair) {
    out << mzIonSpecPair.first.mz().value() << " : " << mzIonSpecPair.second;
    return out;
}

std::ostream& operator<<(std::ostream &out, MzSpectrum const &mzSpectrum) {
    using std::endl;
    for(auto const &mzIntPair : mzSpectrum) {
        out << mzIntPair << endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, MzIntPair const &mzIntPair) {
    out << mzIntPair.first.value() << " : " << mzIntPair.second.value();
    return out;
}

std::ostream& operator<<(std::ostream &out, BinnedSpectrum const &bmzSpectrum) {
    using std::endl;
    for(auto const &bmzSpecPair : bmzSpectrum) {
        out << bmzSpecPair << endl;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, BMzIntPair const &bmzIntPair) {
    out << bmzIntPair.first << " : " << bmzIntPair.second;
    return out;
}

} /* namespace apollo */

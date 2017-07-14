/**
 * @file    sequencescore.cpp
 * @brief   The final result object, responsible for both creating and storing the final
 *  calculations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/26
 * @copyright 2012
 */

#include "../analysis/xcorrelation.hpp"
#include "../analysis/sp.hpp"

#include "sequencescore.hpp"

namespace apollo {

SequenceScore::SequenceScore(SequenceMotif const& sequenceMotif,
    AnalysisOptions const &aOptions,
    CandidateIons &&candidateIons,
    MzSpectrum const &dtaSpectrum,
    BinnedSpectrum const &binnedDtaSpectrum) {}

SequenceScore::SequenceScore(AnalysisOptions const &aOptions,
    CandidateIons &&candidateIons,
    MzSpectrum const &dtaSpectrum,
    BinnedSpectrum const &binnedDtaSpectrum) :
    _candidateIons(std::move(candidateIons)) {
    
    using fn::ionToMzSpectrum;
    using fn::binMzSpectrum;
    using fn::xCorrelation;
    using fn::spCalculation;

    MzSpectrum ionSpectrum = ionToMzSpectrum(_candidateIons.spectrum());
    BinnedSpectrum binnedIonSpectrum = binMzSpectrum(ionSpectrum, 
        aOptions.xCorrelation.binStepSize,
        aOptions.xCorrelation.binSumIntensities);

    // binnedIonSpectrum is the theoretical spectrum
    _xCorrelation = xCorrelation(binnedDtaSpectrum, 
        binnedIonSpectrum, 
        aOptions.xCorrelation.halfWindow);

    // SP Score is bugged for now. Need to figure it out. Fortunately we don't need it atm
    _spResult = spCalculation(dtaSpectrum, 
        _candidateIons.spectrum(),
        aOptions.spSearch.mzTolerance);

}

SequenceScore::SequenceScore(SequenceScore &&rhs) :
    _xCorrelation(rhs._xCorrelation),
    _candidateIons(std::move(rhs._candidateIons)),
    _spResult(std::move(rhs._spResult)) {}

SequenceScore& SequenceScore::operator=(SequenceScore &&rhs) {
    if (this != &rhs) {
        _xCorrelation = rhs._xCorrelation;
        _candidateIons = std::move(rhs._candidateIons);
        _spResult = std::move(rhs._spResult);
    }
    return *this;
}

types::intensity_store_t const SequenceScore::xCorrelation() const {
    return _xCorrelation;
}

SpResult const& SequenceScore::sp() const {
    return _spResult;
}

} /* namespace apollo */

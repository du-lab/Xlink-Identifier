/**
 * @file    sequencescore.hpp
 * @brief   The final result object, responsible for both creating and storing the final
 *  calculations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/26
 * @copyright 2012
 */

#ifndef apollo_sequencescore_hpp_
#define apollo_sequencescore_hpp_

#include "../core/macros.hpp"
#include <utility>
#include <functional>

#include "types.hpp"
#include "optiontypes.hpp"
#include "spectrumtypes.hpp"
#include "sequenceconfig.hpp"
#include "candidateions.hpp"
#include "spresult.hpp"


namespace apollo {

class SequenceScore {
public:
    SequenceScore(SequenceMotif const& sequenceMotif,
        AnalysisOptions const &aOptions,
        CandidateIons &&candidateIons,
        MzSpectrum const &dtaSpectrum,
        BinnedSpectrum const &binnedDtaSpectrum);

    SequenceScore(AnalysisOptions const &aOptions,
        CandidateIons &&candidateIons,
        MzSpectrum const &dtaSpectrum,
        BinnedSpectrum const &binnedDtaSpectrum);

    SequenceScore(SequenceScore &&rhs);

    SequenceScore& operator=(SequenceScore &&rhs);


    types::intensity_store_t const xCorrelation() const;

    SpResult const& sp() const;

    CandidateIons const& candidates() const { return _candidateIons; }

    ~SequenceScore() {}

private:
    types::intensity_store_t _xCorrelation;
    CandidateIons _candidateIons;
    SpResult _spResult;
};

} /* namespace apollo */

#endif /* apollo_sequencescore_hpp_ */

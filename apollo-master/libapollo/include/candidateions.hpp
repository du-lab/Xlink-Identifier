/**
 * @file    candidateions.hpp
 * @brief   A holder for candidate ions for a sequence or linked sequences
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/25
 * @copyright 2012
 */

#ifndef apollo_candidateions_hpp_
#define apollo_candidateions_hpp_

#include <iostream>
#include <unordered_set>
#include <utility>

#include <boost/utility.hpp>

#include "enums.hpp"
#include "dtatypes.hpp"
#include "optiontypes.hpp"
#include "sequenceinterface.hpp"
#include "sequenceconfig.hpp"
#include "spectrumtypes.hpp"
#include "ionconfig.hpp"
#include "../core/linker.hpp"
#include "../theory/ion/mzionspeciter.hpp"

namespace apollo {

// Copying not allowed due to reference requirements
class CandidateIons : boost::noncopyable {

public:

    // Constructors
    CandidateIons(){}

    template <typename IteratorT>
    CandidateIons(IteratorT begin, IteratorT end,
        types::charge_t dtaCharge,
        TheoreticalSpectrumOptions const &tSpecOptions,
        Linker::shp linker = Linker::shp()) :
        _ionConfigSet(begin, end) {
            MzIonSpecIter const specEnd;
            for(auto const &ionConfig : _ionConfigSet) {
                MzIonSpecIter specIter = make_geniter<MzIonSpecGen>(ionConfig, dtaCharge, tSpecOptions, linker);

                _candidateSpectrum.insert(specIter, specEnd);
            }
        }

    // Move 
    CandidateIons(CandidateIons &&rhs);

    // Move
    CandidateIons& operator=(CandidateIons &&rhs);

    IonSpectrum const& spectrum() const;

    ~CandidateIons() {}
private:

    typedef std::unordered_set<IonConfig> IonConfigSet;
    IonConfigSet _ionConfigSet;
    IonSpectrum _candidateSpectrum;
};

} /* namespace apollo */

#endif /* apollo_candidateions_hpp_ */

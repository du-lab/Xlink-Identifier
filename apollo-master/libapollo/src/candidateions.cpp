/**
 * @file    candidateions.cpp
 * @brief   A holder for candidate ions for a sequence or linked sequences
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/25
 * @copyright 2012
 */



#include "candidateions.hpp"

namespace apollo {

CandidateIons::CandidateIons(CandidateIons &&rhs) :
    _ionConfigSet(std::move(rhs._ionConfigSet)),
    _candidateSpectrum(std::move(rhs._candidateSpectrum)) {}

CandidateIons& CandidateIons::operator=(CandidateIons &&rhs) {
    if (this != &rhs) {
        _ionConfigSet = std::move(rhs._ionConfigSet);
        _candidateSpectrum = std::move(rhs._candidateSpectrum);
    }
    return *this;
}

IonSpectrum const& CandidateIons::spectrum() const {
    return _candidateSpectrum;
}

} /* namespace apollo */

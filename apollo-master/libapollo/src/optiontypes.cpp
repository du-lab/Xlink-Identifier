/**
 * @file    optiontypes.cpp
 * @brief   Types returned to represent the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#include <iostream>
#include "../core/stdmass.hpp"
#include "../core/regexdigest.hpp"
#include "../core/linkers.hpp"
#include "optiontypes.hpp"

namespace apollo {


using types::io_string_t;
using validation::DigestTolerance;
using apollo::stdmass::residue::MonoisotopicMap_da;
using units::charge;

JobOptions::JobOptions() :
    id("default"), 
    owner("xiuxia.du@uncc.edu") {}

bool JobOptions::operator==(JobOptions const &rhs) const {
    if ((id == rhs.id) &&
        (owner == rhs.owner)) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream &out, JobOptions const &rhs) {
    out << "id: " << rhs.id << ", owner: " << rhs.owner;
    return out;
}

io_string_t const defaultDigest("trypsin");
DigestTolerance::size_type const digestMinLength = 6;
DigestTolerance::size_type const digestMaxLength = 31;
DigestTolerance::size_type const digestMaxNmx = 4;

DigestOptions::DigestOptions() : 
    digestName(defaultDigest), 
    digestRegex(DigestRegexMap.at(defaultDigest)),
    digestType(enums::Digest::Full),
    digestTolerance(digestMinLength, digestMaxLength, digestMaxNmx) {}

std::ostream& operator<<(std::ostream &out, DigestOptions const &rhs) {
    out << "Regex: " << rhs.digestName <<
        ", Type: " << rhs.digestType <<
        ", Tolerance: " << rhs.digestTolerance;
    return out;
}

SequenceOptions::SequenceOptions() :
    reverse(false),
    stdResidueMass(MonoisotopicMap_da) {}

bool SequenceOptions::operator==(SequenceOptions const &rhs) const {
    if ((reverse == rhs.reverse) && 
        (stdResidueMass == rhs.stdResidueMass) &&
        (staticMods == rhs.staticMods) &&
        (iStaticMods == rhs.iStaticMods) &&
        (dynamicModMasses == rhs.dynamicModMasses) &&
        (dynamicMods == rhs.dynamicMods) &&
        (iDynamicMods == rhs.iDynamicMods) ) {
        return true;
    } else {
        return false;
    }
}

bool SequenceOptions::operator<(SequenceOptions const &rhs) const {
    if ((reverse < rhs.reverse) &&
        (stdResidueMass < rhs.stdResidueMass) &&
        (staticMods < rhs.staticMods) &&
        (iStaticMods < rhs.iStaticMods) &&
        (dynamicModMasses < rhs.dynamicModMasses) &&
        (dynamicMods < rhs.dynamicMods) &&
        (iDynamicMods < rhs.iDynamicMods)) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream &out, SequenceOptions const &sOptions) {
    using std::endl;
    out << "Id: " << sOptions.id << endl;
    out << "Reverse: " << sOptions.reverse << endl;
    out << "StdResidues: " << sOptions.stdResidueMass << endl;
    out << "Static Mods: " << sOptions.staticMods << endl;
    out << "Static Mod Masses: " << sOptions.staticModMasses << endl;
    out << "Dynamic Mods: " << sOptions.dynamicMods << endl;
    out << "Dynamic Mod Masses: " << sOptions.dynamicModMasses;
    return out;
}

std::ostream& operator<<(std::ostream &out, SequenceOptionsMap const &rhs) {
    using std::endl;
    for (auto const & soPair : rhs) {
        out << soPair.second << endl;
    }
    return out;
}


LinkerOptions::LinkerOptions()
    {}

bool LinkerOptions::operator==(LinkerOptions const &rhs) const {
    if (linkers == rhs.linkers) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream &out, LinkerOptions const &lOptions) {
    using std::endl;
    bool afterFirst = false;
    for(auto const &linkerShp : lOptions.linkers) {
        if (afterFirst) {
            out << endl;
        }
        out << *linkerShp;
        afterFirst = true;
    }
    return out;
}

MzSearchTolerance::MzSearchTolerance() {}


std::ostream& operator<<(std::ostream &out, MzSearchTolerance const &searchTolerance) {
    using enums::Tolerance;
    switch(searchTolerance.type) {
    case Tolerance::Mz:
    out << searchTolerance.mzTolerance.value();
    break;
    case Tolerance::Ppm:
    out << searchTolerance.ppmTolerance.value();
    break;
    }
    out << " " << searchTolerance.type;
    return out;
}

TheoreticalSpectrumOptions::TheoreticalSpectrumOptions() :
    H2OLoss(false),
    Nh3Loss(false),
    aIon(false),
    maxFragmentIonCharge(6 * charge)
    {
        using enums::FragmentationMethod;
        fragmentation.intraSequenceFragmentsUnderLinker = false;
        fragmentation.method = FragmentationMethod::Cid;
    }

bool TheoreticalSpectrumOptions::operator==(TheoreticalSpectrumOptions const &rhs) const {
    if ((H2OLoss == rhs.H2OLoss) && 
        (Nh3Loss == rhs.Nh3Loss) &&
        (aIon == rhs.aIon) &&
        (maxFragmentIonCharge == rhs.maxFragmentIonCharge) &&
        (fragmentation.method == fragmentation.method)) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream &out, TheoreticalSpectrumOptions const &tSpecOptions) {
    using std::endl;
    out << "H20Loss: " << tSpecOptions.H2OLoss;
    out << ", Nh3Loss: " << tSpecOptions.Nh3Loss;
    out << ", A-Ion: " << tSpecOptions.aIon;
    out << ", Max Fragment Ion Charge: " << tSpecOptions.maxFragmentIonCharge.value();
    out << ", intraSequenceFragmentsUnderLinker: " << tSpecOptions.fragmentation.intraSequenceFragmentsUnderLinker;
    out << ", Fragment Method: " << tSpecOptions.fragmentation.method;
    return out;
}

XCorrelationOptions::XCorrelationOptions() :
    binStepSize(1.0f * units::mass_charge),
    binSumIntensities(false),
    halfWindow(75)
    {}

std::ostream& operator<<(std::ostream &out, XCorrelationOptions const &xCorrelationOptions) {
    using std::endl;
    out << "binStepSize: " << xCorrelationOptions.binStepSize.value();
    out << ", binSumIntensities: " << xCorrelationOptions.binSumIntensities;
    out << ", halfWindow: " << xCorrelationOptions.halfWindow;
    return out;
}

AnalysisOptions::AnalysisOptions()
    {
        using enums::Tolerance;
        using units::mass_charge;
        precursorSearch.type = Tolerance::Ppm;
        precursorSearch.ppmTolerance = 250;

        spSearch.type = Tolerance::Mz;
        spSearch.mzTolerance = 0.6f * mass_charge;
    }

std::ostream& operator<<(std::ostream &out, AnalysisOptions const &aOptions) {
    using std::endl;
    out << "precursorSearch: " << aOptions.precursorSearch << endl;
    out << "theoreticalSpectrum: " << aOptions.theoreticalSpectrum << endl;
    out << "spSearch: " << aOptions.spSearch;
    return out;
}

} /* namespace apollo */

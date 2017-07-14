/**
 * @file    optiontypes.hpp
 * @brief   Types returned to represent the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#ifndef apollo_optiontypes_hpp_
#define apollo_optiontypes_hpp_

#include <boost/container/flat_map.hpp>

#include "enums.hpp"
#include "types.hpp"
#include "residuemass.hpp"
#include "residuemod.hpp"
#include "residuecount.hpp"
#include "../core/digesttolerance.hpp"
#include "../core/linker.hpp"
#include "../core/reactiongroup.hpp"
#include "sequenceinterface.hpp"
#include "linkloc.hpp"

namespace apollo {

struct JobOptions {
    types::io_string_t id;
    types::io_string_t owner;
    JobOptions();
    bool operator==(JobOptions const &rhs) const;
};

std::ostream& operator<<(std::ostream &out, JobOptions const &rhs);

struct DigestOptions {
    types::io_string_t digestName;
    types::regex_t digestRegex;
    enums::Digest digestType;
    validation::DigestTolerance digestTolerance;
    DigestOptions();
};

std::ostream& operator<<(std::ostream &out, DigestOptions const &rhs);

/*TODO: Perhaps store sequence options as a set? */
struct SequenceOptions {
    types::io_string_t id;
    bool reverse;
    ResidueMass stdResidueMass;
    ResidueMod staticMods;
    ResidueMod iStaticMods;
    ResidueMass staticModMasses;
    ResidueMod dynamicMods;
    ResidueMod iDynamicMods;
    ResidueMass dynamicModMasses;
    SequenceOptions();
    bool operator==(SequenceOptions const &rhs) const;
    bool operator<(SequenceOptions const &rhs) const;
};

std::ostream& operator<<(std::ostream &out, SequenceOptions const &sOptions);

typedef boost::container::flat_map<types::io_string_t, SequenceOptions> SequenceOptionsMap;

std::ostream& operator<<(std::ostream &out, SequenceOptionsMap const &rhs);

struct MustInterlinkOptions {
    bool isEnabled;
    types::io_string_t id;
    SequenceI::shp sequence;
    bool isDynamicModCountKnown;
    ResidueCount dynamicModCount;
    LinkLoc linkLocation;
    MustInterlinkOptions();
    bool operator==(MustInterlinkOptions const &rhs) const;
};

std::ostream& operator<<(std::ostream &out, MustInterlinkOptions const &rhs);

struct LinkerOptions {
    Linker::shp_vec linkers;
    LinkerOptions();
    bool operator==(LinkerOptions const &rhs) const;
};

std::ostream& operator<<(std::ostream &out, LinkerOptions const &lOptions);

struct MzSearchTolerance {
    enums::Tolerance type;
    types::mz_t mzTolerance;
    types::ppm_t ppmTolerance;
    MzSearchTolerance();
};

std::ostream& operator<<(std::ostream &out, MzSearchTolerance const &searchTolerance);

struct TheoreticalSpectrumOptions {
    bool H2OLoss;
    bool Nh3Loss;
    bool aIon;
    types::charge_t maxFragmentIonCharge;
    struct Fragmentation {
        bool intraSequenceFragmentsUnderLinker;
        enums::FragmentationMethod method;
    };
    Fragmentation fragmentation;
    TheoreticalSpectrumOptions();
    bool operator==(TheoreticalSpectrumOptions const &rhs) const;
};

std::ostream& operator<<(std::ostream &out, TheoreticalSpectrumOptions const &tSpecOptions);

struct XCorrelationOptions {
    types::mz_t binStepSize;
    bool binSumIntensities;
    types::mz_bin_t halfWindow;
    XCorrelationOptions();
};

struct ScoringOptions {
    types::intensity_store_t xcorrCutoff;
};

std::ostream& operator<<(std::ostream &out, XCorrelationOptions const &xCorrelationOptions);

struct AnalysisOptions {
    MzSearchTolerance precursorSearch;
    TheoreticalSpectrumOptions theoreticalSpectrum;
    XCorrelationOptions xCorrelation;
    MzSearchTolerance spSearch;
    ScoringOptions scoringOptions;
    AnalysisOptions();
};

std::ostream& operator<<(std::ostream &out, AnalysisOptions const &aOptions);

} /* namespace apollo */

#endif /* apollo_optiontypes_hpp_ */

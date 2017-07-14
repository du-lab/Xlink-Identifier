/**
 * @file    optionsreader.cpp
 * @brief   A simple interface to read the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/08
 * @copyright 2012
 */


#include <memory>
#include <iostream>

#include <boost/log/trivial.hpp>

#include "types.hpp"
#include "units.hpp"
#include "exceptions.hpp"

#include "../core/stdmass.hpp"

#include "optionsreader.hpp"
#include "../core/regexdigest.hpp"
#include "../core/linkers.hpp"
#include "../core/residuecalc.hpp"

namespace apollo {

using Json::Value;
using types::io_string_t;

io_string_t const invalidStr("invalid_empty");

bool isVaid(io_string_t const &str) {
    return (str != invalidStr);
}

JobOptions read_JobOptions(Value const &job) {
    JobOptions jOptions;

    io_string_t const defaultId = "results";
    io_string_t const defaultOwner = "xiuxia@uncc.edu";

    jOptions.id = job.get("id", defaultId).asString();
    jOptions.owner = job.get("owner", defaultOwner).asString();

    return jOptions;
}


DigestOptions read_DigestOptions(Value const &value) {
    DigestOptions dOptions;

    io_string_t const defaultTrypticity("full");
    io_string_t trypticity = value.get("trypticity", defaultTrypticity).asString();


    if(trypticity == "full") {
        dOptions.digestType = enums::Digest::Full;
    } else if (trypticity == "partial") {
        dOptions.digestType = enums::Digest::Partial;
    } else if (trypticity == "none") {
        dOptions.digestType = enums::Digest::None;
    } else {
        throw boost::enable_error_info(std::range_error("Invalid Trypticity: " + trypticity))
                << boost::errinfo_api_function("read_DigestOptions");

    }

    io_string_t const defaultProtease("trypsin");
    dOptions.digestName = value.get("protease", defaultProtease).asString();
    RegexMap::const_iterator dMapIt = DigestRegexMap.find(dOptions.digestName);
    if (dMapIt != DigestRegexMap.end()) {
        dOptions.digestRegex = dMapIt->second;
    } else {
        throw boost::enable_error_info(std::range_error("Invalid Digest: " + dOptions.digestName))
                << boost::errinfo_api_function("read_DigestOptions");
    }

    int const defaultMinLength = 6;
    int const defaultMaxLength = 30;
    int const defaultMaxNmc = 3;

    validation::DigestTolerance::size_type minLength = value.get("minLength", defaultMinLength).asInt();
    validation::DigestTolerance::size_type maxLength = value.get("maxLength", defaultMaxLength).asInt() + 1;
    validation::DigestTolerance::size_type maxNmc = value.get("maxNmc", defaultMaxNmc).asInt() + 1;

    dOptions.digestTolerance = validation::DigestTolerance(minLength, maxLength, maxNmc);
    return dOptions;
}



ResidueMass::value_type read_ResidueMassPair(Value const &value) {
    using types::dalton_t;
    using units::dalton_mass;

    ResidueMass::key_type residue = value.get("residue", "_").asString()[0];
    ResidueMass::mapped_type mass = value.get("mass", 0.0f).asFloat() * dalton_mass;

    return ResidueMass::value_type(residue, mass);
}


ResidueMass::value_type read_ModMassPair(Value const &value) {
    using types::dalton_t;
    using units::dalton_mass;

    ResidueMass::key_type mod = value.get("mod", "_").asString()[0];
    ResidueMass::mapped_type mass = value.get("mass", 0.0f).asFloat() * dalton_mass;

    return ResidueMass::value_type(mod, mass);
}


ResidueMod::value_type read_ResidueModPair(Value const &value) {
    ResidueMod::key_type residue =
            value.get("residue", "_").asString()[0];
    io_string_t modStr = value.get("mod", "").asString();
    ResidueMod::mapped_type mods;
    mods.insert(modStr.begin(), modStr.end());

    return ResidueMod::value_type(residue, mods);
}

ResidueMass read_stdMass(Value const &value) {
    ResidueMass stdMass;
    using stdmass::residue::MonoisotopicMap_da;
    using stdmass::residue::AvgMap_da;

    io_string_t const defaultStdType = "monoisotopic";

    io_string_t stdType = value.get("type", defaultStdType).asString();
    if (stdType == "monoisotopic") {
       stdMass = MonoisotopicMap_da;
    } else if (stdType == "average") {
        stdMass = AvgMap_da;
    } else {
        throw boost::enable_error_info(std::range_error("Invalid Mass Type: " + stdType))
                << boost::errinfo_api_function("read_stdMass");
    }

    Value const additional = value["additional"];
    for(int i = 0; i < additional.size(); ++i) {
        stdMass.insert(read_ResidueMassPair(additional[i]));
    }

    return stdMass;
}


ResidueMod read_ResidueMod(Value const &value) {
    ResidueMod rMod;
    for (int i = 0; i < value.size(); ++i) {
        rMod.insert(read_ResidueModPair(value[i]));
    }
    return rMod;
}

ResidueMass read_ModMass(Value const &value) {
    ResidueMass rMass;
    for (int i = 0; i < value.size(); ++i) {
        rMass.insert(read_ModMassPair(value[i]));
    }
    return rMass;
}

SequenceOptions read_SequenceOptions(Value const &value) {
    SequenceOptions sOptions;

    sOptions.id = value.get("id", "std").asString();
    sOptions.reverse = value.get("reverse", false).asBool();
    sOptions.stdResidueMass = read_stdMass(value["stdMass"]);

    Value const modifications = value["modifications"];
    Value const staticMods = modifications["static"];
    sOptions.staticMods = read_ResidueMod(staticMods["residueMod"]);
    sOptions.iStaticMods = fn::invertResidueMod(sOptions.staticMods);
    sOptions.staticModMasses = read_ModMass(staticMods["modMass"]);
    Value const dynamicMods = modifications["dynamic"];
    sOptions.dynamicMods = read_ResidueMod(dynamicMods["residueMod"]);
    sOptions.iDynamicMods = fn::invertResidueMod(sOptions.dynamicMods);
    sOptions.dynamicModMasses = read_ModMass(dynamicMods["modMass"]);
    return sOptions;
}

SequenceOptionsMap read_SequenceOptionsMap(Value const &value) {
    SequenceOptionsMap sOptionsMap;
    Value const sequences = value["sequences"];
    for(int i = 0; i < sequences.size(); ++i) {
        SequenceOptions sOptions = read_SequenceOptions((sequences[i]));
        sOptionsMap.emplace(sOptions.id, sOptions);
    }
    return sOptionsMap;
}

ReactionGroup read_ReactionGroup(Value const &value) {
    using types::sequence_string_t;
    sequence_string_t residues = value.get("residues", "").asString();
    bool bindsToNh2Term = value.get("bindsToNh2Term", false).asBool();
    bool bindsToCTerm = value.get("bindsToCTerm", false).asBool();
    return ReactionGroup(residues.begin(), residues.end(), 
        bindsToNh2Term, bindsToCTerm);
}

ReactionGroup::vec read_ReactionGroups(Value const &value) {
    ReactionGroup::vec groupVec;
    for (int i = 0; i < value.size(); ++i) {
        groupVec.emplace_back(read_ReactionGroup(value[i]));
    }
    return groupVec;
}

Linker::shp read_Linker(Value const &value) {
    using types::io_string_t;
    using types::residue_t;
    using types::mass_store_t;
    using units::dalton_mass;
    using std::make_shared;

    Linker::shp linker;

    mass_store_t const defaultMass = -0.1f;

    if(!value.get("custom", false).asBool()) {
        linker = LinkersMap.at(value.get("name", "default").asString());
    } else {
        io_string_t name = value.get("name", "default").asString();
        residue_t symbol = value.get("symbol", "~").asString()[0];
        mass_store_t interMass = value.get("interMass", defaultMass).asFloat();
        bool canInterlink = (interMass == defaultMass) ? false : true;
        mass_store_t intraMass = value.get("intraMass", defaultMass).asFloat();
        bool canIntralink = (intraMass == defaultMass) ? false : true;
        mass_store_t deadendMass = value.get("deadendMass", defaultMass).asFloat();
        bool canDeadend = (deadendMass == defaultMass) ? false : true;
        ReactionGroup::vec groupVec = read_ReactionGroups(value["reactionGroups"]);
        ReactionGroup group1;
        ReactionGroup group2;
        if ((groupVec.size() > 2) || (groupVec.size() < 1)) {
           BOOST_LOG_TRIVIAL(error) << "Invalid Reaction Group Count: " << groupVec.size();
        } else if (groupVec.size() == 1) {
            group1 = groupVec[0];
            group2 = groupVec[0];
        } else {
            group1 = groupVec[0];
            group2 = groupVec[1];
        }

        linker = make_shared<Linker>(name,
            symbol,
            canInterlink, interMass * dalton_mass,
            canIntralink, intraMass * dalton_mass,
            canDeadend, deadendMass * dalton_mass,
            group1, group2);
    }

    return linker;
}

Linker::shp_vec read_Linkers(Value const &value) {
    Linker::shp_vec lVec;
    for (int i = 0; i < value.size(); ++i) {
        lVec.emplace_back(read_Linker(value[i]));
    }
    return lVec;
}

LinkerOptions read_LinkerOptions(Value const &value) {
    LinkerOptions lOptions;
        lOptions.linkers = read_Linkers(value["linkers"]);
    return lOptions;
}

MzSearchTolerance read_MzSearchTolerance(Value const &value) {

    using types::mass_store_t;
    using types::mz_t;
    using types::ppm_t;
    using units::mass_charge;

    io_string_t const defaultType = "ppm";
    mass_store_t const defaultPpmTolerance = 250;
    mass_store_t const defaultMzTolerance = 0.6f;

    MzSearchTolerance searchTolerance;

    io_string_t type = value.get("type", defaultType).asString();
    if(type == "mz") {
        searchTolerance.type = enums::Tolerance::Mz;
        searchTolerance.mzTolerance =
                mz_t(value.get("tolerance", defaultMzTolerance).asFloat() * mass_charge);
    } else if (type == "ppm") {
        searchTolerance.type = enums::Tolerance::Ppm;
        searchTolerance.ppmTolerance =
                ppm_t(value.get("tolerance", defaultPpmTolerance).asFloat());
    } else {
        throw boost::enable_error_info(std::range_error("Invalid Tolerance Type: " + type))
                << boost::errinfo_api_function("read_MzSearchTolerance");
    }
    
    return searchTolerance;
}


TheoreticalSpectrumOptions::Fragmentation read_FragmentationOptions(Value const &value) {
    TheoreticalSpectrumOptions::Fragmentation fOptions;
    io_string_t const defaultMethod("cid");

    fOptions.intraSequenceFragmentsUnderLinker =
            value.get("intraSequenceFragmentsUnderLinker", false).asBool();

    io_string_t method = value.get("method", defaultMethod).asString();
    if(method == "cid") {
        fOptions.method = enums::FragmentationMethod::Cid;
    } else if (method == "etd") {
        fOptions.method = enums::FragmentationMethod::Etd;
    } else {
        throw boost::enable_error_info(std::range_error("Invalid Fragmentation Method: " + method))
                << boost::errinfo_api_function("read_FragmentationOptions");
    }
    return fOptions;
}

TheoreticalSpectrumOptions read_TheoreticalSpectrumOptions(Value const &value) {
    using types::charge_t;
    using units::charge;
    TheoreticalSpectrumOptions tSpecOptions;
    tSpecOptions.H2OLoss = value.get("H20_loss", false).asBool();
    tSpecOptions.Nh3Loss = value.get("Nh3_loss", false).asBool();
    tSpecOptions.aIon = value.get("a-ion", false).asBool();
    tSpecOptions.maxFragmentIonCharge = value.get("maxFragmentIonCharge", 6).asInt() * charge;
    tSpecOptions.fragmentation = read_FragmentationOptions(value["fragmentation"]);
    return tSpecOptions;
}

ScoringOptions read_ScoringOptions(Value const &value) {
    ScoringOptions sOptions;
    types::intensity_store_t const defaultXcorrCutoff = 0.0f;
    sOptions.xcorrCutoff = value.get("xcorrCutoff", defaultXcorrCutoff).asFloat();
    return sOptions;
}

AnalysisOptions read_AnalysisOptions(Value const &value) {
    AnalysisOptions aOptions;

    aOptions.precursorSearch =
            read_MzSearchTolerance(value["precursorSearch"]);
    aOptions.theoreticalSpectrum =
            read_TheoreticalSpectrumOptions(value["theoreticalSpectrum"]);
    aOptions.spSearch = read_MzSearchTolerance(value["ionSearch"]);
    aOptions.scoringOptions = read_ScoringOptions(value["scoring"]);

    return aOptions;
}

} /* namespace apollo */

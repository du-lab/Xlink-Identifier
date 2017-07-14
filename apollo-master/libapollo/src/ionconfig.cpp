/**
 * @file    ionconfig.cpp
 * @brief   Various functions for ionconfig operations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/20
 * @copyright 2012
 */

#include <functional>

#include <boost/functional/hash.hpp>

#include "../core/refutil.hpp"
#include "ionconfig.hpp"

namespace apollo {

IonConfig::IonConfig() {}

bool IonConfig::operator==(IonConfig const &rhs) const {
    if ( (isLeftIon == rhs.isLeftIon) &&
        (fragmentedSequence == rhs.fragmentedSequence) &&
        (linkerConfig == rhs.linkerConfig) &&
        (alphaMotif == rhs.alphaMotif) &&
        (betaMotif == rhs.betaMotif)) {
        return true;
    } else {
        return false;
    }
}

std::size_t hash_value(IonConfig const &iConfig) {
    using enums::LinkerConfig;
    std::size_t seed = 0;
    boost::hash_combine(seed, iConfig.isLeftIon);
    boost::hash_combine(seed, int(iConfig.fragmentedSequence));
    boost::hash_combine(seed, iConfig.fragmentLocation);
    boost::hash_combine(seed, int(iConfig.linkerConfig));
    boost::hash_combine(seed, iConfig.alphaMotif);
    if (iConfig.linkerConfig == LinkerConfig::Interlinked) {
        boost::hash_combine(seed, iConfig.betaMotif);
    }
    return seed;
}

std::ostream& operator<<(std::ostream &out, IonConfig const &iConfig) {
    using enums::LinkerConfig;
    out << "frag seq: " << iConfig.fragmentedSequence << ", " <<
        iConfig.linkerConfig << ", " <<
        "alpha: (" << iConfig.alphaMotif << ")";
    if (iConfig.linkerConfig == LinkerConfig::Interlinked) {
        out << ", beta: (" << iConfig.betaMotif << ")";
    }
    return out;
}

IonConfig const default_IonConfig;

IonSpec::IonSpec() :
    ionConfig_cref(default_IonConfig) {}

IonSpec::IonSpec(enums::Ion ion, IonModification mod, IonConfig const &ionConfig) :
     ion(ion),
     mod(mod),
     ionConfig_cref(ionConfig) {}

bool IonSpec::operator==(IonSpec const &rhs) const {
    if ((ion == rhs.ion) &&
        (mod == rhs.mod) &&
        (ionConfig_cref == rhs.ionConfig_cref)) {
        return true;
    } else {
        return false;
    }
}

std::ostream& operator<<(std::ostream &out, IonSpec const &iSpec) {
    using enums::Ion;
    using enums::IonMod;

    out << "ion: " << iSpec.ion;
    if(iSpec.mod.any()) {
       out <<  ", " << "mods:{";
        if (iSpec.mod[IonMod::Nh3Loss]) {
            out << IonMod::Nh3Loss << ", ";
        }
        if (iSpec.mod[IonMod::H2OLoss]) {
            out << IonMod::H2OLoss << ", ";
        }
        if (iSpec.mod[IonMod::CoLoss]) {
            out << IonMod::CoLoss << ", ";
        }
        out << "}";
    }
    out << ", {" << iSpec.ionConfig_cref << "}";
    return out;
}


} /* namespace apollo */

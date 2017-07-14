/**
 * @file    ionconfig.hpp
 * @brief   Represents an ion configuration
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#ifndef apollo_ionconfig_hpp_
#define apollo_ionconfig_hpp_

#include <functional>
#include <iostream>

#include "enums.hpp"
#include "mz.hpp"
#include "sequenceinterface.hpp"
#include "sequenceconfig.hpp"
#include "ionmodification.hpp"

namespace apollo {

class IonConfig {
public:
    bool isLeftIon;
    enums::FragmentedSequence fragmentedSequence;
    SequenceI::size_type fragmentLocation;
    enums::LinkerConfig linkerConfig;
    SequenceMotif alphaMotif;
    SequenceMotif betaMotif;
    IonConfig();
    bool operator==(IonConfig const &rhs) const;
    typedef std::reference_wrapper<IonConfig const> cref;
    ~IonConfig() {}
};

std::size_t hash_value(IonConfig const &iConfig);



std::ostream& operator<<(std::ostream &out, IonConfig const &iConfig);

class IonSpec {
public:
    enums::Ion ion;
    IonModification mod;
    IonConfig::cref ionConfig_cref;
    IonSpec();
    IonSpec(enums::Ion ion, IonModification mod, IonConfig const &ionConfig);
    bool operator==(IonSpec const &rhs) const;
    ~IonSpec() {}
};

std::ostream& operator<<(std::ostream &out, IonSpec const &iSpec);

} /* namespace apollo */

namespace std {

template <>
class hash<apollo::IonConfig> {
public:
    size_t operator()(apollo::IonConfig const &ionConfig) const {
        return apollo::hash_value(ionConfig);
    }
};
} /* namespace std */

#endif /* apollo_ionconfig_hpp_ */

/**
 * @file    linkioncfggen.cpp
 * @brief   Generator for linked ion configs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#include "linkioncfggen.hpp"

namespace apollo {

LinkIonCfgGen::LinkIonCfgGen(SequenceMotif const &sMotif,
    LinkLoc const linkLoc,
    LocResidueMap const &statLocMap,
    LocResidueMap const &dynLocMap,
    SequenceOptions const &sOptions) : 
     _super(),
     _linkLoc(linkLoc) {

    _ionCfgIter = make_geniter<UlinkIonCfgGen>(sMotif, statLocMap, dynLocMap, sOptions);
}

LinkIonCfgGen::LinkIonCfgGen(LinkIonCfgGen const &rhs) : 
_super(rhs),
_ionCfgIter(rhs._ionCfgIter),
_linkLoc(rhs._linkLoc) {}

LinkIonCfgGen::LinkIonCfgGen(LinkIonCfgGen &&rhs) :
_super(std::forward<_super>(rhs)),
_ionCfgIter(std::move(rhs._ionCfgIter)),
_linkLoc(rhs._linkLoc) {}

LinkIonCfgGen& LinkIonCfgGen::operator=(LinkIonCfgGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _ionCfgIter = rhs._ionCfgIter;
        _linkLoc = rhs._linkLoc;
    }
    return *this;
}

LinkIonCfgGen& LinkIonCfgGen::operator=(LinkIonCfgGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _ionCfgIter = std::move(rhs._ionCfgIter);
        _linkLoc = rhs._linkLoc;
    }
    return *this;
}

bool LinkIonCfgGen::operator()(value_type &rv) {
    UlinkIonCfgIter  const ionCfgEnd;

    $gen_start;

    for(; _ionCfgIter != ionCfgEnd; ++_ionCfgIter) {
        $yield(rv);
    }

    $gen_stop;
}

void LinkIonCfgGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool LinkIonCfgGen::operator==(LinkIonCfgGen const &rhs) const {
    if (_super::operator==(rhs) &&
        (_ionCfgIter == rhs._ionCfgIter) &&
        (_linkLoc == rhs._linkLoc)) {

        return true;
    } else {
        return false;
    }
}

LinkIonCfgGen::value_type LinkIonCfgGen::genReturn() const {

    using enums::LinkerConfig;

    value_type ionConfig = *_ionCfgIter;
    if (!_linkLoc.isUnlinked()) {
        if (_linkLoc.isNh2TerminusLinked() && ionConfig.isLeftIon) {
            ionConfig.linkerConfig = LinkerConfig::Deadend;

        } else if (_linkLoc.isCTerminusLinked() && !ionConfig.isLeftIon) {
            ionConfig.linkerConfig = LinkerConfig::Deadend;

        } else {
            if(ionConfig.isLeftIon && (_linkLoc.loc() < ionConfig.fragmentLocation)) {
                ionConfig.linkerConfig = LinkerConfig::Deadend;
            } else if(!ionConfig.isLeftIon && (_linkLoc.loc() >= ionConfig.fragmentLocation)) {
                ionConfig.linkerConfig = LinkerConfig::Deadend;
            }
        }
    }
    return ionConfig;
}

} /* namespace apollo */
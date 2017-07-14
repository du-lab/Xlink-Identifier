/**
 * @file    linker.cpp
 * @brief   Theoretical linker
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#include "stdmass.hpp"
#include "linker.hpp"

namespace apollo {

using types::dalton_t;

using types::io_string_t;
using types::residue_t;

Linker::Linker(io_string_t name,
    types::residue_t symbol,
    bool canInterlink, dalton_t interlinkedMass,
    bool canIntralink, dalton_t intralinkedMass,
    bool canDeadend, dalton_t deadendMass,
    ReactionGroup group1, ReactionGroup group2) :
    _name(name), _symbol(symbol),
    _canInterlink(canInterlink), _interlinkedMass(interlinkedMass),
    _canIntralink(canIntralink), _intralinkedMass(intralinkedMass),
    _canDeadend(canDeadend), _deadendMass(deadendMass),
    _group1(group1), _group2(group2),
    _intraGroup(_group1, _group2) {}

io_string_t const& Linker::name() const {
    return _name;
}

residue_t Linker::symbol() const {
    return _symbol;
}

bool Linker::canInterlink() const {
    return _canInterlink;
}

dalton_t Linker::interlinkedMass() const {
    return _interlinkedMass;
}

bool Linker::canIntralink() const {
    return _canIntralink;
}

dalton_t Linker::intralinkedMass() const {
    return _intralinkedMass;
}

bool Linker::canDeadend() const {
    return _canDeadend;
}

dalton_t Linker::deadendMass() const {
    return _deadendMass;
}

ReactionGroup const& Linker::group1() const {
    return _group1;
}

ReactionGroup const& Linker::group2() const {
    return _group2;
}

ReactionGroup const& Linker::intraGroup() const {
    return _intraGroup;
}

std::ostream& operator<<(std::ostream &out, Linker const &rhs) {
    out << "Name: " << rhs.name() <<
           ", symbol: " << rhs.symbol();
    if (rhs.canInterlink()) { 
        out << ", " << "inter: " << rhs.interlinkedMass();
    }
    if (rhs.canIntralink()) {
        out << ", " << "intra: " << rhs.intralinkedMass();
    }
    if (rhs.canDeadend()) {
        out << ", " << "dead: " << rhs.deadendMass();
    }
    out << ", " << "rGroup1: " << rhs.group1() <<
        ", " << "rGroup2: " << rhs.group2() <<
        ", " << "intraGroup: " << rhs.intraGroup();
    return out;
}

} /* namespace apollo */

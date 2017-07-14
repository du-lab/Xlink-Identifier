/**
 * @file    linkloc.cpp
 * @brief   A representation of the linker's location
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/01/07
 * @copyright 2012
 */

#include "linkloc.hpp"

namespace apollo {
// Last, second to last, and third to last values in std::size_t, respectively

LinkLoc::value_type const LinkLoc::Nh2Loc( (LinkLoc::value_type) -1);

LinkLoc::value_type const LinkLoc::CLoc( (LinkLoc::value_type) -2);

LinkLoc::value_type const LinkLoc::UnlinkedLoc( (LinkLoc::value_type) -3);

LinkLoc::LinkLoc() :
    _loc(UnlinkedLoc) {}

LinkLoc::LinkLoc(LinkLoc const &rhs) : 
    _loc(rhs._loc) {}

LinkLoc LinkLoc::operator=(LinkLoc const &rhs) {
    if (this != &rhs) {
        _loc = rhs._loc;
    }
    return *this;
}

bool LinkLoc::isUnlinked() const {
    if (_loc == UnlinkedLoc) {
        return true;
    } else {
        return false;
    }
}

bool LinkLoc::isTermLinked() const {
    if (_loc > UnlinkedLoc) {
        return true;
    } else {
        return false;
    }
}

bool LinkLoc::isNh2TerminusLinked() const {
    if (_loc == Nh2Loc) {
        return true;
    } else {
        return false;
    }
}

bool LinkLoc::isCTerminusLinked() const {
    if (_loc == CLoc) {
        return true;
    } else {
        return false;
    }
}

bool LinkLoc::operator==(LinkLoc const &rhs) const {
    if (_loc == rhs._loc) {
        return true;
    } else {
        return false;
    }
}

LinkLoc::value_type LinkLoc::loc() const {
    return _loc;
}

std::ostream& operator<<(std::ostream &out, LinkLoc const &rhs) {
    if (rhs.isUnlinked()) {
        out << "Unlinked";
    } else if (rhs.isTermLinked()) {
        if (rhs.isNh2TerminusLinked()) {
            out << "NH2 Terminus";
        } else {
            out << "C Terminus";
        }
    } else {
        out << rhs.loc();
    }
    return out;
}

LinkLoc LinkLoc::Unlinked() {
    return LinkLoc();
}

LinkLoc LinkLoc::OnNh2Terminus() {
    return LinkLoc(Nh2Loc);
}

LinkLoc LinkLoc::OnCTerminus() {
    return LinkLoc(CLoc);
}

LinkLoc LinkLoc::OnPosition(value_type pos) {
    return LinkLoc(pos);
}

LinkLoc::LinkLoc(value_type pos) :
    _loc(pos) {}

}
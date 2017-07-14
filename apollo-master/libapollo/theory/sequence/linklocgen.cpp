/**
 * @file    linklocgen.cpp
 * @brief   A generator to a linker's locations on a sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/07
 * @copyright 2013
 */
#include <iterator>
#include <memory>

#include "linklocgen.hpp"

namespace apollo {

LinkLocGen::LinkLocGen(Linker::shp linkerShp, 
    SequenceI::shp seqShp,
    enums::LinkerConfig linkerConfig) :
    _linkerShp(linkerShp),
    _seqShp(seqShp),
    _linkerConfig(linkerConfig),
    _seqPos(_seqShp->begin()),
    _state(LinkState::Unlinked) {}

LinkLocGen::LinkLocGen(LinkLocGen const &rhs) :
    _super(rhs),
    _linkerShp(rhs._linkerShp),
    _seqShp(rhs._seqShp),
    _linkerConfig(rhs._linkerConfig),
    _seqPos(rhs._seqPos),
    _state(rhs._state) {}

LinkLocGen::LinkLocGen(LinkLocGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _linkerShp(std::move(rhs._linkerShp)),
    _seqShp(std::move(rhs._seqShp)),
    _linkerConfig(rhs._linkerConfig),
    _seqPos(rhs._seqPos),
    _state(rhs._state) {}

LinkLocGen LinkLocGen::operator=(LinkLocGen const &rhs) {
    if (this != &rhs) {
        _linkerShp = rhs._linkerShp;
        _seqShp = rhs._seqShp;
        _linkerConfig = rhs._linkerConfig;
        _seqPos = rhs._seqPos;
        _state = rhs._state;
    }
    return *this;
}

LinkLocGen LinkLocGen::operator=(LinkLocGen &&rhs) {
    if (this != &rhs) {
        _linkerShp = std::move(rhs._linkerShp);
        _seqShp = std::move(rhs._seqShp);
        _linkerConfig = rhs._linkerConfig;
        _seqPos = rhs._seqPos;
        _state = rhs._state;
    }
    return *this;
}

bool LinkLocGen::operator()(value_type &rv) {
    using enums::LinkerConfig;
    $gen_start;
    if (_linkerConfig == LinkerConfig::Unlinked) {
        _state = LinkState::Unlinked;
        $yield(rv);
    } else if (_linkerConfig == LinkerConfig::Intralinked) {
        if (_linkerShp->intraGroup().canBindToNh2Terminus(*_seqShp)) {
            _state = LinkState::Nh2Term;
            $yield(rv);
        }
        for(; _seqPos != _seqShp->end(); ++_seqPos) {
            _state = LinkState::Loc;
            if (_linkerShp->intraGroup()(*_seqPos)) {
                $yield(rv);
            }
        }
        if (_linkerShp->intraGroup().canBindToCTerminus(*_seqShp)) {
            _state = LinkState::CTerm;
            $yield(rv);
        }
    } else {
        if (_linkerShp->group1().canBindToNh2Terminus(*_seqShp) ||
            _linkerShp->group2().canBindToNh2Terminus(*_seqShp) ) {
            _state = LinkState::Nh2Term;
            $yield(rv);
        }
        for(; _seqPos != _seqShp->end(); ++_seqPos) {
            _state = LinkState::Loc;
            if (_linkerShp->group1()(*_seqPos) || 
                _linkerShp->group2()(*_seqPos)) {
                $yield(rv);
            }
        }
        if (_linkerShp->group1().canBindToCTerminus(*_seqShp) ||
            _linkerShp->group2().canBindToCTerminus(*_seqShp) ) {
            _state = LinkState::CTerm;
            $yield(rv);
        }
    }
    $gen_stop;
}

void LinkLocGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool LinkLocGen::operator==(LinkLocGen const &rhs) const {
    if ((_super::operator==(rhs)) &&
        (_linkerShp == rhs._linkerShp) &&
        (_seqShp == rhs._seqShp) &&
        (_linkerConfig == rhs._linkerConfig) &&
        (_seqPos == rhs._seqPos) &&
        (_state == rhs._state)) {

        return true;
    } else {
        return false;
    }
}

LinkLocGen::value_type LinkLocGen::genReturn() const {
    using std::distance;

    switch(_state) {
    case LinkState::Nh2Term:
        return LinkLoc::OnNh2Terminus();
        break;
    case LinkState::CTerm:
        return LinkLoc::OnCTerminus();
        break;
    case LinkState::Loc:
        return LinkLoc::OnPosition(distance(_seqShp->begin(), _seqPos));
        break;
    case LinkState::Unlinked:
    default:
        return LinkLoc::Unlinked();
        break;
    }
}

} /* namespace apollo */

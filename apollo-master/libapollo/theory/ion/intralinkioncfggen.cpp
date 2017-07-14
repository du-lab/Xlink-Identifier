#include "intralinkioncfggen.hpp"

#include <assert.h>

namespace apollo {

IntralinkIonCfgGen::IntralinkIonCfgGen(SequenceMotif const &seqMotif,
    LinkLoc seqLinkLoc1,
    LinkLoc seqLinkLoc2,
    LocResidueMap const &seqStatLocMap,
    LocResidueMap const &seqDynLocMap,
    SequenceOptions const &sOptions) :
    _seqLinkLoc1(seqLinkLoc1),
    _seqLinkLoc2(seqLinkLoc2)
{

    _seqIonCfgIter =
            make_geniter<LinkIonCfgGen>(seqMotif, seqLinkLoc1, seqStatLocMap, seqDynLocMap, sOptions);
}

IntralinkIonCfgGen::IntralinkIonCfgGen(IntralinkIonCfgGen const &rhs) :
        _super(rhs),
        _seqLinkLoc1(rhs._seqLinkLoc1),
        _seqLinkLoc2(rhs._seqLinkLoc2),
        _seqIonCfgIter(rhs._seqIonCfgIter),
        _leftIon(rhs._leftIon),
        _rightIon(rhs._rightIon),
        _returnLIon(rhs._returnLIon){

}

IntralinkIonCfgGen::IntralinkIonCfgGen(IntralinkIonCfgGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _seqLinkLoc1(rhs._seqLinkLoc1),
    _seqLinkLoc2(rhs._seqLinkLoc2),
    _seqIonCfgIter(std::move(rhs._seqIonCfgIter)),
    _leftIon(rhs._leftIon),
    _rightIon(rhs._rightIon),
    _returnLIon(rhs._returnLIon){

}

IntralinkIonCfgGen& IntralinkIonCfgGen::operator=(IntralinkIonCfgGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _seqLinkLoc1 = rhs._seqLinkLoc1;
        _seqLinkLoc2 = rhs._seqLinkLoc2;
        _seqIonCfgIter = rhs._seqIonCfgIter;
        _leftIon = rhs._leftIon;
        _rightIon = rhs._rightIon;
        _returnLIon = rhs._returnLIon;
    }
    return *this;
}

IntralinkIonCfgGen& IntralinkIonCfgGen::operator=(IntralinkIonCfgGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _seqLinkLoc1 = rhs._seqLinkLoc1;
        _seqLinkLoc2 = rhs._seqLinkLoc2;
        _seqIonCfgIter = std::move(rhs._seqIonCfgIter);
        _leftIon = rhs._leftIon;
        _rightIon = rhs._rightIon;
        _returnLIon = rhs._returnLIon;
    }
    return *this;
}

bool ionContainsLink(IonConfig const &ion, LinkLoc const linkLoc) {
    // Terminus linking checks
    if (linkLoc.isTermLinked()) {
        if ((linkLoc.isNh2TerminusLinked() && ion.isLeftIon) ||
                (linkLoc.isCTerminusLinked() && !ion.isLeftIon)) {
            return true;
        } else {
            return false;
        }
    }

    // We know the locations aren't term linked

    if (ion.isLeftIon) {
        if (linkLoc.loc() < ion.fragmentLocation) {
            return true;
        }
    }
    if (!ion.isLeftIon) {
        if (linkLoc.loc() >= ion.fragmentLocation) {
            return true;
        }
    }
    return false;
}

bool ionContainsLinks(IonConfig const &ion, LinkLoc const linkLoc1, LinkLoc const linkLoc2) {
    return (ionContainsLink(ion, linkLoc1) && ionContainsLink(ion, linkLoc2));
}



bool IntralinkIonCfgGen::operator()(value_type &rv) {
    using std::get;
    using enums::LinkerConfig;
    LinkIonCfgIter const linkIonCfgEnd;

    $gen_start;
    // We count on there always being a left and a right ion per fragmentation
    for(; _seqIonCfgIter != linkIonCfgEnd; ++_seqIonCfgIter) {

        // Lots of asserts here. We need to make sure we know the states are correct

        _leftIon = *_seqIonCfgIter;
        assert(_leftIon.isLeftIon == true);

        ++_seqIonCfgIter;

        assert(_seqIonCfgIter != linkIonCfgEnd);

        _rightIon = *_seqIonCfgIter;
        assert(_rightIon.isLeftIon == false);

        assert(_leftIon.fragmentLocation == _rightIon.fragmentLocation);


        // Only return the ions if one or the other contains both link locations
        if(ionContainsLinks(_leftIon, _seqLinkLoc1, _seqLinkLoc2) ||
                ionContainsLinks(_rightIon, _seqLinkLoc1, _seqLinkLoc2)) {
            _returnLIon = true;
            $yield(rv);
            _returnLIon = false;
            $yield(rv);
        }


    }
    $gen_stop;

}

void IntralinkIonCfgGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool IntralinkIonCfgGen::operator==(IntralinkIonCfgGen const &rhs) const {
    if (
        _super::operator ==(rhs) &&
            (_seqLinkLoc1 == rhs._seqLinkLoc1) &&
            (_seqLinkLoc2 == rhs._seqLinkLoc2) &&
            (_seqIonCfgIter == rhs._seqIonCfgIter) &&
            (_leftIon == rhs._leftIon) &&
            (_rightIon == rhs._rightIon)
            ) {
        return true;
    } else {
        return false;
    }

}

IntralinkIonCfgGen::value_type IntralinkIonCfgGen::genReturn() const {

    if (_returnLIon) {
        return _leftIon;
    } else {
        return _rightIon;
    }
}

} /* namespace apollo */

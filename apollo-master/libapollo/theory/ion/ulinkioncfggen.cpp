/**
 * @file    ulinkioncfggen.cpp
 * @brief   Generator for unlinked ion configs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#include <utility>

#include "mz.hpp"
#include "../../core/residuecalc.hpp"
#include "../../core/sequencepart.hpp"
#include "../../core/stdmass.hpp"
#include "ulinkioncfggen.hpp"

namespace apollo {

namespace d {

SequenceMotif const seqMotif;

SequenceOptions const sOptions;

LocResidueMap const emptyLocMap;
} /* namespace default */

UlinkIonCfgGen::UlinkIonCfgGen() :
    _super(),
    _sMotif_cref(d::seqMotif),
    _statLocMap_cref(d::emptyLocMap),
    _dynLocMap_cref(d::emptyLocMap),
    _sOptions_cref(d::sOptions) {}

UlinkIonCfgGen::UlinkIonCfgGen(SequenceMotif const &sMotif,
    LocResidueMap const &statLocMap,
    LocResidueMap const &dynLocMap,
    SequenceOptions const &sOptions) :
    _super(),
    _sMotif_cref(sMotif),
    _statLocMap_cref(statLocMap),
    _dynLocMap_cref(dynLocMap),
    _sOptions_cref(sOptions) {}

UlinkIonCfgGen::UlinkIonCfgGen(UlinkIonCfgGen const &rhs) :
    _super(rhs),
    _sMotif_cref(rhs._sMotif_cref),
    _statLocMap_cref(rhs._statLocMap_cref),
    _dynLocMap_cref(rhs._dynLocMap_cref),
    _sOptions_cref(rhs._sOptions_cref),
    _lIonShp(rhs._lIonShp),
    _lLength(rhs._lLength),
    _lStatMods(rhs._lStatMods),
    _lDynMods(rhs._lDynMods),
    _rIonShp(rhs._rIonShp),
    _rLength(rhs._rLength),
    _rStatMods(rhs._rStatMods),
    _rDynMods(rhs._rDynMods),
    _returnLIon(rhs._returnLIon) {}

UlinkIonCfgGen::UlinkIonCfgGen(UlinkIonCfgGen &&rhs):
    _super(std::forward<_super>(rhs)),
    _sMotif_cref(rhs._sMotif_cref),
    _statLocMap_cref(rhs._statLocMap_cref),
    _dynLocMap_cref(rhs._dynLocMap_cref),
    _sOptions_cref(rhs._sOptions_cref),
    _lIonShp(std::move(rhs._lIonShp)),
    _lLength(rhs._lLength),
    _lStatMods(std::move(rhs._lStatMods)),
    _lDynMods(std::move(rhs._lDynMods)),
    _rIonShp(std::move(rhs._rIonShp)),
    _rLength(rhs._rLength),
    _rStatMods(std::move(rhs._rStatMods)),
    _rDynMods(std::move(rhs._rDynMods)),
    _returnLIon(rhs._returnLIon) {}

UlinkIonCfgGen& UlinkIonCfgGen::operator=(UlinkIonCfgGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _sMotif_cref = rhs._sMotif_cref;
        _statLocMap_cref = rhs._statLocMap_cref;
        _dynLocMap_cref = rhs._dynLocMap_cref;
        _sOptions_cref = rhs._sOptions_cref;
        _lIonShp = rhs._lIonShp;
        _lLength = rhs._lLength;
        _lStatMods = rhs._lStatMods;
        _lDynMods = rhs._lDynMods;
        _rIonShp = rhs._rIonShp;
        _rLength = rhs._rLength;
        _rStatMods = rhs._rStatMods;
        _rDynMods = rhs._rDynMods;
        _returnLIon = rhs._returnLIon;
    }
    return *this;
}

UlinkIonCfgGen& UlinkIonCfgGen::operator=(UlinkIonCfgGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _sMotif_cref = rhs._sMotif_cref;
        _statLocMap_cref = rhs._statLocMap_cref;
        _dynLocMap_cref = rhs._dynLocMap_cref;
        _sOptions_cref = rhs._sOptions_cref;
        _lIonShp = std::move(rhs._lIonShp);
        _lLength = rhs._lLength;
        _lStatMods = std::move(rhs._lStatMods);
        _lDynMods = std::move(rhs._lDynMods);
        _rIonShp = std::move(rhs._rIonShp);
        _rLength = rhs._rLength;
        _rStatMods = std::move(rhs._rStatMods);
        _rDynMods = std::move(rhs._rDynMods);
        _returnLIon = rhs._returnLIon;
    }
    return *this;
}

bool UlinkIonCfgGen::operator()(value_type &rv) {
    using std::make_shared; 

    using fn::rCountToLoc;
    using fn::rCountFromLoc;

    $gen_start;
    for(_lLength = 1;
        _lLength < _sMotif_cref.get().first->length();
        _lLength++) {

        _lIonShp = make_shared<SequencePart>(_sMotif_cref.get().first, 0, _lLength);

        _rLength = _sMotif_cref.get().first->length() - _lLength;

        _rIonShp = make_shared<SequencePart>(_sMotif_cref.get().first, _lLength, 
            _rLength);

        _lStatMods = rCountToLoc(_statLocMap_cref, _lLength);
        _rStatMods = rCountFromLoc(_statLocMap_cref, _lLength);

        _lDynMods = rCountToLoc(_dynLocMap_cref, _lLength);
        _rDynMods = rCountFromLoc(_dynLocMap_cref, _lLength);

        _returnLIon = true;
        $yield(rv);

        _returnLIon = false;
        $yield(rv);
    }
    $gen_stop;
}

void UlinkIonCfgGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool UlinkIonCfgGen::operator==(UlinkIonCfgGen const &rhs) const {
    if ((_super::operator==(rhs)) &&
        (_sMotif_cref == rhs._sMotif_cref) &&
        (_statLocMap_cref == rhs._statLocMap_cref) &&
        (_dynLocMap_cref == rhs._dynLocMap_cref) &&
        (_sOptions_cref == rhs._sOptions_cref) &&
        (_lIonShp == rhs._lIonShp) &&
        (_lLength == rhs._lLength) &&
        (_lStatMods == rhs._lStatMods) &&
        (_lDynMods == rhs._lDynMods) &&
        (_rIonShp == rhs._rIonShp) &&
        (_rLength == rhs._rLength) &&
        (_rStatMods == rhs._rStatMods) &&
        (_rDynMods == rhs._rDynMods) &&
        (_returnLIon == rhs._returnLIon)) {
        return true;
    } else {
        return false;
    }
}

UlinkIonCfgGen::value_type UlinkIonCfgGen::genReturn() const {
    using std::get;
    using std::make_pair;
    using enums::FragmentedSequence;
    using enums::LinkerConfig;

    using fn::massFromSequence;
    using fn::massFromResidueCount;

    using stdmass::H2O_da;

    value_type ionConfig;

    SequenceI::shp ionShp;
    SequenceConfig ionSeqConfig;

    if (_returnLIon) {
        ionShp = _lIonShp;
        get<1>(ionSeqConfig) = _lStatMods;
        get<2>(ionSeqConfig) = _lDynMods;
    } else {
        ionShp = _rIonShp;
        get<1>(ionSeqConfig) = _rStatMods;
        get<2>(ionSeqConfig) = _rDynMods;
    }

    types::dalton_t ionMass = massFromSequence(*ionShp, _sOptions_cref.get().stdResidueMass);

    ionMass += massFromResidueCount(get<1>(ionSeqConfig), _sOptions_cref.get().staticModMasses);

    ionMass +=  massFromResidueCount(get<2>(ionSeqConfig), _sOptions_cref.get().dynamicModMasses);

    ionMass += H2O_da; // Ion is always considered hydralized

    get<0>(ionSeqConfig) = Mz::MhFromM(ionMass);

    ionConfig.isLeftIon = _returnLIon;
    ionConfig.fragmentedSequence = FragmentedSequence::Alpha;
    ionConfig.fragmentLocation = _lLength;
    ionConfig.linkerConfig = LinkerConfig::Unlinked;
    ionConfig.alphaMotif = make_pair(ionShp, ionSeqConfig);

    return ionConfig;
}
} /* namespace apollo */

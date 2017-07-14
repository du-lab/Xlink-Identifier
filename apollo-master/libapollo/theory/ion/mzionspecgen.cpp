/**
 * @file    mzionspecgen.cpp
 * @brief   Generator for ion specifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/31
 * @copyright 2012
 */

#include <algorithm>
#include <tuple>
#include <boost/log/trivial.hpp>

#include "../core/refutil.hpp"
#include "../core/stdcharge.hpp"
#include "../core/stdmass.hpp"
#include "mz.hpp"
#include "mzionspecgen.hpp"

namespace apollo {

types::sequence_string_t const Nh3_Loss_Str("RKQN");
ReactionGroup const MzIonSpecGen::Nh3_Loss(Nh3_Loss_Str.begin(), Nh3_Loss_Str.end());

types::sequence_string_t const H2O_Loss_Str("STED");
ReactionGroup const MzIonSpecGen::H2O_Loss(H2O_Loss_Str.begin(), H2O_Loss_Str.end());

IonModification Nh3LossOnly() {
    using enums::IonMod;
    IonModification nh3Loss;
    nh3Loss[IonMod::Nh3Loss] = true;
    return nh3Loss;
}


IonModification H2OLossOnly() {
    using enums::IonMod;
    IonModification h2OLoss;
    h2OLoss[IonMod::H2OLoss] = true;
    return h2OLoss;
}

IonModification CoLossOnly() {
    using enums::IonMod;
    IonModification cOLoss;
    cOLoss[IonMod::CoLoss] = true;
    return cOLoss;
}

bool containsBPhotoProbe(SequenceMotif const &motif) {
    using types::residue_t;
    for(SequenceI::const_iterator it = motif.first->begin();
        it != motif.first->end(); ++it) {
        if (*it == 'b') {
            return true;
        }
    }
    return false;
}

IonConfig const default_ionConfig;
TheoreticalSpectrumOptions const default_tSpecOptions;

types::charge_t const chargeOfTwo(2  * units::charge);
types::charge_t const chargeOfThree(3  * units::charge);
types::charge_t const chargeOfFour(4  * units::charge);


MzIonSpecGen::MzIonSpecGen() :
    _super(),
    _ionConfig_cref(default_ionConfig),
    _tSpecOptions_cref(default_tSpecOptions),
    _containsBPhotoProbe(false) {}

MzIonSpecGen::MzIonSpecGen(IonConfig const &ionConfig,
    types::charge_t dtaCharge,
    TheoreticalSpectrumOptions const &tSpecOptions,
    Linker::shp linker) :
    _super(),
    _ionConfig_cref(ionConfig),
    _tSpecOptions_cref(tSpecOptions),
    _containsBPhotoProbe(false)
    {
        using types::dalton_t;
        using std::get;
        using stdmass::zero_da;
        using stdmass::H2O_da;
        using stdcharge::singleCharge;
        using enums::LinkerConfig;
        using enums::FragmentationMethod;
        using enums::Ion;


        bool linkerIsPhoto = false;

        // For clarity and simplification
        if (ionConfig.linkerConfig == LinkerConfig::Interlinked) {
            _isInterlinked = true;

            if (linker->name() == "photo_biotin") {
                linkerIsPhoto = true;
            }
        } else {
            _isInterlinked = false;
        }




        switch(dtaCharge.value()) {
        case 1:
        case 2:
        case 3:
            _maxCharge = singleCharge;
            break;
        case 4:
            _maxCharge = chargeOfTwo;
            break;
        case 5:
        case 6:
            _maxCharge = chargeOfThree;
            break;
        default:
            _maxCharge = chargeOfFour;
        }

        // Determine the unmodded ion type
        switch(tSpecOptions.fragmentation.method) {
        case FragmentationMethod::Cid:
            if (ionConfig.isLeftIon) {
                _unmoddedIon = Ion::B;
            } else {
                _unmoddedIon = Ion::Y;
            }
            break;
        case FragmentationMethod::Etd:
            if (ionConfig.isLeftIon) {
                _unmoddedIon = Ion::C;
            } else {
                _unmoddedIon = Ion::Z;
            }        
            break;
        }

        dalton_t linkerMass;

        switch(ionConfig.linkerConfig) {
        case LinkerConfig::Deadend:
            linkerMass = linker->deadendMass();
            break;
        case LinkerConfig::Intralinked:
            linkerMass = linker->intralinkedMass();
            break;
        case LinkerConfig::Interlinked:
            linkerMass = linker->interlinkedMass();
            break;
        default:
            linkerMass = zero_da;
            break;
        }

        // Determine the unmodded ion mass
       // BOOST_LOG_TRIVIAL(info) << "Ion: " << ionConfig;

        _unmoddedMass = Mz::MFromMh(get<0>(ionConfig.alphaMotif.second));

        // handle special case looking for biotin photoprobe
        if(linkerIsPhoto && containsBPhotoProbe(ionConfig.alphaMotif)) {
            _containsBPhotoProbe = true;
        }

        if (ionConfig.isLeftIon) {
            std::cout << "\tB/C Ion. Lose H2O." << std::endl;
            _unmoddedMass -= H2O_da; // Left Ions lose H2O
        }
        if (_isInterlinked) {
            //BOOST_LOG_TRIVIAL(info) << "Beta: " << ionConfig.betaMotif;
            _unmoddedMass += Mz::MFromMh(get<0>(ionConfig.betaMotif.second));

            // handle special case looking for biotin photoprobe
            if(linkerIsPhoto && containsBPhotoProbe(ionConfig.betaMotif)) {
                _containsBPhotoProbe = true;
            }
        }
        _unmoddedMass += linkerMass;

        std::cout << "\tUModded Mass + Linker: " << _unmoddedMass << std::endl;

        // Determine if NH3 loss can occur
        if (tSpecOptions.Nh3Loss) {
            if (Nh3_Loss(*ionConfig.alphaMotif.first) ||
                (_isInterlinked &&
                    Nh3_Loss(*ionConfig.betaMotif.first))) {
                _canLoseNh3 = true;
            }
               
        } else {
            _canLoseNh3 = false;
        }

        // Determine if H2O loss can occur
        if (tSpecOptions.H2OLoss) {
            if (H2O_Loss(*ionConfig.alphaMotif.first) ||
                (_isInterlinked &&
                    H2O_Loss(*ionConfig.betaMotif.first))) {
                _canLoseH2O = true;
            }
               
        } else {
            _canLoseH2O = false;
        }

        // Determine if an A-ion will be generated
        if (tSpecOptions.aIon && (_unmoddedIon == Ion::B)) {
            _canAIon = true;
        } else {
            _canAIon = false;
        }
    }

MzIonSpecGen::MzIonSpecGen(MzIonSpecGen const &rhs) :
    _super(rhs),
    _ionConfig_cref(rhs._ionConfig_cref),
    _tSpecOptions_cref(rhs._tSpecOptions_cref),
    _isInterlinked(rhs._isInterlinked),
    _unmoddedMass(rhs._unmoddedMass),
    _unmoddedIon(rhs._unmoddedIon),
    _canLoseNh3(rhs._canLoseNh3),
    _canLoseH2O(rhs._canLoseH2O),
    _canAIon(rhs._canAIon),
    _currentCharge(rhs._currentCharge),
    _maxCharge(rhs._maxCharge),
    _currentIon(rhs._currentIon),
    _currentMod(rhs._currentMod),
    _containsBPhotoProbe(rhs._containsBPhotoProbe)
    {}

MzIonSpecGen::MzIonSpecGen(MzIonSpecGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _ionConfig_cref(rhs._ionConfig_cref),
    _tSpecOptions_cref(rhs._tSpecOptions_cref),
    _isInterlinked(rhs._isInterlinked),
    _unmoddedMass(rhs._unmoddedMass),
    _unmoddedIon(rhs._unmoddedIon),
    _canLoseNh3(rhs._canLoseNh3),
    _canLoseH2O(rhs._canLoseH2O),
    _canAIon(rhs._canAIon),
    _currentCharge(rhs._currentCharge),
    _maxCharge(rhs._maxCharge),
    _currentIon(rhs._currentIon),
    _currentMod(rhs._currentMod),
    _containsBPhotoProbe(rhs._containsBPhotoProbe)
    {}

MzIonSpecGen& MzIonSpecGen::operator=(MzIonSpecGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _ionConfig_cref = rhs._ionConfig_cref;
        _tSpecOptions_cref = rhs._tSpecOptions_cref;
        _isInterlinked = rhs._isInterlinked;
        _unmoddedMass = rhs._unmoddedMass;
        _unmoddedIon = rhs._unmoddedIon;
        _canLoseNh3 = rhs._canLoseNh3;
        _canLoseH2O  = rhs._canLoseH2O;
        _canAIon = rhs._canAIon;
        _currentCharge = rhs._currentCharge;
        _maxCharge = rhs._maxCharge;
        _currentIon = rhs._currentIon;
        _currentMod = rhs._currentMod;
        _containsBPhotoProbe = rhs._containsBPhotoProbe;
    }
    return *this;
}

MzIonSpecGen& MzIonSpecGen::operator=(MzIonSpecGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _ionConfig_cref = rhs._ionConfig_cref;
        _tSpecOptions_cref = rhs._tSpecOptions_cref;
        _isInterlinked = rhs._isInterlinked;
        _unmoddedMass = rhs._unmoddedMass;
        _unmoddedIon = rhs._unmoddedIon;
        _canLoseNh3 = rhs._canLoseNh3;
        _canLoseH2O  = rhs._canLoseH2O;
        _canAIon = rhs._canAIon;
        _currentCharge = rhs._currentCharge;
        _maxCharge = rhs._maxCharge;
        _currentIon = rhs._currentIon;
        _currentMod = rhs._currentMod;
        _containsBPhotoProbe = rhs._containsBPhotoProbe;
    }
    return *this;
}

bool MzIonSpecGen::operator()(value_type &rv) {
    using stdcharge::singleCharge;
    using enums::Ion;
    using enums::FragmentationMethod;
    using enums::LinkerConfig;

    $gen_start;

    for(_currentCharge = singleCharge; 
        _currentCharge <= _maxCharge;
        _currentCharge += singleCharge) {

        _currentMod = IonModification();
        _currentIon = _unmoddedIon;
        $yield(rv);

        if (_canLoseNh3) {
            _currentMod = Nh3LossOnly();
            $yield(rv);
        }
        
        if (_canLoseH2O) {
            _currentMod = H2OLossOnly();
            $yield(rv);
        }
        
        if (_canAIon) {
            _currentIon = Ion::A;
            _currentMod = CoLossOnly();
            $yield(rv);
            _currentIon = _unmoddedIon;
        }
        
    }
    $gen_stop;
}

void MzIonSpecGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

bool MzIonSpecGen::operator==(MzIonSpecGen const &rhs) const {
    if (_super::operator==(rhs) &&
        (_ionConfig_cref == rhs._ionConfig_cref) &&
        (_tSpecOptions_cref == rhs._tSpecOptions_cref) &&
        (_isInterlinked == rhs._isInterlinked) &&
        (_unmoddedMass == rhs._unmoddedMass) &&
        (_unmoddedIon == rhs._unmoddedIon) &&
        (_canLoseNh3 == rhs._canLoseNh3) &&
        (_canLoseH2O == rhs._canLoseH2O) &&
        (_canAIon == rhs._canAIon) &&
        (_currentCharge == rhs._currentCharge) &&
        (_currentIon == rhs._currentIon) &&
        (_currentMod == rhs._currentMod)) {
        return true;
    } else {
        return false;
    }
}

MzIonSpecGen::value_type MzIonSpecGen::genReturn() const {
    using enums::Ion;
    using enums::IonMod;
    using types::dalton_t;
    using units::dalton_mass;
    using std::make_pair;
    using stdmass::NH3_da;
    using stdmass::H2O_da;
    using stdmass::CO_da;

    // I would prefer to have these coded other than just raw numbers
    dalton_t const cDiff(17.0265 * dalton_mass);
    dalton_t const zDiff(-16.0187 * dalton_mass);

    types::dalton_t currentMass = _unmoddedMass;

    std::cout << "\tCurrent Charge: " << _currentCharge << std::endl;
    if (_currentIon == Ion::C) {
        currentMass += cDiff;
    } else if (_currentIon == Ion::Z) {
        currentMass += zDiff;
    }

    if (_currentMod[IonMod::Nh3Loss]) {
        currentMass -= NH3_da;
    }
    if (_currentMod[IonMod::H2OLoss]) {
        currentMass -= H2O_da;
    }
    if (_currentMod[IonMod::CoLoss]) {
        currentMass -= CO_da;
    }

    Mz mz;
    if (_containsBPhotoProbe) {
        mz = Mz::MzFromPhoto(currentMass, _currentCharge);
       // mz = Mz(currentMass, _currentCharge);
    } else {
        mz = Mz(currentMass, _currentCharge);
    }
    //BOOST_LOG_TRIVIAL(info) << "Final MZ: " << mz;


    return make_pair(
        mz,
        IonSpec(_currentIon, _currentMod, _ionConfig_cref)
        );
}

} /* namespace apollo */

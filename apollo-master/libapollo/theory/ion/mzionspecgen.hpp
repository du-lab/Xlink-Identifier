/**
 * @file    mzionspecgen.hpp
 * @brief   Generator for the various ion ion specifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/31
 * @copyright 2012
 */

#ifndef apollo_mzionspecgen_hpp_
#define apollo_mzionspecgen_hpp_

#include <functional>
#include <utility>

#include "types.hpp"
#include "units.hpp"
#include "enums.hpp"
#include "optiontypes.hpp"
#include "ionconfig.hpp"
#include "spectrumtypes.hpp"
#include "../core/generator.hpp"


namespace apollo {

class MzIonSpecGen : public Generator<MzIonSpecPair> {
public:

    MzIonSpecGen();

    // Add dta charge state
    MzIonSpecGen(IonConfig const &ionConfig,
        types::charge_t dtaCharge,
        TheoreticalSpectrumOptions const &tSpecOptions,
        Linker::shp linker = Linker::shp());
    
    MzIonSpecGen(MzIonSpecGen const &rhs);

    MzIonSpecGen(MzIonSpecGen &&rhs);

    MzIonSpecGen& operator=(MzIonSpecGen const &rhs);

    MzIonSpecGen& operator=(MzIonSpecGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(MzIonSpecGen const &rhs) const;

    static ReactionGroup const H2O_Loss;
    static ReactionGroup const Nh3_Loss;

    ~MzIonSpecGen() {}
private:
    // Generator Definitions
    typedef Generator<MzIonSpecPair> _super;


    // Generator Config
    std::reference_wrapper<IonConfig const> _ionConfig_cref;
    std::reference_wrapper<TheoreticalSpectrumOptions const> _tSpecOptions_cref;
    types::dalton_t _unmoddedMass;
    enums::Ion _unmoddedIon;
    bool _isInterlinked;
    bool _containsBPhotoProbe;
    bool _canLoseNh3;
    bool _canLoseH2O;
    bool _canAIon;

    // Generator State
    types::charge_t _currentCharge;
    types::charge_t _maxCharge;
    enums::Ion _currentIon;
    IonModification _currentMod;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_mzionspecgen_hpp_ */

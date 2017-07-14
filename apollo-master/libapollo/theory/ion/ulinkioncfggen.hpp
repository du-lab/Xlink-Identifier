/**
 * @file    ulinkioncfggen.hpp
 * @brief   Generator for unlinked ion configs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#ifndef apollo_ulinkioncfggen_hpp_
#define apollo_ulinkioncfggen_hpp_

#include <functional>

#include "optiontypes.hpp"
#include "sequenceinterface.hpp"
#include "locresiduemap.hpp"
#include "sequenceconfig.hpp"
#include "ionconfig.hpp"
#include "../core/generator.hpp"

namespace apollo {

class UlinkIonCfgGen : public Generator<IonConfig> {
public:
    UlinkIonCfgGen();

    UlinkIonCfgGen(SequenceMotif const &sMotif,
        LocResidueMap const &statLocMap,
        LocResidueMap const &dynLocMap,
        SequenceOptions const &sOptions);

    UlinkIonCfgGen(UlinkIonCfgGen const &rhs);

    UlinkIonCfgGen(UlinkIonCfgGen &&rhs);

    UlinkIonCfgGen& operator=(UlinkIonCfgGen const &rhs);

    UlinkIonCfgGen& operator=(UlinkIonCfgGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(UlinkIonCfgGen const &rhs) const;

    ~UlinkIonCfgGen() {}
private:
    //Generator Definitions
    typedef Generator<IonConfig> _super;

    // Generator Config
    std::reference_wrapper<SequenceMotif const> _sMotif_cref;
    std::reference_wrapper<LocResidueMap const> _statLocMap_cref;
    std::reference_wrapper<LocResidueMap const> _dynLocMap_cref;
    std::reference_wrapper<SequenceOptions const> _sOptions_cref;

    // Generator state
    SequenceI::shp _lIonShp;
    SequenceI::size_type _lLength;
    ResidueCount _lStatMods;
    ResidueCount _lDynMods;

    SequenceI::shp _rIonShp;
    SequenceI::size_type _rLength;
    ResidueCount _rStatMods;
    ResidueCount _rDynMods;

    bool _returnLIon;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_ul_ioncfggen_hpp_ */

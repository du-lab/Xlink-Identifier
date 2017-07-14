/**
 * @file    linkioncfggen.hpp
 * @brief   Generator for linked ion configs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#ifndef apollo_linkioncfggen_hpp_
#define apollo_linkioncfggen_hpp_

#include <functional>

#include "optiontypes.hpp"
#include "sequenceinterface.hpp"
#include "locresiduemap.hpp"
#include "sequenceconfig.hpp"
#include "linkloc.hpp"
#include "ionconfig.hpp"
#include "../core/generator.hpp"

#include "ulinkioncfgiter.hpp"

namespace apollo {

class LinkIonCfgGen : public Generator<IonConfig> {
public:
    LinkIonCfgGen() {}

    LinkIonCfgGen(SequenceMotif const &sMotif,
        LinkLoc linkLoc,
        LocResidueMap const &statLocMap,
        LocResidueMap const &dynLocMap,
        SequenceOptions const &sOptions);

    LinkIonCfgGen(LinkIonCfgGen const &rhs);

    LinkIonCfgGen(LinkIonCfgGen &&rhs);

    LinkIonCfgGen& operator=(LinkIonCfgGen const &rhs);

    LinkIonCfgGen& operator=(LinkIonCfgGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(LinkIonCfgGen const &rhs) const;

    ~LinkIonCfgGen() {}
private:
    typedef Generator<IonConfig> _super;

    UlinkIonCfgIter _ionCfgIter;

    LinkLoc _linkLoc;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_linkioncfggen_hpp_ */  

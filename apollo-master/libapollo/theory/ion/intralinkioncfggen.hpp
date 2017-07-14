#ifndef apollo_intralinkioncfggen_hpp_
#define apollo_intralinkioncfggen_hpp_

#include "types.hpp"
#include "optiontypes.hpp"
#include "sequenceinterface.hpp"
#include "locresiduemap.hpp"
#include "sequenceconfig.hpp"
#include "linkloc.hpp"
#include "ionconfig.hpp"
#include "../core/generator.hpp"

#include "linkioncfgiter.hpp"

namespace apollo {

class IntralinkIonCfgGen : public Generator<IonConfig>
{
public:
    IntralinkIonCfgGen() {}

    IntralinkIonCfgGen(SequenceMotif const &seqMotif,
        LinkLoc seqLinkLoc1,
        LinkLoc seqLinkLoc2,
        LocResidueMap const &seqStatLocMap,
        LocResidueMap const &seqDynLocMap,
        SequenceOptions const &sOptions);

    IntralinkIonCfgGen(IntralinkIonCfgGen const &rhs);

    IntralinkIonCfgGen(IntralinkIonCfgGen &&rhs);

    IntralinkIonCfgGen& operator=(IntralinkIonCfgGen const &rhs);

    IntralinkIonCfgGen& operator=(IntralinkIonCfgGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(IntralinkIonCfgGen const &rhs) const;

    ~IntralinkIonCfgGen() {}
private:
    typedef Generator<IonConfig> _super;

    // Generator Config
    LinkLoc _seqLinkLoc1, _seqLinkLoc2;

    // Generator State
    LinkIonCfgIter _seqIonCfgIter;
    IonConfig _leftIon, _rightIon;
    bool _returnLIon;


    value_type genReturn() const;
};

} /* namespace apollo */

#endif // apollo_intralinkioncfggen_hpp_

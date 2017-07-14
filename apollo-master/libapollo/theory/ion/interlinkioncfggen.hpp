#ifndef apollo_interlinkioncfggen_hpp_
#define apollo_interlinkioncfggen_hpp_

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

class InterlinkIonCfgGen : public Generator<IonConfig>
{
public:
    InterlinkIonCfgGen();

    InterlinkIonCfgGen(SequenceMotif const &seq1Motif,
        LinkLoc seq1LinkLoc,
        LocResidueMap const &seq1StatLocMap,
        LocResidueMap const &seq1DynLocMap,
        SequenceMotif const &seq2Motif,
        LinkLoc seq2LinkLoc,
        LocResidueMap const &seq2StatLocMap,
        LocResidueMap const &seq2DynLocMap,
        SequenceOptions const &sOptions);

    InterlinkIonCfgGen(InterlinkIonCfgGen const &rhs);

    InterlinkIonCfgGen(InterlinkIonCfgGen &&rhs);

    InterlinkIonCfgGen& operator=(InterlinkIonCfgGen const &rhs);

    InterlinkIonCfgGen& operator=(InterlinkIonCfgGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(InterlinkIonCfgGen const &rhs) const;

    ~InterlinkIonCfgGen() {}
private:
    typedef Generator<IonConfig> _super;

    bool _seq1IsAlpha;
    bool _onSeq1;

    LinkIonCfgIter _seq1IonCfgIter;
    std::reference_wrapper<SequenceMotif const> _seq1Motif_cref;
    LinkLoc _seq1LinkLoc;

    LinkIonCfgIter _seq2IonCfgIter;
    std::reference_wrapper<SequenceMotif const> _seq2Motif_cref;
    LinkLoc _seq2LinkLoc;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif // apollo_interlinkioncfggen_hpp_

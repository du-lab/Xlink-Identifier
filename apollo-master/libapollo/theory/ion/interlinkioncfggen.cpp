#include "mz.hpp"
#include "../../core/residuecalc.hpp"

#include "interlinkioncfggen.hpp"

namespace apollo {

namespace d {

SequenceMotif const seqMotif;

}

InterlinkIonCfgGen::InterlinkIonCfgGen() :
    _super(),
    _seq1Motif_cref(d::seqMotif),
    _seq2Motif_cref(d::seqMotif)
{}

InterlinkIonCfgGen::InterlinkIonCfgGen(SequenceMotif const &seq1Motif,
    LinkLoc seq1LinkLoc,
    LocResidueMap const &seq1StatLocMap,
    LocResidueMap const &seq1DynLocMap,
    SequenceMotif const &seq2Motif,
    LinkLoc seq2LinkLoc,
    LocResidueMap const &seq2StatLocMap,
    LocResidueMap const &seq2DynLocMap,
    SequenceOptions const &sOptions) :
    _super(),
    _onSeq1(true),
    _seq1Motif_cref(seq1Motif),
    _seq1LinkLoc(seq1LinkLoc),
    _seq2Motif_cref(seq2Motif),
    _seq2LinkLoc(seq2LinkLoc)
{
    _seq1IonCfgIter =
            make_geniter<LinkIonCfgGen>(seq1Motif, seq1LinkLoc, seq1StatLocMap, seq1DynLocMap, sOptions);
    _seq2IonCfgIter =
            make_geniter<LinkIonCfgGen>(seq2Motif, seq2LinkLoc, seq2StatLocMap, seq2DynLocMap, sOptions);

    if (seq1Motif.first->length() >= seq2Motif.first->length()) {
        _seq1IsAlpha = true;
    } else {
        _seq1IsAlpha = false;
    }
}

InterlinkIonCfgGen::InterlinkIonCfgGen(const InterlinkIonCfgGen &rhs) :
    _super(rhs),
    _seq1IsAlpha(rhs._seq1IsAlpha),
    _onSeq1(rhs._onSeq1),
    _seq1IonCfgIter(rhs._seq1IonCfgIter),
    _seq1Motif_cref(rhs._seq1Motif_cref),
    _seq1LinkLoc(rhs._seq1LinkLoc),
    _seq2IonCfgIter(rhs._seq2IonCfgIter),
    _seq2Motif_cref(rhs._seq2Motif_cref),
    _seq2LinkLoc(rhs._seq2LinkLoc) {}

InterlinkIonCfgGen::InterlinkIonCfgGen(InterlinkIonCfgGen &&rhs) :
    _super(std::forward<_super>(rhs)),
    _seq1IsAlpha(rhs._seq1IsAlpha),
    _onSeq1(rhs._onSeq1),
    _seq1IonCfgIter(std::move(rhs._seq1IonCfgIter)),
    _seq1Motif_cref(rhs._seq1Motif_cref),
    _seq1LinkLoc(rhs._seq1LinkLoc),
    _seq2IonCfgIter(std::move(rhs._seq2IonCfgIter)),
    _seq2Motif_cref(rhs._seq2Motif_cref),
    _seq2LinkLoc(rhs._seq2LinkLoc) {}

InterlinkIonCfgGen& InterlinkIonCfgGen::operator=(InterlinkIonCfgGen const &rhs) {
    if (this != &rhs) {
        _super::operator=(rhs);
        _seq1IsAlpha = rhs._seq1IsAlpha;
        _onSeq1 = rhs._onSeq1;
        _seq1IonCfgIter = rhs._seq1IonCfgIter;
        _seq1Motif_cref = rhs._seq1Motif_cref;
        _seq1LinkLoc = rhs._seq1LinkLoc;
        _seq2IonCfgIter = rhs._seq2IonCfgIter;
        _seq2Motif_cref = rhs._seq2Motif_cref;
        _seq2LinkLoc = rhs._seq2LinkLoc;
    }
    return *this;
}

InterlinkIonCfgGen& InterlinkIonCfgGen::operator=(InterlinkIonCfgGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::forward<_super>(rhs));
        _seq1IsAlpha = rhs._seq1IsAlpha;
        _onSeq1 = rhs._onSeq1;
        _seq1IonCfgIter = std::move(rhs._seq1IonCfgIter);
        _seq1Motif_cref = rhs._seq1Motif_cref;
        _seq1LinkLoc = rhs._seq1LinkLoc;
        _seq2IonCfgIter = std::move(rhs._seq2IonCfgIter);
        _seq2Motif_cref = rhs._seq2Motif_cref;
        _seq2LinkLoc = rhs._seq2LinkLoc;
    }
    return *this;
}

bool InterlinkIonCfgGen::operator ()(value_type &rv) {
    LinkIonCfgIter const linkIonCfgEnd;

    $gen_start;

    for(; _seq1IonCfgIter != linkIonCfgEnd; ++_seq1IonCfgIter) {
        $yield(rv);
    }
    _onSeq1 = false;
    for(; _seq2IonCfgIter != linkIonCfgEnd; ++_seq2IonCfgIter) {
        $yield(rv);
    }
    $gen_stop;
}

void InterlinkIonCfgGen::generate(value_type &rv) const {
    rv = genReturn();
}

bool InterlinkIonCfgGen::operator==(InterlinkIonCfgGen const &rhs) const {
    if (_super::operator==(rhs) &&
            (_seq1IsAlpha == rhs._seq1IsAlpha) &&
            (_onSeq1 == rhs._onSeq1) &&
            (_seq1IonCfgIter == rhs._seq1IonCfgIter) &&
            (_seq1Motif_cref == rhs._seq1Motif_cref) &&
            (_seq1LinkLoc == rhs._seq1LinkLoc) &&
            (_seq2IonCfgIter == rhs._seq2IonCfgIter) &&
            (_seq2Motif_cref == rhs._seq2Motif_cref) &&
            (_seq2LinkLoc == rhs._seq2LinkLoc)
            ) {
        return true;
    } else {
        return false;
    }
}

InterlinkIonCfgGen::value_type InterlinkIonCfgGen::genReturn() const {
    using enums::LinkerConfig;
    using enums::FragmentedSequence;
    using std::get;

    value_type ionConfig;

    std::reference_wrapper<SequenceMotif const> stableSequenceMotif(_seq2Motif_cref);

    if (_onSeq1) {
        ionConfig = *_seq1IonCfgIter;
    } else {
        ionConfig = *_seq2IonCfgIter;
        stableSequenceMotif = _seq1Motif_cref;
    }

    if (ionConfig.linkerConfig == LinkerConfig::Deadend) {
        if (_onSeq1) {
            if (_seq1IsAlpha) {
                ionConfig.betaMotif = stableSequenceMotif;
            } else {
                ionConfig.fragmentedSequence = FragmentedSequence::Beta;
                ionConfig.betaMotif = std::move(ionConfig.alphaMotif);
                ionConfig.alphaMotif = stableSequenceMotif;
            }
        } else {
            if (_seq1IsAlpha) {
                ionConfig.fragmentedSequence = FragmentedSequence::Beta;
                ionConfig.betaMotif = std::move(ionConfig.alphaMotif);
                ionConfig.alphaMotif = stableSequenceMotif;
            } else {
                ionConfig.betaMotif = stableSequenceMotif;
            }
        }
        ionConfig.linkerConfig = LinkerConfig::Interlinked;
    }

    return ionConfig;

}

} /* namespace apollo */

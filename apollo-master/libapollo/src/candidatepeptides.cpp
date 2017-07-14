/**
 * @file    candidatepeptides.cpp
 * @brief   A set of types meant to represent candidate peptides
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/26
 * @copyright 2012
 */

#include <iterator>

#include <boost/log/trivial.hpp>

#include "../core/macros.hpp"
#include "units.hpp"
#include "../analysis/peptidesearch.hpp"
#include "candidatepeptides.hpp"

namespace apollo {

namespace fn {

LinkedCandidates linkedCandidates(
    MhSequenceTree const &mhTree,
    types::mz_t const experimentalMh,
    Linker const &linker,
    SequenceOptions const &sOptions,
    AnalysisOptions const &aOptions) {

    using types::mz_t;
    using units::mass_charge;
    using fn::peptideSearchUsingGroup;
    using fn::peptideSearchUsingInterlink;

    LinkedCandidates lCandidates;

    if (linker.canDeadend()) {
        // Find the mass of the peptide by subtracting off the mass of the linker and the H2O
        mz_t deadendMh =
            experimentalMh - mz_t(linker.deadendMass().value() * mass_charge);
        // for this dead endmh which is the peptide mass -> search the theoretical peptdides i.e.
        //search mhTree
        lCandidates.deadend = peptideSearchUsingGroup(
                // QUESTION about linker.group1(). havent we already subtracted that off?
            mhTree, deadendMh, sOptions, aOptions, linker.group1()
            );
        // cross linker has two groups. groups to two peptides. homofunctiona crosslinker is when
        // both cross linking groups are the same... They can also be different.
        if (linker.group1() != linker.group2()) {
            SequenceMotifs group2Candidates = peptideSearchUsingGroup(
                mhTree, deadendMh, sOptions, aOptions, linker.group2()
            );
            // combined all possible candidates for the two different possibilities.
            lCandidates.deadend.insert(
                std::make_move_iterator(group2Candidates.begin()),
                std::make_move_iterator(group2Candidates.end())
                );

        }
        BOOST_LOG_TRIVIAL(info) << "Deadend Matches for " <<
            experimentalMh << ": " << lCandidates.deadend.size();
    }

    if (linker.canIntralink()) {
        // subtract a linker -> intralinked mass will not have H2O and something else (ask about
        // later. QUESTION. 
        mz_t intralinkMh =
            experimentalMh - mz_t(linker.intralinkedMass().value() * mass_charge);
        lCandidates.intralinked = peptideSearchUsingGroup(
            mhTree, intralinkMh, sOptions, aOptions, linker.intraGroup()
        );
        BOOST_LOG_TRIVIAL(info) << "Intralink Matches for " <<
            experimentalMh << ": " << lCandidates.intralinked.size();
    }

    if (linker.canInterlink()) {
        lCandidates.interlinked = peptideSearchUsingInterlink(
            mhTree, experimentalMh, sOptions, aOptions, linker);

        BOOST_LOG_TRIVIAL(info) << "Interlink Matches for " <<
            experimentalMh << ": " << lCandidates.interlinked.size();
    }

    return lCandidates;
}

} /* namespace fn */

CandidatePeptides::CandidatePeptides(MhSequenceTree const &mhTree,
    DtaFile const &dtaFile,
    Options const &options) : 
    _dtaFile(dtaFile) {

    using std::get;
    using fn::peptideSearch;
    using fn::linkedCandidates;

    types::mz_t const experimentalMh = get<1>(dtaFile.first);
    BOOST_LOG_TRIVIAL(info) << "Linkers size: " << options.linker().linkers.size();
    _unlinked = peptideSearch(mhTree, experimentalMh, options.sequence(), options.analysis());
    
    for( auto linkerShp : options.linker().linkers) {
        _linkable[linkerShp] = 
            linkedCandidates(mhTree, experimentalMh, *linkerShp, options.sequence(), options.analysis());
    }

}


CandidatePeptides::CandidatePeptides(CandidatePeptides const &rhs) :
    _dtaFile(rhs._dtaFile),
    _unlinked(rhs._unlinked),
    _linkable(rhs._linkable) {}

CandidatePeptides::CandidatePeptides(CandidatePeptides &&rhs) :
    _dtaFile(rhs._dtaFile),
    _unlinked(std::move(rhs._unlinked)),
    _linkable(std::move(rhs._linkable)) {}

CandidatePeptides& CandidatePeptides::operator=(CandidatePeptides const &rhs) {
    if (this != &rhs) {
        _dtaFile = rhs._dtaFile;
        _unlinked = rhs._unlinked;
        _linkable = rhs._linkable;
    }

        //Owen Edit
        std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
    return *this;
}

CandidatePeptides& CandidatePeptides::operator=(CandidatePeptides &&rhs) {
    if (this != &rhs) {
        _dtaFile = rhs._dtaFile;
        _unlinked = std::move(rhs._unlinked);
        _linkable = std::move(rhs._linkable);
    }

        //Owen Edit
        std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
    return *this;
}

DtaFile const& CandidatePeptides::dta() const {

    return _dtaFile;
}

SequenceMotifs const& CandidatePeptides::unlinked() const {

    return _unlinked;
}

LinkerCandidateMap const& CandidatePeptides::linkable() const {

    return _linkable;
}

bool CandidatePeptides::hasCandidates() const {

    if (!_unlinked.empty()) {
        return true;
    }
    for(auto const &lCandidatePair : _linkable) {
        if( !lCandidatePair.second.deadend.empty()
                || !lCandidatePair.second.intralinked.empty()
                || !lCandidatePair.second.interlinked.empty()) {
            return true;
        }
    }
    return false;
}

} /* namespace apollo  */

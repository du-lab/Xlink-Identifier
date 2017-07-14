/**
 * @file    candidatepeptides.hpp
 * @brief   A set of types meant to represent candidate peptides
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/26
 * @copyright 2012
 */


#ifndef apollo_candidatepeptides_hpp_
#define apollo_candidatepeptides_hpp_

#include <utility>
#include <functional>

#include <boost/container/flat_set.hpp>
#include <boost/container/flat_map.hpp>

#include "../core/linker.hpp"
#include "types.hpp"
#include "dtatypes.hpp"
#include "theorytypes.hpp"
#include "options.hpp"
#include "sequenceconfig.hpp"

namespace apollo {

typedef boost::container::flat_set<SequenceMotif> SequenceMotifs;

typedef boost::container::flat_map<SequenceMotif, SequenceMotifs> LinkedSequenceMotifs;

struct LinkedCandidates {
    SequenceMotifs deadend;
    SequenceMotifs intralinked;
    LinkedSequenceMotifs interlinked;
};

typedef boost::container::flat_map<Linker::shp, LinkedCandidates> LinkerCandidateMap;

class CandidatePeptides {
public:

    CandidatePeptides(MhSequenceTree const &mhTree,
        DtaFile const &dtaFile,
        Options const &options);

    CandidatePeptides(CandidatePeptides const &rhs);

    CandidatePeptides(CandidatePeptides &&rhs);

    CandidatePeptides& operator=(CandidatePeptides const &rhs);

    CandidatePeptides& operator=(CandidatePeptides &&rhs);

    DtaFile const& dta() const;

    SequenceMotifs const& unlinked() const;

    LinkerCandidateMap const& linkable() const;

    bool hasCandidates() const;

    ~CandidatePeptides() {}
private:
    std::reference_wrapper<DtaFile const> _dtaFile;
    SequenceMotifs _unlinked;
    LinkerCandidateMap _linkable;
};

} /* namespace apollo */

#endif /* apollo_candidatepeptides_hpp_ */

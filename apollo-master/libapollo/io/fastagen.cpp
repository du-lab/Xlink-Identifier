/**
 * @file    fastagen.cpp
 * @brief   Sequence generator from a fasta file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#include <algorithm>
#include <iostream>

#include <boost/algorithm/string.hpp>

#include "fastagen.hpp"
#include "kseq.h"
#include "../core/sequence.hpp"

namespace apollo {

namespace detail {
KSEQ_INIT(gzFile, gzread)
}


FastaGen::FastaGen(boost::filesystem::path path, bool reverseSequence) :
    _path(path), _reverseSequence(reverseSequence) {

    _filep = gzopen(_path.c_str(), "r");
    if ( _filep != NULL) {
        _seqp = detail::kseq_init(_filep);
    }
}

FastaGen::FastaGen(FastaGen &&rhs) :
    _super(std::move(static_cast<_super&>(rhs))),
    _path(std::move(rhs._path)),
    _filep(rhs._filep), 
    _seqp(rhs._seqp),
    _reverseSequence(rhs._reverseSequence) {
        rhs._filep = NULL;
        rhs._seqp = NULL;
}

FastaGen& FastaGen::operator=(FastaGen &&rhs) {
    if (this != &rhs) {
        _super::operator=(std::move(static_cast<_super&>(rhs)));
        _path = std::move(rhs._path);
        _filep = rhs._filep;
        _seqp = rhs._seqp;
        _reverseSequence = rhs._reverseSequence;
        rhs._filep = NULL;
        rhs._seqp = NULL;
    }
    return *this;
}

bool FastaGen::operator()(value_type &rv) {
    using detail::kseq_t;
    $gen_start;
    while (detail::kseq_read(static_cast<kseq_t*>(_seqp)) > 0 ) {
        $yield(rv);
    }
    $gen_stop;
}

void FastaGen::generate(value_type &rv) const {
    rv = std::move(genReturn());
}

bool FastaGen::operator==(FastaGen const &rhs) const {
    if (_super::operator==(rhs)) {
        return _path == rhs._path;
    } else {
        return false;
    }
}

namespace validation {

bool string_exists(char const *cstr) {
    return (cstr != NULL);
}

} /* namespace validation */

const bool newSeqHasNh2Terminus = true;
const bool newSeqHasCTerminus = true;

SequenceIdPair FastaGen::genReturn() const {
    using detail::kseq_t;
    using types::io_string_t;
    using validation::string_exists;
    using std::make_pair;
    using std::make_shared;
    using namespace boost::algorithm;

    io_string_t id;
    io_string_t description;
    io_string_t sequence;
    if (string_exists(static_cast<kseq_t*>(_seqp)->name.s))  {
        id += static_cast<kseq_t*>(_seqp)->name.s;
    }
    
    if (string_exists(static_cast<kseq_t*>(_seqp)->comment.s)) {
        description += static_cast<kseq_t*>(_seqp)->comment.s;
    }
    
    if (string_exists(static_cast<kseq_t*>(_seqp)->seq.s)) {
        sequence += static_cast<kseq_t*>(_seqp)->seq.s;
    }

    trim(id);
    trim(description);
    trim(sequence);
    SequenceId seqId = make_pair(id, description);

    SequenceI::shp seqShp;
    if (_reverseSequence) {
        seqShp = make_shared<Sequence>(sequence.rbegin(), sequence.rend(),
            newSeqHasNh2Terminus, newSeqHasCTerminus);
    } else {
        seqShp = make_shared<Sequence>(sequence.begin(), sequence.end(),
            newSeqHasNh2Terminus, newSeqHasCTerminus);        
    }
    return SequenceIdPair(seqShp, seqId);
}

FastaGen::~FastaGen() {
    using detail::kseq_t;
    if (_seqp) {
        detail::kseq_destroy(static_cast<kseq_t*>(_seqp));
    }
    if (_filep) {
        gzclose(_filep);
    }
}

} /* namespace apollo */

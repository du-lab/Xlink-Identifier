/**
 * @file    fastagen.hpp
 * @brief   Sequence generator from a fasta file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/11
 * @copyright 2012
 */

#ifndef apollo_fastagen_hpp_
#define apollo_fastagen_hpp_

#define BOOST_FILESYSTEM_NO_DEPRECATED

#include <zlib.h>
#include <utility>
#include <boost/filesystem.hpp>

#include "fastatypes.hpp"
#include "sequenceinterface.hpp"
#include "../core/generator.hpp"

namespace apollo {


class FastaGen : public Generator<SequenceIdPair> {
public:

    FastaGen() : _super(), _filep(NULL), _seqp(NULL) {}

    explicit FastaGen(boost::filesystem::path path, bool reverseSequence = false);

    explicit FastaGen(FastaGen &&rhs);

    FastaGen& operator=(FastaGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(FastaGen const &rhs) const;

    ~FastaGen();
private:
    typedef Generator<SequenceIdPair> _super;

    boost::filesystem::path _path;
    gzFile _filep;
    void *_seqp;
    bool _reverseSequence;

    SequenceIdPair genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_fastagen_hpp_ */

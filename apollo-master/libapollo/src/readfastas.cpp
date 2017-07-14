/**
 * @file    readfastas.cpp
 * @brief   Read fasta files from a path vector 
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/07
 * @copyright 2012
 */

#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <boost/log/trivial.hpp>

#include <boost/container/container_fwd.hpp>
#include <boost/assign/list_of.hpp>

#include "readfastas.hpp"

namespace apollo {

const ExtensionSet fastaExtensions =
    boost::assign::list_of(".fa")(".fasta")(".gz");

namespace fn {


SequenceIdMap readFastas(PathVector const &fastaVector, bool reverseSequence) {
    using std::sort;
    using boost::container::ordered_unique_range;

    FastaIter fastaEnd;
    std::vector<SequenceIdMap::value_type> seqIdVector;
    PathVector expandedFVector = fn::expandPaths(fastaVector, fastaExtensions);
    for(auto const &fPath : expandedFVector) {
        //BOOST_LOG_TRIVIAL(info) << "Reading: " << fPath.string();
        for (FastaIter fIt = make_geniter<FastaGen>(fPath, reverseSequence); fIt != fastaEnd; ++fIt) {
            //BOOST_LOG_TRIVIAL(debug) << "Sequence: " << fIt->second.first << ": " << *(fIt->first);
            seqIdVector.emplace_back(*fIt);
        }
    }
    sort(seqIdVector.begin(), seqIdVector.end());
    SequenceIdMap sequenceMap(ordered_unique_range,
        std::make_move_iterator(seqIdVector.begin()),
        std::make_move_iterator(seqIdVector.end()));

    return sequenceMap;
}

} /* namespace fn */
} /* namespace apollo */

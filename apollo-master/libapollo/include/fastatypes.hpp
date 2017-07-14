/**
 * @file    fastatypes.hpp
 * @brief   Types returned as a result of the fasta read functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#ifndef apollo_fastatypes_hpp_
#define apollo_fastatypes_hpp_

#include <boost/container/flat_map.hpp>
#include "types.hpp"
#include "sequenceinterface.hpp"

namespace apollo {

typedef std::pair<types::io_string_t, types::io_string_t> SequenceId;

typedef boost::container::flat_map<SequenceI::shp, SequenceId> SequenceIdMap;

typedef SequenceIdMap::value_type SequenceIdPair;

} /* namespace apollo */

#endif /* apollo_fastatypes_hpp_ */

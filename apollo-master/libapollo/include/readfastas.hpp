/**
 * @file    readfastas.hpp
 * @brief   Read fasta files from a path vector 
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/07
 * @copyright 2012
 */

#ifndef apollo_readfastas_hpp_
#define apollo_readfastas_hpp_


#include "pathvector.hpp"
#include "fastatypes.hpp"
#include "../io/fastagen.hpp"
#include "../io/fastaiter.hpp"

namespace apollo {

namespace fn {

SequenceIdMap readFastas(PathVector const &fastaVector, 
    bool reverseSequence = false);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_readfastas_hpp_ */

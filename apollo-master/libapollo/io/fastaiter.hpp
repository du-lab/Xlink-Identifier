/**
 * @file    fastaiter.hpp
 * @brief   Sequence iterator from a fasta file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/26
 * @copyright 2012
 */

#ifndef apollo_fastaiter_hpp_
#define apollo_fastaiter_hpp_

#include "fastagen.hpp"
#include "../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<FastaGen> FastaIter;

} /* namespace apollo */

 #endif /* apollo_fastaiter_hpp_ */

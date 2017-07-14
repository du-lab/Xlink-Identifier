/**
 * @file    ntrypticiter.hpp
 * @brief   Iterator for n tryptic digestion
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/26
 * @copyright 2012
 */

#ifndef apollo_ntrypticiter_hpp_
#define apollo_ntrypticiter_hpp_

#include "ntrypticgen.hpp"
#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<NTrypticGen> NTrypticIter;

} /* namespace apollo */

 #endif /* apollo_ntrypticiter_hpp_ */

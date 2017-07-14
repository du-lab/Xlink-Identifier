/**
 * @file    fullytrypticiter.hpp
 * @brief   Iterator for fully tryptic digestion
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/26
 * @copyright 2012
 */

#ifndef apollo_fullytrypticiter_hpp_
#define apollo_fullytrypticiter_hpp_

#include "fullytrypticgen.hpp"
#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<FullyTrypticGen> FullyTrypticIter;

} /* namespace apollo */

 #endif /* apollo_fullytrypticiter_hpp_ */

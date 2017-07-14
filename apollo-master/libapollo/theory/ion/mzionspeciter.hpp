/**
 * @file    mzionspeciter.hpp
 * @brief   Iterator for mz/ion spec pairs
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/20
 * @copyright 2012
 */

#ifndef apollo_mzionspeciter_hpp_
#define apollo_mzionspeciter_hpp_

#include "mzionspecgen.hpp"
#include "../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<MzIonSpecGen> MzIonSpecIter;

} /* namespace apollo */

 #endif /* apollo_mzionspeciter_hpp_ */

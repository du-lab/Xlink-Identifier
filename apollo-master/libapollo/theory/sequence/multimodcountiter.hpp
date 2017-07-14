/**
 * @file    multimodcountiter.hpp
 * @brief   Iterator for all possible multiple dynamic modifications
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/26
 * @copyright 2012
 */

#ifndef apollo_multimodcountiter_hpp_
#define apollo_multimodcountiter_hpp_

#include "multimodcountgen.hpp"
#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<MultiModCountGen> MultiModCountIter;

} /* namespace apollo */

 #endif /* apollo_modcountiter_hpp_ */

/**
 * @file    multimodlociter.hpp
 * @brief   Iterator all possible multiple dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#ifndef apollo_multimodlociter_hpp_
#define apollo_multimodlociter_hpp_

#include "multimodlocgen.hpp"

#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<MultiModLocGen> MultiModLocIter;

} /* namespace apollo */

#endif /* apollo_multiodlociter_hpp_ */
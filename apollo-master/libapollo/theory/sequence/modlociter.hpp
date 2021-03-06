/**
 * @file    modlociter.hpp
 * @brief   Iterator all possible dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */

#ifndef apollo_modlociter_hpp_
#define apollo_modlociter_hpp_

#include "modlocgen.hpp"

#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<ModLocGen> ModLocIter;

} /* namespace apollo */

#endif /* apollo_modlociter_hpp_ */
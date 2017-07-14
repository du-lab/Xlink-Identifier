/**
 * @file    linklociter.hpp
 * @brief   Iterator for all possible link locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/07
 * @copyright 2013
 */

#ifndef apollo_linklociter_hpp_
#define apollo_linklociter_hpp_

#include "linklocgen.hpp"
#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<LinkLocGen> LinkLocIter;

} /* namespace apollo */

 #endif /* apollo_linklociter_hpp_ */
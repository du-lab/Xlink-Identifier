/**
 * @file    modcountiter.hpp
 * @brief   Iterator for all possible dynamic modification counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/26
 * @copyright 2012
 */

#ifndef apollo_modcountiter_hpp_
#define apollo_modcountiter_hpp_

#include "modcountgen.hpp"
#include "../../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<ModCountGen> ModCountIter;

} /* namespace apollo */

 #endif /* apollo_modcountiter_hpp_ */
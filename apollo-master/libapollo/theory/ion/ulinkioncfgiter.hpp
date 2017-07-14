/**
 * @file    ulinkioncfgiter.hpp
 * @brief   Iterator for unlinked ion configurations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/14
 * @copyright 2013
 */

#ifndef apollo_ulinkioncfgiter_hpp_
#define apollo_ulinkioncfgiter_hpp_

#include "ulinkioncfggen.hpp"
#include "../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<UlinkIonCfgGen> UlinkIonCfgIter;

} /* namespace apollo */

 #endif /* apollo_ulinkioncfgiter_hpp_ */

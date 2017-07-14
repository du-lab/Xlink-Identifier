/**
 * @file    linkioncfgiter.hpp
 * @brief   Iterator for unlinked ion configurations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/07/14
 * @copyright 2013
 */

#ifndef apollo_linkioncfgiter_hpp_
#define apollo_linkioncfgiter_hpp_

#include "linkioncfggen.hpp"
#include "../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<LinkIonCfgGen> LinkIonCfgIter;

} /* namespace apollo */

 #endif /* apollo_linkioncfgiter_hpp_ */

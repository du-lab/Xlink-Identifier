/**
 * @file    intralinkioncfgiter.hpp
 * @brief   Iterator for intralinked ion configurations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/08/19
 * @copyright 2013
 */

#ifndef apollo_intralinkioncfgiter_hpp_
#define apollo_intralinkioncfgiter_hpp_

#include "intralinkioncfggen.hpp"
#include "../core/generatoriterator.hpp"

namespace apollo {

typedef GeneratorIterator<IntralinkIonCfgGen> IntralinkIonCfgIter;


} /* namespace apollo */

#endif // apollo_intralinkioncfgiter_hpp_

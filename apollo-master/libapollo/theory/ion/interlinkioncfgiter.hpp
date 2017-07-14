/**
 * @file    intralinkioncfgiter.hpp
 * @brief   Iterator for intralinked ion configurations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/08/19
 * @copyright 2013
 */

#ifndef apollo_interlinkioncfgiter_hpp_
#define apollo_interlinkioncfgiter_hpp_


#include "interlinkioncfggen.hpp"
#include "../core/generatoriterator.hpp"


namespace apollo {

typedef GeneratorIterator<InterlinkIonCfgGen> InterlinkIonCfgIter;

} /* namespace apollo */

#endif // apollo_interlinkioncfgiter_hpp_

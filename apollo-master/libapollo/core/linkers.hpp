/**
 * @file    linkers.hpp
 * @brief   Compile time linkers
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/16
 * @copyright 2012
 */

#ifndef apollo_linkers_hpp_
#define apollo_linkers_hpp_

#include "linkermap.hpp"

namespace apollo {


/**
 *	A map (string->linker::shp) of compiletime linkers 
 *
 */
extern const LinkerMap LinkersMap;

} /* namespace apollo */
#endif /* apollo_regexdigest_hpp_ */

/**
 * @file    linkermap.hpp
 * @brief   Defines a map of string->regex
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/16
 * @copyright 2012
 */

#ifndef apollo_linkermap_hpp_
#define apollo_linkermap_hpp_

#include <boost/container/flat_map.hpp>
#include "linker.hpp"

namespace apollo {


/**
 *	A typedef of string->linker::shp
 */
typedef std::map<types::io_string_t,
    Linker::shp> LinkerMap;

} /* namespace apollo */
#endif /* apollo_linkermap_hpp_ */

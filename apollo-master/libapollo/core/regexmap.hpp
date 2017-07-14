/**
 * @file    regexmap.hpp
 * @brief   Defines a map of string->regex
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */

#ifndef apollo_regexmap_hpp_
#define apollo_regexmap_hpp_

#include <boost/container/flat_map.hpp>
#include "types.hpp"

namespace apollo {

/**
 *	A map between a name and the regular expression it represents
 */
typedef std::map<types::io_string_t,
    types::regex_t> RegexMap;

} /* namespace apollo */
#endif /* apollo_regexmap_hpp_ */

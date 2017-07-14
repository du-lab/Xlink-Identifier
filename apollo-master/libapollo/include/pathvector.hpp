/**
 * @file    pathvector.hpp
 * @brief   Functions to make paths from strings and to expand directories
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/07
 * @copyright 2012
 */

#ifndef apollo_pathvector_hpp_
#define apollo_pathvector_hpp_

#include <string>
#include <vector>

#include <boost/container/flat_set.hpp>
#include <boost/filesystem.hpp>

namespace apollo {

typedef std::vector<boost::filesystem::path> PathVector;

typedef boost::container::flat_set<std::string> ExtensionSet;

namespace fn {

PathVector make_PathVector(std::vector<std::string> const &stringVector);

PathVector expandPaths(PathVector const &pVector, 
    ExtensionSet const &allowedExtensions);

} /* namespace fn */
} /* namespace apollo */

#endif /* apollo_pathvector_hpp_ */

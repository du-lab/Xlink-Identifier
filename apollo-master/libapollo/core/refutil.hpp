/**
 * @file    refutil.hpp
 * @brief   A set of functions to define working with references
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/17
 * @copyright 2012
 */

#ifndef apollo_refutil_hpp_
#define apollo_refutil_hpp_

#include <functional>

namespace std {

/**
 * Adds an == operator for reference wrapper objects, otherwise 
 	we get some unbearably stupid compiler errors
 */
template<typename T>
bool operator==(std::reference_wrapper<T> const &lhs,
    std::reference_wrapper<T> const &rhs) {

	// Check if pointers match first, then check if the actual object matches
	if (
		(&lhs.get() == &rhs.get()) || 
		(lhs.get() == rhs.get())
		) {
		return true;
	} else {
		return false;
	}
}

} /* namespace std */

#endif /* apollo_refutil_hpp_ */

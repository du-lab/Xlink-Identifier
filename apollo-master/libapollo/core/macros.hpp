/*
 * macros.hpp
 *
 * Created on: May 23, 2012
 *      Author: Adam Baxter
 *
*/

#ifndef apollo_macros_hpp_
#define apollo_macros_hpp_

/**
 * A cross-platform macro to define depreciation status
 * of functions
 */
#ifdef __GNUC__
#define DEPRECATED(func) func __attribute__ ((deprecated))
#elif defined(_MSC_VER)
#define DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
#endif

/**
 * Make BOOST_FOREACH much less ugly
 */
#define _foreach         BOOST_FOREACH
#define _rforeach BOOST_REVERSE_FOREACH

 #endif /* apollo_macros_hpp_ */

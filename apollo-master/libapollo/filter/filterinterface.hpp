/**
 * @file    filterinterface.hpp
 * @brief   A simple interface for filters to use
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/23
 * @copyright 2012
 */

 #ifndef apollo_filterinterface_hpp_
 #define apollo_filterinterface_hpp_

#include <functional>

namespace apollo {

namespace filter {

template <typename T>
class FilterI {
public:
	typedef T filter_type;

	typedef std::reference_wrapper<FilterI<T> > ref;
	
    typedef std::reference_wrapper<FilterI<T> const > cref;

	virtual bool operator()(filter_type const &value) const = 0;

	virtual ~FilterI() {}
};

} /* namespace filet */
} /* namespace apollo */

 #endif /* apollo_filterinterface_hpp_ */

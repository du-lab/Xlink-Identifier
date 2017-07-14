/**
 * @file    f_modcount.hpp
 * @brief   Predicates for filtering mod counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#ifndef apollo_filter_modcount_hpp_
#define apollo_filter_modcount_hpp_

#include "filterinterface.hpp"
#include "residuecount.hpp"

namespace apollo {

namespace filter {

class range_ModCount : public FilterI<ResidueCount> {
public:
	typedef filter_type::mapped_type count_t;

	range_ModCount() : _upperCount(-1), _lowerCount(0) {}

	range_ModCount(count_t upperCount, count_t lowerCount = 0) :
		_upperCount(upperCount), _lowerCount(lowerCount) {}

	bool operator()(filter_type const &modCount) const;

    ~range_ModCount() {}
private:	
    count_t _upperCount;
    count_t _lowerCount;
};

} /* namespace filter */
} /* namespace apollo */

#endif /* apollo_modcount_hpp_ */

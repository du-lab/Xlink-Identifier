/**
 * @file    f_multimodcount.hpp
 * @brief   Predicates for filtering multi mod counts
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/30
 * @copyright 2012
 */
#ifndef apollo_filter_multimodcount_hpp_
#define apollo_filter_multimodcount_hpp_

#include "../core/multirefresiduecount.hpp"
#include "filterinterface.hpp"

namespace apollo {
namespace filter {

class range_MultiModCount : public FilterI<MultiRefResidueCount> {
public:
    typedef ResidueCount range_type;

    range_MultiModCount() {}

    range_MultiModCount(range_type upperRange, range_type lowerRange = range_type()) :
        _upperRange(upperRange), _lowerRange(lowerRange) {}

    bool operator()(filter_type const &multiModCount) const;

    ~range_MultiModCount() {}
private:    
    range_type _upperRange;
    range_type _lowerRange;
};

} /* namespace filter */
} /* namespace apollo */


#endif /* apollo_filter_multimodcount_hpp_ */

/**
 * @file    f_mz.hpp
 * @brief   A filter for use when iterating through masses using 
 *  an mz range as a determinant
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/21
 * @copyright 2012
 */

#ifndef apollo_filter_mz_hpp_
#define apollo_filter_mz_hpp_

#include "filterinterface.hpp"
#include "types.hpp"
#include "theorytypes.hpp"

namespace apollo {

namespace filter {

class range_Mz : public FilterI<types::mz_t> {
public:
    range_Mz() {}

    range_Mz(types::mz_t lowerMh, types::mz_t upperMh) :
        _lowerMh(lowerMh), _upperMh(upperMh) {}

    bool operator()(filter_type const &theoreticalMh) const;

    types::mz_t lower() const;

    types::mz_t upper() const;

    Box1D toBox() const;

    static range_Mz FromMhAndTolerance(types::mz_t const mh, types::mz_t const tolerance);

    static range_Mz FromPpm(types::mz_t const mh, types::ppm_t const ppm);

    ~range_Mz() {}
private:
    types::mz_t _lowerMh;
    types::mz_t _upperMh;
};

} /* namespace filter */
} /* namespace apollo */

#endif /* apollo_filter_mz_hpp_ */

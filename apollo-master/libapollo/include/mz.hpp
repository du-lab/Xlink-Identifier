/**
 * @file    mz.hpp
 * @brief   Simple interface for charged mass related calculations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/30
 * @copyright 2012
 */

#ifndef apollo_mz_hpp_
#define apollo_mz_hpp_

#include <ostream>
#include <boost/operators.hpp>
#include "units.hpp"
#include "types.hpp"
#include "../core/stdcharge.hpp"

namespace apollo {

class Mz : 
    boost::equality_comparable1<Mz>, 
    boost::equality_comparable2<Mz, types::mz_t>,
    boost::less_than_comparable1<Mz>,
    boost::less_than_comparable2<Mz, types::mz_t> {
public:

    Mz();

    Mz(types::mass_store_t m, types::charge_store_t z = 1);

    Mz(types::dalton_t m, types::charge_t z = stdcharge::singleCharge);

    Mz(types::mz_t mz, types::charge_t z = stdcharge::singleCharge);

    types::mz_t mz() const;

    types::charge_t z() const;

    types::dalton_t m() const;

    static Mz Mh(Mz const &mz);

    static types::mz_t MhFromM(types::dalton_t const m_da);

    static types::dalton_t MFromMh(types::mz_t const mh);

    // Special Photoprobe calculation where different charge calculations are required
    static Mz MzFromPhoto(types::dalton_t m_da, types::charge_t z);

    /* Comparison operators */
    bool operator<(Mz const &rhs) const;

    bool operator<(types::mz_t const &rhs) const;

    bool operator>(types::mz_t const &rhs) const;

    bool operator==(Mz const &rhs) const;

    bool operator==(types::mz_t const rhs) const;


private:
    types::mz_t _mz;
    types::charge_t _z;

    static types::mz_t mzFromMAndZ(types::dalton_t const m, types::charge_t const z);

    static types::dalton_t mFromMz(types::mz_t const mz, types::charge_t const z);

};


std::ostream& operator<<(std::ostream &out, Mz const &mz);

} /* namespace apollo */
#endif /* apollo_mz_hpp_ */

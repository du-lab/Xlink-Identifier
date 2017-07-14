/**
 * @file    mz.cpp
 * @brief   Simple interface for charged mass related calculations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/30
 * @copyright 2012
 */

#include "../core/stdmass.hpp"
#include "mz.hpp"

namespace apollo {
using units::mass_charge;
using units::charge;
using units::dalton_mass;
using types::count_t;
using types::charge_t;
using types::dalton_t;
using types::mz_t;

const charge_t singleCharge(1 * charge);

Mz::Mz() : _mz(0 * mass_charge), _z(0 * charge) {}

Mz::Mz(types::mass_store_t m, types::charge_store_t z) :
    _mz(mzFromMAndZ(m * dalton_mass, z * charge)), _z(z * charge) {}

Mz::Mz(dalton_t m, charge_t z) :
    _mz(mzFromMAndZ(m, z)), _z(z) {} 

Mz::Mz(mz_t mz, charge_t z) :
    _mz(mz), _z(z) {}

mz_t Mz::mz() const {
    return _mz;
}

charge_t Mz::z() const {
    return _z;
}

dalton_t Mz::m() const {
    return mFromMz(mz(), z());
}

Mz Mz::Mh(Mz const &mz) {
    return Mz(mz.m(), singleCharge);
}

mz_t Mz::MhFromM(dalton_t const m) {
    return mzFromMAndZ(m, singleCharge);
}

dalton_t Mz::MFromMh(mz_t const mh) {
    return mFromMz(mh, singleCharge);
}

Mz Mz::MzFromPhoto(types::dalton_t m_da, types::charge_t z) {
    using apollo::stdmass::H_da;

    count_t zCount(z.value() - 1);

    mz_t mz = ((m_da + dalton_t(zCount * H_da)) / z);
    return Mz(mz, z);
}

/* Comparison operators */
bool Mz::operator<(Mz const &rhs) const {
    return (_mz < rhs._mz);
}

bool Mz::operator<(mz_t const &rhs) const {
    return (_mz < rhs);
}

bool Mz::operator>(mz_t const &rhs) const {
    return (_mz > rhs);
}

bool Mz::operator==(Mz const &rhs) const {
    return (_mz == rhs._mz);
}

bool Mz::operator==(mz_t const rhs) const {
    return (_mz == rhs);
}

mz_t Mz::mzFromMAndZ(dalton_t m, charge_t z) {
    using apollo::stdmass::H_da;

    return (
        ( m + dalton_t(count_t(z.value()) * H_da))
            /z);
}

dalton_t Mz::mFromMz(mz_t const mz, charge_t const z) {
    using apollo::stdmass::H_da;
    return (
        dalton_t(mz * z) - dalton_t(count_t(z.value()) * H_da)
        );
}

std::ostream& operator<<(std::ostream &out, Mz const &mz) {
    out << mz.mz().value() << "(" << mz.z() << ")";
    return out;
}

} /* namespace apollo */

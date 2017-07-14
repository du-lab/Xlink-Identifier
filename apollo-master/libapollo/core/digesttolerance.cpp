/**
 * @file    digesttolerance.cpp
 * @brief   Codifies theoretical digest tolerance rules
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */
 #include "digesttolerance.hpp"

namespace apollo {

namespace validation {

bool DigestTolerance::withinTolerance(size_type const length, size_type const nmc) const {
    // Return true only if it's juuuuust right
    return (!isTooSmall(length) && !isTooLarge(length, nmc));
}

bool DigestTolerance::isTooSmall(size_type const length) const {
    return (length < _minLength);
}

bool DigestTolerance::isTooLarge(size_type const length, size_type const nmc) const {
    /// This check is to let large peptides with no missed cleavages pass
    /// the maxLength check. Currently Dr. Du wants this disabled
    /*
    if ((length > _maxLength) && (nmc == 0)) {
        return false;
    }
    */
    if ((length < _maxLength) && (nmc < _maxNmc)) {
        return false;
    } else {
        return true;
    }
}

bool DigestTolerance::operator==(DigestTolerance const &other) const {
    return (
        (_minLength == other._minLength) &&
        (_maxLength == other._maxLength) &&
        (_maxNmc == other._maxNmc)
        );
}

std::ostream& operator<<(std::ostream &out, DigestTolerance const &rhs) {
    out << "Length:[" << rhs._minLength << "-" << rhs._maxLength << ")" <<
    ", NMC:[0-" << rhs._maxNmc << ")";
    return out;
}

} /* namespace validation */
} /* namespace apollo */

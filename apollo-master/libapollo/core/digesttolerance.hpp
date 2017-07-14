/**
 * @file    digesttolerance.hpp
 * @brief   Codifies theoretical digest tolerance rules
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */

#ifndef apollo_digesttolerance_hpp_
#define apollo_digesttolerance_hpp_

#include <ostream>
#include "sequenceinterface.hpp"

namespace apollo {

namespace validation {

/** 
 *  @class  DigestTolerance digesttolerance.hpp "digesttolerance.hpp"
 *  @brief  A helper class that determines if a the proposed digestion
 *      peptide is within acceptable tolernace.
 */
class DigestTolerance {
public:
    typedef SequenceI::size_type size_type;

    /**
     *  Constructor
     *
     *  @param[in] minLength  The peptide is acceptable if its length is >= minLength
     *  @param[in] maxLength  The peptide is acceptable if its length is < maxLength
     *  @param[in] maxNmc     The peptide is acceptable if its number of missed cleavages
            is < maxNmc
     */
    DigestTolerance(size_type minLength = 6, size_type maxLength = 31,
        size_type maxNmc = 4) :
        _minLength(minLength), _maxLength(maxLength),
        _maxNmc(maxNmc) {}
    

    /**
     * Check if proposed peptide length and nmc is within the allowed tolerance
     * 
     *  @param[in] length  The length of the digested peptide
     *  @parem[in] nmc     The number of missed cleavages of the digest peptide
     *
     *  @return True if _minLength <= length < _maxLength && nmc < _maxNmc, otherwise false
     */
    bool withinTolerance(size_type const length, size_type const nmc) const;

    /**
     * Check if proposed peptide length is too small
     *
     *  @param[in] length  The length of the digested peptide
     *
     *  @return True if length < _minLength
     */
    bool isTooSmall(size_type const length) const;

    /**
     * Check if proposed peptide length and nmc is too large
     *
     *  @param[in] length  The length of the digested peptide
     *  @param[in] nmc     The number of missed cleavages of the digested peptide
     *
     *  @return  True if length >= _maxLength || nmc >= _maxNmc
     */
    bool isTooLarge(size_type const length, size_type const nmc) const;

    bool operator==(DigestTolerance const &other) const;

    friend std::ostream& operator<<(std::ostream &out, DigestTolerance const &rhs);

    ~DigestTolerance() {}
private:
    size_type _minLength;
    size_type _maxLength;
    size_type _maxNmc;
};

} /* namespace validation */
} /* namespace apollo */
#endif /* apollo_digesttolerance_hpp_ */

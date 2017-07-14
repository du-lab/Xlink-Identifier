/**
 * @file    fullytrypticgen.hpp
 * @brief   Generator for fully tryptic theoretical digestion
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */

#ifndef apollo_fullytrypticgen_hpp_
#define apollo_fullytrypticgen_hpp_

#include <utility>

#include "sequenceinterface.hpp"
#include "../core/generator.hpp"
#include "../core/digesttolerance.hpp"

namespace apollo {

class FullyTrypticGen : public Generator<SequenceI::shp> {
public:
    typedef SequenceI::size_type size_type;

    typedef types::regex_t regex_type;

    typedef types::regex_it_t regex_iter_type;

    typedef SequenceI::shp_deque deque_type;

    typedef validation::DigestTolerance tolerance_type;

    FullyTrypticGen() : _super() {}

    FullyTrypticGen(SequenceI::shp parentShp,
        regex_type const digestRegex,
        tolerance_type tolerance = tolerance_type());

    FullyTrypticGen(FullyTrypticGen const &rhs);

    FullyTrypticGen(FullyTrypticGen &&rhs);

    FullyTrypticGen& operator=(FullyTrypticGen const &rhs);

    FullyTrypticGen& operator=(FullyTrypticGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(FullyTrypticGen const &rhs) const;

    ~FullyTrypticGen() {}
private:
    typedef Generator<SequenceI::shp> _super;
    size_type _currentLength;
    size_type _currentNmc;
    tolerance_type _tolerance;
    deque_type::const_iterator _digestIter;
    deque_type _digestDeq;


    SequenceI::shp genReturn() const;
};

} /* namespace apollo */

#endif  /* apollo_fullytrypticgen_hpp_ */

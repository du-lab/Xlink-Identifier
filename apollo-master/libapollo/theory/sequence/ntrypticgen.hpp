/**
 * @file    ntrypticgen.hpp
 * @brief   Generator for n tryptic theoretical digestion
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/16
 * @copyright 2012
 */

#ifndef apollo_ntrypticgen_hpp_
#define apollo_ntrypticgen_hpp_

#include <utility>

#include <boost/container/flat_set.hpp>

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "../core/generator.hpp"
#include "../core/digesttolerance.hpp"


namespace apollo {

class NTrypticGen : public Generator<SequenceI::shp> {
public:
    typedef SequenceI::size_type size_type;

    typedef types::regex_t regex_type;

    typedef types::regex_it_t regex_iter_type;

    typedef validation::DigestTolerance tolerance_type;

    NTrypticGen() : _super() {}

    NTrypticGen(SequenceI::shp parentShp,
        size_type trypticity,
        regex_type const digestRegex,
        tolerance_type tolerance = tolerance_type());

    NTrypticGen(NTrypticGen const &other);

    NTrypticGen(NTrypticGen &&other);

    NTrypticGen& operator=(NTrypticGen const &other);

    NTrypticGen& operator=(NTrypticGen &&other);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(NTrypticGen const &other) const;

    ~NTrypticGen() {}
private:
    typedef Generator<SequenceI::shp> _super;
    typedef boost::container::flat_set<size_type> PositionSet;
    static const bool Nh2TerminusIsTryptic = true;
    static const bool CTerminusIsTryptic = true;
    size_type _currentLength;
    size_type _currentNmc;
    tolerance_type _tolerance;
    SequenceI::shp _parentShp;
    size_type _trypticity;
    size_type _currentTrypticity;
    PositionSet _trypticPositions;
    size_type _first;
    size_type _last;

    bool firstIsTryptic() const;
    bool lastIsTryptic() const;
    SequenceI::shp genReturn() const;

};

} /* namespace apollo */

#endif /* apollo_ntrypticgen_hpp_ */

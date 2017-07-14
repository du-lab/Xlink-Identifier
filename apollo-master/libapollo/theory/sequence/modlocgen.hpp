/**
 * @file    modlocgen.hpp
 * @brief   Generates all possible dynamic modification locations
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/12/21
 * @copyright 2012
 */


#ifndef apollo_modlocgen_hpp
#define apollo_modlocgen_hpp

#include "types.hpp"
#include "sequenceinterface.hpp"
#include "residueset.hpp"

#include "../core/generator.hpp"
#include "../core/locset.hpp"

namespace apollo {

class ModLocGen : public Generator<LocSet> {

public:
    ModLocGen() : _super() {}

    ModLocGen(SequenceI const &seq, types::count_t locCount, ResidueSet const &rSet);

    ModLocGen(ModLocGen const &rhs);

    ModLocGen(ModLocGen &&rhs);

    ModLocGen& operator=(ModLocGen const &rhs);

    ModLocGen& operator=(ModLocGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(ModLocGen const &rhs) const;

    ~ModLocGen() {}

private:
    typedef Generator<LocSet> _super;
    types::count_t _locCount;
    LocSet _locations;

    LocSet genReturn() const;
};

} /* namespace apollo */
#endif /* apollo_modlocgen_hpp */

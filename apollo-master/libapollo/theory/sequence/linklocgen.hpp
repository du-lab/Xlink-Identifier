/**
 * @file    linklocgen.hpp
 * @brief   A generator to a linker's locations on a sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/07
 * @copyright 2013
 */


#ifndef apollo_linklocgen_hpp_
#define apollo_linklocgen_hpp_

#include "enums.hpp"
#include "sequenceinterface.hpp"
#include "linkloc.hpp"

#include "../../core/linker.hpp"
#include "../../core/generator.hpp"

namespace apollo {

class LinkLocGen : public Generator<LinkLoc> {
public:

    LinkLocGen() : _super() {}

    LinkLocGen(Linker::shp linkerShp,
        SequenceI::shp seqShp,
        enums::LinkerConfig linkerConfig);

    LinkLocGen(LinkLocGen const &rhs);

    LinkLocGen(LinkLocGen &&rhs);

    LinkLocGen operator=(LinkLocGen const &rhs);

    LinkLocGen operator=(LinkLocGen &&rhs);

    bool operator()(value_type &rv);

    void generate(value_type &rv) const;

    bool operator==(LinkLocGen const &rhs) const;

    ~LinkLocGen() {}
private:
    typedef Generator<LinkLoc> _super;

    enum LinkState {Unlinked, Nh2Term, CTerm, Loc};

    Linker::shp _linkerShp;
    SequenceI::shp _seqShp;
    enums::LinkerConfig _linkerConfig;
    SequenceI::const_iterator _seqPos;
    LinkState _state;

    value_type genReturn() const;
};

} /* namespace apollo */

#endif /* apollo_linklocgen_hpp_ */

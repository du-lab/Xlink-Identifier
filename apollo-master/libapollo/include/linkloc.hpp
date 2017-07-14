/**
 * @file    linkloc.hpp
 * @brief   A representation of the linker's location
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2013/01/07
 * @copyright 2013
 */


#ifndef apollo_linkloc_hpp_
#define apollo_linkloc_hpp_

#include <ostream>

#include "sequenceinterface.hpp"

namespace apollo {

class LinkLoc {
public:
    typedef SequenceI::size_type value_type;

    LinkLoc();

    LinkLoc(LinkLoc const &rhs);

    LinkLoc operator=(LinkLoc const &rhs);

    bool isUnlinked() const;

    bool isTermLinked() const;

    bool isNh2TerminusLinked() const;

    bool isCTerminusLinked() const;

    value_type loc() const;

    bool operator==(LinkLoc const &rhs) const;

    friend std::ostream& operator<<(std::ostream &out, LinkLoc const &rhs);

    static LinkLoc Unlinked();

    static LinkLoc OnNh2Terminus();

    static LinkLoc OnCTerminus();

    static LinkLoc OnPosition(value_type pos);

private:
    value_type _loc;
    
    LinkLoc(value_type pos);

    static value_type const Nh2Loc;

    static value_type const CLoc;

    static value_type const UnlinkedLoc;
};

} /* namespace apollo */
#endif /* apollo_linkloc_hpp_ */
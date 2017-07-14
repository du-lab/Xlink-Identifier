/**
 * @file    linker.hpp
 * @brief   Theoretical linker
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/18
 * @copyright 2012
 */

#ifndef apollo_linker_hpp_
#define apollo_linker_hpp_

#include <functional>
#include <memory>
#include <ostream>
#include <vector>

#include <boost/utility.hpp>

#include "types.hpp"
#include "reactiongroup.hpp"
#include "intrareactiongroup.hpp"

namespace apollo {


/**
 * @class Linker linker.hpp "linker.hpp"
 *  Represents a proteomics linker and its reaction groups
 */
class Linker : boost::noncopyable {
public:

    /**
     * Std shared pointer for the linker
     */
    typedef std::shared_ptr<Linker> shp;

    /**
     * Vector of linker shared pointers
     */
    typedef std::vector<Linker::shp> shp_vec;

    /**
     * Constant reference to a linker
     */
    typedef std::reference_wrapper<Linker const> cref; 

    // default ctor
    Linker() {}

    /**
     * Linker constructor
     *
     *  @param[in] name             The linker's name
     *  @param[in] canInterlink     Whether or not the linker can interlink
     *  @param[in] interlinkedMass  The mass of the linker if it interlinks
     *  @param[in] canIntralink     Whether or not the linker can intralink
     *  @param[in] intralinkedMass  The mass of the linker if it intralinks
     *  @param[in] canDeadend       Whether or not the linker can deadend
     *  @param[in] deadendMass      The mass of the linker if it deadends
     *  @param[in] group1           The first reaction group
     *  @param[in] group2           The second reaction group
     *
     *  @note The order of the reaction groups does not matter
     */
    Linker(types::io_string_t name,
        types::residue_t symbol,
        bool canInterlink, types::dalton_t interlinkedMass,
        bool canIntralink, types::dalton_t intralinkedMass,
        bool canDeadend, types::dalton_t deadendMass,
        ReactionGroup group1, 
        ReactionGroup group2);

    /**
     * returns the Linker's name
     */
    types::io_string_t const& name() const;

    types::residue_t symbol() const;

    /**
     * Whether or not the linker can interlink
     */
    bool canInterlink() const;

    /**
     * The linker's mass if it interlinks
     */
    types::dalton_t interlinkedMass() const;

    /**
     * Whether or not the linker can intralink
     */
    bool canIntralink() const;

    /**
     * The linker's mass if it intralinks
     */
    types::dalton_t intralinkedMass() const;

    /**
     * Whether or not the linker can deadend
     */
    bool canDeadend() const;

    /** 
     * The linker's mass if it deadends
     */
    types::dalton_t deadendMass() const;

    /**
     * The linker's first reaction group
     */
    ReactionGroup const& group1() const;

    /**
     * The linker's second reaction group 
     */
    ReactionGroup const& group2() const;

    /**
     * The reaction group used to test intralinking
     */
    ReactionGroup const& intraGroup() const;

    ~Linker() {}
private:
    types::io_string_t _name;
    types::residue_t _symbol;
    bool _canInterlink;
    types::dalton_t _interlinkedMass;
    bool _canIntralink;
    types::dalton_t _intralinkedMass;
    bool _canDeadend;
    types::dalton_t _deadendMass;
    ReactionGroup _group1;
    ReactionGroup _group2;
    IntraReactionGroup _intraGroup;
};

std::ostream& operator<<(std::ostream &out, Linker const &rhs);

} /* namespace apollo */

#endif /* apollo_linker_hpp_ */

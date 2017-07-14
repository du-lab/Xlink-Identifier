/**
 * @file    stdmass.cpp
 * @brief   Define residue mass maps
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#include <boost/assign/list_of.hpp>

#include "stdmass.hpp"

namespace apollo {

namespace stdmass {

namespace residue {
using types::dalton_t;
using units::dalton_mass;
using namespace boost::assign;

ResidueMass const AvgMap_da =
    map_list_of
    ('G', dalton_t(57.05136 * dalton_mass))
    ('A', dalton_t(71.07794 * dalton_mass))
    ('S', dalton_t(87.07734 * dalton_mass))
    ('P', dalton_t(97.11522 * dalton_mass))
    ('V', dalton_t(99.1311 * dalton_mass))
    ('T', dalton_t(101.10392 * dalton_mass))
    ('C', dalton_t(103.14394 * dalton_mass))
    ('L', dalton_t(113.15768 * dalton_mass))
    ('I', dalton_t(113.15768 * dalton_mass))
    ('N', dalton_t(114.10272 * dalton_mass))
    ('D', dalton_t(115.08744 * dalton_mass))
    ('Q', dalton_t(128.1293 * dalton_mass))
    ('K', dalton_t(128.17236 * dalton_mass))
    ('E', dalton_t(129.11402 * dalton_mass))
    ('M', dalton_t(131.1971 * dalton_mass))
    ('H', dalton_t(137.1394 * dalton_mass))
    ('F', dalton_t(147.1739 * dalton_mass))
    ('R', dalton_t(156.18584 * dalton_mass))
    ('Y', dalton_t(163.1733 * dalton_mass))
    ('W', dalton_t(186.20998 * dalton_mass))
    ('g', dalton_t(57.05136 * dalton_mass)) // lower case in some scenarios
    ('a', dalton_t(71.07794 * dalton_mass))
    ('s', dalton_t(87.07734 * dalton_mass))
    ('p', dalton_t(97.11522 * dalton_mass))
    ('v', dalton_t(99.1311 * dalton_mass))
    ('t', dalton_t(101.10392 * dalton_mass))
    ('c', dalton_t(103.14394 * dalton_mass))
    ('l', dalton_t(113.15768 * dalton_mass))
    ('i', dalton_t(113.15768 * dalton_mass))
    ('n', dalton_t(114.10272 * dalton_mass))
    ('d', dalton_t(115.08744 * dalton_mass))
    ('q', dalton_t(128.1293 * dalton_mass))
    ('k', dalton_t(128.17236 * dalton_mass))
    ('e', dalton_t(129.11402 * dalton_mass))
    ('m', dalton_t(131.1971 * dalton_mass))
    ('h', dalton_t(137.1394 * dalton_mass))
    ('f', dalton_t(147.1739 * dalton_mass))
    ('r', dalton_t(156.18584 * dalton_mass))
    ('y', dalton_t(163.1733 * dalton_mass))
    ('w', dalton_t(186.20998 * dalton_mass));

ResidueMass const MonoisotopicMap_da =
    // map_list_of
    // ('G', dalton_t(57.02146 * dalton_mass))
    // ('A', dalton_t(71.03711 * dalton_mass))
    // ('S', dalton_t(87.03203 * dalton_mass))
    // ('P', dalton_t(97.05276 * dalton_mass))
    // ('V', dalton_t(99.06841 * dalton_mass))
    // ('T', dalton_t(101.04768 * dalton_mass))
    // ('C', dalton_t(103.00918 * dalton_mass))
    // ('L', dalton_t(113.08406 * dalton_mass))
    // ('I', dalton_t(113.08406 * dalton_mass))
    // ('N', dalton_t(114.04293 * dalton_mass))
    // ('D', dalton_t(115.02694 * dalton_mass))
    // ('Q', dalton_t(128.05857 * dalton_mass))
    // ('K', dalton_t(128.09496 * dalton_mass))
    // ('E', dalton_t(129.04259 * dalton_mass))
    // ('M', dalton_t(131.04048 * dalton_mass))
    // ('H', dalton_t(137.05891 * dalton_mass))
    // ('F', dalton_t(147.06841 * dalton_mass))
    // ('R', dalton_t(156.10111 * dalton_mass))
    // ('Y', dalton_t(163.06333 * dalton_mass))
    // ('W', dalton_t(186.07931 * dalton_mass))
    // ('g', dalton_t(57.02146 * dalton_mass)) // lower case in some scenarios
    // ('a', dalton_t(71.03711 * dalton_mass))
    // ('s', dalton_t(87.03203 * dalton_mass))
    // ('p', dalton_t(97.05276 * dalton_mass))
    // ('v', dalton_t(99.06841 * dalton_mass))
    // ('t', dalton_t(101.04768 * dalton_mass))
    // ('c', dalton_t(103.00918 * dalton_mass))
    // ('l', dalton_t(113.08406 * dalton_mass))
    // ('i', dalton_t(113.08406 * dalton_mass))
    // ('n', dalton_t(114.04293 * dalton_mass))
    // ('d', dalton_t(115.02694 * dalton_mass))
    // ('q', dalton_t(128.05857 * dalton_mass))
    // ('k', dalton_t(128.09496 * dalton_mass))
    // ('e', dalton_t(129.04259 * dalton_mass))
    // ('m', dalton_t(131.04048 * dalton_mass))
    // ('h', dalton_t(137.05891 * dalton_mass))
    // ('f', dalton_t(147.06841 * dalton_mass))
    // ('r', dalton_t(156.10111 * dalton_mass))
    // ('y', dalton_t(163.06333 * dalton_mass))
    // ('w', dalton_t(186.07931 * dalton_mass));

    map_list_of
    ('G', dalton_t(57.02146 * dalton_mass))
    ('A', dalton_t(71.03711 * dalton_mass))
    ('S', dalton_t(87.03203 * dalton_mass))
    ('P', dalton_t(97.05276 * dalton_mass))
    ('V', dalton_t(99.06841 * dalton_mass))
    ('T', dalton_t(101.04768 * dalton_mass))
    ('C', dalton_t(103.00918 * dalton_mass))
    ('L', dalton_t(113.08406 * dalton_mass))
    ('I', dalton_t(113.08406 * dalton_mass))
    ('N', dalton_t(114.04293 * dalton_mass))
    ('D', dalton_t(115.02694 * dalton_mass))
    ('Q', dalton_t(128.05857 * dalton_mass))
    ('K', dalton_t(128.09496 * dalton_mass))
    ('E', dalton_t(129.04259 * dalton_mass))
    ('M', dalton_t(131.04048 * dalton_mass))
    ('H', dalton_t(137.05891 * dalton_mass))
    ('F', dalton_t(147.06841 * dalton_mass))
    ('R', dalton_t(156.10111 * dalton_mass))
    ('Y', dalton_t(163.06333 * dalton_mass))
    ('W', dalton_t(186.07931 * dalton_mass))
    ('g', dalton_t(57.02146 * dalton_mass)) // lower case in some scenarios
    ('a', dalton_t(71.03711 * dalton_mass))
    ('s', dalton_t(167.002 * dalton_mass))  // phosphorylation
    ('p', dalton_t(97.05276 * dalton_mass))
    ('v', dalton_t(99.06841 * dalton_mass))
    ('t', dalton_t(181.0177 * dalton_mass)) // phosphorylation
    ('c', dalton_t(103.00918 * dalton_mass))
    ('l', dalton_t(113.08406 * dalton_mass))
    ('i', dalton_t(113.08406 * dalton_mass))
    ('n', dalton_t(114.04293 * dalton_mass))
    ('d', dalton_t(115.02694 * dalton_mass))
    ('q', dalton_t(128.05857 * dalton_mass))
    ('k', dalton_t(128.09496 * dalton_mass))
    ('e', dalton_t(129.04259 * dalton_mass))
    ('m', dalton_t(147.0305 * dalton_mass)) // oxidation
    ('h', dalton_t(137.05891 * dalton_mass))
    ('f', dalton_t(147.06841 * dalton_mass))
    ('r', dalton_t(156.10111 * dalton_mass))
    ('y', dalton_t(243.0333 * dalton_mass)) // phosphorylation
    ('w', dalton_t(186.07931 * dalton_mass));

} /* namespace residue */
} /* namespace stdmass */
} /* namespace apollo */

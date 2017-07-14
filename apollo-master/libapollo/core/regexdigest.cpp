/**
 * @file    regexdigest.cpp
 * @brief   Available digests via a regex engine
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/13
 * @copyright 2012
 */

#include <boost/assign/list_of.hpp>
#include "types.hpp"
#include "regexdigest.hpp"

namespace apollo {

using namespace boost::xpressive;
using namespace boost::assign;
using types::regex_t;

// for Trypsin digestion it will cut protien after K or R but if K or R is followed by P you DONT // cut.
regex_t const TrypsinRegex = (set= 'K', 'R') >> ~before('P');

regex_t const ChemoTrypsinRegex = (set= 'Y', 'W', 'F', 'L', 'M') >> ~before('P');

regex_t const GluCRegex = (set= 'D', 'E') >> ~before('P');

// One-off for france photo-crosslinking, since Z doesn't exist
// Sometimes lower case is used in the fasta files.
regex_t const PhotoTrypsinRegex = (set= 'K', 'R', 'k', 'r') >> ~before((set= 'P', 'p'));

RegexMap const DigestRegexMap =
    map_list_of
    ("trypsin", TrypsinRegex)
    ("chemotrypsin", ChemoTrypsinRegex)
    ("gluc", GluCRegex)
    ("photo", PhotoTrypsinRegex);


} /* namespace apollo */

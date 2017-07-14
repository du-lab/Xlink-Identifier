/**
 * @file    sequenceconfig.cpp
 * @brief   Types to represent sequence configuration
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/27
 * @copyright 2012
 */

#include <boost/functional/hash.hpp>

#include "sequenceconfig.hpp"

namespace apollo {

std::ostream& operator<<(std::ostream &out, SequenceConfig const &rhs) {
    using std::get;
    if (!get<1>(rhs).empty()) {
        out << "Static: " << get<1>(rhs);
    }
    if (!get<2>(rhs).empty()) {
        if (!get<1>(rhs).empty()) {
            out << ", ";
        }
        out << "Dynamic: " << get<2>(rhs);
    }
	return out;
}

std::size_t hash_value(SequenceConfig const &sConfig) {
    using std::get;
    std::size_t seed = 0;
    boost::hash_combine(seed, get<0>(sConfig).value());
    boost::hash_combine(seed, get<1>(sConfig));
    boost::hash_combine(seed, get<2>(sConfig));
    return seed;
}

std::ostream& operator<<(std::ostream &out, SequenceMotif const &rhs) {
    out << *(rhs.first) << " " << rhs.second;
	return out;
}

std::size_t hash_value(SequenceMotif const &sMotif) {
    std::size_t seed = 0;
    boost::hash_combine(seed, sMotif.first);
    boost::hash_combine(seed, sMotif.second);
    return seed;
}

} /* namespace apollo */

/**
 * @file    multirefresiduecount.cpp
 * @brief   Defines MultiRefResidueCount
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/24
 * @copyright 2012
 */


#include <boost/functional/hash.hpp>

#include "multirefresiduecount.hpp"

namespace apollo {

std::size_t hash_value(MultiRefResidueCount const &mrCount) {
	return boost::hash_range(mrCount.begin(), mrCount.end());
}

} /* namespace apollo */

std::ostream& operator<<(std::ostream &out, apollo::MultiRefResidueCount const &rhs) {
	using apollo::MultiRefResidueCount;
	for(auto const &mrCountPair : rhs) {
		MultiRefResidueCount::key_type const residue = mrCountPair.first;
		out << "{" << residue << ":" << mrCountPair.second << "}";
	}
	return out;
}

/**
 * @file    dtatypes.hpp
 * @brief   Types returned as a result of the dta read functions
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/30
 * @copyright 2012
 */

#ifndef apollo_dtatypes_hpp_
#define apollo_dtatypes_hpp_

#include <vector>
#include <tuple>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/tr1/tuple.hpp>
#include <boost/container/flat_map.hpp>

#include "types.hpp"
#include "spectrumtypes.hpp"

/**
 * @namespace apollo
 * @brief Apollo library
 */
namespace apollo {

typedef std::tuple<
	types::scanCount_store_t,		// get<0> is scan count
    types::mz_t,                    // get<1> is mh
    types::charge_t,                // get<2> is z
    boost::filesystem::path         // get<3> is the file path
    > DtaDesc;

typedef std::pair<DtaDesc, MzSpectrum> DtaFile;

typedef std::vector<DtaFile> DtaFiles;

} /* namespace apollo */

#endif /* apollo_dtatypes_hpp_ */

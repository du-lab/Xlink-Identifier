/**
 * @file    readdtas.hpp
 * @brief   Reads all dtas into a single data structure
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/15
 * @copyright 2012
 */

#ifndef apollo_readdtas_hpp_
#define apollo_readdtas_hpp_

#include "pathvector.hpp"
#include "../io/dtareader.hpp"
#include "dtatypes.hpp"

#include "ThreadPool.hpp"

namespace apollo {

namespace fn {

typedef std::pair<bool, DtaFile> ParsedDta;

ParsedDta readDtaFile(boost::filesystem::path const &dtaPath);

DtaFiles readDtas(ThreadPool &threadpool,
                  PathVector const &dtaVector);

}
} /* namespace apollo */

#endif /* apollo_readdtas_hpp_ */

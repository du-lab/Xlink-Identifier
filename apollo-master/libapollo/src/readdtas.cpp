/**
 * @file    readdtas.cpp
 * @brief   Reads all dtas into a single data structure
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/15
 * @copyright 2012
 */

#include <vector>
#include <istream>
#include <algorithm>
#include <utility>

#include <boost/log/trivial.hpp>

#include <boost/container/container_fwd.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/xpressive/regex_actions.hpp>

#include "readdtas.hpp"

namespace apollo {

const ExtensionSet dtaExtensions =
    boost::assign::list_of(".dta");


namespace fn {

typedef std::pair<bool, types::scanCount_store_t> ParsedScan;

ParsedScan parseDtaName(boost::filesystem::path const &dtaPath) {
    using std::make_pair;
    using namespace boost::xpressive;
    using types::regex_t;
    using types::scanCount_store_t;

    scanCount_store_t scanNumber = 0;

    regex_t const period = regex_t::compile("\\.");
    regex_t const dtaName = +_ >> period >>
        (s1 = +_d) [ref(scanNumber) = as<scanCount_store_t>(s1)] >>
        period >> s1 >> period >> +_d >> period >> "dta";

    if (regex_match(dtaPath.filename().string(), dtaName)) {
        BOOST_LOG_TRIVIAL(info) << "Scan Number: " << scanNumber;
        return make_pair(true, scanNumber);
    } else {
        BOOST_LOG_TRIVIAL(error) << "Dta File Name Parse Failed: " <<
            dtaPath.string();
        return make_pair(false, scanNumber);
    }
}

typedef std::pair<bool, DtaFile> ParsedDta;

ParsedDta readDtaFile(boost::filesystem::path const &dtaPath) {
    using boost::container::ordered_unique_range;
    using boost::filesystem::ifstream;
    using boost::spirit::ascii::space;
    using std::move;
    using std::make_pair;
    using detail::dta_file;
    using types::scanCount_store_t;

    namespace spirit = boost::spirit;

    dta_reader<spirit::istream_iterator> const reader;

    DtaFile dtaFile;

    ParsedScan parsedScan = parseDtaName(dtaPath);

    if (!parsedScan.first) {
        return make_pair(false, move(dtaFile));
    }

    scanCount_store_t const scanNumber = parsedScan.second;



    ifstream dtaStream(dtaPath);
    // Disable skipping whitespace. Spirit will handle that, instead
    dtaStream.unsetf(std::ios::skipws);

    // Wrap the istream into the spirit istream iterator
    spirit::istream_iterator dtaBegin(dtaStream);
    spirit::istream_iterator dtaEnd;

    dta_file dta;
    bool const parsePassed  = spirit::qi::phrase_parse(dtaBegin, dtaEnd,
        reader, space, dta);
    if (parsePassed) {

        dtaFile.first = DtaDesc(scanNumber, dta.header.mh, dta.header.z, dtaPath);

        /*
         * We expect all dta files to have ordered and unique reads
         * If this expectation is incorrect, add a sort and unique functions
         * to ensure this.
         */
        dtaFile.second = MzSpectrum(ordered_unique_range,
            dta.reads.begin(),
            dta.reads.end());
        return make_pair(true, move(dtaFile));

    } else {
        BOOST_LOG_TRIVIAL(error) <<"Read Failed: " << dtaPath.string();
        return make_pair(false, move(dtaFile));
    }
}

DtaFiles readDtas(ThreadPool &threadpool, PathVector const &dtaVector) {
    using std::sort;
    
    PathVector expandedDVector = fn::expandPaths(dtaVector, dtaExtensions);

    DtaFiles dtaFiles;

    for(PathVector::value_type const &dtaPath : expandedDVector) {

        ParsedDta parsedDta = readDtaFile(dtaPath);
        if (!parsedDta.first) {
            continue;
        }

        dtaFiles.emplace_back(std::move(parsedDta.second));
    }

    std::sort(dtaFiles.begin(), dtaFiles.end());
    return dtaFiles;
}

} /* namespace fn */

} /* namespace apollo */

/**
 * @file    options.hpp
 * @brief   A simple interface to access information in the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/08
 * @copyright 2012
 */

#include <boost/filesystem/fstream.hpp>


#include </usr/local/include/json/json.h>



#include "exceptions.hpp"
#include "options.hpp"

namespace apollo {

types::io_string_t const Options::stdSequenceStr = "std";
types::io_string_t const Options::interlinkSequenceStr = "il";

Options::Options(boost::filesystem::path optionsPath) :
     _optionsPath(optionsPath) {

    using boost::filesystem::ifstream;

    ifstream optionsFile(_optionsPath);

    Json::Value root;
    Json::Reader reader;

    if(!reader.parse(optionsFile, root)) {
        throw boost::enable_error_info(
                    std::range_error("Failed to parse options.json: " +
                                     reader.getFormatedErrorMessages()))
                << boost::errinfo_api_function("Options::Options")
                << boost::errinfo_file_name(optionsPath.string());
    } else {
        try {
        _job = read_JobOptions(root["job"]);
        _digest = read_DigestOptions(root["digestion"]);
        _sequenceOptionsMap = read_SequenceOptionsMap(root["sequence"]);
        _linker = read_LinkerOptions(root["linker"]);
        _analysis = read_AnalysisOptions(root["analysis"]);
        } catch (boost::exception & e) {
            e << boost::errinfo_file_name(optionsPath.string());
            throw;
        }
    }
}

JobOptions const& Options::job() const {
    return _job;
}

DigestOptions const& Options::digest() const {
    return _digest;
}

SequenceOptions const& Options::sequence() const {
    return _sequenceOptionsMap.at(stdSequenceStr);
}

LinkerOptions const& Options::linker() const {
    return _linker;
}

AnalysisOptions const& Options::analysis() const {
    return _analysis;
}

SequenceOptions const& Options::mustInterlinkSequence() const {
    return _sequenceOptionsMap.at(interlinkSequenceStr);
}
} /* namespace apollo */

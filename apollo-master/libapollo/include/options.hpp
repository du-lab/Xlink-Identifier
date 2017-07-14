/**
 * @file    options.hpp
 * @brief   A simple interface to access information in the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/08
 * @copyright 2012
 */

#ifndef apollo_options_hpp_
#define apollo_options_hpp_

#include <string>

#include <boost/filesystem.hpp>
#include <boost/utility.hpp>

#include "../io/optionsreader.hpp"
#include "optiontypes.hpp"

namespace apollo {


class Options : boost::noncopyable {
public:
    Options() {}

    Options(boost::filesystem::path optionsPath);

    JobOptions const& job() const;

    DigestOptions const& digest() const;

    SequenceOptions const& sequence() const;

    LinkerOptions const& linker() const;

    AnalysisOptions const& analysis() const;

    MustInterlinkOptions const& mustInterlink() const;

    SequenceOptions const& mustInterlinkSequence() const;

private:
    static types::io_string_t const stdSequenceStr;
    static types::io_string_t const interlinkSequenceStr;

    boost::filesystem::path _optionsPath;
    JobOptions _job;
    DigestOptions _digest;
    LinkerOptions _linker;
    AnalysisOptions _analysis;
    SequenceOptionsMap _sequenceOptionsMap;
};

} /* namespace apollo */

#endif /* apollo_options_hpp_ */

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <iostream>
#include <string>
#include <vector>


#include <boost/assign/list_of.hpp>

// Handles parsing command line options
#include <boost/program_options.hpp>

// Handles windows and unix file system access
#include <boost/filesystem.hpp>

#include <boost/log/trivial.hpp>

#include "options.hpp"
#include "pathvector.hpp"
#include "readfastas.hpp"
#include "readdtas.hpp"
#include "theory.hpp"
#include "analysis.hpp"
#include "reports.hpp"
#include "stdrun.hpp"
#include "ThreadPool.hpp"
#include "exceptions.hpp"

const std::string versionString = "Apollo 2.0 Beta 2";

// A helper function to simplify the outputing vector<string>.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, "\n")); 
    return os;
}


int main(int argc, char *argv[]) {

    namespace po = boost::program_options;
    using std::cout;
    using std::endl;
    using std::vector;
    using std::string;
    using boost::filesystem::path;
    using apollo::Options;
    using apollo::PathVector;
    using apollo::fn::make_PathVector;
    using apollo::SequenceIdMap;
    using apollo::fn::readFastas;
    using apollo::fn::calcPeptides;
    using apollo::MhSequenceTree;
    using apollo::fn::stdrun;

    const vector<string> defaultFasta =
        boost::assign::list_of("./fasta/");
    vector<string> fastaInput;

    const vector<string> defaultDta =
        boost::assign::list_of("./dta/");
    vector<string> dtaInput;

    const string defaultResults("./results/");
    string resultsDir;
    
    const string defaultOptions("./options.json");
    string optionsFile;

    const string defaultLog("");
    string logOptions;


    po::options_description generic("Generic options");
    generic.add_options()
        ("help,h", "produces help message")
        ("version,v", "print version string")
    ;

    po::options_description config("Config options");
    config.add_options()
        ("fasta", po::value(&fastaInput)->multitoken(), 
            "fasta files or the directory containing them")
        ("dta", po::value(&dtaInput)->multitoken(),
            "dta files or the directory containing them")
        ("results", po::value(&resultsDir)->default_value(defaultResults), 
            "results directory")
        ("options", po::value(&optionsFile)->default_value(defaultOptions),
            "options file")
    ;

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, cmdline_options), vm);
    po::notify(vm);

    path optionsPath(optionsFile);

    if (vm.count("help")) {
        cout << cmdline_options << endl;
        return 1;
    }

    if (vm.count("version")) {
        cout << versionString << endl;
        return 1;
    }

    if (vm.count("fasta")) {
        // BOOST_LOG_TRIVIAL(info) << "Option set: fasta:" <<
        //     vm["fasta"].as< vector<string> >();
    } else {
        fastaInput = defaultFasta;
    }

    if (vm.count("dta")) {
        // BOOST_LOG_TRIVIAL(info) << "Option set: dta:" <<
        //     vm["dta"].as< vector<string> >();
    } else {
        dtaInput = defaultDta;
    }

    // set to 1 for debuging Owen Edit
    ThreadPool threadpool(2);


    // Read in the options file

    try {
    Options const options(optionsPath);
    BOOST_LOG_TRIVIAL(info) << options.job();
    BOOST_LOG_TRIVIAL(info) << options.digest();
    BOOST_LOG_TRIVIAL(info) << options.sequence();
    BOOST_LOG_TRIVIAL(info) << options.linker();
    BOOST_LOG_TRIVIAL(info) << options.analysis();
    //BOOST_LOG_TRIVIAL(info) << options.mustInterlinkSequence();

    // Analyze and read in the fasta directory
    PathVector fastaPaths = make_PathVector(fastaInput);

    SequenceIdMap seqMap = readFastas(fastaPaths, options.sequence().reverse);

    MhSequenceTree mhSeqTree = calcPeptides(threadpool, seqMap, options);

    BOOST_LOG_TRIVIAL(info) << "Sequences Read: " << seqMap.size();


    // Analyze the dat directory
    PathVector dtaPaths = make_PathVector(dtaInput);

    path resultsPath(resultsDir);

    stdrun(threadpool,
                   dtaPaths,
                   resultsPath,
                   seqMap,
                   mhSeqTree,
                   options);
    BOOST_LOG_TRIVIAL(info) << "Finished writing candidates.";
    } catch (boost::exception &e) {
        std::cerr << diagnostic_information(e);
        return -1;
    }

    return 0;
}

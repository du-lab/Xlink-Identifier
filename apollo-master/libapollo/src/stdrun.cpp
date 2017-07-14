#include <boost/assign/list_of.hpp>
#include <boost/filesystem/fstream.hpp>

#include "readdtas.hpp"
#include "stdrun.hpp"

namespace apollo {

const ExtensionSet dtaExtensions =
    boost::assign::list_of(".dta");

namespace fn {

// Pulling this in to make it work
void createDirectory(boost::filesystem::path const &directory) {
    using boost::filesystem::exists;
    using boost::filesystem::create_directory;
    if (!exists(directory)) {
        create_directory(directory);
    }
}

ScoreReport_vec singleRun(
        boost::filesystem::path const &dtaPath,
        boost::filesystem::path const &resultsPath,
        SequenceIdMap const &seqIdMap,
        MhSequenceTree const &mhSeqTree,
        Options const &options,
        std::atomic_long &candidateCount) {

    ScoreReport_vec reports;

    ParsedDta parsedDta = readDtaFile(dtaPath);
    if (parsedDta.first) {
        DtaFile const &dtaFile = parsedDta.second;

        CandidatePeptides candidatePeptides(mhSeqTree, dtaFile, options);

        reports = produceReport(candidatePeptides,
                                resultsPath,
                                seqIdMap,
                                options,
                                candidateCount);
    }

    return reports;
}

void printScoreHeader(std::ostream &out) {
    using std::endl;
    using std::string;

    string const tabStr("\t");
    out << "XCor" << tabStr <<
           //"SP" << tabStr <<
           "Mass Error" << tabStr <<
           "Theoretical Mh" << tabStr <<
           "DTA" << tabStr <<
           "Linker Config"<< tabStr <<
           "Linker" << tabStr <<
           "ID" << tabStr <<
           "Sequence 1" << tabStr <<
           "Decorated 1" << tabStr <<
           "Parent 1" << tabStr <<
           "Sequence 2" << tabStr <<
           "Decorated 2" << tabStr <<
           "Parent 2" << endl;
}

void printScores(std::ostream &out,
                SequenceIdMap const &seqIdMap,
                ScoreReport_vec const &scores) {
    using std::endl;
    using std::get;
    using std::string;
    string const tabStr("\t");

    for(ScoreReport const &score : scores) {
        out << get<0>(score) << tabStr << // xcor
              // get<1>(score) << tabStr <<
               get<10>(score).value() << tabStr << // mass error
               get<11>(score).value() << tabStr <<
               get<2>(score) << tabStr << // dta
               get<3>(score) << tabStr; // Linker Config
        if (get<3>(score) == enums::LinkerConfig::Unlinked) {
            out << tabStr;
        } else {
            out << get<4>(score)->name() << tabStr; // Linker
        }
        out << get<5>(score) << tabStr; // unique ID
        out << *get<6>(score) << tabStr; // Sequence 1
        out << get<8>(score) << tabStr; // Sequence 1 Decorated

        SequenceI::shp seqParent1 = get<6>(score)->rootProtein();
        out << seqIdMap.at(seqParent1).first << tabStr; // Sequence 1 Parent

        if (get<3>(score) == enums::LinkerConfig::Interlinked) {
            out << *get<7>(score) << tabStr; // Sequence 2
            out << get<9>(score) << tabStr; // Sequence 2 Decorated

            SequenceI::shp seqParent2 = get<7>(score)->rootProtein();
            out << seqIdMap.at(seqParent2).first << tabStr; // Sequence 2 Parent
        } else {
            out << tabStr << tabStr;
        }
        out << endl;
    }
}

void stdrun(
        ThreadPool &threadpool,
        PathVector const &dtaPaths,
        boost::filesystem::path const &resultsPath,
        SequenceIdMap const &seqIdMap,
        MhSequenceTree const &mhSeqTree,
        Options const &options
        ) {

    using std::ios_base;

    using boost::filesystem::path;
    using boost::filesystem::ofstream;

    typedef std::vector<
        std::future<ScoreReport_vec>
        > score_report_future_vec;

    std::atomic_long candidateCount(0);
    ScoreReport_vec scoreReport;

    score_report_future_vec scoreReportFutures;

    PathVector expandedPaths = fn::expandPaths(dtaPaths, dtaExtensions);

    createDirectory(resultsPath);

    for(PathVector::value_type const &dtaPath : expandedPaths) {
        scoreReportFutures.emplace_back(
                    threadpool.enqueue(singleRun,
                                   std::cref(dtaPath),
                                    std::cref(resultsPath),
                                    std::cref(seqIdMap),
                                    std::cref(mhSeqTree),
                                    std::cref(options),
                                    std::ref(candidateCount))
                    );
    }

    path const overviewPath = resultsPath / "results.csv";
    ofstream overviewOut(overviewPath, ios_base::trunc & ios_base::out);
    overviewOut << std::fixed;
    overviewOut << std::setprecision(5);
    printScoreHeader(overviewOut);

    for(auto &reportFuture : scoreReportFutures) {
        reportFuture.wait();
        ScoreReport_vec newReports = std::move(reportFuture.get());
        printScores(overviewOut, seqIdMap, newReports);
    }

    overviewOut.flush();
    overviewOut.close();
}

} /* namespace fn */
} /* namespace apollo */

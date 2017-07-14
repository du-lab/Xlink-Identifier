/**
 * @file    pathvector.cpp
 * @brief   Typedefs a simple boost::container::vector<boost::filesystem::path>
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/07/10
 * @copyright 2012
 */

#include <boost/log/trivial.hpp>

#include "pathvector.hpp"

namespace apollo {

namespace fn {
PathVector make_PathVector(std::vector<std::string> const &sPathVector) {
    
    namespace fs = boost::filesystem;
    using fs::path;
    using std::string;
    PathVector pVector;
    for(string const &sPath : sPathVector) {
        pVector.emplace_back(sPath);
    }
    return pVector;
}

bool shouldAddFile(boost::filesystem::path const &p, 
    ExtensionSet const &allowedExtensions) {
    
    namespace fs = boost::filesystem;
    using fs::path;
    if (fs::exists(p) && fs::is_regular_file(p)) {
        if (allowedExtensions.find(p.extension().string()) != allowedExtensions.end()) {
            return true;
        }
    }
    return false;
}

PathVector expandPaths(PathVector const &pVector, 
    ExtensionSet const &allowedExtensions) {

    namespace fs = boost::filesystem;
    fs::directory_iterator dirEnd;
    using fs::path;
    using std::string;
    PathVector expandedPVector;
    for(path const &p : pVector) {
        if (!fs::exists(p)) {
            BOOST_LOG_TRIVIAL(warning) << "does not exist: " << p.string();
        } else {
            if (fs::is_directory(p)) {
                for (fs::directory_iterator dirIt(p); dirIt != dirEnd; ++dirIt ) {
                    if (shouldAddFile(*dirIt, allowedExtensions)) {
                        expandedPVector.emplace_back(*dirIt);
                    } else {
                        BOOST_LOG_TRIVIAL(warning) << "skipping: " << p.string();
                    }
                }
            } else {
                if (shouldAddFile(p, allowedExtensions)) {
                    expandedPVector.emplace_back(p);
                } else {
                    BOOST_LOG_TRIVIAL(warning) << "skipping: " << p.string();
                }
            }
        }
    }
    return expandedPVector;
}

} /* namespace fn */
} /* namespace apollo */

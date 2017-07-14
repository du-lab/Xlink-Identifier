/**
 * @file    sp.cpp
 * @brief   SP Calculation function
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/10/09
 * @copyright 2012
 */

#include <algorithm>
#include <utility>
#include <iterator>
#include <vector>

#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/utility.hpp>

#include "../core/macros.hpp"
#include "../core/refutil.hpp"

#include "types.hpp"
#include "units.hpp"
#include "enums.hpp"
#include "ionconfig.hpp"
#include "sp.hpp"

namespace apollo {

namespace fn {

class IonCompareLess {
public:
    bool operator()(IonConfig const &first,
                    IonConfig const &second) const {
                    if(first.fragmentedSequence < second.fragmentedSequence) {
                        return true;
                    } else {
                        if (first.fragmentLocation < second.fragmentLocation) {
                            return true;
                        }
                    }
                    return false;
                }
};


/*
 * @note This version of the SP algorithm doesn't consider ion modifications. 
 * Thus, if there comes a time where mod type a and mod type b can exist in the same series
 * this algorithm will break
 * 
 */

bool ionNextInSeries(IonConfig const &first,
    IonConfig const &second) {
    if (first.fragmentedSequence == second.fragmentedSequence) {
        if ((first.fragmentLocation + 1 ) == second.fragmentLocation) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

types::intensity_store_t continuityCalculation(MatchedSpectrumVector const &mSpectrumVector) {

    typedef boost::container::flat_multiset<IonConfig::cref, IonCompareLess> ContinuitySet;

    typedef boost::container::flat_map<
        types::charge_t, 
        boost::container::flat_map<
            enums::Ion, 
            ContinuitySet
        >
    > ContinuityMap;



    using std::sort;
    using types::intensity_store_t;
    using types::count_store_t;

    bool isFirstSeriesScore = true;
    intensity_store_t continuityScore = 0.0f;
    intensity_store_t const baseSeriesScore = 1.0f;
    intensity_store_t const seriesModifier = 0.075f;
    ContinuityMap cMap;
    for(auto const &mSpectrumPair : mSpectrumVector) {
        cMap[mSpectrumPair.second->first.z()]
            [mSpectrumPair.second->second.ion].emplace(
                mSpectrumPair.second->second.ionConfig_cref
            );
    }
    // Note that, while we're not modifying the continuity map itself, we do sort the
    // vector it holds. 

    // Walk the continuity map by charge and ion type
    for(auto &chargeIonPair : cMap) {
        for(auto &ionConfigPair : chargeIonPair.second) {
            ContinuitySet &cSet = ionConfigPair.second;

            // if there are enough entries to have a series
            if(cSet.size() > 1) {
                count_store_t seriesCount = 0;
                intensity_store_t seriesScore = baseSeriesScore;

                auto ionConfigPrev = cSet.begin();
                auto ionConfigIt = std::next(ionConfigPrev);


                for(; ionConfigIt != cSet.end(); ++ionConfigIt) {
                    // if the current ion is the next in the series, increment the count
                    if (ionNextInSeries(*ionConfigPrev, *ionConfigIt)) {
                        seriesCount += 1;
                    // Otherwise we are finished with this series
                    } else {
                        seriesScore += (seriesModifier * seriesCount);
                        if (isFirstSeriesScore) {
                            continuityScore = seriesScore;
                            isFirstSeriesScore = false;
                        } else {
                            continuityScore *= seriesScore;
                        }
                        seriesCount = 0;
                        seriesScore = baseSeriesScore;
                    }
                    ionConfigPrev = ionConfigIt;
                }
            }
        }
    }
    return continuityScore;
}


SpResult spCalculation(MzSpectrum const &expSpectrum, 
    IonSpectrum const &theoSpectrum,
    types::mz_t const halfWindow) {

    using std::make_pair;
    using types::mz_t;

    using types::intensity_store_t;
    using types::intensity_t;
    using units::intensity;
    using types::count_t;

    intensity_t matchedIntensities(0.0f * intensity);
    count_t matchedCount = 0;
    count_t const theoCount = theoSpectrum.size();  

    SpResult result;

    for(IonSpectrum::const_iterator theoSpecIt = theoSpectrum.begin();
        theoSpecIt != theoSpectrum.end(); 
        ++theoSpecIt) {

        mz_t lowerLimit = theoSpecIt->first.mz() - halfWindow;
        mz_t upperLimit = theoSpecIt->first.mz() + halfWindow;

        MzSpectrum::const_iterator expLowerIt = expSpectrum.lower_bound(lowerLimit);
        
        // If there are no entries >= to the lower bound, then none of the other experimental entries
        // that will match the theoretical spectrum 
        if (expLowerIt == expSpectrum.end()) {
            break;
        }

        // If the iterators match, then there are no entries in the range we're interested in
        MzSpectrum::const_iterator const expUpperIt = expSpectrum.upper_bound(upperLimit);
        if (expLowerIt == expUpperIt) {
            continue;
        }


        MzSpectrum::const_iterator maxIntensityIt = expLowerIt;


        // Max instead of summation for multiple matching peaks
        for(; expLowerIt != expUpperIt; ++expLowerIt) {
            if (expLowerIt->second > maxIntensityIt->second) {
                maxIntensityIt = expLowerIt;
            }
        }

        matchedIntensities += maxIntensityIt->second;
        matchedCount += 1;

        result.second.emplace_back(maxIntensityIt, theoSpecIt);

    }
    intensity_store_t const continuityScore = continuityCalculation(result.second);
    intensity_store_t score = (matchedIntensities.value() * matchedCount * continuityScore) / (float) theoCount;

    
    result.first = score;
    return result;
}

} /* namespace fn*/
} /* namespace apollo */

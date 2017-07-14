/**
 * @file    ionmodification.hpp
 * @brief   A simple bitset to hold Ion Modification info
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/09/11
 * @copyright 2012
 */

 #ifndef apollo_ionmodifications_hpp_
 #define apollo_ionmodifications_hpp_

#include <bitset>
#include "enums.hpp"

namespace apollo {

typedef std::bitset<enums::IonMod::NumOfIonMods> IonModification;

}

 #endif /* apollo_ionmodifications_hpp_ */
/**
 * @file    enum.hpp
 * @brief   apollo enums
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/17
 * @copyright 2012
 */

#ifndef apollo_enums_hpp_
#define apollo_enums_hpp_

#include <ostream>

namespace apollo {

namespace enums {


enum Digest {Full, Partial, None};

std::ostream& operator<<(std::ostream &out, Digest const rhs);

enum Tolerance {Mz, Ppm};

std::ostream& operator<<(std::ostream &out, Tolerance const rhs);

enum FragmentationMethod { Cid, Etd };

std::ostream& operator<<(std::ostream &out, FragmentationMethod const rhs);

enum Ion { B, Y, C, Z, A };

std::ostream& operator<<(std::ostream &out, Ion const rhs);

enum IonMod { Nh3Loss, H2OLoss, CoLoss, NumOfIonMods };

std::ostream& operator<<(std::ostream &out, IonMod const rhs);

enum FragmentedSequence { Alpha, Beta };

std::ostream& operator<<(std::ostream &out, FragmentedSequence const rhs);

enum LinkerConfig { Unlinked, Deadend, Intralinked, Interlinked };

std::ostream& operator<<(std::ostream &out, LinkerConfig const rhs);

} /* namespace enums */
} /* namespace apollo */

#endif /* apollo_enums_hpp_ */

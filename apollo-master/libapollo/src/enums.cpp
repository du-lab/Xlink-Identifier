/**
 * @file    enums.cpp
 * @brief   Output for various enums
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/10
 * @copyright 2012
 */

#include "enums.hpp"
namespace apollo {
namespace enums {

std::ostream& operator<<(std::ostream &out, Digest const rhs) {
    switch(rhs) {
    case Digest::Full:
        out << "full";
        break;
    case Digest::Partial:
        out << "partial";
        break;
    case Digest::None:
        out << "none";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, Tolerance const rhs) {
    switch(rhs) {
    case Tolerance::Mz:
        out << "MZ";
        break;
    case Tolerance::Ppm:
        out << "PPM";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, FragmentationMethod const rhs) {
    switch(rhs) {
    case FragmentationMethod::Cid:
        out << "CID";
        break;
    case FragmentationMethod::Etd:
        out << "ETD";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, Ion const rhs) {
    switch(rhs) {
    case Ion::B:
        out << "B";
        break;
    case Ion::Y:
        out << "Y";
        break;
    case Ion::C:
        out << "C";
        break;
    case Ion::Z:
        out << "Z";
        break;
    case Ion::A:
        out << "A";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, FragmentedSequence const rhs) {
    switch(rhs) {
    case FragmentedSequence::Alpha:
        out << "alpha";
        break;
    case FragmentedSequence::Beta:
        out << "beta";
        break; 
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, LinkerConfig const rhs) {
    switch(rhs) {
    case LinkerConfig::Unlinked:
        out << "unlinked";
        break;
    case LinkerConfig::Deadend:
        out << "deadend";
        break;
    case LinkerConfig::Intralinked:
        out << "intralinked";
        break;
    case LinkerConfig::Interlinked:
        out << "interlinked";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream &out, IonMod const rhs) {
    switch(rhs) {
    case IonMod::Nh3Loss:
        out << "-NH3";
        break;
    case IonMod::H2OLoss:
        out << "-H2O";
        break;
    case IonMod::CoLoss:
        out << "-CO";
        break;
    default:
        out << "Unknown";
        break;
    }
    return out;
}

} /* namespace enums */
} /* namespace apollo */

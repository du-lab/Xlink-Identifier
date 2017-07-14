#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

// Handles windows and unix file system access
#include <boost/filesystem.hpp>

#include "sequenceinterface.hpp"
#include "residuecount.hpp"
#include "linkloc.hpp"
#include "locresiduemap.hpp"
#include "residuecount.hpp"
#include "residuemass.hpp"
#include "residuemod.hpp"
#include "sequenceconfig.hpp"
#include "optiontypes.hpp"
#include "mz.hpp"
#include "candidateions.hpp"

#include "../core/stdmass.hpp"
#include "../core/stdcharge.hpp"
#include "../core/sequence.hpp"
#include "../core/linker.hpp"
#include "../core/reactiongroup.hpp"
#include "../core/residuecalc.hpp"

#include "../theory/ion/interlinkioncfgiter.hpp"
#include "../theory/ion/mzionspeciter.hpp"
#include "../theory/sequence/sequencemhiter.hpp"
#include "ionconfig.hpp"
#include "options.hpp"

#include <boost/assign/list_of.hpp>
#include <boost/bind.hpp>
#include <boost/log/trivial.hpp>

#include </usr/local/include/json/json.h>

std::string decorateCandidate(apollo::SequenceMotif const &candidate,
                           apollo::LocResidueMap const &staticLocations,
                           apollo::LocResidueMap const &dynamicLocations,
                           apollo::types::residue_t const linkerSymbol,
                           apollo::LinkLoc const linkLoc1 = apollo::LinkLoc::Unlinked(),
                           apollo::LinkLoc const linkLoc2 = apollo::LinkLoc::Unlinked()
                           ) {
    using std::string;
    using std::stringstream;

    using apollo::LinkLoc;
    using apollo::LocResidueMap;
    using apollo::SequenceMotif;
    using apollo::SequenceI;
    stringstream decoratedCandidate;

    if ((linkLoc1 == LinkLoc::OnNh2Terminus() || linkLoc2 == LinkLoc::OnNh2Terminus())) {
        decoratedCandidate << linkerSymbol << " ";
    }

    SequenceI::shp sequence = candidate.first;
    string const strCandidate = sequence->toString();
    for(SequenceI::size_type i = 0; i < sequence->length(); i++) {
        decoratedCandidate << strCandidate[i];
        LocResidueMap::const_iterator staticDecorator = staticLocations.find(i);
        if(staticDecorator != staticLocations.end()) {
            decoratedCandidate << staticDecorator->second;
        }
        LocResidueMap::const_iterator dynamicDecorator = dynamicLocations.find(i);
        if(dynamicDecorator != dynamicLocations.end()) {
            decoratedCandidate << dynamicDecorator->second;
        }
        if ((linkLoc1.loc() == i) || (linkLoc2.loc() == i)) {
            decoratedCandidate << linkerSymbol;
        }
    }

    if((linkLoc1 == LinkLoc::OnCTerminus()) || (linkLoc2 == LinkLoc::OnCTerminus())) {
        decoratedCandidate << " " << linkerSymbol;
    }


    return decoratedCandidate.str();
}

void printSpectrum(std::ostream &out, apollo::IonSpectrum const &ionSpectrum) {
    using std::endl;
    using std::string;
    string const tabStr("\t");
    out << "Theoretical" << tabStr << "ionConfig" << endl;
    for (apollo::IonSpectrum::value_type const &isPair : ionSpectrum) {
        out << isPair.first << tabStr << isPair.second << endl;
    }
}

int main(int argc, char *argv[]) {

    using std::cout;
    using std::endl;
    using std::make_shared;
    using std::get;
    using std::string;

    using boost::filesystem::path;
    using apollo::Options;
    using apollo::LinkLoc;
    using apollo::LocResidueMap;
    using apollo::ResidueCount;
    using apollo::SequenceI;
    using apollo::Sequence;
    using apollo::SequenceConfig;
    using apollo::SequenceMotif;
    using apollo::SequenceOptions;
    using apollo::stdmass::residue::MonoisotopicMap_da;
    using apollo::stdmass::H2O_da;
    using apollo::InterlinkIonCfgGen;
    using apollo::InterlinkIonCfgIter;
    using apollo::MzIonSpecGen;
    using apollo::MzIonSpecIter;
    using apollo::IonConfig;
    using apollo::make_geniter;
    using apollo::Linker;
    using apollo::ReactionGroup;
    using apollo::fn::massFromSequence;
    using apollo::fn::massFromResidueCount;
    using apollo::units::dalton_mass;
    using apollo::types::dalton_t;
    using apollo::types::mz_t;
    using apollo::Mz;
    using apollo::types::charge_t;
    using apollo::units::charge;
    using apollo::IonSpectrum;
    using apollo::CandidateIons;
    dalton_t mass = dalton_t(500.0f * dalton_mass);
    mz_t massMh = Mz::MhFromM(mass);
    dalton_t unMh = Mz::MFromMh(massMh);

    cout << "******** Base Mh Calculations (500 dalton, Mh, then converted back) ******** " << endl;

    cout <<" Mass: " << mass << endl;
    cout << "Mh: " << massMh << endl;
    cout << "UnMh: " << unMh << endl;

    cout << "******** Base Mz Calculations (500 dalton, increasing charge) ******** " << endl;
    Mz mz1(500.0f, 1);
    Mz mz2(500.0f, 2);
    Mz mz3(500.0f, 3);
    Mz mz4(500.0f, 4);
    Mz mz5(500.0f, 5);
    cout << "Mz 1: " << mz1 << endl;
    cout << "Mz 2: " << mz2 << endl;
    cout << "Mz 3: " << mz3 << endl;
    cout << "Mz 4: " << mz4 << endl;
    cout << "Mz 5: " << mz5 << endl;

    //return 0;
//    Json::Value root;
//    Json::Reader reader;

//    std::ifstream newOptionsFile("options.json");

//    bool parsingSuccessful = reader.parse(newOptionsFile, root);
//    if (!parsingSuccessful) {
//        std::cout << "Failed to parse options.json: \n" <<
//                     reader.getFormatedErrorMessages();
//        return 1;
//    }

//    const Json::Value job = root["job"];
//    const std::string jobId = job.get("id", "results").asString();
//    const std::string owner = job.get("owner", "n/a").asString();

//    std::cout << "Job: " << jobId << ", Owner: " << owner << std::endl;

//    const Json::Value sequence = root["sequence"];
//    const Json::Value sequences = sequence["sequences"];
//    for( int seq = 0; seq < sequences.size(); ++seq) {
//        const Json::Value sequenceOptions = sequences[seq];
//        const std::string id = sequenceOptions.get("id", "n/a").asString();
//        const bool reverse = sequenceOptions.get("reverse", false).asBool();
//        std::cout << "Seq Options Id: " << id << ", Reverse: " << reverse << std::endl;
//        const Json::Value stdMass = sequenceOptions["stdMass"];
//        const std::string stdMassType = stdMass.get("type", "monoisotopic").asString();
//        std::cout << "mass type: " << stdMassType << std::endl;
//        const Json::Value additionalStdMass = stdMass["additional"];
//        for(int addtl = 0; addtl < additionalStdMass.size(); ++addtl) {
//            const Json::Value addtlMass = additionalStdMass[addtl];
//            const std::string residue = addtlMass.get("residue", "empty").asString();
//            const float mass = addtlMass.get("mass", 0.0f).asFloat();
//            std::cout << "residue: " << residue << ", mass: " << mass << std::endl;
//        }
//        const Json::Value modifications = sequenceOptions["modifications"];
//        const Json::Value dynamicMods = modifications["dynamic"];
//        const Json::Value staticMods = modifications["static"];
//        const Json::Value residueMod = dynamicMods["residueMod"];
//        for(int rm = 0; rm < residueMod.size(); ++rm) {
//            const Json::Value rmValue = residueMod[rm];
//            const std::string residue = rmValue.get("residue", "empty").asString();
//            const std::string mod = rmValue.get("mod", "empty").asString();
//            std::cout << "residue: " << residue << ", mod: " << mod << std::endl;
//        }
//        const Json::Value modMass = dynamicMods["modMass"];
//        for(int mm = 0; mm < modMass.size(); ++mm) {
//            const Json::Value mmValue = modMass[mm];
//            const std::string mod = mmValue.get("mod", "empty").asString();
//            const float mass = mmValue.get("mass", 0.0f).asFloat();
//            std::cout << "mod: " << mod << ", mass: " << mass << std::endl;
//        }
//    }
    const string optionsFile("options.json");
    path optionsPath(optionsFile);
    Options const options(optionsPath);

    ResidueCount emptyRCount;

    cout << "******** Printing Options ******** " << endl;
    BOOST_LOG_TRIVIAL(info) << options.job();
    BOOST_LOG_TRIVIAL(info) << options.digest();
    BOOST_LOG_TRIVIAL(info) << options.sequence();
    BOOST_LOG_TRIVIAL(info) << options.linker();
    BOOST_LOG_TRIVIAL(info) << options.analysis();
    cout << "******** End Options ******** " << endl;

    Linker::shp linker = options.linker().linkers.at(0);

    SequenceI::shp seq1 =
            make_shared<Sequence>("bgggggkr");
    SequenceMotif motif1;
    LinkLoc seq1LinkLoc = LinkLoc::OnPosition(6);
    LocResidueMap staticModLocs1;
    LocResidueMap dynamicModLocs1;

    dalton_t seq1Mass = massFromSequence(*seq1, options.sequence().stdResidueMass) + H2O_da;
    mz_t seq1Mh = Mz::MhFromM(seq1Mass);

    SequenceConfig config1(seq1Mh, emptyRCount, emptyRCount);
    motif1 = std::make_pair(seq1, config1);

    std::string decoratedCandidate1 =
            decorateCandidate(motif1, staticModLocs1, dynamicModLocs1, linker->symbol(), seq1LinkLoc);

    SequenceI::shp seq2 =
            make_shared<Sequence>("ECCHGDLLECADDR");
    SequenceMotif motif2;
    LinkLoc seq2LinkLoc = LinkLoc::OnPosition(7);
    LocResidueMap staticModLocs2;
    LocResidueMap dynamicModLocs2;
    dynamicModLocs2[1] = '!';
    dynamicModLocs2[2] = '!';
    dynamicModLocs2[9] = '!';

    dalton_t seq2Mass = massFromSequence(*seq2, options.sequence().stdResidueMass) + H2O_da;
    dalton_t modMass = options.sequence().dynamicModMasses.at('!');
    modMass *= 3;
    mz_t seq2Mh = Mz::MhFromM(seq2Mass + modMass);

    SequenceConfig config2(seq2Mh, emptyRCount, emptyRCount);
    motif2 = std::make_pair(seq2, config2);

    std::string decoratedCandidate2 =
            decorateCandidate(motif2, staticModLocs2, dynamicModLocs2, linker->symbol(), seq2LinkLoc);

    InterlinkIonCfgIter linkedIter =
            make_geniter<InterlinkIonCfgGen>(motif1, seq1LinkLoc, staticModLocs1, dynamicModLocs1,
                                             motif2, seq2LinkLoc, staticModLocs2, dynamicModLocs2,
                                             options.sequence());
    InterlinkIonCfgIter const linkedIterEnd;
    MzIonSpecIter mzIterEnd;
    charge_t dtaCharge(4 * charge);

    cout << "Printing Ion report for " << decoratedCandidate1 <<
            " <-> " << decoratedCandidate2 << endl;

    for(; linkedIter != linkedIterEnd; ++linkedIter) {
        IonConfig ion = *linkedIter;
        cout << "Ion Config: " << ion << endl;
        MzIonSpecIter mzIter =
                make_geniter<MzIonSpecGen>(ion, dtaCharge, options.analysis().theoreticalSpectrum, linker);
        for(; mzIter != mzIterEnd; ++mzIter) {
            cout << "\tIon: " << *mzIter << endl;
        }
    }

    if (linker->name() == "photo_biotin") {
        cout << "Is Photo: true" << endl;
    }
    return 0;
}


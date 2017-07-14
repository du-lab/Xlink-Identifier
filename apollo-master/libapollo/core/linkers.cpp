/**
 * @file    linkers.cpp
 * @brief   Compile time linkers
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/16
 * @copyright 2012
 */

#include <memory>
#include <string>
#include <boost/assign/list_of.hpp>

#include "types.hpp"
#include "units.hpp"
#include "stdmass.hpp"
#include "reactiongroup.hpp"
#include "linker.hpp"
#include "linkers.hpp"

namespace apollo {

using namespace boost::assign;
using std::string;
using types::dalton_t;
using units::dalton_mass;
using types::residue_t;
using stdmass::H2O_da;

/** Reaction Groups */
namespace group {

bool const doesLinkToNh2Terminus = true;
bool const noLinkToNh2Terminus = false;

bool const doesLinkToCTerminus = true;
bool const noLinkToCTerminus = false;

ReactionGroup const Ala('A', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Arg('R', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Asn('N', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Asp('D', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Cys('C', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Glu('E', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Gln('Q', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Gly('G', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const His('H', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Ile('I', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Leu('L', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Lys('K', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Met('M', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Phe('F', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Pro('P', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Ser('S', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Thr('T', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Trp('W', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Tyr('Y', noLinkToNh2Terminus, noLinkToCTerminus);

ReactionGroup const Val('V', noLinkToNh2Terminus, noLinkToCTerminus);

string const AAsWithNh2("K");
ReactionGroup const Nh2(AAsWithNh2.begin(), AAsWithNh2.end(),
    doesLinkToNh2Terminus, noLinkToCTerminus);

string const AAsWithCarboxyl("DE");
ReactionGroup const Carboxyl(AAsWithCarboxyl.begin(), AAsWithCarboxyl.end(),
    noLinkToNh2Terminus, noLinkToCTerminus);

} /* namespace group */


/** Linkers */
namespace linker {

using std::make_shared;

// I make this verbose to simplify the understanding of 
// the Linker definitions what's going on

bool const doesInterlink = true;
bool const noInterlink = false;

bool const doesIntralink = true;
bool const noIntralink = false;

bool const doesDeadend = true;
bool const noDeadend = false;

residue_t const defaultSymbol = '!';

using group::Lys;
using group::Cys;
using group::Nh2;
using group::Carboxyl;


// All masses are monoisotopic, unless otherwise specified

/** Light BS3 */
string const string_lightBs3("light-bs3");
dalton_t const inter_lightBs3(138.06808f * dalton_mass);
dalton_t const intra_lightBs3 = inter_lightBs3;
dalton_t const deadend_lightBs3 = inter_lightBs3 + H2O_da;

Linker::shp LightBs3 = make_shared<Linker>(
    string_lightBs3,
    defaultSymbol,
    doesInterlink, inter_lightBs3,
    doesIntralink, intra_lightBs3,
    doesDeadend, deadend_lightBs3,
    Nh2, Nh2
    );

/** Heavy BS3 */
string const string_heavyBs3("heavy-bs3");
dalton_t const inter_heavyBs3(150.15f * dalton_mass);
dalton_t const intra_heavyBs3 = inter_heavyBs3;
dalton_t const deadend_heavyBs3 = inter_heavyBs3 + H2O_da;

Linker::shp HeavyBs3 = make_shared<Linker>(
    string_heavyBs3,
    defaultSymbol,
    doesInterlink, inter_heavyBs3,
    doesIntralink, intra_heavyBs3,
    doesDeadend, deadend_heavyBs3,
    Nh2, Nh2
    );

/** EDC */
string const string_EDC("edc");
dalton_t const inter_EDC(-19.018f * dalton_mass);
dalton_t const intra_EDC = inter_EDC;
dalton_t const deadend_EDC(43.042f * dalton_mass);

Linker::shp EDC = make_shared<Linker>(
    string_EDC,
    defaultSymbol,
    doesInterlink, inter_EDC,
    doesIntralink, intra_EDC,
    doesDeadend, deadend_EDC,
    Carboxyl, Lys
    );

/** Formaldehyde */
string const string_Formaldehyde("formaldehyde");
dalton_t const inter_Formaldehyde(12.0f * dalton_mass);
dalton_t const intra_Formaldehyde = inter_Formaldehyde;
dalton_t const deadend_Formaldehyde(12.0f * dalton_mass);


Linker::shp Formaldehyde = make_shared<Linker>(
    string_Formaldehyde,
    defaultSymbol,
    doesInterlink, inter_Formaldehyde,
    doesIntralink, intra_Formaldehyde,
    doesDeadend, deadend_Formaldehyde,
    Lys, Lys
    );

/** Disulfide */

string const string_Disulfide("disulfide");
dalton_t const inter_Disulfide(-2.0156f * dalton_mass);
dalton_t const intra_Disulfide = inter_Disulfide;
dalton_t const deadend_Disulfide(0.0f * dalton_mass);

Linker::shp Disulfide = make_shared<Linker>(
    string_Disulfide,
    defaultSymbol,
    doesInterlink, inter_Disulfide,
    doesIntralink, intra_Disulfide,
    noDeadend, deadend_Disulfide,
    Cys, Cys
    );
} /* namespace linker */

using linker::LightBs3;
using linker::HeavyBs3;
using linker::EDC;
using linker::Formaldehyde;
using linker::Disulfide;

const LinkerMap LinkersMap = 
    map_list_of
    (LightBs3->name(), LightBs3)
    (HeavyBs3->name(), HeavyBs3)
    (EDC->name(), EDC)
    (Formaldehyde->name(), Formaldehyde)
    (Disulfide->name(), Disulfide);



} /* namespace apollo */

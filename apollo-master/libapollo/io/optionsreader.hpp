/**
 * @file    optionsreader.hpp
 * @brief   A simple interface to read the options file
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/08
 * @copyright 2012
 */

#ifndef apollo_optionsreader_hpp_
#define apollo_optionsreader_hpp_

#include <ostream>

#include </usr/local/include/json/json.h>


#include "enums.hpp"
#include "types.hpp"
#include "residuemass.hpp"
#include "residuemod.hpp"
#include "../core/digesttolerance.hpp"
#include "../core/linker.hpp"
#include "../core/reactiongroup.hpp"
#include "optiontypes.hpp"


namespace apollo {

JobOptions read_JobOptions(Json::Value const &value);

DigestOptions read_DigestOptions(Json::Value const &value);


ResidueMass::value_type read_ResidueMassPair(Json::Value const &value);
ResidueMod::value_type read_ResidueModPair(Json::Value const &value);

ResidueMass read_stdMass(Json::Value const &value);

ResidueMod read_ResidueMod(Json::Value const &value);

ResidueMass read_ModMass(Json::Value const &value);

SequenceOptions read_SequenceOptions(Json::Value const &value);

SequenceOptionsMap read_SequenceOptionsMap(Json::Value const &value);




LinkerOptions read_LinkerOptions(Json::Value const &valuej);

MzSearchTolerance read_MzSearchTolerance(Json::Value const &value);





TheoreticalSpectrumOptions read_TheoreticalSpectrumOptions(Json::Value const &value);


AnalysisOptions read_AnalysisOptions(Json::Value const &value);


} /* namespace apollo */

#endif /* apollo_optionsreader_hpp_ */

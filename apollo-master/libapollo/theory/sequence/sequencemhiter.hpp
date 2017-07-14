/**
 * @file    sequencemhiter.hpp
 * @brief   Iterator through possible mods and mhs given a sequence
 *
 * @author  Adam Baxter
 * @version 2.0
 * @date    2012/08/14
 * @copyright 2012
 */

#ifndef apollo_sequencemhiter_hpp_
#define apollo_sequencemhiter_hpp_

#include "../../core/generatoriterator.hpp"
#include "sequencemhgen.hpp"

namespace apollo {

typedef GeneratorIterator<SequenceMhGen> SequenceMhIter;

} /* namespace apollo */

#endif /* apollo_sequencemhiter_hpp_ */

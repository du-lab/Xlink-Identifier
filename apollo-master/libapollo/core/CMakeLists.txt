include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(core_SRCS
    generator.hpp generatoriterator.hpp
    macros.hpp
    regexmap.hpp
    digesttolerance.hpp digesttolerance.cpp
    regexdigest.hpp regexdigest.cpp
    geometryutil.hpp geometryutil.cpp
    multireflocset.hpp multireflocset.cpp
    multirefresiduecount.hpp multirefresiduecount.cpp
    linker.hpp linker.cpp
    linkers.hpp linkers.cpp
    linkermap.hpp
    locset.hpp locset.cpp
    rangeiter.hpp
    refutil.hpp
    intrareactiongroup.hpp intrareactiongroup.cpp
    reactiongroup.hpp reactiongroup.cpp
    residuecalc.hpp residuecalc.cpp
    sequence.hpp sequence.cpp
    sequencepart.hpp sequencepart.cpp
    sequencechain.hpp sequencechain.cpp
    sequenceterminals.hpp sequenceterminals.cpp
    stdcharge.hpp
    stdmass.hpp stdmass.cpp
)

ADD_LIBRARY(core STATIC ${core_SRCS})
target_link_libraries(core libapollo)

set(Boost_NO_SYSTEM_PATHS       ON)
find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)


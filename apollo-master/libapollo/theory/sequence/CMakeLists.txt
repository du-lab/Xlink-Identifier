include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(theory_sequence_SRCS
    fullytrypticgen.hpp fullytrypticgen.cpp
    fullytrypticiter.hpp
    linklocgen.hpp linklocgen.cpp
    linklociter.hpp
    modcountgen.hpp modcountgen.cpp
    modcountiter.hpp
    modlocgen.hpp modlocgen.cpp
    modlociter.hpp
    multimodcountgen.hpp multimodcountgen.cpp
    multimodcountiter.hpp
    multimodlocgen.hpp multimodlocgen.cpp
    multimodlociter.hpp
    ntrypticgen.hpp ntrypticgen.cpp
    ntrypticiter.hpp
    sequencemhgen.hpp sequencemhgen.cpp
    sequencemhiter.hpp
    locationutil.hpp locationutil.cpp
)

ADD_LIBRARY(theory_sequence STATIC ${theory_sequence_SRCS})
target_link_libraries(theory_sequence filter core)

set(Boost_NO_SYSTEM_PATHS       ON)

find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(analysis_SRCS
    peptidesearch.hpp peptidesearch.cpp
    sp.hpp sp.cpp
    xcorrelation.hpp xcorrelation.cpp
)

ADD_LIBRARY(analysis STATIC ${analysis_SRCS})
target_link_libraries(analysis filter theory_sequence core experiment)

set(Boost_NO_SYSTEM_PATHS       ON)

find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

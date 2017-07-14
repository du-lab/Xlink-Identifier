include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(experiment_SRCS
    denoise.hpp denoise.cpp
    experimentutils.hpp experimentutils.cpp
    normalize.hpp normalize.cpp
)

ADD_LIBRARY(experiment STATIC ${experiment_SRCS})

set(Boost_NO_SYSTEM_PATHS       ON)

find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)


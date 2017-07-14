include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(filter_SRCS
    filterinterface.hpp
    f_modcount.hpp f_modcount.cpp
    f_multimodcount.hpp f_multimodcount.cpp
    f_multimodloc.hpp f_multimodloc.cpp
    f_mz.hpp f_mz.cpp
)

ADD_LIBRARY(filter STATIC ${filter_SRCS})
target_link_libraries(filter core)

set(Boost_NO_SYSTEM_PATHS       ON)

find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)


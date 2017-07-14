include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(theory_ion_SRCS
    ulinkioncfggen.hpp ulinkioncfggen.cpp
    ulinkioncfgiter.hpp
    linkioncfggen.hpp linkioncfggen.cpp
    linkioncfgiter.hpp
    interlinkioncfggen.hpp interlinkioncfggen.cpp
    interlinkioncfgiter.hpp
    intralinkioncfggen.hpp intralinkioncfggen.cpp
    intralinkioncfgiter.hpp
    mzionspecgen.hpp mzionspecgen.cpp
    mzionspeciter.hpp
)

ADD_LIBRARY(theory_ion STATIC ${theory_ion_SRCS})
target_link_libraries(theory_ion filter core theory_sequence)

set(Boost_NO_SYSTEM_PATHS       ON)

find_package(Boost 1.55.0 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif (Boost_FOUND)

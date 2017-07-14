include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(io_SRCS
    kseq.h
    dtareader.hpp
    fastagen.hpp fastagen.cpp
    fastaiter.hpp
    optionsreader.hpp optionsreader.cpp
)

ADD_LIBRARY(io STATIC ${io_SRCS})
target_link_libraries(io core)

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries(io ${ZLIB_LIBRARIES})
endif (ZLIB_FOUND)

set(Boost_NO_SYSTEM_PATHS        ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem log)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(io ${Boost_LIBRARIES})
endif (Boost_FOUND)

find_package(Jsoncpp REQUIRED)
if(Jsoncpp_FOUND)
    include_directories(${Jasoncpp_INCLUDE_DIR})
    target_link_libraries(io ${Jsoncpp_LIBRARY})
endif(Jsoncpp_FOUND)

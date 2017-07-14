include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(scoring_SRCS
)

ADD_LIBRARY(scoring STATIC ${scoring_SRCS})

target_link_libraries(scoring core experiment theory_sequence analysis theory_ion)

find_package(Threads REQUIRED)
if (Threads_FOUND)
target_link_libraries (scoring ${CMAKE_THREAD_LIBS_INIT})
endif (Threads_FOUND)

set(Boost_NO_SYSTEM_PATHS        ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.54.0 REQUIRED COMPONENTS system thread filesystem date_time chrono log)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(scoring ${Boost_LIBRARIES})
endif (Boost_FOUND)

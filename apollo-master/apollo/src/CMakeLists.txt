include_directories(${apollo_SOURCE_DIR}/apollo/include)
include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(apollo_SRCS apollo.cpp)
SET(sandbox_SRCS sandbox.cpp)

add_executable(apollo ${apollo_SRCS})
target_link_libraries(apollo core libapollo)

add_executable(sandbox ${sandbox_SRCS})
target_link_libraries(sandbox core libapollo)

set(Boost_NO_SYSTEM_PATHS        ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem log thread date_time chrono program_options)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(apollo ${Boost_LIBRARIES})
    target_link_libraries(sandbox ${Boost_LIBRARIES})
endif (Boost_FOUND)

find_package(Jsoncpp)
if(Jsoncpp_FOUND)
    include_directories(${Jasoncpp_INCLUDE_DIR})
    target_link_libraries(sandbox ${Jsoncpp_LIBRARY})
endif(Jsoncpp_FOUND)

include_directories(${apollo_SOURCE_DIR}/libapollo/include)

SET(src_SRCS
    analysis.cpp
    options.cpp
    residuecount.cpp
    residuemass.cpp
    residueset.cpp
    ionconfig.cpp
    reports.cpp
    candidateions.cpp
    linkloc.cpp
    locresiduemap.cpp
    mz.cpp
    optiontypes.cpp
    residuemod.cpp
    readfastas.cpp
    readdtas.cpp
    pathvector.cpp
    sequenceconfig.cpp
    spectrumtypes.cpp
    theory.cpp
    enums.cpp
    candidatepeptides.cpp
    sequencescore.cpp
    stdrun.cpp
    #ThreadPool.cpp
)

ADD_LIBRARY(libapollo STATIC ${src_SRCS})

target_link_libraries(libapollo core io experiment theory_sequence analysis theory_ion)

find_package(Threads REQUIRED)
if (Threads_FOUND)
target_link_libraries (libapollo ${CMAKE_THREAD_LIBS_INIT})
endif (Threads_FOUND)

set(Boost_NO_SYSTEM_PATHS        ON)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost 1.55.0 REQUIRED COMPONENTS system thread filesystem date_time chrono log)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(libapollo ${Boost_LIBRARIES})
endif (Boost_FOUND)

find_package(Jsoncpp REQUIRED)
if(Jsoncpp_FOUND)
    include_directories(${Jasoncpp_INCLUDE_DIR})
    target_link_libraries(libapollo ${Jsoncpp_LIBRARY})
endif(Jsoncpp_FOUND)

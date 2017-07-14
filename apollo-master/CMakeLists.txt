cmake_minimum_required(VERSION 2.8.6)
project(apollo)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

SET(BOOST_ROOT "/usr/local")

subdirs(apollo libapollo)
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-std=c++11 LIBCXX_HAS_STDCXX11_FLAG)
if (LIBCXX_HAS_STDCXX11_FLAG)
        ADD_DEFINITIONS("-std=c++11")
else()
        MESSAGE(FATAL_ERROR "C++11 support is required.")
endif(LIBCXX_HAS_STDCXX11_FLAG)

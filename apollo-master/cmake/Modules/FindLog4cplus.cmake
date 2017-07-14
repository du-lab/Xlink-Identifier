# Locate Log4cplus library
# This module defines
#  Log4cplus_FOUND, if false, do not try to link to Log4cplus
#  Log4cplus_LIBRARIES
#  Log4cplus_INCLUDE_DIR, where to find log4cplus.hpp


include(LibFindMacros)

# Dependencies
libfind_package(Log4cplus Threads)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Log4cplus_PKGCONF log4cplus)

# Include dir
find_path(Log4cplus_INCLUDE_DIR
    NAMES log4cplus/logger.h
    PATHS ${Log4cplus_PKGCONF_INCLUDE_DIRS}
)

# Library
find_library(Log4cplus_LIBRARY
    NAMES log4cplus
    PATHS ${Log4cplus_PKGCONF_LIBRARY_DIRS}
)

SET(Log4cplus_PROCESS_INCLUDES Log4cplus_INCLUDE_DIR)
SET(Log4cplus_PROCESS_LIBS Log4cplus_LIBRARY)
libfind_process(Log4cplus)

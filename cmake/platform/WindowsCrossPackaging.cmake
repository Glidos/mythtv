#
# Copyright (C) 2022-2023 David Hampton
#
# See the file LICENSE_FSF for licensing information.
#

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows" OR NOT CMAKE_CROSSCOMPILING)
  return()
endif()

# Build a windows package
ExternalProject_Add(
  PackageWindows
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/platform/win32/w64-mingw32
  CMAKE_ARGS ${CMDLINE_ARGS}
             ${PLATFORM_ARGS}
             ${USES_QT_PLATFORM_ARGS}
             -DQT_VERSION_MAJOR:STRING=${QT_VERSION_MAJOR}
             -DSUPER_VERSION=${PROJECT_VERSION}
             -DSUPER_SOURCE_DIR=${PROJECT_SOURCE_DIR}
             -DSUPER_BINARY_DIR=${PROJECT_BINARY_DIR}
             -DMYTHTV_SOURCE_VERSION=${MYTHTV_SOURCE_VERSION}
  CMAKE_CACHE_ARGS
    -DCMAKE_FIND_ROOT_PATH:STRING=${CMAKE_FIND_ROOT_PATH}
    -DCMAKE_JOB_POOL_COMPILE:STRING=compile
    -DCMAKE_JOB_POOL_LINK:STRING=link
    -DCMAKE_JOB_POOLS:STRING=${CMAKE_JOB_POOLS}
    -DPKG_CONFIG_LIBDIR:PATH=${PKG_CONFIG_LIBDIR}
    -DPKG_CONFIG_PATH:PATH=${PKG_CONFIG_PATH}
  USES_TERMINAL_CONFIGURE TRUE
  USES_TERMINAL_BUILD TRUE
  DEPENDS MythTV MythPlugins)
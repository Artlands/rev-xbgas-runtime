# xBGAS Top-Level CMake Description
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory of
# this distribution.
#

# Prevent in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif()

# SST-REV Setup
set(REV "$ENV{REV}")
if(REV)
  message(STATUS "REV set to ${REV}.")
else()
  message(FATAL_ERROR "REV environment variable is not set.")
endif()

# RISCV Setup
set(RISCV "$ENV{RISCV}")
if(RISCV)
  message(STATUS "RISCV set to ${RISCV}.")
else()
  message(FATAL_ERROR "RISCV environment variable is not set.")
endif()

# XBGAS_RUNTIME Setup
set(XBGAS_RUNTIME "$ENV{XBGAS_RUNTIME}")
if(XBGAS_RUNTIME)
  message(STATUS "XBGAS_RUNTIME set to ${XBGAS_RUNTIME}.")
else()
  message(FATAL_ERROR "XBGAS_RUNTIME environment variable is not set.")
endif()

# Override the default compiler/assembler
set(CMAKE_C_COMPILER "${RISCV}/bin/riscv64-unknown-elf-gcc")
set(CMAKE_CXX_COMPILER "${RISCV}/bin/riscv64-unknown-elf-g++")
set(CMAKE_ASM_COMPILER "${RISCV}/bin/riscv64-unknown-elf-as")

# Minimum required version of CMake and project information
cmake_minimum_required (VERSION 3.19)
project(xbgas-runtime C CXX ASM)

#------------------------------------------------------------------------
#-- COMPILER OPTIONS
#------------------------------------------------------------------------

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -static -w")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -O0 -static -w -DXBRTIME_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O3 -static -w")

# xbrtime paths
set(REV_SYSCALLS_PATH "${REV}/common/syscalls" CACHE PATH "REV syscalls path")
set(XBRTIME_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE PATH "Xbrtime include path")

# Include directories
include_directories(
  ${REV_SYSCALLS_PATH}
  ${XBRTIME_INCLUDE_PATH}
)

#------------------------------------------------------------------------
#-- FIND PACKAGES
#------------------------------------------------------------------------

# # Find all the relevant packages
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the doxygen-ized API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

#------------------------------------------------------------------------
#-- DOCUMENTATION
#------------------------------------------------------------------------

# Doxygen config
if(BUILD_DOCUMENTATION)
  if( NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is required to build the documentation.")
  endif()

  set(doxyfile ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/xbgas-runtime.conf)

  add_custom_target(doc
                    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    COMMENT "Generating API documentation with Doxygen"
                    VERBATIM)

  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/html DESTINATION share/doc)
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/man DESTINATION share/man)

  message(STATUS "Enabling developer documentation")
endif()

#------------------------------------------------------------------------
#-- TESTING
#------------------------------------------------------------------------
 enable_testing()

#------------------------------------------------------------------------
#-- SUBDIRECTORIES
#------------------------------------------------------------------------
# Add our subdirectories
add_subdirectory( src )
add_subdirectory( test )

#-- EOF

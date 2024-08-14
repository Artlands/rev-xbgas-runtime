# test/alloc CMakeLists.txt driver
#
# Copyright (C) 2017-2024 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# This file is a part of the XBGAS-RUNTIME package.  For license
# information, see the LICENSE file in the top level directory of
# this distribution.
#

include_directories(${XBGAS_PATH})

set(CMAKE_EXECUTABLE_SUFFIX ".exe")
set(CMAKE_VERBOSE_MAKEFILE ON)  # Enable verbose output

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)

if(BUILD_COLLECTIVE_TESTING)
foreach(testSrc ${TEST_SRCS})
  # Extract the file name
  get_filename_component(testName ${testSrc} NAME_WE)

  # Add compile target
  add_executable(${testName} ${testSrc})

  # Override the compiler
  set(CMAKE_C_COMPILER "${RISCV_ENV}/bin/riscv64-unknown-elf-gcc")
  set(CMAKE_ASM_COMPILER "${RISCV_ENV}/bin/riscv64-unknown-elf-gcc")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=rv64gc_zifencei -mcmodel=medany -static -std=gnu11 -fno-common -fno-builtin-printf -w")
  set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

  # Add linker deps
  target_link_libraries(${testName} xbrtime m)

  # Drop the exe's in a separate directory
  set_target_properties(${testName} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin)

  # Add the tests for execution
  add_test(NAME ${testName}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
    COMMAND sst ${CMAKE_CURRENT_SOURCE_DIR}/testBin/rev-xbgas-coll.py --model-options=${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName}.exe\ 6)
  set_tests_properties( ${testName} 
	PROPERTIES 
    TIMEOUT 30
		PASS_REGULAR_EXPRESSION "")
endforeach(testSrc)
endif()

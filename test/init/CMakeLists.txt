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

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)

if(BUILD_INIT_TESTING)
  set (passRegex "Simulation is complete")

  add_test(
    NAME BUILD_CLEAN
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND make clean
  )

  foreach(testSrc ${TEST_SRCS})
    # Extract the file name
    get_filename_component(testName ${testSrc} NAME_WE)

    # Add the tests for execution
    add_test(NAME ${testName}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      COMMAND ./run_xbrtime_test.sh)
    set_tests_properties( ${testName} 
      PROPERTIES
      ENVIRONMENT "RVASM=${testName}; RVCC=${RVCC}"
      TIMEOUT 30
      PASS_REGULAR_EXPRESSION "${passRegex}")
  endforeach(testSrc)
endif()

# **********************************************************
# Copyright (c) 2013-2016 Google, Inc.    All rights reserved.
# **********************************************************

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
#
# * Neither the name of Google, Inc. nor the names of its contributors may be
#   used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE:q
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL GOOGLE, INC. OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.

cmake_minimum_required(VERSION 3.1.3)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities
	
include_directories(${UTILITY_BUNNY_DIR}/src)	
include_directories(${SLICER_BUNNY_DIR}/src)   
include_directories(${INSTRUMENTATION_BUNNY_DIR}/src)   
	
set(DynamoRIO_USE_LIBC ON)

find_package(DynamoRIO)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

find_package(DrMemoryFramework)
if (NOT DrMemoryFramework_FOUND)
  message(FATAL_ERROR "DrMemoryFramework package required to build")
 endif ()

configure_DynamoRIO_global(OFF ON)

function(compile_test targetName sources)
  add_library(${targetName} SHARED ${sources})
  configure_DynamoRIO_client(${targetName})

  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)

  target_link_libraries(${targetName} ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
  target_link_libraries(${targetName} ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a) 
  target_link_libraries(${targetName} ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
 
  use_DynamoRIO_extension(${targetName} drmgr)
  use_DynamoRIO_extension(${targetName} drreg)
  use_DynamoRIO_extension(${targetName} drbbdup)
  use_DynamoRIO_extension(${targetName} drutil)
  use_DynamoRIO_extension(${targetName} drwrap)
  use_DynamoRIO_extension(${targetName} drsyscall_static)
  

endfunction(compile_test)

function(compile_app_test targetName sources)
  add_executable(${targetName} ${sources})
  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
endfunction(compile_app_test)

function (compile_library_test libraryName header sources)
  add_library(${libraryName} SHARED ${sources})
  set_target_properties(${libraryName} PROPERTIES LINKER_LANGUAGE C)
  set_property(TARGET ${libraryName} PROPERTY C_STANDARD 99)
endfunction(compile_library_test)

set(ib_mod_slicer_lib_srcs
  ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/ib_module_slicer_test_lib.h
  ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/ib_module_slicer_test_lib.c
)

compile_library_test(ib_mod_slicer_lib ${ib_mod_slicer_lib_srcs})

compile_app_test(ib_mod_slicer_app ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/ib_module_slicer_test_app.c )
target_link_libraries(ib_mod_slicer_app ib_mod_slicer_lib)

compile_test(ib_instrumentation_bunny_test ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test.c)
compile_test(ib_instrumentation_bunny_test2 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test2.c)
compile_test(ib_instrumentation_bunny_test3 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test3.c)
compile_test(ib_instrumentation_bunny_test4 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test4.c)
compile_test(ib_instrumentation_bunny_test5 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test5.c)
compile_test(ib_instrumentation_bunny_test6 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test6.c)
compile_test(ib_instrumentation_bunny_test7 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test7.c)
compile_test(ib_instrumentation_bunny_test8 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test8.c)
compile_test(ib_instrumentation_bunny_test9 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test9.c)
compile_test(ib_instrumentation_bunny_test10 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test10.c)
compile_test(ib_instrumentation_bunny_test11 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test11.c)
compile_test(ib_instrumentation_bunny_test12 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test12.c)
compile_test(ib_instrumentation_bunny_test13 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test13.c)
compile_test(ib_instrumentation_bunny_test14 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test14.c)
compile_test(ib_instrumentation_bunny_test15 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test15.c)
compile_test(ib_instrumentation_bunny_test16 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test16.c)
compile_test(ib_instrumentation_bunny_test17 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test17.c)
compile_test(ib_instrumentation_bunny_test18 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test18.c)
compile_test(ib_instrumentation_bunny_test19 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test19.c)
compile_test(ib_instrumentation_bunny_test20 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test20.c)
compile_test(ib_instrumentation_bunny_test21 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test21.c)
compile_test(ib_instrumentation_bunny_test22 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test22.c)
compile_test(ib_instrumentation_bunny_test24 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test24.c)
compile_test(ib_instrumentation_bunny_test25 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test25.c)
compile_test(ib_instrumentation_bunny_test26 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test26.c)
compile_test(ib_instrumentation_bunny_test27 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test27.c)
compile_test(ib_instrumentation_bunny_test28 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test28.c)
compile_test(ib_instrumentation_bunny_test29 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test29.c)
compile_test(ib_instrumentation_bunny_test30 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test30.c)
compile_test(ib_instrumentation_bunny_test31 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test31.c)
compile_test(ib_instrumentation_bunny_test32 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test32.c)
compile_test(ib_instrumentation_bunny_test33 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test33.c)
compile_test(ib_instrumentation_bunny_test34 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test34.c)
compile_test(ib_instrumentation_bunny_test35 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test35.c)
compile_test(ib_instrumentation_bunny_test36 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test36.c)
compile_test(ib_instrumentation_bunny_test37 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test37.c)
compile_test(ib_instrumentation_bunny_test38 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test38.c)
compile_test(ib_instrumentation_bunny_test39 ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/instrumentation_bunny_test39.c)

compile_test(ib_opcode_hook_manager_test ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/opcode_hook_manager/ib_opcode_hook_manager_test.c)
compile_test(ib_option_test ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/options/ib_option_test.c)

file(COPY ${INSTRUMENTATION_BUNNY_DIR}/src/unit_tests/mod.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


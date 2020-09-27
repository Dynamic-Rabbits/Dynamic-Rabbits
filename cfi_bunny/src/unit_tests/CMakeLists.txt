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

cmake_minimum_required(VERSION 2.6)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities

include_directories(${UTILITY_BUNNY_DIR}/src)
include_directories(${SLICER_BUNNY_DIR}/src)
include_directories(${INSTRUMENTATION_BUNNY_DIR}/src)	
include_directories(${TAINT_BUNNY_DIR}/src)	
include_directories(${CFI_BUNNY_DIR}/src)	

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
 
  target_link_libraries(${targetName} ${CFI_BUNNY_DIR}/src/build/libcfi_bunny_static.a)
  target_link_libraries(${targetName} ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny_static.a)
  target_link_libraries(${targetName} ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
  target_link_libraries(${targetName} ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a) 
  target_link_libraries(${targetName} ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
 
  target_include_directories(${targetName} PRIVATE ${DrMemoryFramework_DIR}/include)
 
  use_DynamoRIO_extension(${targetName} drmgr)
  use_DynamoRIO_extension(${targetName} drreg)
  use_DynamoRIO_extension(${targetName} drhit) 
  use_DynamoRIO_extension(${targetName} drbbdup) 
  use_DynamoRIO_extension(${targetName} drutil)
  use_DynamoRIO_extension(${targetName} drwrap)
  use_DynamoRIO_extension(${targetName} drsyscall_static)
  use_DynamoRIO_extension(${targetName} drsyms_static)
  use_DynamoRIO_extension(${targetName} umbra_static)

endfunction(compile_test)

function(compile_app_test targetName sources)
  add_executable(${targetName} ${sources})
  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
  SET_TARGET_PROPERTIES(${targetName} PROPERTIES COMPILE_FLAGS "-fno-stack-protector")
endfunction(compile_app_test)

compile_app_test(program1 ${CFI_BUNNY_DIR}/src/unit_tests/program1.c)
compile_app_test(program2 ${CFI_BUNNY_DIR}/src/unit_tests/program2.c)
compile_app_test(program3 ${CFI_BUNNY_DIR}/src/unit_tests/program3.c)
compile_app_test(program4 ${CFI_BUNNY_DIR}/src/unit_tests/program4.c)
compile_app_test(program5 ${CFI_BUNNY_DIR}/src/unit_tests/program5.c)

file(COPY ${CFI_BUNNY_DIR}/src/unit_tests/crash.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_test(cfib_test ${CFI_BUNNY_DIR}/src/unit_tests/cfib_test.c)
compile_test(cfib_test2 ${CFI_BUNNY_DIR}/src/unit_tests/cfib_test2.c)
compile_test(cfib_test3 ${CFI_BUNNY_DIR}/src/unit_tests/cfib_test3.c)

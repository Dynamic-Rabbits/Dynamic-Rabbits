
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
	
set(DynamoRIO_USE_LIBC ON)

include_directories(${SLICER_BUNNY_DIR}/src)
include_directories(${UTILITY_BUNNY_DIR}/src)

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
 
  target_link_libraries(${targetName} ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a)
  target_link_libraries(${targetName} ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
 
  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)

  use_DynamoRIO_extension(${targetName} drmgr)
  use_DynamoRIO_extension(${targetName} drreg)
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
  set_property(TARGET ${libraryName} PROPERTY C_STANDARD 99)
  set_target_properties(${libraryName} PROPERTIES LINKER_LANGUAGE C)
endfunction(compile_library_test)

compile_test(sb_pc_slicer_test ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/sb_pc_slicer_test.c)

set(sb_mod_slicer_lib_srcs
  ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/sb_module_slicer_test_lib.h
  ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/sb_module_slicer_test_lib.c
)

compile_test(sb_mod_slicer_test ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/sb_module_slicer_test.c)

compile_library_test(sb_mod_slicer_lib ${sb_mod_slicer_lib_srcs})

compile_app_test(sb_mod_slicer_app ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/sb_module_slicer_test_app.c )
target_link_libraries(sb_mod_slicer_app sb_mod_slicer_lib)

file(COPY ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/pc_addr.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/pc_addr2.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${SLICER_BUNNY_DIR}/src/unit_tests/slicers/mod.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


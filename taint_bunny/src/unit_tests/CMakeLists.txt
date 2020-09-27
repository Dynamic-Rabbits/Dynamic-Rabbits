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

function(compile_test targetName)
  add_library(${targetName} SHARED ${ARGN})
  configure_DynamoRIO_client(${targetName})

  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
 
  target_link_libraries(${targetName} ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny_static.a)
  target_link_libraries(${targetName} ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
  target_link_libraries(${targetName} ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a) 
  target_link_libraries(${targetName} ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
 
  target_include_directories(${targetName} PRIVATE ${DrMemoryFramework_DIR}/include)
 
  use_DynamoRIO_extension(${targetName} drmgr)
  use_DynamoRIO_extension(${targetName} drreg)
  use_DynamoRIO_extension(${targetName} drbbdup) 
  use_DynamoRIO_extension(${targetName} drhit) 
  use_DynamoRIO_extension(${targetName} drutil)
  use_DynamoRIO_extension(${targetName} drwrap)
  use_DynamoRIO_extension(${targetName} drsyscall_static)
  use_DynamoRIO_extension(${targetName} drsyms_static)
  use_DynamoRIO_extension(${targetName} umbra_static)

endfunction(compile_test)

function (use_TAINT_RABBIT_annotations target_srcs)
  set(taintrabbit_annotation_dir "${TAINT_BUNNY_DIR}/src/taint_annotations/annotations")
  set(taintrabbit_annotation_srcs "${taintrabbit_annotation_dir}/tb_annotations.c")
  configure_DynamoRIO_annotation_sources("${taintrabbit_annotation_srcs}")
  set(${target_srcs} ${${target_srcs}} ${taintrabbit_annotation_srcs} PARENT_SCOPE)
endfunction (use_TAINT_RABBIT_annotations target_srcs)

function(compile_app_test targetName sources)
  use_TAINT_RABBIT_annotations(sources)
  add_executable(${targetName} ${sources})
  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
  SET_TARGET_PROPERTIES(${targetName} PROPERTIES COMPILE_FLAGS "-fno-stack-protector")
endfunction(compile_app_test)

file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/socket_test_driver.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_app_test(program1 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program1.c)
compile_app_test(program2 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program2.c)
compile_app_test(program3 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program3.c)
compile_app_test(program4 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program4.c)
compile_app_test(program5 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program5.c)
compile_app_test(program6 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program6.c)
compile_app_test(program7 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program7.c)
compile_app_test(program8 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program8.c)
compile_app_test(program9 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program9.c)
compile_app_test(program10 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program10.c)
compile_app_test(program11 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program11.c)
compile_app_test(program12 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program12.c)
compile_app_test(program13 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program13.c)
compile_app_test(program14 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program14.c)
compile_app_test(program15 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program15.c)
compile_app_test(program16 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program16.c)
compile_app_test(program17 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program17.c)
compile_app_test(program18 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/program18.c)

compile_app_test(socket_program1 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/socket_program1.c)
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/crash.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/phptest.php DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/phptest2.php DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/my_name.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/my_boat.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/sample.mp3 DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/my_file DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_test(stack_checker ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker.c)
compile_test(stack_checker2 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker2.c)
compile_test(stack_checker3 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker3.c)
compile_test(stack_checker4 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker4.c)
compile_test(stack_checker5 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker5.c)
compile_test(stack_checker6 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker6.c)
compile_test(stack_checker7 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker7.c)
compile_test(stack_checker8 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker8.c)
compile_test(stack_checker9 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker9.c)
compile_test(stack_checker10 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker10.c)
compile_test(stack_checker11 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker11.c)
compile_test(stack_checker12 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker12.c)
compile_test(stack_checker13 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker13.c)
compile_test(stack_checker14 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker14.c)
compile_test(stack_checker15 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker15.c)
compile_test(stack_checker16 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker16.c)
compile_test(stack_checker17 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker17.c)
compile_test(stack_checker18 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker18.c)
compile_test(stack_checker19 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker19.c)
compile_test(stack_checker20 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker20.c)
compile_test(stack_checker21 ${TAINT_BUNNY_DIR}/src/unit_tests/stack_corruption_tests/stack_checker21.c)

compile_test(cc_taint_policies_test ${TAINT_BUNNY_DIR}/src/unit_tests/taint_policy/tb_cc_taint_policies.c)
compile_test(tb_map_driver_test ${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/taint_maps/tb_cc_map_driver_test.c)
compile_test(tb_cc_map_test ${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/taint_maps/tb_cc_map_test.c)
compile_test(tb_bunny_test ${TAINT_BUNNY_DIR}/src/unit_tests/taint_bunny_test.c)

set(cc_ta_driver
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_dst_test.c
    ${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_test_driver.c
    ${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst_test.c
    ${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_untainted_test.c 
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_p_src_srcdst_test.c
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_punpck_test.c
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_pack_test.c
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_xchg_test.c
	${TAINT_BUNNY_DIR}/src/unit_tests/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst_dst_test.c
)
compile_test(tb_cc_ta_test ${cc_ta_driver})

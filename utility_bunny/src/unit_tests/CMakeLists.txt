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
 
  target_link_libraries(${targetName} ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
 
  use_DynamoRIO_extension(${targetName} drmgr)
  use_DynamoRIO_extension(${targetName} drreg)
  use_DynamoRIO_extension(${targetName} drutil)
  use_DynamoRIO_extension(${targetName} drwrap)
  use_DynamoRIO_extension(${targetName} drsyscall_static)
  use_DynamoRIO_extension(${targetName} drsyms_static)
  

endfunction(compile_test)

function(compile_app_test targetName sources)
  add_executable(${targetName} ${sources})
  set_property(TARGET ${targetName} PROPERTY C_STANDARD 99)
endfunction(compile_app_test)

compile_test(ub_buf_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/buffers/ub_buf_test.c)
compile_test(ub_list_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/lists/ub_list_test.c)
compile_test(ub_arraymap_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_arraymap_test.c)
compile_test(ub_lp_hashmap_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_lp_hashmap_test.c)
compile_test(ub_lp_hashmap_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_lp_hashmap_test2.c)
compile_test(ub_tk_lp_hashmap_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_tk_lp_hashmap_test.c)
compile_test(ub_tk_lp_hashmap_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_tk_lp_hashmap_test2.c)
compile_test(ub_tk_arraymap_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_tk_arraymap_test2.c)
compile_test(ub_intptr_hashmap_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_intptr_hashmap_test.c)
compile_test(ub_str_hashmap_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/maps/ub_str_hashmap_test.c)
compile_test(ub_intptr_hashset_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/sets/ub_intptr_hashset_test.c)
compile_test(ub_str_hashset_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/sets/ub_str_hashset_test.c)
compile_test(ub_splaytree_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/trees/splay/ub_splaytree_test.c)
compile_test(ub_bitvector_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/vectors/ub_bitvector_test.c)
compile_test(ub_bdd_test ${UTILITY_BUNNY_DIR}/src/unit_tests/datastructs/trees/robdd/ub_bdd_test.c)

compile_test(ub_env_var_input_option_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/env_var_option/ub_env_var_input_option_test.c)
compile_test(ub_env_var_input_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_input_test.c)
compile_app_test(ub_env_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_test_app.c)
compile_test(ub_env_var_input_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_input_test2.c)
compile_app_test(ub_env_test_app2  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_test_app2.c)
compile_test(ub_env_var_input_test3 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_input_test3.c)
compile_test(ub_env_var_input_test4 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/env_var/ub_env_var_input_test4.c)

compile_test(ub_cl_arg_input_option_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/cl_arg_option/ub_cl_arg_input_option_test.c)
compile_app_test(ub_cl_arg_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_test_app.c)
compile_test(ub_cl_arg_input_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test.c)
compile_test(ub_cl_arg_input_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test2.c)
compile_test(ub_cl_arg_input_test3 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test3.c)
compile_test(ub_cl_arg_input_test4 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test4.c)
compile_test(ub_cl_arg_input_test5 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test5.c)
compile_test(ub_cl_arg_input_test6 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/cl_arg/ub_cl_arg_input_test6.c)

compile_test(ub_file_input_option_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/fd_option/ub_file_input_option_test.c)

compile_test(ub_alloc_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test.c)
compile_test(ub_alloc_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test2.c)
compile_test(ub_alloc_test3 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test3.c)
compile_app_test(ub_alloc_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test_app.c)
compile_app_test(ub_alloc_test_app2  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test_app2.c)
compile_app_test(ub_alloc_test_app3  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/alloc/ub_alloc_test_app3.c)

compile_test(ub_dealloc_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/dealloc/ub_dealloc_test.c)
compile_app_test(ub_dealloc_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/dealloc/ub_dealloc_test_app.c)

compile_test(ub_realloc_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/realloc/ub_realloc_test.c)
compile_app_test(ub_realloc_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/heap/realloc/ub_realloc_test_app.c)

compile_app_test(ub_file_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app.c)
compile_app_test(ub_file_test_app2  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app2.c)
compile_app_test(ub_file_test_app3  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app3.c)
compile_app_test(ub_file_test_app4  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app4.c)
compile_app_test(ub_file_test_app5  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app5.c)
compile_app_test(ub_file_test_app6  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app6.c)
compile_app_test(ub_file_test_app7  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app7.c)
compile_app_test(ub_file_test_app8  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_test_app8.c)

compile_test(ub_ip_test  ${UTILITY_BUNNY_DIR}/src/unit_tests/ip/ip_test.c)

compile_test(ub_input_buf_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/input_buf/ub_input_buf_test.c)

compile_test(ub_file_input_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test.c)
compile_test(ub_file_input_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test2.c)
compile_test(ub_file_input_test3 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test3.c)
compile_test(ub_file_input_test4 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test4.c)
compile_test(ub_file_input_test5 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test5.c)
compile_test(ub_file_input_test6 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test6.c)
compile_test(ub_file_input_test7 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test7.c)
compile_test(ub_file_input_test8 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test8.c)
compile_test(ub_file_input_test9 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test9.c)
compile_test(ub_file_input_test10 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test10.c)
compile_test(ub_file_input_test11 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test11.c)
compile_test(ub_file_input_test12 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_file_input_test12.c)

compile_test(ub_socket_input_test ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test.c)
compile_test(ub_socket_input_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test2.c)
compile_test(ub_socket_input_test3 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test3.c)
compile_test(ub_socket_input_test4 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test4.c)
compile_test(ub_socket_input_test5 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test5.c)
compile_test(ub_socket_input_test6 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test6.c)
compile_test(ub_socket_input_test7 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test7.c)
compile_test(ub_socket_input_test8 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test8.c)
compile_test(ub_socket_input_test9 ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_event_socket_input_test9.c)

compile_app_test(ub_socket_test_app  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app.c)
compile_app_test(ub_socket_test_app2  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app2.c)
compile_app_test(ub_socket_test_app3  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app3.c)
compile_app_test(ub_socket_test_app4  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app4.c)
compile_app_test(ub_socket_test_app5  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app5.c)
compile_app_test(ub_socket_test_app6  ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_app6.c)

compile_test(ub_instrum_insert_test  ${UTILITY_BUNNY_DIR}/src/unit_tests/instrumentation/ub_instrum_insert_test.c)

file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_driver.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_driver2.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_socket_test_driver3.py DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_test(ub_string_test ${UTILITY_BUNNY_DIR}/src/unit_tests/string/ub_string_test.c)

file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_input_test1.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/events/input/fd/ub_file_input_test2.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_test(ub_eflags_test ${UTILITY_BUNNY_DIR}/src/unit_tests/register/ub_eflags_test.c)
compile_test(ub_register_test ${UTILITY_BUNNY_DIR}/src/unit_tests/register/ub_register_test.c)

compile_test(ub_file_reader_test ${UTILITY_BUNNY_DIR}/src/unit_tests/readers/ub_file_reader_test.c)
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/readers/ub_file_reader_test1.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/readers/ub_file_reader_test2.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${UTILITY_BUNNY_DIR}/src/unit_tests/readers/ub_file_reader_test3.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

compile_test(ub_loc_test ${UTILITY_BUNNY_DIR}/src/unit_tests/location/ub_loc_test.c)

compile_test(spinlock_test ${UTILITY_BUNNY_DIR}/src/unit_tests/spinlock/spinlock_test.c)

compile_test(allocator_test ${UTILITY_BUNNY_DIR}/src/unit_tests/allocator/allocator_test.c)
compile_test(allocator_test2 ${UTILITY_BUNNY_DIR}/src/unit_tests/allocator/allocator_test2.c)

compile_test(ub_bit_checker_test ${UTILITY_BUNNY_DIR}/src/unit_tests/byte/ub_bit_checker_test.c)
compile_test(ub_byte_array_test ${UTILITY_BUNNY_DIR}/src/unit_tests/byte/ub_byte_array_test.c)

compile_test(ub_dataflow_tests ${UTILITY_BUNNY_DIR}/src/unit_tests/dataflow/dataflow_tests.c)
compile_test(ub_dataflow_in_out ${UTILITY_BUNNY_DIR}/src/unit_tests/dataflow/dataflow_in_out.c)
compile_test(ub_dataflow_constant_analysis ${UTILITY_BUNNY_DIR}/src/unit_tests/dataflow/dataflow_constant_analysis.c)
compile_test(ub_dataflow_analysis ${UTILITY_BUNNY_DIR}/src/unit_tests/dataflow/dataflow_analysis.c)

compile_test(ub_comparison_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_comparison_instr_test.c)
compile_test(ub_cti_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_cti_instr_test.c)
compile_test(ub_rep_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_rep_instr_test.c)
compile_test(ub_xinstr_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_xinstr_instr_test.c)
compile_test(ub_ptr_arith_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_ptr_arith_instr_test.c)
compile_test(ub_transfer_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_transfer_instr_test.c)
compile_test(ub_srcdst_src_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_srcdst_src_instr_test.c)
compile_test(ub_complex_arithmetic_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_complex_arithmetic_instr_test.c)
compile_test(ub_generic_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_generic_instr_test.c)
compile_test(ub_misc_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_misc_instr_test.c)
compile_test(ub_shift_instr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_shift_instr_test.c)
compile_test(ub_pinstr_test ${UTILITY_BUNNY_DIR}/src/unit_tests/instruction/ub_pinstr_test.c)

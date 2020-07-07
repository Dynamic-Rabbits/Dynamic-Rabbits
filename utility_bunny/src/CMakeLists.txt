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
	
set(DynamoRIO_USE_LIBC OFF)

set(srcs

    instruction/ub_complex_arithmetic_instr.c
    instruction/ub_ptr_arith_instr.c
    instruction/ub_rep_instr.c
    instruction/ub_srcdst_src_instr.c
    instruction/ub_transfer_instr.c
    instruction/ub_xinstr_instr.c
    instruction/ub_cti_instr.c
    instruction/ub_comparison_instr.c
    instruction/ub_generic_instr.c
    instruction/ub_shift_instr.c
    instruction/ub_misc_instr.c
    instruction/ub_pinstr.c
    instruction/ub_ptr_arith_instr.c
    
    datastructs/buffers/ub_circular_buffer.c
    datastructs/lists/ub_list.c
    datastructs/maps/ub_arraymap.c
    datastructs/maps/ub_lp_hashmap.c
    datastructs/maps/ub_tk_lp_hashmap.c
    datastructs/maps/ub_two_key_arraymap.c
    datastructs/maps/ub_hashmap.c
    datastructs/maps/ub_intptr_hashmap.c
    datastructs/maps/ub_str_hashmap.c
    datastructs/sets/ub_hashset.c
    datastructs/sets/ub_intptr_hashset.c
    datastructs/sets/ub_str_hashset.c
    datastructs/splaytrees/ub_splaytree.c
    datastructs/robdd/ub_bdd.c
    
    datastructs/vectors/ub_bitvector_basic.c
	datastructs/vectors/ub_bitvector.c
	
	dataflow/ub_instr_flows.c
	dataflow/ub_instr_parser.c
	dataflow/ub_opnd_access.c
	dataflow/ub_in_out_analysis.c
    dataflow/ub_constant_analysis.c
	dataflow/ub_dataflow_analysis.c
	
	app_bb_truncators/ub_addr_constant_reg_truncator.c
    app_bb_truncators/ub_opnd_limit_truncator.c
    app_bb_truncators/ub_drwrap_post_point_truncator.c
    
    location/ub_loc.c
    
    locks/ub_spin_lock.c
    
    instrumentation/ub_instrum_insert.c
    
    allocator/ub_allocator.c
    
    register/ub_eflags.c
    register/ub_register.c
    
    events/heap/routine_entry_checker.c
    
    events/heap/alloc/ub_event_alloc.c
    events/heap/dealloc/ub_event_dealloc.c
    events/heap/realloc/ub_event_realloc.c
    
    syscalls/ub_syscall_helper.c
    
    ip/ip.c
    
    events/input/env_var/ub_event_env_var_input.c
    events/input/env_var/env_var_option/ub_env_var_input_option.c

    events/input/fd/ub_event_fd_input.c
    events/input/fd/fd_option/ub_fd_input_option.c
    
    symbol_access/ub_symbol_access.c
    
    events/input/cl_arg/ub_event_cl_arg_input.c
    events/input/cl_arg/cl_arg_option/ub_cl_arg_input_option.c
    
    events/input/input_buf/input_buf.c

    string/ub_string.c

    readers/ub_file_reader.c
    
    byte/ub_bit_checker.c
    byte/ub_byte_array.c
  )

set(srcs_static ${srcs})

find_package(DynamoRIO)

if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

MESSAGE( STATUS ${DrMemoryFramework_DIR})
find_package(DrMemoryFramework)

if (NOT DrMemoryFramework_FOUND)
  message(FATAL_ERROR "DrMemoryFramework package required to build")
endif(NOT DrMemoryFramework_FOUND)

add_library(utility_bunny SHARED ${srcs})
configure_DynamoRIO_client(utility_bunny)
use_DynamoRIO_extension(utility_bunny drmgr)
use_DynamoRIO_extension(utility_bunny drreg)
use_DynamoRIO_extension(utility_bunny drutil)
use_DynamoRIO_extension(utility_bunny drwrap)
use_DynamoRIO_extension(utility_bunny drsyscall)
use_DynamoRIO_extension(utility_bunny drsyms)
#target_compile_options(utility_bunny PRIVATE -Werror -Wall -Wextra -Wno-unused-parameter 
#                                           -Wno-missing-field-initializers)

if (UNIX)
  _DR_append_property_string(TARGET utility_bunny COMPILE_FLAGS "-fPIC")
else ()
	include_directories(${DYNAMORIO_DIR}/core/lib)
  _DR_append_property_string(TARGET utility_bunny COMPILE_DEFINITIONS "RC_IS_utility_bunny")
endif ()

add_library(utility_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(utility_bunny_static)
use_DynamoRIO_extension(utility_bunny_static drmgr_static)
use_DynamoRIO_extension(utility_bunny_static drreg)
use_DynamoRIO_extension(utility_bunny_static drutil)
use_DynamoRIO_extension(utility_bunny_static drwrap)
use_DynamoRIO_extension(utility_bunny_static drsyscall_static)
use_DynamoRIO_extension(utility_bunny_static drsyms_static)

set_property(TARGET utility_bunny PROPERTY C_STANDARD 99)
set_property(TARGET utility_bunny_static PROPERTY C_STANDARD 99)


if (UNIX)
  _DR_append_property_string(TARGET utility_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET utility_bunny_static COMPILE_DEFINITIONS "RC_IS_utility_bunny")
endif ()

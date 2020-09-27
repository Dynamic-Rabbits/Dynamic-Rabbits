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
include_directories(${PATH_BUNNY_DIR}/src)

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

set(srcs

	logger/db_fuzz_print.c
	logger/cmp_logger/db_fuzz_cmp_logger.c
	logger/lea_logger/db_fuzz_lea_logger.c
	logger/lea_logger/db_fuzz_lea_spill.c
	db_fuzz.c
)

add_library("db_fuzz" SHARED ${srcs})
configure_DynamoRIO_client("db_fuzz")

set_property(TARGET "db_fuzz" PROPERTY C_STANDARD 99)

target_link_libraries("db_fuzz" ${PATH_BUNNY_DIR}/src/build/libpath_bunny_static.a)
target_link_libraries("db_fuzz" ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny_static.a)
target_link_libraries("db_fuzz" ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
target_link_libraries("db_fuzz" ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a)
target_link_libraries("db_fuzz" ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)

target_include_directories("db_fuzz" PRIVATE ${DrMemoryFramework_DIR}/include)

use_DynamoRIO_extension("db_fuzz" drmgr)
use_DynamoRIO_extension("db_fuzz" drbbdup)
use_DynamoRIO_extension("db_fuzz" drhit)
use_DynamoRIO_extension("db_fuzz" drreg)
use_DynamoRIO_extension("db_fuzz" drutil)
use_DynamoRIO_extension("db_fuzz" drwrap)
use_DynamoRIO_extension("db_fuzz" drsyscall_static)
use_DynamoRIO_extension("db_fuzz" drsyms_static)
use_DynamoRIO_extension("db_fuzz" umbra_static)


cmake_minimum_required(VERSION 3.1.3)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities

set(DynamoRIO_USE_LIBC OFF)

set(srcs

    code_cache/ib_code_cache.h
    code_cache/ib_code_cache.c

    code_inline/ib_code_inline.h
    code_inline/ib_code_inline.c

    hook_info/ib_hook_info.c
    
    instrumentation/ib_instrumenter.c
    instrumentation/ib_opnd_store.c
    instrumentation/ib_slot.c
    instrumentation/ib_slot.c
    instrumentation/ib_thread_data_loader.c

    opcode_hook_manager/ib_instrum_tool.c
    opcode_hook_manager/ib_opcode_hook_manager.c
    opcode_hook_manager/ib_hook_summary.c

    tls_access/ib_tls_access.c

    options/ib_option.c
		
	bbdup_instrum/ib_bbdup_instrum.c
	bbdup_instrum/ib_bbdup_register.c
	
    instrumentation_bunny.c
)

include_directories(${UTILITY_BUNNY_DIR}/src ${SLICER_BUNNY_DIR}/src)

set(srcs_static ${srcs})

find_package(DrMemoryFramework)

find_package(DynamoRIO)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

add_library(instrumentation_bunny SHARED ${srcs})
configure_DynamoRIO_client(instrumentation_bunny)
use_DynamoRIO_extension(instrumentation_bunny drmgr)
use_DynamoRIO_extension(instrumentation_bunny drcontainers)
use_DynamoRIO_extension(instrumentation_bunny drreg)
use_DynamoRIO_extension(instrumentation_bunny drbbdup)
use_DynamoRIO_extension(instrumentation_bunny drwrap)
use_DynamoRIO_extension(instrumentation_bunny drutil)
use_DynamoRIO_extension(instrumentation_bunny drsyscall_static)
use_DynamoRIO_extension(instrumentation_bunny drsyms_static)
#target_compile_options(instrumentation_bunny PRIVATE -Werror -Wall -Wextra -Wno-unused-parameter 
#                                           -Wno-missing-field-initializers)

if (UNIX)
  target_link_libraries(instrumentation_bunny ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny.so)
  target_link_libraries(instrumentation_bunny ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny.so)
  _DR_append_property_string(TARGET instrumentation_bunny COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET instrumentation_bunny COMPILE_DEFINITIONS "RC_IS_instrumentation_bunny")
endif ()

add_library(instrumentation_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(instrumentation_bunny_static)
use_DynamoRIO_extension(instrumentation_bunny_static drmgr_static)
use_DynamoRIO_extension(instrumentation_bunny_static drreg_static)
use_DynamoRIO_extension(instrumentation_bunny_static drbbdup_static)
use_DynamoRIO_extension(instrumentation_bunny_static drwrap_static)
use_DynamoRIO_extension(instrumentation_bunny_static drutil)
use_DynamoRIO_extension(instrumentation_bunny_static drsyscall_static)
use_DynamoRIO_extension(instrumentation_bunny_static drsyms_static)

set_property(TARGET instrumentation_bunny PROPERTY C_STANDARD 99)
set_property(TARGET instrumentation_bunny_static PROPERTY C_STANDARD 99)

if (UNIX)
  target_link_libraries(instrumentation_bunny_static ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a)
  target_link_libraries(instrumentation_bunny_static ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
  _DR_append_property_string(TARGET instrumentation_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET instrumentation_bunny_static COMPILE_DEFINITIONS "RC_IS_instrumentation_bunny")
endif ()


cmake_minimum_required(VERSION 3.1.3)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities

set(DynamoRIO_USE_LIBC OFF)

set(srcs

    slicer_bunny.c
    slicer_bunny.h
    
    slicers/sb_module_slicer.c
    slicers/sb_module_slicer.h
    slicers/sb_pc_slicer.c
    slicers/sb_pc_slicer.h
)

include_directories(${UTILITY_BUNNY_DIR}/src)

set(srcs_static ${srcs})

find_package(DynamoRIO)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

add_library(slicer_bunny SHARED ${srcs})
configure_DynamoRIO_client(slicer_bunny)
use_DynamoRIO_extension(slicer_bunny drmgr)
use_DynamoRIO_extension(slicer_bunny drcontainers)
use_DynamoRIO_extension(slicer_bunny drreg)
use_DynamoRIO_extension(slicer_bunny drwrap)
use_DynamoRIO_extension(slicer_bunny drutil)

if (UNIX)
  target_link_libraries(slicer_bunny ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny.so)
  _DR_append_property_string(TARGET slicer_bunny COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET slicer_bunny COMPILE_DEFINITIONS "RC_IS_slicer_bunny")
endif ()

add_library(slicer_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(slicer_bunny_static)
use_DynamoRIO_extension(slicer_bunny_static drmgr_static)
use_DynamoRIO_extension(slicer_bunny_static drreg)
use_DynamoRIO_extension(slicer_bunny_static drwrap)
use_DynamoRIO_extension(slicer_bunny_static drutil)

set_property(TARGET slicer_bunny PROPERTY C_STANDARD 99)
set_property(TARGET slicer_bunny_static PROPERTY C_STANDARD 99)

if (UNIX)
  target_link_libraries(slicer_bunny_static ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
  _DR_append_property_string(TARGET slicer_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET slicer_bunny_static COMPILE_DEFINITIONS "RC_IS_slicer_bunny")
endif ()


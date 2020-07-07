cmake_minimum_required(VERSION 3.1.3)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities

set(DynamoRIO_USE_LIBC OFF)

find_package(DynamoRIO)
if (NOT DynamoRIO_FOUND)
  message(FATAL_ERROR "DynamoRIO package required to build")
endif(NOT DynamoRIO_FOUND)

find_package(DrMemoryFramework)
if (NOT DrMemoryFramework_FOUND)
  message(FATAL_ERROR "DrMemoryFramework package required to build")
 endif ()

set(srcs

  instrumentation/pb_spill.c
  instrumentation/handlers/pb_handlers.c
  instrumentation/pb_instrum_register.c   
  path_bunny.c
)

set(srcs_static ${srcs})

include_directories(${UTILITY_BUNNY_DIR}/src)
include_directories(${SLICER_BUNNY_DIR}/src)
include_directories(${INSTRUMENTATION_BUNNY_DIR}/src)   
include_directories(${TAINT_BUNNY_DIR}/src) 

add_library(path_bunny SHARED ${srcs})
configure_DynamoRIO_client(path_bunny)
use_DynamoRIO_extension(path_bunny drmgr)
use_DynamoRIO_extension(path_bunny drreg)
use_DynamoRIO_extension(path_bunny drutil)
use_DynamoRIO_extension(path_bunny drwrap)
use_DynamoRIO_extension(path_bunny drsyscall_static)
use_DynamoRIO_extension(path_bunny drsyms_static)
use_DynamoRIO_extension(path_bunny umbra_static)

add_library(path_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(path_bunny_static)
use_DynamoRIO_extension(path_bunny_static drmgr_static)
use_DynamoRIO_extension(path_bunny_static drreg)
use_DynamoRIO_extension(path_bunny_static drwrap)
use_DynamoRIO_extension(path_bunny_static drutil)
use_DynamoRIO_extension(path_bunny_static umbra)

set_property(TARGET path_bunny PROPERTY C_STANDARD 99)
set_property(TARGET path_bunny_static PROPERTY C_STANDARD 99)

if (UNIX)
target_link_libraries("path_bunny" ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny.so)
target_link_libraries("path_bunny" ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny.so)
target_link_libraries("path_bunny" ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny.so)
target_link_libraries("path_bunny" ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny.so)

  _DR_append_property_string(TARGET path_bunny COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET path_bunny COMPILE_DEFINITIONS "RC_IS_path_bunny")
endif ()

if (UNIX)
target_link_libraries("path_bunny_static" ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny_static.a)
target_link_libraries("path_bunny_static" ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
target_link_libraries("path_bunny_static" ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a)
target_link_libraries("path_bunny_static" ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)

  _DR_append_property_string(TARGET path_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET path_bunny_static COMPILE_DEFINITIONS "RC_IS_path_bunny")
endif ()

 



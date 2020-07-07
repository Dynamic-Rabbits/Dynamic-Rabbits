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

  instrumentation/handlers/cfib_handlers.c  
  instrumentation/cfib_instrum_register.c
  cfi_bunny.c

)

set(srcs_static ${srcs})

include_directories(${UTILITY_BUNNY_DIR}/src ${SLICER_BUNNY_DIR}/src ${INSTRUMENTATION_BUNNY_DIR}/src ${TAINT_BUNNY_DIR}/src) 

add_library(cfi_bunny SHARED ${srcs})
configure_DynamoRIO_client(cfi_bunny)
use_DynamoRIO_extension(cfi_bunny drmgr)
use_DynamoRIO_extension(cfi_bunny drreg)
use_DynamoRIO_extension(cfi_bunny drbbdup)
use_DynamoRIO_extension(cfi_bunny drhit)
use_DynamoRIO_extension(cfi_bunny drutil)
use_DynamoRIO_extension(cfi_bunny drwrap)
use_DynamoRIO_extension(cfi_bunny drsyscall_static)
use_DynamoRIO_extension(cfi_bunny drsyms_static)
use_DynamoRIO_extension(cfi_bunny umbra_static)

add_library(cfi_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(cfi_bunny_static)
use_DynamoRIO_extension(cfi_bunny_static drmgr_static)
use_DynamoRIO_extension(cfi_bunny_static drbbdup_static)
use_DynamoRIO_extension(cfi_bunny_static drhit_static) 
use_DynamoRIO_extension(cfi_bunny_static drreg)
use_DynamoRIO_extension(cfi_bunny_static drutil)
use_DynamoRIO_extension(cfi_bunny_static drwrap)
use_DynamoRIO_extension(cfi_bunny_static drsyscall_static)
use_DynamoRIO_extension(cfi_bunny_static drsyms_static)
use_DynamoRIO_extension(cfi_bunny_static umbra_static)


set_property(TARGET cfi_bunny PROPERTY C_STANDARD 99)
set_property(TARGET cfi_bunny_static PROPERTY C_STANDARD 99)


if (UNIX)
target_link_libraries("cfi_bunny" ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny.so)
target_link_libraries("cfi_bunny" ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny.so)
target_link_libraries("cfi_bunny" ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny.so)
target_link_libraries("cfi_bunny" ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny.so)

  _DR_append_property_string(TARGET cfi_bunny COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET cfi_bunny COMPILE_DEFINITIONS "RC_IS_cfi_bunny")
endif ()


if (UNIX)
target_link_libraries("cfi_bunny_static" ${TAINT_BUNNY_DIR}/src/build/libtaint_bunny_static.a)
target_link_libraries("cfi_bunny_static" ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
target_link_libraries("cfi_bunny_static" ${SLICER_BUNNY_DIR}/src/build/libslicer_bunny_static.a)
target_link_libraries("cfi_bunny_static" ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)

  _DR_append_property_string(TARGET cfi_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET cfi_bunny_static COMPILE_DEFINITIONS "RC_IS_cfi_bunny")
endif ()

 



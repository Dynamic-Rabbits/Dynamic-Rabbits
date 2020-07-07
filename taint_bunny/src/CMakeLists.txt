cmake_minimum_required(VERSION 3.1.3)

include(${DYNAMORIO_SOURCE_DIR}/make/utils.cmake)
include(${DYNAMORIO_SOURCE_DIR}/make/policies.cmake NO_POLICY_SCOPE)

# DynamoRIO Register Management Utilities

set(DynamoRIO_USE_LIBC OFF)

set(srcs
   
    optimisations/fast_path_generator/tb_fp.c
    optimisations/fast_path_generator/tb_fp_optimisation.c
    optimisations/fast_path_generator/tb_fp_stat.c
    optimisations/fast_path_generator/tb_fp_helper.c

    instrumentation/tb_instrum_register_unsupported.c
    instrumentation/tb_instrum_register.c
    instrumentation/tb_instrum_register_helper.c
    
    taint_policies/cc_taint_policies/tb_cc_bitwise_policy.c
    taint_policies/cc_taint_policies/tb_cc_dummy_policy.c
    taint_policies/cc_taint_policies/tb_cc_dst_id_policy.c
    taint_policies/cc_taint_policies/tb_cc_set_policy.c
    taint_policies/cc_taint_policies/tb_cc_bitvector_policy.c
    taint_policies/cc_taint_policies/tb_cc_bitvect_tree_policy.c
    
    taint_policies/raw_taint_policies/tb_raw_bitvect_policy.c  
    taint_policies/raw_taint_policies/tb_raw_bitwise_policy.c
    taint_policies/raw_taint_policies/tb_raw_dst_id_policy.c
    taint_policies/raw_taint_policies/tb_raw_dummy_policy.c
    taint_policies/raw_taint_policies/tb_raw_bitvect_tree_policy.c
    
    taint_engines/instr_handlers/tb_ih_cc/instr_hndlrs/tb_cc_byt_instr_hndlrs.c
    taint_engines/instr_handlers/tb_ih_cc/instr_hndlrs/tb_cc_byte_ih_info.c
    taint_engines/instr_handlers/tb_ih_cc/instr_hndlrs/tb_cc_execution.c
    taint_engines/instr_handlers/tb_ih_cc/tb_ih_cc_instrum.c

    taint_engines/instr_handlers/tb_ih_raw/raw_instr_hndlrs/tb_raw_byt_instr_hndlrs.c
    taint_engines/instr_handlers/tb_ih_raw/raw_instr_hndlrs/tb_raw_byte_ih_info.c
    taint_engines/instr_handlers/tb_ih_raw/simd_instr_hndlrs/tb_simd_byt_instr_hndlrs.c
    taint_engines/instr_handlers/tb_ih_raw/simd_instr_hndlrs/tb_simd_byte_ih_info.c
    taint_engines/instr_handlers/tb_ih_raw/tb_raw_execution.c
    taint_engines/instr_handlers/tb_ih_raw/tb_raw_execution_helper.c
    taint_engines/instr_handlers/tb_ih_raw/tb_ih_raw_instrum.c

    taint_engines/instr_handlers/spill.c
    taint_engines/instr_handlers/tb_instruction_handler.c
    taint_engines/instr_handlers/tb_cc_instruction_handler_driver.c
    taint_engines/instr_handlers/tb_raw_instruction_handler_driver.c
    taint_engines/instr_handlers/tb_simd_instruction_handler_driver.c    

    taint_engines/taint_analysis/taint_checks/tb_ta_cc_check/tb_ta_cc_check.c
    taint_engines/taint_analysis/taint_checks/tb_ta_raw_check/tb_ta_raw_check.c
    taint_engines/taint_analysis/taint_checks/tb_ta_simd_check/tb_ta_simd_check.c

    taint_engines/taint_analysis/shdw_fault_handlers/tb_umbra_fault_handlers.c

    taint_engines/taint_analysis/taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.c

    taint_engines/taint_analysis/taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.c
    
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt_functionality.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_p_src_srcdst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_pack.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_punpck.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_dst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_src_dst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst_dst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst_srcdst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_src_srcdst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_srcdst.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_untaint.c
    taint_engines/taint_analysis/tb_cc_taint_analysis/tb_ta_cc_byt/tb_ta_cc_byt_xchg.c
   
    taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt_functionality.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_dst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_src_dst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_srcdst_dst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_srcdst_srcdst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_srcdst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_srcdst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_untaint.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_xchg.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_p_src_srcdst.c
	taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_punpck.c
    taint_engines/taint_analysis/tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_pack.c
    
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt_functionality.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_src_dst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_src_src_dst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_src_srcdst_dst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_src_srcdst_srcdst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_src_srcdst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_srcdst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_untaint.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_xchg.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_p_src_srcdst.c
	taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_punpck.c
    taint_engines/taint_analysis/tb_simd_taint_analysis/tb_ta_simd_byt/tb_ta_simd_byt_pack.c

    syscall_handlers/tb_syscall_handlers.c
    
    taint_engines/taint_analysis/taint_maps/tb_cc_map_driver.c
    taint_engines/taint_analysis/taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.c
    
    taint_engines/taint_analysis/taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.c
    taint_engines/taint_analysis/taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.c

	taint_annotations/tb_annotation_handler.c

    tls_access/tb_tls_access.c

    taint_bunny.c
)

include_directories(${UTILITY_BUNNY_DIR}/src ${INSTRUMENTATION_BUNNY_DIR}/src)
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

add_library(taint_bunny SHARED ${srcs})
configure_DynamoRIO_client(taint_bunny)
use_DynamoRIO_extension(taint_bunny drmgr)
use_DynamoRIO_extension(taint_bunny drcontainers)
use_DynamoRIO_extension(taint_bunny drreg)
use_DynamoRIO_extension(taint_bunny drbbdup)
use_DynamoRIO_extension(taint_bunny drhit)
use_DynamoRIO_extension(taint_bunny drwrap)
use_DynamoRIO_extension(taint_bunny drutil)
use_DynamoRIO_extension(taint_bunny umbra)
target_compile_options(taint_bunny PRIVATE -march=native)
#target_compile_options(taint_bunny PRIVATE -Werror -Wall -Wextra -Wno-unused-parameter 
#                                           -Wno-missing-field-initializers)


if (UNIX)
  target_link_libraries(taint_bunny ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny.so)
  target_link_libraries(taint_bunny ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny.so)
  _DR_append_property_string(TARGET taint_bunny COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET taint_bunny COMPILE_DEFINITIONS "RC_IS_taint_bunny")
endif ()

add_library(taint_bunny_static STATIC ${srcs_static})
configure_DynamoRIO_client(taint_bunny_static)
use_DynamoRIO_extension(taint_bunny_static drmgr_static)
use_DynamoRIO_extension(taint_bunny_static drreg_static)
use_DynamoRIO_extension(taint_bunny drbbdup_static)
use_DynamoRIO_extension(taint_bunny drhit_static)
use_DynamoRIO_extension(taint_bunny_static drwrap)
use_DynamoRIO_extension(taint_bunny_static drutil)
use_DynamoRIO_extension(taint_bunny_static umbra)
target_compile_options(taint_bunny_static PRIVATE -march=native)

set_property(TARGET taint_bunny PROPERTY C_STANDARD 99)
set_property(TARGET taint_bunny_static PROPERTY C_STANDARD 99)

if (UNIX)
  target_link_libraries(taint_bunny_static ${INSTRUMENTATION_BUNNY_DIR}/src/build/libinstrumentation_bunny_static.a)
  target_link_libraries(taint_bunny_static ${UTILITY_BUNNY_DIR}/src/build/libutility_bunny_static.a)
  _DR_append_property_string(TARGET taint_bunny_static COMPILE_FLAGS "-fPIC")
else ()
  include_directories(${DYNAMORIO_SOURCE_DIR}/core/lib)
  _DR_append_property_string(TARGET taint_bunny_static COMPILE_DEFINITIONS "RC_IS_taint_bunny")
endif ()


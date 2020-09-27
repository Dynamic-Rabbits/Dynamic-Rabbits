/**
 *  @file tb_defines.h
 *  @brief Definitions which are exported.
 *  @author John F.X. Galea
 */
#ifndef TB_DEFINES_H_
#define TB_DEFINES_H_

#include <stddef.h>
#include "utility_bunny.h"
#include "instrumentation_bunny.h"

#define TB_MEM_CONSERVATIVE 1

/***************************************************************************
 *  Introducing Taint Data
 */

/***************************************************************************
 *  Taint Introduction
 */

/**
 *  Considers memory byte location, passed as parameter, as tainted.
 *
 *  @param addr The memory address to taint
 *  @param taint_label The label to associate with the addr. Note this value cannot be NULL
 *  as we use this value to denote if a location is not tainted.
 */
DR_EXPORT void tb_taint_mem(void *taint_bunny_ctx, uintptr_t addr,
        void *taint_label);

/**
 *  Considers memory block location, passed as parameter, as tainted.
 *
 *  @param start_addr The starting memory address of the block to taint
 *  @param size The size of the block
 *  @param taint_label The label to associate with the block. Note this value cannot be NULL
 *  as we use this value to denote if a location is not tainted.
 */
DR_EXPORT void tb_taint_mem_block(void *taint_bunny_ctx, uintptr_t start_addr,
        size_t size, void *taint_label);

/**
 *  Considers a the entire register, passed as parameter, as tainted.
 *
 *  @param reg_id The register ID denoting which register to taint
 */
DR_EXPORT void tb_taint_reg(void *taint_bunny_ctx, void *drcontext,
        reg_id_t reg_id, void *taint_label);

/**
 *  Considers a byte in a register, passed as parameter, as tainted.
 *
 *  @param reg_id The register ID denoting which register to taint
 *  @param byte_index The register ID denoting which register to taint
 */
DR_EXPORT void tb_taint_reg_byte(void *taint_bunny_ctx, void *drcontext,
        reg_id_t reg_id, unsigned int byte_index, void *taint_label);

/**
 *  Untaints memory block location, passed as parameter.
 *
 *  @param addr The memory address to untaint
 */
DR_EXPORT void tb_untaint_mem_block(void *taint_bunny_ctx, uintptr_t addr,
        size_t size);

/**
 *  Untaints memory byte location.
 *
 *  @param addr The memory address to untaint
 */
DR_EXPORT void tb_untaint_mem(void *taint_bunny_ctx, uintptr_t addr);

/**
 *  Untaints a register.
 *
 *  @param reg_id The register ID denoting which register to untaint
 */
DR_EXPORT void tb_untaint_reg(void *taint_bunny_ctx, void *drcontext,
        reg_id_t reg_id);

/**
 *  Untaints a byte in a register, passed as parameter.
 *
 *  @param reg_id The register ID denoting which register to untaint
 *  @param byte_index The register ID denoting which register to untaint
 */
DR_EXPORT void tb_untaint_reg_byte(void *taint_bunny_ctx, void *drcontext,
        reg_id_t reg_id, unsigned int byte_index);

/****************************************************************************************
 *  Taint Checks
 */

/**
 * Returns whether a byte in the memory buffer is tainted.
 *
 * @param addr The starting address of the block
 * @param block_size The block size of memory.
 * @return Returns true if any byte within the memory block is tainted
 */
DR_EXPORT bool tb_is_mem_tainted(void *taint_bunny_ctx, uintptr_t addr);

/**
 * Returns whether some of the memory buffer is tainted.
 *
 * @param addr The starting address of the block
 * @param block_size The block size of memory.
 * @return Returns true if one or more bytes within the memory block are tainted
 */
DR_EXPORT bool tb_is_some_mem_tainted(void *taint_bunny_ctx,
        uintptr_t start_addr, size_t block_size);

/**
 * Returns whether memory buffer is completely tainted.
 *
 * @param addr The starting address of the block
 * @param block_size The block size of memory.
 * @return Returns true if all bytes within the memory block are tainted
 */
DR_EXPORT bool tb_is_mem_all_tainted(void *taint_bunny_ctx, uintptr_t addr,
        size_t block_size);

/**
 *  Determines whether a byte in a register is tainted.
 *
 *  @param reg_id The reg ID which denotes the register to check
 *  @return Returns true if any byte within the register is tainted
 */
DR_EXPORT bool tb_is_some_reg_byte_tainted(void *taint_bunny_ctx,
        void* drcontext, reg_id_t reg_id);

/**
 *  Determines whether all bytes in a register are tainted.
 *
 *  @param reg_id The reg ID which denotes the register to check
 *  @return Returns true if all bytes within the register is tainted
 */
DR_EXPORT bool tb_is_all_reg_tainted(void *taint_bunny_ctx, void* drcontext,
        reg_id_t reg_id);

/**
 *  Determines whether the byte in a register is tainted.
 *
 *  @param reg_id The reg ID which denotes the register to check
 *  @param byte_index The index of the byte in the register
 *  @return Returns true if any byte within the register is tainted
 */
DR_EXPORT bool tb_is_reg_byte_tainted(void *taint_bunny_ctx, void* drcontext,
        reg_id_t reg_id, unsigned long byte_index);

DR_EXPORT bool tb_is_reg_byte_tainted_via_byte_id(void *tb_ctx_opaque,
        void* drcontext, uintptr_t reg_byte_id);

DR_EXPORT bool tb_is_all_reg_block_tainted_via_byte_id(void *tb_ctx_opaque,
        void* drcontext, uintptr_t reg_byte_id, size_t block_size);

DR_EXPORT bool tb_is_some_reg_block_tainted_via_byte_id(void *tb_ctx_opaque,
        void* drcontext, uintptr_t reg_byte_id, size_t block_size);

/**
 * Retrieves the taint label of an address
 *
 * @param addr The address to check.
 * @return Returns the taint label or NULL if the passed address is not tainted.
 */
DR_EXPORT void* tb_mem_get_taint_label(void *taint_bunny_ctx, uintptr_t addr);

/**
 *  Retrieves the taint label of a register's byte
 *
 *  @param reg_id The register ID denoting which register to taint
 *  @param byte_index The index of the byte in the register
 *  @return Returns the taint label or NULL if the passed address is not tainted.
 */
DR_EXPORT void *tb_get_reg_byte_taint_label(void *taint_bunny_ctx,
        void* drcontext, reg_id_t reg_id, unsigned long byte_index);

DR_EXPORT void *tb_get_reg_byte_taint_label_via_byte_id(void *tb_ctx_opaque,
        void* drcontext, uintptr_t reg_byte_id);

/**
 * Retrieval via insert
 */

DR_EXPORT void tb_insert_get_mem_label(void *tb_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t scratch_reg);

DR_EXPORT void tb_insert_get_reg_label(void *tb_ctx_opaque, void *drcontext,
        instrlist_t *ilist, instr_t *where, reg_id_t scratch_reg,
        reg_id_t label_reg);

DR_EXPORT void tb_insert_is_some_reg_tainted_via_reg(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
        reg_id_t map_reg, reg_id_t vector_reg, size_t block_size,
        instr_t *true_case);

DR_EXPORT void tb_insert_is_some_reg_tainted(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t scratch_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *true_case);

DR_EXPORT void tb_insert_is_some_mem_tainted(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *true_case);

DR_EXPORT void tb_insert_is_all_reg_tainted_via_reg(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t id_reg,
        reg_id_t map_reg, reg_id_t vector_reg, size_t block_size,
        instr_t *false_case);

DR_EXPORT void tb_insert_is_all_reg_tainted(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t map_reg,
        unsigned int reg_byte_id, reg_id_t vector_reg,
        reg_id_t scaler_scratch_reg, size_t block_size, instr_t *false_case);

DR_EXPORT void tb_insert_is_all_mem_tainted(void *tb_ctx_opaque,
        void *drcontext, instrlist_t *ilist, instr_t *where, reg_id_t addr_reg,
        reg_id_t vector_reg, reg_id_t scratch_reg, size_t block_size,
        instr_t *false_case);

/**
 * Analysis Control
 */

DR_EXPORT void tb_turn_on_analysis(void *tb_ctx_opaque, void *drcontext);

DR_EXPORT void tb_turn_off_analysis(void *tb_ctx_opaque, void *drcontext);

DR_EXPORT bool tb_is_analysis_on(void *tb_ctx_opaque, void *drcontext);

DR_EXPORT void tb_insert_is_analysis_on(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *tb_ctx_opaque, instr_t* false_label);

typedef struct {
    size_t required_size;
    ushort dynamic_path_hit_threshold;
    size_t dups_limit;
    float bb_in_out_threshold;
    float pop_limit;
} tb_fp_settings_t;

typedef struct {
    bool enable_inline;
    bool enable_taint_off;
    bool enable_fp;
} tb_options_t;


#endif /* TB_DEFINES_H_ */

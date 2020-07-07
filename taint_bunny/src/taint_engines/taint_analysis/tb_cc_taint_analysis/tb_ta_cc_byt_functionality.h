/**
 *  @file tb_tracker_helper.h
 *  @brief A variety of helper functions used to
 *  @author John F.X. Galea
 */

#ifndef SRC_TRACKERS_TB_TRACKER_HELPER_H_
#define SRC_TRACKERS_TB_TRACKER_HELPER_H_

#include "../../../tb_bunny_private.h"
#include <stdint.h>
#include "utility_bunny.h"

/**********************************************************************************
 * Taint Introduction (Clean Call)
 ***********************************************************************************/

void tb_ta_cc_intro_taint_mem(tb_context_t *tb_ctx, uintptr_t addr,
        void *taint_label);

void tb_ta_cc_intro_taint_mem_block(tb_context_t *tb_ctx, uintptr_t start_addr,
        int block_sz, void *taint_label);

void tb_ta_cc_intro_taint_reg(tb_context_t *tb_ctx, void *map_opaque,
        unsigned int reg_byte_id, void *taint_label);

/**********************************************************************************
 * Taint Propagation (Clean Call)
 ***********************************************************************************/

void tb_ta_cc_set_untaint_mem(tb_context_t *tb_ctx, uintptr_t addr);
void tb_ta_cc_set_untaint_mem_block(tb_context_t *tb_ctx, uintptr_t addr_start,
        size_t block_sz);

void tb_ta_cc_set_untaint_reg(tb_context_t *tb_ctx, void *map_opaque,
        unsigned int reg_byte_id);

bool tb_ta_cc_prop_mem(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        uintptr_t dst_addr, void *result_label, bool perform_call);
bool tb_ta_cc_prop_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, unsigned int dst_reg, void * result_label,
        bool perform_call);

bool tb_ta_cc_prop_xchg_reg_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t reg_id1, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call);
bool tb_ta_cc_prop_xchg_mem_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t addr_id1, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call);
bool tb_ta_cc_prop_xchg_mem_mem(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t addr_id1, void *result_label1,
        uintptr_t addr_id2, void *result_label2, bool perform_call);

bool tb_ta_cc_prop_xadd_reg_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t reg_id1, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call);
bool tb_ta_cc_prop_xadd_mem_reg(tb_cc_instr_hndlr_info_t*instr_hndlr_info,
        void *reg_taint_map, uintptr_t addr, void *result_label1,
        uintptr_t reg_id2, void *result_label2, bool perform_call);

#endif /* SRC_TRACKERS_TB_TRACKER_HELPER_H_ */

/*
 * tb_ta_cc_byt_src_dst.c
 *
 *      Author: john
 */

#include "tb_ta_cc_byt_src_dst.h"

#include "../tb_ta_cc_byt_functionality.h"
#include "../../../../tb_bunny_private.h"
#include "../../../../tls_access/tb_tls_access.h"
#include "../../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_cc_reg_maps/tb_cc_array_reg_maps/tb_cc_array_reg_map.h"

#include "utility_bunny.h"
#include <stdint.h>

/****************************************************************************
 * SRC DST - DMEM SMEM
 */

static void tb_cc_handle_src_dst_dmem_smem(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
		uintptr_t dst_addr, uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;

	for (size_t i = 0; i < size; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);

		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, dst_addr + i,
				result_label, !succ);
		succ = succ || temp_res;
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_dmem_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id) {

	tb_cc_handle_src_dst_dmem_smem(instr_hndlr_info, 1, dst_addr, src_mem_id);
}

void tb_cc_byt_handle_src_dst_dmem_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id) {

	tb_cc_handle_src_dst_dmem_smem(instr_hndlr_info, 2, dst_addr, src_mem_id);
}

void tb_cc_byt_handle_src_dst_dmem_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id) {

	tb_cc_handle_src_dst_dmem_smem(instr_hndlr_info, 4, dst_addr, src_mem_id);
}

void tb_cc_byt_handle_src_dst_dmem_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id) {

	tb_cc_handle_src_dst_dmem_smem(instr_hndlr_info, 8, dst_addr, src_mem_id);
}

void tb_cc_byt_handle_src_dst_dmem_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_mem_id) {

	tb_cc_handle_src_dst_dmem_smem(instr_hndlr_info, 16, dst_addr, src_mem_id);
}

/*****************************************************************************
 * SRC DST - DMEM SREG
 */

static void tb_cc_handle_src_dst_dmem_sreg(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
		uintptr_t dst_addr, uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < size; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, dst_addr + i,
				result_label, !succ);
		succ = succ || temp_res;

	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_dmem_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dmem_sreg(instr_hndlr_info, 1, dst_addr, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dmem_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dmem_sreg(instr_hndlr_info, 2, dst_addr, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dmem_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dmem_sreg(instr_hndlr_info, 4, dst_addr, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dmem_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dmem_sreg(instr_hndlr_info, 8, dst_addr, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dmem_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dmem_sreg(instr_hndlr_info, 16, dst_addr, src_reg_id);
}

/*****************************************************************************
 * SRC DST - DREG SREG
 */

static void tb_cc_handle_src_dst_dreg_sreg(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
		uintptr_t dst_reg_id, uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < size; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ || temp_res;
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_dreg_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 1, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 2, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 4, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 8, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, dst_reg_id,
			src_reg_id);
}

/*****************************************************************************
 * SRC DST - DREG SMEM
 */

static void tb_cc_handle_src_dst_dreg_smem(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
		uintptr_t dst_reg_id, uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < size; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);

		succ = succ || temp_res;
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_dreg_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 1, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 2, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 4, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 8, dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 16, dst_reg_id,
			src_reg_id);
}

/*****************************************************************************
 * SRC DST - DREG SREG (EXTENSION)
 */

void tb_cc_byt_handle_src_dst_extension_dreg_2_sreg_1(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	void *reg_map = tb_get_reg_map(tb_ctx);
	void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map, src_reg_id);
	void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

	bool succ = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map, dst_reg_id,
			result_label,
			true);

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 1);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_1(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	void *reg_map = tb_get_reg_map(tb_ctx);
	void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map, src_reg_id);
	void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

	bool succ = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map, dst_reg_id,
			result_label,
			true);

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 1);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 2);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 3);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_4_sreg_2(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 2; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);

		succ = succ || temp_res;
	}

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 2);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 3);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_8_sreg_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 4; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);

		succ = succ || temp_res;
	}

	for (size_t i = 4; i < 8; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 4; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);

		succ = succ || temp_res;
	}

	for (size_t i = 4; i < 16; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_16_sreg_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 8; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);

		succ = succ || temp_res;
	}

	for (size_t i = 8; i < 16; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_2_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	void *reg_map = tb_get_reg_map(tb_ctx);
	void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map, src_mem_id);
	void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

	bool succ = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map, dst_reg_id,
			result_label,
			true);

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 1);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_4_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	void *reg_map = tb_get_reg_map(tb_ctx);
	void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map, src_mem_id);
	void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

	bool succ = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map, dst_reg_id,
			result_label,
			true);

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 1);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 2);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 3);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_4_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 2; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ | temp_res;
	}

	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 2);
	tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + 3);

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_8_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 4; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ | temp_res;
	}

	for (size_t i = 4; i < 8; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_16_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 4; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ | temp_res;
	}

	for (size_t i = 4; i < 16; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_extension_dreg_16_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	for (size_t i = 0; i < 8; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);
		void *result_label = tb_ctx->propogate_func_1dst_1src(src_label);

		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ | temp_res;
	}

	for (size_t i = 8; i < 16; i++) {
		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

/*****************************************************************************
 * SRC DST - DREG SREG (WHOLE)
 */

static void tb_cc_handle_src_dst_whole_dreg_sreg_untaint(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t dsize,
		size_t dsize_untaint, size_t ssize, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {
	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	void *meet_src_label = NULL;

	for (size_t i = 0; i < ssize; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);

		bool stop = tb_ctx->meet_func(&meet_src_label, src_label);

		if (stop)
			break;
	}

	if (tb_ctx->new_ref_func) {

		if (meet_src_label)
			tb_ctx->new_ref_func(meet_src_label);
	}

	for (size_t i = 0; i < dsize; i++) {

		void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label);
		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ || temp_res;
	}

	if (tb_ctx->delete_ref_func) {

		if (meet_src_label)
			tb_ctx->delete_ref_func(meet_src_label);
	}

	/** Untaint remaining bytes **/
	for (size_t i = dsize; i < dsize_untaint; i++) {

		tb_ta_cc_set_untaint_reg(tb_ctx, reg_map, dst_reg_id + i);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 0, 1,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 0, 2,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 4,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 8,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 16, 0, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 4, 8,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 8, 8,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 4, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 4, 8,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 8,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 4, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_8(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_4_sreg_16(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 16,
			dst_reg_id, src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_8_sreg_16(
		tb_cc_instr_hndlr_info_t *instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 16,
			dst_reg_id, src_reg_id);
}

/*****************************************************************************
 * SRC DST - DREG SMEM (WHOLE)
 */

static void tb_cc_handle_whole_src_dst_dreg_smem(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t size,
		uintptr_t dst_reg_id, uintptr_t src_mem_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	void *meet_src_label = NULL;

	for (size_t i = 0; i < size; i++) {

		void *src_label = tb_umbra_get_mem_taint_label(tb_ctx->mem_map,
				src_mem_id + i);

		bool stop = tb_ctx->meet_func(&meet_src_label, src_label);

		if (stop)
			break;
	}

	if (tb_ctx->new_ref_func) {

		if (meet_src_label)
			tb_ctx->new_ref_func(meet_src_label);
	}

	for (size_t i = 0; i < size; i++) {

		void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label);
		bool temp_res = tb_ta_cc_prop_reg(instr_hndlr_info, reg_map,
				dst_reg_id + i, result_label, !succ);
		succ = succ || temp_res;
	}

	if (tb_ctx->delete_ref_func) {

		if (meet_src_label)
			tb_ctx->delete_ref_func(meet_src_label);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_whole_dreg_1_smem_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 1, dst_reg_id,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_2_smem_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 2, dst_reg_id,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_4_smem_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 4, dst_reg_id,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_8_smem_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 8, dst_reg_id,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 16, dst_reg_id,
			src_reg_id);
}

/*****************************************************************************
 * SRC DST - DMEM SREG (WHOLE)
 */

static void tb_cc_handle_whole_src_dst_dmem_sreg(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, size_t dsize, size_t ssize,
		uintptr_t dst_addr, uintptr_t src_reg_id) {

	tb_context_t *tb_ctx = (tb_context_t *) instr_hndlr_info->tb_ctx;

	bool succ = false;
	void *reg_map = tb_get_reg_map(tb_ctx);

	void *meet_src_label = NULL;

	for (size_t i = 0; i < ssize; i++) {

		void *src_label = tb_cc_arraymap_get_reg_taint_label(reg_map,
				src_reg_id + i);

		bool stop = tb_ctx->meet_func(&meet_src_label, src_label);

		if (stop)
			break;
	}

	if (tb_ctx->new_ref_func) {

		if (meet_src_label)
			tb_ctx->new_ref_func(meet_src_label);
	}

	for (size_t i = 0; i < dsize; i++) {

		void *result_label = tb_ctx->propogate_func_1dst_1src(meet_src_label);
		bool temp_res = tb_ta_cc_prop_mem(instr_hndlr_info, dst_addr + i,
				result_label, !succ);
		succ = succ || temp_res;
	}

	if (tb_ctx->delete_ref_func) {

		if (meet_src_label)
			tb_ctx->delete_ref_func(meet_src_label);
	}

	if (succ && instr_hndlr_info->post_prop_func)
		instr_hndlr_info->post_prop_func(tb_ctx);
}

void tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_1(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 1, 1, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_2(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 2, 2, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_4(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 4, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_8(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 8, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 16, 16, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_1_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 1, 16, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_2_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 2, 16, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_4_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 16, dst_addr,
			src_reg_id);
}

void tb_cc_byt_handle_src_dst_whole_dmem_8_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_addr,
		uintptr_t src_reg_id) {

	tb_cc_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 16, dst_addr,
			src_reg_id);
}

/***********************************************************************
 * HIGH Mov
 */

void tb_cc_byt_handle_high_src_dst_dreg_16_sreg_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, dst_reg_id + 8,
			src_reg_id + 8);
}

void tb_cc_byt_handle_high_src_dst_dreg_16_smem_16(
		tb_cc_instr_hndlr_info_t*instr_hndlr_info, uintptr_t dst_reg_id,
		uintptr_t src_reg_id) {

	tb_cc_handle_src_dst_dreg_smem(instr_hndlr_info, 16, dst_reg_id + 8,
			src_reg_id + 8);
}

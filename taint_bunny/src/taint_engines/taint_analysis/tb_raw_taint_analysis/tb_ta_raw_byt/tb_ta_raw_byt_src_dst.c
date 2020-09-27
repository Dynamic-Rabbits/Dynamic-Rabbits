/*
 * tb_ta_raw_byt_src_dst.c
 *
 *      Author: john
 */

#include "../../tb_raw_taint_analysis/tb_ta_raw_byt/tb_ta_raw_byt_src_dst.h"

#include "../../taint_maps/memory_maps/tb_raw_mem_maps/tb_raw_umbra_mem_maps/tb_raw_umbra_mem_map.h"
#include "../../taint_maps/register_map/tb_raw_reg_maps/tb_raw_array_reg_maps/tb_raw_array_reg_map.h"
#include <stdint.h>
#include "utility_bunny.h"
#include "../../tb_raw_taint_analysis/tb_ta_raw_byt_functionality.h"

/****************************************************************************
 * SRC DST - DMEM SMEM
 */

static void tb_raw_handle_src_dst_dmem_smem_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
		instr_t *app_instr, reg_id_t dst_mem_id, reg_id_t src_mem_id,
		tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	// Translation
	if (translate) {
		tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, src_mem_id, spill_info->scaler_regs[2]);
		tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, dst_mem_id, spill_info->scaler_regs[2]);
	}

	for (size_t i = 0; i < size; i++) {

		opnd_t src_tl_opnd =
		OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));
		opnd_t dst_tl_opnd =
		OPND_CREATE_MEMPTR(dst_mem_id, i * sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_tl_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where,
				tb_raw_get_app_pc(app_instr), &dst_tl_opnd,
				spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
	}

	// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
}

static void tb_raw_handle_src_dst_dmem_smem(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, true, size, drcontext,
			ilist, where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_1_smem_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem(instr_hndlr_info, 1, drcontext, ilist,
			where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_2_smem_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem(instr_hndlr_info, 2, drcontext, ilist,
			where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_4_smem_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem(instr_hndlr_info, 4, drcontext, ilist,
			where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_8_smem_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem(instr_hndlr_info, 8, drcontext, ilist,
			where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_16_smem_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem(instr_hndlr_info, 16, drcontext, ilist,
			where, app_instr, dst_mem_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_1_smem_1_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 1,
			drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_2_smem_2_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 2,
			drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_4_smem_4_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 4,
			drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_8_smem_8_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 8,
			drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_16_smem_16_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_smem_ex(instr_hndlr_info, translate, 16,
			drcontext, ilist, where, app_instr, dst_mem_id, src_mem_id,
			spill_info);
}

/*****************************************************************************
 * SRC DST - DMEM SREG
 */

static void tb_raw_handle_src_dst_dmem_sreg_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		size_t size, void *drcontext, instrlist_t *ilist, instr_t *where,
		instr_t *app_instr, reg_id_t dst_mem_id, reg_id_t src_reg_id,
		tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	// Translation
	if (translate) {
		tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, spill_info->scaler_regs[3]);

		tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, spill_info->scaler_regs[3],
				src_reg_id);
		tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, dst_mem_id, spill_info->scaler_regs[2]);
	}

	for (size_t i = 0; i < size; i++) {

		opnd_t src_tl_opnd =
		OPND_CREATE_MEMPTR(src_reg_id, i * sizeof(void *));
		opnd_t dst_tl_opnd =
		OPND_CREATE_MEMPTR(dst_mem_id, i * sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_tl_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_mem(instr_hndlr_info, drcontext, ilist, where,
				tb_raw_get_app_pc(app_instr), &dst_tl_opnd,
				spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2]);

}

static void tb_raw_handle_src_dst_dmem_sreg(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, true, size, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_1_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg(instr_hndlr_info, 1, drcontext, ilist,
			where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_2_sreg_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg(instr_hndlr_info, 2, drcontext, ilist,
			where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_4_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg(instr_hndlr_info, 4, drcontext, ilist,
			where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_8_sreg_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg(instr_hndlr_info, 8, drcontext, ilist,
			where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_16_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg(instr_hndlr_info, 16, drcontext, ilist,
			where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_1_sreg_1_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 1,
			drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
			spill_info);

}

void tb_raw_byt_handle_src_dst_dmem_2_sreg_2_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 2,
			drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
			spill_info);

}

void tb_raw_byt_handle_src_dst_dmem_4_sreg_4_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 4,
			drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_8_sreg_8_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 8,
			drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_dmem_16_sreg_16_ex(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, bool translate,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dmem_sreg_ex(instr_hndlr_info, translate, 16,
			drcontext, ilist, where, app_instr, dst_mem_id, src_reg_id,
			spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SREG
 */

static void tb_raw_handle_src_dst_dreg_sreg(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size, size_t start,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(start < size);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[3]);

// Translation
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[3], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

	for (size_t i = start; i < size; i++) {

		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i * sizeof(void *));
		opnd_t dst_tl_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_tl_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_tl_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_src_dst_dreg_1_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 1, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_2_sreg_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 2, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_4_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 4, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_8_sreg_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 8, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_16_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SMEM
 */

static void tb_raw_handle_src_dst_dreg_smem(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size, size_t start,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	DR_ASSERT(start < size);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[3]);

// Translation
	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[2]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[3], dst_reg_id);

	for (size_t i = start; i < size; i++) {

		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));
		opnd_t dst_tl_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_tl_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_tl_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_src_dst_dreg_1_smem_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 1, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_2_smem_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 2, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_4_smem_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 4, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_8_smem_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 8, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_dreg_16_smem_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 16, 0, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SREG (EXTENSION)
 */

void tb_raw_byt_handle_src_dst_extension_dreg_2_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 2);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);

	// Fetch label and store it in dst

	// Get source label operand
	opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, 0);

	// Get new label.
	tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, tb_raw_get_app_pc(app_instr),
			spill_info->scaler_regs[2], &src_tl_opnd,
			spill_info->scaler_regs[3]);

	opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, 0);

	tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where, &dst_opnd,
			spill_info->scaler_regs[2], src_reg_id);

	dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, sizeof(void *));
	tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext, ilist,
			where, &dst_opnd, spill_info->scaler_regs[2], src_reg_id);

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], src_reg_id);
}

void tb_raw_byt_handle_src_dst_extension_dreg_4_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 2);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);

	// Fetch label and store it in dst

	// Get source label operand
	opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, 0);

	// Get new label.
	tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, tb_raw_get_app_pc(app_instr),
			spill_info->scaler_regs[2], &src_tl_opnd,
			spill_info->scaler_regs[3]);

	opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, 0);

	tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where, &dst_opnd,
			spill_info->scaler_regs[2], src_reg_id);

	for (int i = 1; i < 4; i++) {
		dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				src_reg_id);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], src_reg_id);
}

void tb_raw_byt_handle_src_dst_extension_dreg_4_sreg_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 2; i++) {
		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i* sizeof(void *));
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[2], &src_tl_opnd,
				spill_info->scaler_regs[3]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

	for (int i = 2; i < 4; i++) {

		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));
		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_8_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 4; i++) {
		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i* sizeof(void *));
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[2], &src_tl_opnd,
				spill_info->scaler_regs[3]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

	for (int i = 4; i < 8; i++) {

		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_16_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 4; i++) {
		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i* sizeof(void *));
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[2], &src_tl_opnd,
				spill_info->scaler_regs[3]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

	for (int i = 4; i < 16; i++) {

		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_16_sreg_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load Map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 8; i++) {
		opnd_t src_tl_opnd = OPND_CREATE_MEMPTR(src_reg_id, i* sizeof(void *));
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		// Get new label.
		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[2], &src_tl_opnd,
				spill_info->scaler_regs[3]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

	for (int i = 8; i < 16; i++) {

		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i* sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				spill_info->scaler_regs[3]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_2_smem_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 2);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[2]);

	// Load Reg Map:
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	// Fetch label and store it in dst
	opnd_t src_label_opnd = OPND_CREATE_MEMPTR(src_mem_id, 0);
	opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, 0);

	tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, tb_raw_get_app_pc(app_instr),
			spill_info->scaler_regs[2], &src_label_opnd,
			spill_info->scaler_regs[3]);

	tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where, &dst_opnd,
			spill_info->scaler_regs[2], src_mem_id);

	dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, sizeof(void *));

	tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext, ilist,
			where, &dst_opnd, spill_info->scaler_regs[2], src_mem_id);

	// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			src_mem_id, spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_4_smem_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 2);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[2]);

	// Load Reg Map:
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	// Fetch label and store it in dst
	opnd_t src_label_opnd = OPND_CREATE_MEMPTR(src_mem_id, 0);
	opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, 0);

	tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, tb_raw_get_app_pc(app_instr),
			spill_info->scaler_regs[2], &src_label_opnd,
			spill_info->scaler_regs[3]);

	tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where, &dst_opnd,
			spill_info->scaler_regs[2], src_mem_id);

	for (int i = 1; i < 4; i++) {

		dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[2],
				src_mem_id);
	}

	// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			src_mem_id, spill_info->scaler_regs[2]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_4_smem_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[3]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 2; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));
		opnd_t src_label_opnd =
		OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));

		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_label_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

	for (int i = 2; i < 4; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_8_smem_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[3]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 4; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));
		opnd_t src_label_opnd =
		OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));

		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_label_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

	for (int i = 4; i < 8; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_16_smem_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[3]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 4; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));
		opnd_t src_label_opnd =
		OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));

		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_label_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

	for (int i = 4; i < 16; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

void tb_raw_byt_handle_src_dst_extension_dreg_16_smem_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[3]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	for (int i = 0; i < 8; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));
		opnd_t src_label_opnd =
		OPND_CREATE_MEMPTR(src_mem_id, i * sizeof(void *));

		tb_raw_insert_get_new_label_from_1_src(instr_hndlr_info->tb_ctx,
				drcontext, ilist, where, tb_raw_get_app_pc(app_instr),
				spill_info->scaler_regs[3], &src_label_opnd,
				spill_info->scaler_regs[2]);

		tb_raw_insert_prop_reg(instr_hndlr_info, drcontext, ilist, where,
				&dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

	for (int i = 8; i < 16; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], spill_info->scaler_regs[3]);
}

/*****************************************************************************
 * SRC DST - DREG SREG (WHOLE)
 */

static void tb_raw_handle_src_dst_whole_dreg_sreg_untaint(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize,
		size_t dsize_untaint, size_t ssize, void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *app_instr, reg_id_t dst_reg_id,
		reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load reg map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext, ilist,
			where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
			src_reg_id, spill_info->scaler_regs[2]);

	tb_raw_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
			tb_raw_get_app_pc(app_instr), true, dst_reg_id, 0, dsize,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2], src_reg_id);

	for (size_t i = dsize; i < dsize_untaint; i++) {

		// Fetch label and store it in dst
		opnd_t dst_opnd = OPND_CREATE_MEMPTR(dst_reg_id, i * sizeof(void *));

		tb_raw_insert_set_untaint_reg(instr_hndlr_info->tb_ctx, drcontext,
				ilist, where, &dst_opnd, spill_info->scaler_regs[3],
				spill_info->scaler_regs[2]);
	}

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], src_reg_id);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 0, 1,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 0, 2,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_4_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 4,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_8_sreg_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 8,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_16_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 16, 0, 16,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 4, 8,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_8_untaint_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 8, 8,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 16, 4,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_sreg_16_untaint_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 1, 16, 8,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 4,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_8_untaint_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 8,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 4, 16,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_sreg_16_untaint_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 2, 8, 16,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_4_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 4, 0, 16,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_8_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_whole_dreg_sreg_untaint(instr_hndlr_info, 8, 0, 16,
			drcontext, ilist, where, app_instr, dst_reg_id, src_reg_id,
			spill_info);
}

/*****************************************************************************
 * SRC DST - DREG SMEM (WHOLE)
 */

static void tb_raw_handle_whole_src_dst_dreg_smem(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t size,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load reg map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, src_mem_id, spill_info->scaler_regs[3]);
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], dst_reg_id);

	tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, size, drcontext, ilist,
			where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
			src_mem_id, spill_info->scaler_regs[2]);

	tb_raw_apply_to_1_reg_from_1_src(instr_hndlr_info, drcontext, ilist, where,
			tb_raw_get_app_pc(app_instr), true, dst_reg_id, 0, size,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2], src_mem_id);

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], src_mem_id);
}

void tb_raw_byt_handle_src_dst_whole_dreg_1_smem_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 1, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_2_smem_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 2, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_4_smem_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 4, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_8_smem_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 8, drcontext, ilist,
			where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dreg_16_smem_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_mem_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dreg_smem(instr_hndlr_info, 16, drcontext,
			ilist, where, app_instr, dst_reg_id, src_mem_id, spill_info);
}

/*****************************************************************************
 * SRC DST - DMEM SREG (WHOLE)
 */

static void tb_raw_handle_whole_src_dst_dmem_sreg(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, size_t dsize, size_t ssize,
		void *drcontext, instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	DR_ASSERT(spill_info->scaler_cnt > 3);
	DR_ASSERT(spill_info->xmm_cnt == 0);

	tb_raw_clear_pre_post_propagate_flags(instr_hndlr_info, drcontext, ilist,
			where);

// Load reg map
	tb_raw_arraymap_insert_load_reg_map(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, spill_info->scaler_regs[2]);

// Translation:
	tb_raw_arraymap_insert_translate_address(instr_hndlr_info->tb_ctx,
			drcontext, ilist, where, spill_info->scaler_regs[2], src_reg_id);
	tb_umbra_insert_translate_address(instr_hndlr_info->tb_ctx, drcontext,
			ilist, where, dst_mem_id, spill_info->scaler_regs[3]);

	tb_raw_meet_from_1_src(instr_hndlr_info->tb_ctx, 0, ssize, drcontext, ilist,
			where, tb_raw_get_app_pc(app_instr), spill_info->scaler_regs[3],
			src_reg_id, spill_info->scaler_regs[2]);

	tb_raw_apply_to_1_mem_from_1_src(instr_hndlr_info, drcontext, ilist, where,
			tb_raw_get_app_pc(app_instr), dst_mem_id, 0, dsize,
			spill_info->scaler_regs[3], spill_info->scaler_regs[2], src_reg_id);

// We check whether we perform the post propagation call.
	tb_raw_check_post_propagate(instr_hndlr_info, drcontext, ilist, where,
			spill_info->scaler_regs[2], src_reg_id);
}

void tb_raw_byt_handle_src_dst_whole_dmem_1_sreg_1(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 1, 1, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_2_sreg_2(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 2, 2, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_4_sreg_4(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 4, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_8_sreg_8(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 8, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_16_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 16, 16, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_1_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 1, 16, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_2_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 2, 16, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_4_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 4, 16, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

void tb_raw_byt_handle_src_dst_whole_dmem_8_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_mem_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_whole_src_dst_dmem_sreg(instr_hndlr_info, 8, 16, drcontext,
			ilist, where, app_instr, dst_mem_id, src_reg_id, spill_info);
}

/***********************************************************************
 * HIGH Mov
 */

void tb_raw_byt_handle_high_src_dst_dreg_16_sreg_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_sreg(instr_hndlr_info, 16, 8, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);

}

void tb_raw_byt_handle_high_src_dst_dreg_16_smem_16(
		tb_raw_instr_hndlr_info_t *instr_hndlr_info, void *drcontext,
		instrlist_t *ilist, instr_t *where, instr_t *app_instr,
		reg_id_t dst_reg_id, reg_id_t src_reg_id, tb_spill_info_t *spill_info) {

	tb_raw_handle_src_dst_dreg_smem(instr_hndlr_info, 16, 8, drcontext, ilist,
			where, app_instr, dst_reg_id, src_reg_id, spill_info);

}

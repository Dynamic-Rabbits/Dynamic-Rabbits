/*
 * @author John F.X. Galea
 */

#include "ib_instrumenter.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "drreg.h"

#include "../tls_access/ib_tls_access.h"

#include "ib_opnd_store.h"
#include "ib_thread_data_loader.h"

#include "../hook_info/ib_hook_info.h"
#include "../ib_data.h"
#include "../options/ib_option.h"
#include "../opcode_hook_manager/ib_instrum_tool.h"
#include "../code_cache/ib_code_cache.h"

#include "utility_bunny.h"
#include "slicer_bunny.h"
#include <stddef.h>

extern ib_ctx_t *ib_ctx;

/***********************************************************************
 * Prototypes
 */
static void ib_instrument(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, ib_hook_summary_t *summary);

static void ib_insert_opcode(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where, ib_thrd_data_spill_info_t *info);

static void ib_insert_pc(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, ib_thrd_data_spill_info_t *info);
static void ib_insert_flags(void *drcontext, instrlist_t *ilist, instr_t *where,
		ib_thrd_data_spill_info_t *info);
static void ib_insert_opnd_counts(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where, ib_thrd_data_spill_info_t *info);

static void ib_instrument_jmp(void *drcontext, instrlist_t *ilist,
		instr_t *instr, ib_hook_info_t *hook_info);
static void ib_insert_instr_handle(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *app_instr, ib_hook_info_t *hook_info,
		void *instrumentation_handle);
static void ib_save_context(void *drcontext, instrlist_t *ilist, instr_t *where,
		reg_id_t *out_reg1, reg_id_t *out_reg2);
static void ib_restore_context(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg1, reg_id_t reg2);

static void ib_instrument_instr(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where,
		ib_instrum_analysis_data_t *analysis_data);

/***********************************************************************
 * Instrumentation Functions.
 */

void ib_instrumenter_init() {

	// We need to be conservative just in case.
	drreg_options_t ops = { sizeof(ops), 4, false, NULL, true };

	if (drreg_init(&ops) != DRREG_SUCCESS)
		DR_ASSERT(false);

}

void ib_instrumenter_exit() {
	drreg_exit();
}

void clean_call_trace(app_pc pc) {

	void *drcontext = dr_get_current_drcontext();

	instr_t instr;
	instr_init(drcontext, &instr);
	decode(drcontext, pc, &instr);

	char dis_instr_buf[300];

	if (instr_disassemble_to_buffer(drcontext, &instr, dis_instr_buf, 300)) {

		dr_fprintf(STDERR, "-----------------------------------------\n");

		dr_fprintf(STDERR, "Instr : %s (%d)\n", dis_instr_buf,
				instr_get_opcode(&instr));

		int sources = instr_num_srcs(&instr);
		int destinations = instr_num_dsts(&instr);

		for (int i = 0; i < sources; i++) {

			opnd_t src = instr_get_src(&instr, i);

			dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
			dr_get_mcontext(drcontext, &mcontext);

			if (opnd_is_memory_reference(src)) {
				dr_fprintf(STDERR, "\t Source: %p\n",
						opnd_compute_address(src, &mcontext));

				byte *buf = NULL;
				size_t read_size;
				dr_safe_read((void *) opnd_compute_address(src, &mcontext), 4,
						&buf, &read_size);
				dr_fprintf(STDERR, "\t\t The value is : %p\n", buf);

			} else if (ub_opnd_is_reg(&src)) {
				dr_fprintf(STDERR, "\t Source: %p\n",
						ub_get_byte_id(opnd_get_reg(src), 0));

				if (reg_is_xmm(opnd_get_reg(src))
						|| reg_is_gpr(opnd_get_reg(src))) {
					void *buf[200];
					reg_get_value_ex(opnd_get_reg(src), &mcontext, (byte*) buf);

					dr_fprintf(STDERR, "\t\t The value is : %p\n", *buf);
				}
			}
		}

		for (int i = 0; i < destinations; i++) {

			opnd_t dst = instr_get_dst(&instr, i);

			dr_mcontext_t mcontext = { sizeof(mcontext), DR_MC_ALL, };
			dr_get_mcontext(drcontext, &mcontext);

			if (opnd_is_memory_reference(dst)) {
				dr_fprintf(STDERR, "\t Dest: %p\n",
						opnd_compute_address(dst, &mcontext));

				byte *buf = NULL;
				size_t read_size;
				dr_safe_read((void *) opnd_compute_address(dst, &mcontext), 4,
						&buf, &read_size);
				dr_fprintf(STDERR, "\t\t The value is : %p\n", buf);

			} else if (ub_opnd_is_reg(&dst)) {
				dr_fprintf(STDERR, "\t Dest: %p\n",
						ub_get_byte_id(opnd_get_reg(dst), 0));

				if (reg_is_xmm(opnd_get_reg(dst))
						|| reg_is_gpr(opnd_get_reg(dst))) {
					void *buf[200];
					reg_get_value_ex(opnd_get_reg(dst), &mcontext,
							(byte*) &buf);

					dr_fprintf(STDERR, "\t\t The value is : %p\n", *buf);
				}
			}

		}
	}

	instr_free(drcontext, &instr);

}

/**
 *  The main dispatch function for instrumentation.
 *
 *  @param instr The instruction to instrument.
 */
void ib_dispatch_instr(void *drcontext, instrlist_t *ilist, instr_t *instr,  instr_t *where,
		ib_instrum_analysis_data_t *analysis_data) {

	// Check if instr is valid and an application instruction (and not a meta-instruction)
	if (!instr_valid(instr) || !instr_opcode_valid(instr)
			|| !instr_is_app(instr))
		return;

//    drreg_restore_all_now(drcontext, ilist, instr);
//    // Uncomment this code if you want to print data on the instructions executed!
//    dr_insert_clean_call(drcontext, ilist, instr, clean_call_trace,
//    false, 1, OPND_CREATE_INTPTR(instr_get_app_pc(instr)));

	/** We could make use of DR's module exclude here, but lets make use of slicer. **/
	if (!ib_ctx->slicer
			|| !sb_slice_instr(ib_ctx->slicer, instr_get_app_pc(instr)))
		ib_instrument_instr(drcontext, ilist, instr, where, analysis_data);
}

static void ib_instrument_instr(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where,
		ib_instrum_analysis_data_t *analysis_data) {

#ifdef DEBUG
	DR_ASSERT(ib_ctx);
	DR_ASSERT(ib_ctx->opcode_hook_mngr);
#endif

	int opcode = instr_get_opcode(instr);

	ib_hook_summary_t hook_summary;
	bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
			instr, &hook_summary, analysis_data);

	if (check != NULL && analysis_data
			&& analysis_data->action == IB_INSTRUM_ACTION_SKIP) {

		drreg_restore_all_now(drcontext, ilist, where);

		dr_insert_clean_call(drcontext, ilist, where, check, false, 2,
				OPND_CREATE_INTPTR(instr_get_app_pc(instr)),
				OPND_CREATE_INTPTR(check_data));
	}

	if (!skip) {

		ib_thrd_data_spill_info_t spill_info;
		ib_save_context(drcontext, ilist, where, &(spill_info.reg1),
				&(spill_info.reg2));
		spill_info.is_loaded = false;

		// We need to load pointer to thread data.

		if (hook_summary.is_opcode_enabled) {
			ib_loaded_thread_data(drcontext, ilist, where, &spill_info);
			ib_insert_opcode(drcontext, ilist, instr, where, &spill_info);
		}

		if (hook_summary.is_pc_enabled) {

			ib_insert_pc(drcontext, ilist, instr, where, &spill_info);
		}

		if (hook_summary.is_flag_enabled) {

			ib_loaded_thread_data(drcontext, ilist, where, &spill_info);
			ib_insert_flags(drcontext, ilist, where, &spill_info);
		}

		if (hook_summary.is_opnd_count_enabled) {
			ib_loaded_thread_data(drcontext, ilist, where, &spill_info);
			ib_insert_opnd_counts(drcontext, ilist, instr, where, &spill_info);
		}

		ib_insert_operands(drcontext, ilist, instr, where, opcode, &spill_info,
				&hook_summary);

		ib_restore_context(drcontext, ilist, where, spill_info.reg1,
				spill_info.reg2);

		ib_instrument(drcontext, ilist, instr, where, &hook_summary);
	}
}

/**
 *  Instruments a jmp instruction Depending on which branch is taken, control will jump to the appropriate
 *  code cache.
 *
 *  @param instr The instruction to instrument. Must be a JMP instruction
 */
static void ib_instrument_jmp(void *drcontext, instrlist_t *ilist,
		instr_t *instr, ib_hook_info_t *hook_info) {

	app_pc pc = instr_get_app_pc(instr);

#ifdef DEBUG
	//TODO Make this assert more precise.
	DR_ASSERT(instr_is_cti(instr));
	// Get PC of the jmp instruction.
	DR_ASSERT(pc != 0);
#endif

	app_pc fall_addr = (app_pc) decode_next_pc(drcontext, (byte *) pc);

	instr_t *fall_label = INSTR_CREATE_label(drcontext);

	instrlist_postinsert(ilist, instr,
			INSTR_CREATE_jmp(drcontext, opnd_create_instr(fall_label)));

	instrlist_meta_preinsert(ilist, NULL, fall_label);

	if (hook_info->is_inline) {

		if (hook_info->fall_through_func) {
			ib_insert_instr_handle(drcontext, ilist, NULL, instr, hook_info,
					hook_info->fall_through_func);
		}
	} else {

		if (hook_info->fall_through_func) {
			ib_insert_instr_handle(drcontext, ilist, NULL, instr, hook_info,
					hook_info->fall_through_func);
		}
	}

	instrlist_preinsert(ilist, NULL,
			INSTR_XL8(INSTR_CREATE_jmp(drcontext, opnd_create_pc(fall_addr)),
					fall_addr));

	app_pc target_addr = instr_get_branch_target_pc(instr);

	instr_t *target_label = INSTR_CREATE_label(drcontext);
	instr_set_meta_no_translation(instr);
	instr_set_target(instr, opnd_create_instr(target_label));

	// Place target label
	instrlist_meta_preinsert(ilist, NULL, target_label);

	if (hook_info->is_inline) {

		if (hook_info->target_func) {
			ib_insert_instr_handle(drcontext, ilist, NULL, instr, hook_info,
					hook_info->target_func);
		}
	} else {

		if (hook_info->target_func) {
			ib_insert_instr_handle(drcontext, ilist, NULL, instr, hook_info,
					hook_info->target_func);
		}
	}

	instrlist_preinsert(ilist, NULL,
			INSTR_XL8(INSTR_CREATE_jmp(drcontext, opnd_create_pc(target_addr)),
					target_addr));
}

/***********************************************************************
 * Helper Functions instrumenting instructions.
 */

static void ib_instrument_user_hook(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ib_hook_info_t *considered_hook_info) {

	if (considered_hook_info->user_func) {

		ib_insert_instr_handle(drcontext, ilist, where, instr,
				considered_hook_info, considered_hook_info->user_func);
	}
}

/**
 *  Instruments an instruction, jumping to code found in the passed caches.
 *
 *  These caches are stored in the hook list. Each entry in the hook list also
 *  has functions used for spilling and restoring registers.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param instr The instruction being optimised.
 *  @param is_taken_cache An internal flag to denote whether to use the code cache associated with
 *  the taken or fall through branch. For non-jmp instructions, is_taken_cache should be set to true.
 */
static void ib_instrument(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, ib_hook_summary_t *summary) {

	for (int i = 0; i < MAX_INSTRUM_HOOKS; i++) {

		ib_hook_info_t *considered_hook_info = summary->considered_hooks[i];

		if (!considered_hook_info) {
			return;
		}

		if (!considered_hook_info->is_branch_hook) {

			ib_instrument_user_hook(drcontext, ilist, where, instr,
					considered_hook_info);

		} else {

			DR_ASSERT(
					considered_hook_info->target_func
							|| considered_hook_info->fall_through_func);

			ib_instrument_user_hook(drcontext, ilist, where, instr,
					considered_hook_info);

			ib_instrument_jmp(drcontext, ilist, instr, considered_hook_info);

		}
	}
}

/**
 *  Inserts code responsible for populating with the opcode value of the
 *  instrumented instruction.
 *
 *  @param instr The instruction to store the opcode of.
 *  @param where The instruction where instrumentation will be placed before it
 *  @param data_reg Stores a pointer to the instrumentation data of the current thread
 *  @param scratch_reg_id Used as scratch. No guarantees on its resultant content
 */
static void ib_insert_opcode(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where, ib_thrd_data_spill_info_t *info) {

	opnd_t opnd = OPND_CREATE_MEMPTR(info->reg1,
			offsetof(ib_per_thread_t, instr_opcode));

	instrlist_insert_mov_immed_ptrsz(drcontext,
			(ptr_int_t) instr_get_opcode(instr), opnd, ilist, where, NULL,
			NULL);
}

/**
 *  Inserts code responsible for populating with the pc of the
 *  instrumented instruction.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param data_reg Stores a pointer to the instrum data of the current thread
 *  @param scratch_reg_id Used as scratch. No guarantees on its resultant content
 */
static void ib_insert_pc(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, ib_thrd_data_spill_info_t *info) {

	opnd_t opnd = ib_tls_get_raw_slot_opnd(IB_RAW_SLOT_PC_DATA);

	instrlist_insert_mov_immed_ptrsz(drcontext,
			(ptr_int_t) instr_get_app_pc(instr), opnd, ilist, where, NULL,
			NULL);
}

/**
 *  Inserts code responsible for populating with the value of the arithmetic of the
 *  instrumented instruction.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param data_reg Stores a pointer to the instrum data of the current thread
 *  @param scratch_reg_id Used as scratch. No guarantees on its resultant content.
 */
static void ib_insert_flags(void *drcontext, instrlist_t *ilist, instr_t *where,
		ib_thrd_data_spill_info_t *info) {

	// We need to restore aflags because we will be storing them.
	drreg_restore_app_aflags(drcontext, ilist, where);

	// Spill the stack pointer
	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, DR_REG_XSP,
			info->reg2);

	ub_instrum_store_eflags(drcontext, ilist, where, info->reg1,
			offsetof(ib_per_thread_t, flag_value));

	// Restore the stack pointer
	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, info->reg2,
			DR_REG_XSP);
}

/**
 *  Inserts code responsible storing the count of source and destination
 *  operands for an instrumented instruction.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param data_reg Stores a pointer to the instrum data of the current thread
 *  @param scratch_reg_id Used as scratch. No guarantees on its content
 */
static void ib_insert_opnd_counts(void *drcontext, instrlist_t *ilist,
		instr_t *instr, instr_t *where, ib_thrd_data_spill_info_t *info) {

	// Fetch the number of sources and destination operands.
	ptr_int_t num_srcs = (ptr_int_t) instr_num_srcs(instr);
	ptr_int_t num_dsts = (ptr_int_t) instr_num_dsts(instr);

	opnd_t opnd = OPND_CREATE_MEMPTR(info->reg1,
			offsetof(ib_per_thread_t, instr_src_count));

	instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) num_srcs, opnd,
			ilist, where, NULL, NULL);

	opnd = OPND_CREATE_MEMPTR(info->reg1,
			offsetof(ib_per_thread_t, instr_dst_count));

	instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) num_dsts, opnd,
			ilist, where, NULL, NULL);
}

/**
 *  Inserts jumps to the code caches, taking care of saving and restoring
 *  the current machine state.
 *
 *  @param where The instruction where instrumentation will be placed before it.
 *  @param hook_info Hook information to perform jump to code cache.
 */
static void ib_insert_instr_handle(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *app_instr, ib_hook_info_t *hook_info,
		void *instrumentation_handle) {

	if (hook_info->is_inline) {
		ib_insert_code_inline(drcontext, ilist, where, app_instr,
				instrumentation_handle);
	} else {
		ib_code_cache_insert_jmp_cache_instr(drcontext, ilist, where,
				instrumentation_handle);
	}
}

/****************************************************************************************
 *  Helper functions for saving and restoring the app machine state.
 */

/**
 *  Spills needed registers.
 *
 *  @param where The instruction where instrumentation will be placed
 *  before it
 */
static void ib_save_context(void *drcontext, instrlist_t *ilist, instr_t *where,
		reg_id_t *out_reg1, reg_id_t *out_reg2) {

	*out_reg1 = DR_REG_NULL;
	*out_reg2 = DR_REG_NULL;

	// Reg 2 needs to be able to access lower 8-bit reg.
	drvector_t allowed;
	drreg_init_and_fill_vector(&allowed, true);
	drreg_set_vector_entry(&allowed, DR_REG_ESP, false);
	drreg_set_vector_entry(&allowed, DR_REG_ESI, false);
	drreg_set_vector_entry(&allowed, DR_REG_EBP, false);
	drreg_set_vector_entry(&allowed, DR_REG_EDI, false);

	if (drreg_reserve_register(drcontext, ilist, where, &allowed, out_reg2)
			!= DRREG_SUCCESS) {
		DR_ASSERT(false); /* cannot recover */
		return;
	}
	drvector_delete(&allowed);

	if (drreg_reserve_register(drcontext, ilist, where, NULL, out_reg1)
			!= DRREG_SUCCESS) {
		DR_ASSERT(false); /* cannot recover */
		return;
	}
}

static void ib_restore_context(void *drcontext, instrlist_t *ilist,
		instr_t *where, reg_id_t reg1, reg_id_t reg2) {

	if (drreg_unreserve_register(drcontext, ilist, where, reg1)
			!= DRREG_SUCCESS)
		DR_ASSERT(false);
	if (drreg_unreserve_register(drcontext, ilist, where, reg2)
			!= DRREG_SUCCESS)
		DR_ASSERT(false);
}


/**
 *  @author John F.X. Galea
 */

#include "ib_opnd_store.h"

#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include "ib_thread_data_loader.h"

#include "drutil.h"
#include "drreg.h"

#include "../ib_data.h"
#include "../ib_defines.h"
#include "../options/ib_option.h"
#include "../opcode_hook_manager/ib_opcode_hook_manager.h"
#include "ib_slot.h"

#include "utility_bunny.h"

/***********************************************************************
 * Prototypes
 */

static void ib_insert_operands_all(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);
static void ib_insert_operands_dataflow(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

static void ib_extract_opnd_info(opnd_t *opnd,
		ib_opnd_extraction_data_t *out_opnd_data);

static void ib_insert_mem_opnd_store(void *drcontext, bool is_dst,
		instrlist_t *ilist, instr_t *where, ub_opnd_access_t opnd_access,
		ib_opnd_extraction_data_t *opnd_data, instr_t *instr,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary);

static void ib_insert_fixed_value_opnd_store(void *drcontext,
		instrlist_t *ilist, instr_t *where, loc_t type,
		ub_opnd_access_t *opnd_access, ib_opnd_extraction_data_t *opnd_data,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary);

static void ib_insert_immed_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

static void ib_insert_pc_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

static void ib_insert_invalid_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary);

static void ib_insert_store_conc_mem(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info);

static void ib_insert_reg_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

static void ib_insert_store_conc_reg(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info);

static void ib_insert_conc_reg_store_ind_hp(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, int mov_opcode,
		ib_thrd_data_spill_info_t *info);

static void ib_insert_conc_reg_store_hp(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, int mov_opcode,
		ib_thrd_data_spill_info_t *info, reg_id_t reg);

static void ib_insert_eff_addr_store(void *drcontext, bool is_dst,
		instrlist_t *ilist, instr_t *where, instr_t *instr,
		ub_opnd_access_t *opnd_access, ib_opnd_extraction_data_t *opnd_data,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary);

static bool ib_insert_opnd_store(void *drcontext, bool is_dst,
		instrlist_t *ilist, instr_t *where, opnd_t *opnd, instr_t *instr,
		ub_opnd_access_t opnd_access, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary);

/***********************************************************************
 * Implementation
 */

void ib_insert_operands(void *drcontext, instrlist_t *ilist, instr_t *instr,
		instr_t *where, int opcode, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	/*
	 The default is to save information on every operand. However, if partial save flag
	 is set, we attempt to save operand information without duplication. For instance,
	 when dealing with a src + srcdst instr, we do not store information of srcdst twice,
	 where one info is for the src, and the other is for the dst. Another example is
	 xchg. Rather than storing info as 4 pieces, where info on a register is stored twice because
	 it is both a src and dst, we store 2 pieces of info.

	 For push and pop, we do not store info on esp, because we are not really concerned with
	 the register. However The info related to the address present inside esp is stored
	 (which is useful)

	 We may achieve this functionality by making use of the UB's dataflow info extractor.
	 */

	if (summary->is_full_opnd_storage_enabled) {
		ib_insert_operands_all(drcontext, ilist, where, instr, info, summary);

	} else {
		ib_insert_operands_dataflow(drcontext, ilist, where, instr, info,
				summary);
	}
}

static void ib_insert_operands_dataflow(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

//    instr_disassemble(drcontext, instr, STDERR);
//    dr_fprintf(STDERR, "\n");

	ub_instr_dataflow_t dataflow_instr_info;
	ub_dataflow_get_info(instr, &dataflow_instr_info);

	size_t num_opnds = dataflow_instr_info.num_opnds;

	for (uint i = 0; i < num_opnds; i++) {

		ub_opnd_access_t opnd_access = dataflow_instr_info.opnd_access[i];
		opnd_t opnd = ub_opnd_access_get_opnd(instr, &opnd_access);
		ib_insert_opnd_store(drcontext, false, ilist, where, &opnd, instr,
				opnd_access, info, summary);
	}
}

static void ib_insert_operands_all(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	ub_opnd_access_t src_opnd_access;
	src_opnd_access.opnd_field = UB_SRC_OPND_1;
	src_opnd_access.comp_field = UB_COMP_1;

	if (instr_get_opcode(instr) == OP_rep_movs) {

		/* Special case for rep movs. We do not store the conc value for rep movs
		 * to avoid dereferencing invalid memory when XCX is zero.
		 */

		// Store source operands
		for (size_t i = 0; i < (unsigned int) instr_num_srcs(instr); i++) {

			opnd_t src_opnd = instr_get_src(instr, i);
			ib_insert_opnd_store(drcontext, ub_opnd_is_reg(&src_opnd), ilist,
					where, &src_opnd, instr, src_opnd_access, info, summary);
			src_opnd_access.opnd_field++;

#ifdef DEBUG
			DR_ASSERT(src_opnd_access.opnd_field <= IB_SRC_OPND_SLOT_6);
#endif
		}

	} else {
		// Store source operands
		for (size_t i = 0; i < (unsigned int) instr_num_srcs(instr); i++) {

			opnd_t src_opnd = instr_get_src(instr, i);
			ib_insert_opnd_store(drcontext, true, ilist, where, &src_opnd,
					instr, src_opnd_access, info, summary);
			src_opnd_access.opnd_field++;

#ifdef DEBUG
			DR_ASSERT(src_opnd_access.opnd_field <= IB_SRC_OPND_SLOT_6);
#endif
		}
	}

	ub_opnd_access_t dst_opnd_access;
	dst_opnd_access.opnd_field = UB_DST_OPND_1;
	dst_opnd_access.comp_field = UB_COMP_1;

	// Store destination operands
	for (size_t i = 0; i < (unsigned int) instr_num_dsts(instr); i++) {

		opnd_t dst_opnd = instr_get_dst(instr, i);

		/* Dont store conc values for destination */
		ib_insert_opnd_store(drcontext, false, ilist, where, &dst_opnd, instr,
				dst_opnd_access, info, summary);

		dst_opnd_access.opnd_field++;

#ifdef DEBUG
		DR_ASSERT(dst_opnd_access.opnd_field <= IB_DST_OPND_SLOT_6);
#endif
	}
}

/**
 * 	Responsible for inserting operand data in instrumentation data.
 * 	Such information will then be accessible via the code cache during
 * 	runtime.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd The opnd to store data on.
 *  @param opnd_mode Denotes which information of the opnd to store.
 *  @param opcode The opcode of the instruction.
 *  @param slot The slot used to store the information of the opnd
 *  @param data_reg Reg ID that contains pointer to instrum data for current thread.
 *  @param scratch_reg1 A scratch reg. No guarantees on the resultant value in
 *  this register.
 *  @return Returns true if the operand is not valid. Otherwise false.
 */
static bool ib_insert_opnd_store(void *drcontext, bool store_conc,
		instrlist_t *ilist, instr_t *where, opnd_t *opnd, instr_t *instr,
		ub_opnd_access_t opnd_access, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	ib_opnd_extraction_data_t opnd_data;
	ib_extract_opnd_info(opnd, &opnd_data);

	bool is_not_invalid = true;

	if (opnd_data.loc_data.type == UB_MEM_TYPE) {

		ib_insert_mem_opnd_store(drcontext, store_conc, ilist, where,
				opnd_access, &opnd_data, instr, info, summary);

		return true;
	}

	if (opnd_data.loc_data.type == UB_REG_TYPE) {

		ib_insert_reg_opnd_store(drcontext, ilist, where, instr, &opnd_access,
				&opnd_data, info, summary);

	} else if (opnd_data.loc_data.type == UB_IMMED_TYPE) {

		ib_insert_immed_opnd_store(drcontext, ilist, where, &opnd_access,
				&opnd_data, info, summary);

	} else if (opnd_data.loc_data.type == UB_PC_TYPE) {

		ib_insert_pc_opnd_store(drcontext, ilist, where, &opnd_access,
				&opnd_data, info, summary);

	} else {

		ib_insert_invalid_opnd_store(drcontext, ilist, where, &opnd_access,
				info, summary);
		is_not_invalid = false;
	}

	return is_not_invalid;
}

/***********************************************************************
 * Helper Functions
 */

/**
 *  Extracts information from opnds and stores it in out_opnd_data
 *
 *  @param opnd The opnd struct (defined by DynamoRIO) to extract data from
 *  @param out_opnd_data The struct to store extracted data
 */
static void ib_extract_opnd_info(opnd_t *opnd,
		ib_opnd_extraction_data_t *out_opnd_data) {

	out_opnd_data->opnd_data = *opnd;
	ub_get_loc_info(&(out_opnd_data->loc_data), opnd);
}

/**
 *  Gathers data on mem operand data and stores it in instrumentation data at a given slot
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd_slot The slot used to store opnd data
 *  @param opcode The opcode of the instruction.
 *  @param opnd_data Extracted opnd data
 *  @param data_reg Stores a pointer to the instrumentation data of the current thread
 *  @param scratch_reg1 Used as scratch. No guarantees on its resultant content
 *  @param scratch_reg2 Used as scratch. No guarantees on its resultant content.
 *  Must be different from scratch_reg1
 */
static void ib_insert_mem_opnd_store(void *drcontext, bool store_conc,
		instrlist_t *ilist, instr_t *where, ub_opnd_access_t opnd_access,
		ib_opnd_extraction_data_t *opnd_data, instr_t *instr,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary) {

	DR_ASSERT(opnd_access.comp_field == UB_COMP_1);

	ib_insert_eff_addr_store(drcontext, store_conc, ilist, where, instr,
			&opnd_access, opnd_data, info, summary);

	/*
	 *  The mode that determines which information about an operand to store and load.
	 *  If set false, the instrumenter will only store the effective address,
	 *  otherwise, it will also store sub-components.
	 */

	if (summary->is_addr_gen_enabled) {

		// Store the effective address, as well as the sub components
		if (opnd_is_base_disp(opnd_data->opnd_data)) {

			ib_opnd_extraction_data_t comp_opnd_data;

			opnd_access.comp_field = UB_COMP_2;

			reg_id_t base_reg = opnd_get_base(opnd_data->opnd_data);

			if (base_reg != DR_REG_NULL) {

				opnd_t base_opnd = opnd_create_reg(base_reg);
				ib_extract_opnd_info(&base_opnd, &comp_opnd_data);
				ib_insert_reg_opnd_store(drcontext, ilist, where, instr,
						&opnd_access, &comp_opnd_data, info, summary);
			}

			reg_id_t index_reg = opnd_get_index(opnd_data->opnd_data);
			if (index_reg != DR_REG_NULL) {

				opnd_access.comp_field = UB_COMP_3;

				opnd_t index_opnd = opnd_create_reg(index_reg);
				ib_extract_opnd_info(&index_opnd, &comp_opnd_data);
				ib_insert_reg_opnd_store(drcontext, ilist, where, instr,
						&opnd_access, &comp_opnd_data, info, summary);
			}

			if (summary->is_full_addr_gen_enabled) {

				opnd_access.comp_field = UB_COMP_4;

				opnd_t disp_opnd = opnd_create_immed_int(
						opnd_get_disp(opnd_data->opnd_data), OPSZ_32);
				ib_extract_opnd_info(&disp_opnd, &comp_opnd_data);
				ib_insert_immed_opnd_store(drcontext, ilist, where,
						&opnd_access, &comp_opnd_data, info, summary);

				opnd_access.comp_field = UB_COMP_5;

				opnd_t scale_opnd = opnd_create_immed_int(
						opnd_get_scale(opnd_data->opnd_data), OPSZ_32);
				ib_extract_opnd_info(&scale_opnd, &comp_opnd_data);
				ib_insert_immed_opnd_store(drcontext, ilist, where,
						&opnd_access, &comp_opnd_data, info, summary);
			}

		} else {
			DR_ASSERT(false);
		}
	}
}

/**
 *  Gathers data on mem operand data and stores it in thread context at a given slot.
 *
 *  @param where The instruction where instrumentation will be placed before it.
 *  @param instr The instruction.
 *  @param opnd_slot The slot used to store opnd data.
 *  @param comp_slot The inner component slot used to store the information of the opnd.
 *  @param data_reg Stores a pointer to the instrumentation data of the current thread.
 *  @param scratch_reg1 Used as scratch. No guarantees on its resultant content.
 *  @param scratch_reg2 Used as scratch. No guarantees on its resultant content.
 *  Must be different from scratch_reg1
 */
static void ib_insert_eff_addr_store(void *drcontext, bool store_conc,
		instrlist_t *ilist, instr_t *where, instr_t *instr,
		ub_opnd_access_t *opnd_access, ib_opnd_extraction_data_t *opnd_data,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary) {

	opnd_t opnd1, opnd2;
	instr_t *instr_tmp;

	if (summary->is_addr_opnd_enabled) {

		drreg_restore_app_values(drcontext, ilist, where, opnd_data->opnd_data,
				DR_REG_NULL);

		if (opnd_get_base(opnd_data->opnd_data) == info->reg1
				|| opnd_get_index(opnd_data->opnd_data) == info->reg1)
			info->is_loaded = false;

		bool scratch_used = false;

		// Operand is a memory reference operand. We use drutil to get the memory address.
#ifdef DEBUG
		bool succ =
#endif
		drutil_insert_get_mem_addr_ex(drcontext, ilist, where,
				opnd_data->opnd_data, info->reg2, info->reg1, &scratch_used);

#ifdef DEBUG
		DR_ASSERT(succ);
#endif

		if (scratch_used || !info->is_loaded) {
			info->is_loaded = false;
		}

		if (!ib_get_fast_slot(opnd_access, &opnd2)) {
			ib_loaded_thread_data(drcontext, ilist, where, info);
			opnd2 = ib_get_slow_comp_slot_opnd(info->reg1, opnd_access);
		}

		opnd1 = opnd_create_reg(info->reg2);
		instr_tmp = INSTR_CREATE_mov_st(drcontext, opnd2, opnd1);
		instrlist_meta_preinsert(ilist, where, instr_tmp);

		if (store_conc && summary->is_conc_enabled) {
			ib_loaded_thread_data(drcontext, ilist, where, info);

			ib_insert_store_conc_mem(drcontext, ilist, where, opnd_access,
					opnd_data, info);
		}
	}

	if (summary->is_loc_type_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_type(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext, UB_MEM_TYPE, opnd1, ilist,
				where, NULL, NULL);
	}

	if (summary->is_loc_size_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_size(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext,
				(ptr_int_t) opnd_data->loc_data.size, opnd1, ilist, where, NULL,
				NULL);
	}
}

static void ib_insert_fixed_value_opnd_store(void *drcontext,
		instrlist_t *ilist, instr_t *where, loc_t type,
		ub_opnd_access_t *opnd_access, ib_opnd_extraction_data_t *opnd_data,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary) {

	ib_loaded_thread_data(drcontext, ilist, where, info);

	opnd_t opnd;
	size_t size;

#ifdef X86_32
	size = 4;
#elif defined(X86_64)
	size = 8;
#endif

	if (summary->is_loc_type_enabled) {
		opnd = ib_get_comp_slot_type(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) type, opnd,
				ilist, where, NULL, NULL);
	}

	if (summary->is_loc_size_enabled) {
		opnd = ib_get_comp_slot_size(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext,
				(ptr_int_t) opnd_data->loc_data.size, opnd, ilist, where, NULL,
				NULL);
	}

	if (summary->is_immed_opnd_enabled) {
		opnd = ib_get_comp_slot_conc(info->reg1, size, opnd_access, 0);
		instrlist_insert_mov_immed_ptrsz(drcontext,
				(ptr_int_t) opnd_data->loc_data.opnd, opnd, ilist, where, NULL,
				NULL);
	}
}

/**
 *  Gathers immed operand data and stores it at a given slot.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd_data Extracted opnd data
 *  @param opnd_slot The opnd slot used to store the information of the opnd
 *  @param comp_slot The inner component slot used to store the information of the opnd
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread.
 *  @return Returns true if the operand is not valid. Otherwise false.
 */
static void ib_insert_immed_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	ib_insert_fixed_value_opnd_store(drcontext, ilist, where, UB_IMMED_TYPE,
			opnd_access, opnd_data, info, summary);
}

/**
 *  Gathers PC operand data and stores it at a given slot.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd_data Extracted opnd data
 *  @param opnd_slot The opnd slot used to store the information of the opnd
 *  @param comp_slot The inner component slot used to store the information of the opnd
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread.
 *  @return Returns true if the operand is not valid. Otherwise false.
 */
static void ib_insert_pc_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	ib_insert_fixed_value_opnd_store(drcontext, ilist, where, UB_PC_TYPE,
			opnd_access, opnd_data, info, summary);

}

/**
 *  Handles data stored in slot when an invalid opnd is encountered. Essentially, it
 *  nullifies the data.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd_data Extracted opnd data
 *  @param opnd_slot The opnd slot used to store the information of the opnd
 *  @param comp_slot The inner component slot used to store the information of the opnd
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread.
 *  @return Returns true if the operand is not valid. Otherwise false.
 */
static void ib_insert_invalid_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_thrd_data_spill_info_t *info, ib_hook_summary_t *summary) {

	opnd_t opnd1;

	if (!ib_get_fast_slot(opnd_access, &opnd1)) {
		ib_loaded_thread_data(drcontext, ilist, where, info);
		opnd1 = ib_get_slow_comp_slot_opnd(info->reg1, opnd_access);
	}

	instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd1, ilist,
			where, NULL, NULL);

	if (summary->is_loc_type_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_type(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd1,
				ilist, where, NULL, NULL);
	}

	if (summary->is_loc_size_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_size(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext, (ptr_int_t) NULL, opnd1,
				ilist, where, NULL, NULL);
	}
}

/**
 *  Responsible storing concrete memory to destination register, and storing the content.
 *  Note that memory content can be stored in a stepwise fashion the case we are dealing
 *  with memory dereferences that are larger than the size of a gpr.
 *
 *  For instance, storing a 128-bit sized value would involve using the EAX reg, which
 *  is 32-bit in size, 4 times.
 *
 *  It is a helper function for ib_insert_store_conc_mem
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param opnd_data Extracted opnd data
 *  @param disp A displacement value used to access the array responsible for storing the
 *  conc value at a particular index.
 *  @param opnd_slot The opnd slot used to store the information of the opnd
 *  @param comp_slot The inner component slot used to store the information of the opnd
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread
 *  @param src_opnd The memory address to dereference.
 *  @param dst_opnd The register to contain the memory value. Note it has to be suitably sized
 *  according to the size of the memory dereference.
 *  @return Returns true if the operand is not valid. Otherwise false.
 */
static void ib_insert_store_mem_hp(void *drcontext, instrlist_t *ilist,
		instr_t *where, bool use_zx, ub_opnd_access_t *comp_access_slot,
		size_t disp, reg_id_t data_reg, opnd_t src_opnd, opnd_t dst_reg) {

#ifdef DEBUG
	DR_ASSERT(opnd_is_reg(dst_reg));
#endif

	instr_t *instr;

	/**
	 *  First store memory to register. Remember, we need to consider the
	 *  operand size to know how many bytes to store.
	 */

	if (use_zx) {

		instr = INSTR_CREATE_movzx(drcontext, dst_reg, src_opnd);
		app_pc pc = instr_get_app_pc(where);
		instr_set_translation(instr, pc);
		instrlist_meta_preinsert(ilist, where, instr);

	} else {

		instr = INSTR_CREATE_mov_ld(drcontext, dst_reg, src_opnd);
		app_pc pc = instr_get_app_pc(where);
		instr_set_translation(instr, pc);
		instrlist_meta_preinsert(ilist, where, instr);

	}

	size_t size = opnd_size_in_bytes(OPSZ_PTR);

	// TODO use movz here to break dependency chain. Need to check if src register is smaller
	// than dst reg to use movz, (use standard mov when their sizes are equal).

	opnd_t opnd2 = ib_get_comp_slot_conc(data_reg, size, comp_access_slot,
			disp);
	instr = INSTR_CREATE_mov_st(drcontext, opnd2, dst_reg);
	instrlist_meta_preinsert(ilist, where, instr);
}

/**
 *  Responsible storing and storing conc memory
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param comp_access_slot The inner component slot used to store the information of the opnd
 *  @param opnd_data Extracted opnd data
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread
 *  @param addr_reg A register that contains the effective address
 */
static void ib_insert_store_conc_mem(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info) {

	reg_id_t addr_reg;

	switch (opnd_data->loc_data.size) {

	case 16:

		drreg_reserve_register(drcontext, ilist, where, NULL, &addr_reg);
		ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, info->reg2,
				addr_reg);

#ifdef X86_32

		for (int i = 0; i < 16; i += 4) {

			ib_insert_store_mem_hp(drcontext, ilist, where, false, opnd_access,
					i, info->reg1, OPND_CREATE_MEM32(addr_reg, i),
					opnd_create_reg(info->reg2));
		}

#elif defined(X86_64)

		for (int i = 0; i < 16; i += 8) {

			ib_insert_store_mem_hp(drcontext, ilist, where, opnd_slot, comp_slot, i,
					reg1, OPND_CREATE_MEM64(addr_reg, i),
					opnd_create_reg(info->reg2));

		}
#endif

		drreg_unreserve_register(drcontext, ilist, where, addr_reg);
		break;

	case 8:
		drreg_reserve_register(drcontext, ilist, where, NULL, &addr_reg);
		ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where, info->reg2,
				addr_reg);

#ifdef X86_32
		for (int i = 0; i < 8; i += 4) {

			ib_insert_store_mem_hp(drcontext, ilist, where, false, opnd_access,
					i, info->reg1, OPND_CREATE_MEM32(addr_reg, i),
					opnd_create_reg(info->reg2));
		}
#elif defined(X86_64)

		ib_insert_store_mem_hp(drcontext, ilist, where, opnd_slot, comp_slot, 0,
				reg1, OPND_CREATE_MEM32(addr_reg, 0),
				opnd_create_reg(info->reg2));

#endif

		drreg_unreserve_register(drcontext, ilist, where, addr_reg);
		break;

	case 4:
		ib_insert_store_mem_hp(drcontext, ilist, where, false, opnd_access, 0,
				info->reg1, OPND_CREATE_MEM32(info->reg2, 0),
				opnd_create_reg(info->reg2));
		break;

	case 2:
		ib_insert_store_mem_hp(drcontext, ilist, where, true, opnd_access, 0,
				info->reg1, OPND_CREATE_MEM16(info->reg2, 0),
				opnd_create_reg(info->reg2));
		break;

	case 1:

		ib_insert_store_mem_hp(drcontext, ilist, where, true, opnd_access, 0,
				info->reg1, OPND_CREATE_MEM8(info->reg2, 0),
				opnd_create_reg(info->reg2));
		break;
	}

}

/**
 * 	Gathers data on reg operand data and stores it in instrumentation data at a given component slot.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @param comp_access_slot The slot for storing information of the opnd
 *  @param opnd_data Extracted opnd data
 *  @param opcode The opcode of the instr.
 *  @param data_reg A reg ID that contains pointer to instrumentation data for current thread
 *  @param scratch_reg Used as scratch. No guarantees on its resultant content
 *  @return Returns true if the operand is not valid. Otherwise false
 */
static void ib_insert_reg_opnd_store(void *drcontext, instrlist_t *ilist,
		instr_t *where, instr_t *instr, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info,
		ib_hook_summary_t *summary) {

	opnd_t opnd1;

	if (summary->is_reg_opnd_enabled || summary->is_addr_gen_enabled) {

		if (!ib_get_fast_slot(opnd_access, &opnd1)) {
			ib_loaded_thread_data(drcontext, ilist, where, info);
			opnd1 = ib_get_slow_comp_slot_opnd(info->reg1, opnd_access);
		}

		instrlist_insert_mov_immed_ptrsz(drcontext,
				ub_get_byte_id(opnd_data->loc_data.opnd, 0), opnd1, ilist,
				where, NULL, NULL);
	}

	if (summary->is_loc_type_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_type(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext, UB_REG_TYPE, opnd1, ilist,
				where, NULL, NULL);
	}

	// Insert opnd size
	if (summary->is_loc_size_enabled) {
		ib_loaded_thread_data(drcontext, ilist, where, info);

		opnd1 = ib_get_comp_slot_size(info->reg1, opnd_access);
		instrlist_insert_mov_immed_ptrsz(drcontext,
				(ptr_int_t) opnd_data->loc_data.size, opnd1, ilist, where, NULL,
				NULL);
	}

	if (summary->is_conc_enabled) {
		// Loads the instrum data us.
		ib_insert_store_conc_reg(drcontext, ilist, where, opnd_access,
				opnd_data, info);
	}
}

/**
 *  Gathers reg operand data and stores it in  at a given component slot.
 *
 *	Note, it is assumed that DR_REG_XAX is spilled.
 *
 *  @param where Instrumentation code is placed prior to where
 *	@param comp_access_slot The comp slot considered for accessing
 *	@param opnd_data Extracted opnd data
 *	@param data_reg A register used to load instrumentation data of current reg.
 *	Note this function will load the instrumentation data. It does this in the case that
 *	the register used to store the data contains the conc value we are interested
 *	in
 */
static void ib_insert_store_conc_reg(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, ib_thrd_data_spill_info_t *info) {

	if (!reg_is_xmm(opnd_data->loc_data.opnd)
			&& !reg_is_gpr(opnd_data->loc_data.opnd)) {

#ifdef DEBUG
		DR_ASSERT_MSG(false, "Register type not supported yet!\n");
#endif
		return;
	}

	drreg_restore_app_values(drcontext, ilist, where, opnd_data->opnd_data,
			DR_REG_NULL);

	if (reg_resize_to_opsz(opnd_data->loc_data.opnd, OPSZ_PTR) == info->reg1)
		info->is_loaded = false;

	/*
	 * We use the appropriate reg and instruction depending on the size of
	 * the operand
	 */

	switch (opnd_data->loc_data.size) {

	case 16:
		ib_insert_conc_reg_store_ind_hp(drcontext, ilist, where, opnd_access,
				opnd_data, OP_movdqu, info);

		break;

	case 8:

#ifdef X86_32
		ib_insert_conc_reg_store_ind_hp(drcontext, ilist, where, opnd_access,
				opnd_data, OP_movq, info);

#elif defined(X86_64)

		ib_insert_conc_reg_store_hp(drcontext, ilist, where,
				opnd_access, opnd_data, OP_mov_st,
				info, info->reg2);
#endif

		break;

	case 4:
		if (reg_is_64bit(opnd_data->loc_data.opnd)
				|| reg_is_xmm(opnd_data->loc_data.opnd))
			ib_insert_conc_reg_store_ind_hp(drcontext, ilist, where,
					opnd_access, opnd_data, OP_movd, info);

		else
			ib_insert_conc_reg_store_hp(drcontext, ilist, where, opnd_access,
					opnd_data, OP_mov_st, info, info->reg2);

		break;

	case 2:
		ib_insert_conc_reg_store_hp(drcontext, ilist, where, opnd_access,
				opnd_data, OP_mov_st, info, reg_32_to_16(info->reg2));
		break;

	case 1:
		ib_insert_conc_reg_store_hp(drcontext, ilist, where, opnd_access,
				opnd_data, OP_mov_st, info, reg_32_to_8(info->reg2));
		break;
	}

	// We dont add an assert here, but we need to ensure that upon exit, data_reg is loaded
}

static void ib_insert_conc_reg_store_ind_hp(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, int mov_opcode,
		ib_thrd_data_spill_info_t *info) {

	opnd_t opnd1, opnd2;
	instr_t *instr;

	reg_id_t reg_val = opnd_data->loc_data.opnd;

	if (reg_resize_to_opsz(opnd_data->loc_data.opnd, OPSZ_PTR) == info->reg1) {

		info->is_loaded = false;

		ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where,
				opnd_data->loc_data.opnd, info->reg2);
		reg_val = info->reg2;
	}

	ib_loaded_thread_data(drcontext, ilist, where, info);

	opnd1 = opnd_create_reg(reg_val);
	opnd2 = ib_get_comp_slot_conc(info->reg1, opnd_data->loc_data.size,
			opnd_access, 0);

	instr = instr_create_1dst_1src(drcontext, mov_opcode, opnd2, opnd1);
	instrlist_meta_preinsert(ilist, where, instr);

}

/**
 *  Stores the concrete value of a register to the scratch reg, and stores
 *  it in the instrumentation data at the specified component slot.
 *
 *  A helper function for ib_insert_conc_reg_store.
 *
 *  @param where Instrumentation code is placed prior to where
 *	@param comp_access_slot The comp slot considered for accessing
 *	@param opnd_data Extracted opnd data
 *	@param data_reg A register used to load instrumentation data of current reg.
 *	Note this function will load the instrumentation data. It does this in the case that
 *	the register used to store the data contains the conc value we are interested
 *	in.
 *	@param mov_opcode A register used to load instrumentation data of current reg.
 *	@param reg Used as an intermediary register to when storing in a slot. It is
 *	used to avoid clobbering the conc value if it is in data_reg
 */
static void ib_insert_conc_reg_store_hp(void *drcontext, instrlist_t *ilist,
		instr_t *where, ub_opnd_access_t *opnd_access,
		ib_opnd_extraction_data_t *opnd_data, int mov_opcode,
		ib_thrd_data_spill_info_t *info, reg_id_t reg) {

#ifdef DEBUG
	DR_ASSERT(reg != info->reg1);
#endif

	/**
	 * We store in contents of the reg first in cases where
	 * opnd_data->opnd is equal to data_reg
	 */

	opnd_t opnd1, opnd2;
	instr_t *instr;

	drreg_restore_app_values(drcontext, ilist, where, opnd_data->opnd_data,
			DR_REG_NULL);

	// If the conc value in the the same register as the data_reg, we need
	// to use a temp register.
	if (reg_resize_to_opsz(opnd_data->loc_data.opnd, OPSZ_PTR) == info->reg1) {
		info->is_loaded = false;

		DR_ASSERT(opnd_data->loc_data.opnd != reg);
		ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where,
				opnd_data->loc_data.opnd, reg);
	} else {
		reg = opnd_data->loc_data.opnd;
	}

	ib_loaded_thread_data(drcontext, ilist, where, info);

	opnd1 = opnd_create_reg(reg);
	opnd2 = ib_get_comp_slot_conc(info->reg1, opnd_data->loc_data.size,
			opnd_access, 0);
	instr = instr_create_1dst_1src(drcontext, mov_opcode, opnd2, opnd1);
	instrlist_meta_preinsert(ilist, where, instr);
}

/*
 * ub_mod_analysis.c
 *
 *      Author: john
 */

#include "ub_constant_analysis.h"
#include "drvector.h"
#include "string.h"
#include "../instruction/ub_instruction_checker.h"

#define GPR_IDX(reg) ((reg)-DR_REG_START_GPR)

/*
 * When determining which fast path to take, we need to calculate the taint status of memory.
 * Unfortunately, things get very complex due to pointer analysis if previous instructions, such as
 * lea, calculates the addresses via data.
 *
 * When we encounter a memory reference where the base or index are modified between the start and the reference,
 * we truncate the basic block, so that future analysis of the bb will have the taint check right prior to the reference.
 *
 * We therefore avoid HARD IMPRECISE POINTER ANALYSIS. WOOT!
 *
 * However, this comes at a cost of more taint checks which becomes the bottleneck!
 *
 * Keeping track of bools that indicate whether registers have been modified is not enough,
 * otherwise we will end up trancating quite a lot, for individual instructions such as push.
 *
 * We therefore need to be a bit more intelligent...
 *
 * We keep track of disps too! We do not perform full blown emulation, just add and subtraction.
 * For stack related operations, such as push and pop, this is enough...
 *
 * In future work, I will improve this! If you too got any ideas, please contact me.
 *
 */

static bool opnd_uses_mod_address(opnd_t opnd, ub_constant_state_t *state) {

    reg_id_t reg;

    if (opnd_is_base_disp(opnd) && opnd_get_size(opnd) != OPSZ_lea) {
        for (reg = DR_REG_START_GPR; reg <= DR_REG_STOP_GPR; reg++) {
            if ((state->reg_constant_data[GPR_IDX(reg)].modified)
                    && opnd_uses_reg(opnd, reg))
                return true;
        }
    }

    return false;
}

static void ub_constant_default(ub_constant_info_t *constant_info) {

    constant_info->modified = true;
    constant_info->emulated_disp = 0;
}

static void ub_constant_propagation(instr_t *instr, reg_id_t reg_id,
        ub_constant_info_t *constant_info) {

    // TODO: Elaborate this function and make it more robust!
    // Keep calm, it's just a prototype!


    reg_id_t xsp_check;
    int opcode = instr_get_opcode(instr);
    switch (opcode) {

    case OP_add:

        if (ub_is_srcdst_src_dreg_simm_instr(instr)) {

            opnd_t immed_src = instr_get_src(instr, 0);
            DR_ASSERT(opnd_is_immed_int(immed_src));
            ptr_int_t disp = opnd_get_immed_int(immed_src);

            constant_info->emulated_disp += (int) disp;
            return;
        }
        ub_constant_default(constant_info);
        break;

    case OP_sub:

        if (ub_is_srcdst_src_dreg_simm_instr(instr)) {

            opnd_t immed_src = instr_get_src(instr, 0);
            DR_ASSERT(opnd_is_immed_int(immed_src));
            ptr_int_t disp = opnd_get_immed_int(immed_src);

            constant_info->emulated_disp -= (int) disp;
            return;
        }
        ub_constant_default(constant_info);
        break;

    case OP_inc:
        constant_info->emulated_disp += 1;
        return;

    case OP_dec:
        constant_info->emulated_disp -= 1;
        return;

    case OP_pop:

        xsp_check = opnd_get_reg(instr_get_dst(instr, 0));
        if (xsp_check != DR_REG_XSP && reg_id == DR_REG_XSP) {
            /* Make sure xsp is not dst reg */
            constant_info->emulated_disp += sizeof(void *);
            return;
        }

        ub_constant_default(constant_info);
        break;

    case OP_push:
    case OP_push_imm:

        if (reg_id == DR_REG_XSP) {

            constant_info->emulated_disp -= sizeof(void *);
            return;
        }
        ub_constant_default(constant_info);
        break;

    default:
        ub_constant_default(constant_info);
    }
}

/****************************************************************
 * On point
 *
 * Useful to avoid heavy mem allocs.
 */

void ub_constant_analysis_init(ub_constant_state_t *state) {

    memset(state, 0, sizeof(ub_constant_state_t));
}

bool ub_constant_analysis_instr_uses_mod_addr_regs(ub_constant_state_t *state,
        instr_t *instr) {

    // Check sources:
    int src_num = instr_num_srcs(instr);
    for (int i = 0; i < src_num; i++) {

        opnd_t src_opnd = instr_get_src(instr, i);
        if (opnd_uses_mod_address(src_opnd, state))
            return true;
    }

    // Check destinations:
    int dst_num = instr_num_dsts(instr);
    for (int i = 0; i < dst_num; i++) {

        opnd_t dst_opnd = instr_get_dst(instr, i);
        if (opnd_uses_mod_address(dst_opnd, state))
            return true;
    }

    return false;
}

bool ub_constant_analysis_is_reg_constant(ub_constant_state_t *state,
        reg_id_t reg_id, int *disp) {

    ub_constant_info_t * constant_info = &(state->reg_constant_data[GPR_IDX(
            reg_id)]);

    *disp = constant_info->emulated_disp;
    return !constant_info->modified;
}

void ub_constant_analysis_update(ub_constant_state_t *state, instr_t *instr) {

    DR_ASSERT(instr);
    DR_ASSERT(state);

    reg_id_t reg;

    for (reg = DR_REG_START_GPR; reg <= DR_REG_STOP_GPR; reg++) {

        if (instr_writes_to_reg(instr, reg, DR_QUERY_INCLUDE_ALL)) {
            ub_constant_propagation(instr, reg,
                    &(state->reg_constant_data[GPR_IDX(reg)]));
        }
    }
}

bool ub_constant_analysis_patch_addr(ub_constant_state_t *state,
        opnd_t *mem_opnd) {

    if (!opnd_is_memory_reference(*mem_opnd))
        return false;

    if (opnd_is_base_disp(*mem_opnd)) {

        int constant_disp = 0;

        // Check Base
        reg_id_t base = opnd_get_base(*mem_opnd);
        if (base != DR_REG_NULL) {
            DR_ASSERT(!state->reg_constant_data[GPR_IDX(base)].modified);
            constant_disp +=
                    state->reg_constant_data[GPR_IDX(base)].emulated_disp;
        }

        // Check Index
        reg_id_t index = opnd_get_index(*mem_opnd);
        if (index != DR_REG_NULL) {

            int scale = opnd_get_scale(*mem_opnd);

            DR_ASSERT(!state->reg_constant_data[GPR_IDX(index)].modified);
            constant_disp += (scale
                    * state->reg_constant_data[GPR_IDX(index)].emulated_disp);
        }

        int disp = opnd_get_disp(*mem_opnd);
        opnd_set_disp(mem_opnd, constant_disp + disp);
        return true;
    }

    return false;
}

/****************************************************************
 * VIA result
 *
 * Useful to avoid heavy mem allocs.
 */

bool ub_constant_analysis_patch_addr_via_result(void* constant_analysis_opaque,
        opnd_t *mem_opnd, uint instr_index) {

    drvector_t *constant_analysis = (drvector_t *) constant_analysis_opaque;
    ub_constant_state_t *state = drvector_get_entry(constant_analysis,
            instr_index);

    return ub_constant_analysis_patch_addr(state, mem_opnd);
}

bool ub_constant_analysis_instr_uses_mod_addr_regs_via_result(
        void* constant_analysis_opaque, instr_t *instr, uint instr_index) {

    DR_ASSERT(constant_analysis_opaque);

    drvector_t *result = (drvector_t *) constant_analysis_opaque;
    ub_constant_state_t *state = drvector_get_entry(result, instr_index);

    return ub_constant_analysis_instr_uses_mod_addr_regs(state, instr);
}

bool ub_constant_analysis_is_reg_constant_via_result(
        void* constant_analysis_opaque, uint instr_index, reg_id_t reg_id,
        int *disp) {

    DR_ASSERT(constant_analysis_opaque);

    drvector_t *result = (drvector_t *) constant_analysis_opaque;
    ub_constant_state_t *state = drvector_get_entry(result, instr_index);

    return ub_constant_analysis_is_reg_constant(state, reg_id, disp);
}

static void ub_free_reg_constant_data(void *data) {

    dr_global_free(data, sizeof(ub_constant_state_t));
}

void* ub_constant_analysis_result(instrlist_t *bb) {

    drvector_t *constant_analysis = (drvector_t *) dr_global_alloc(
            sizeof(drvector_t));
    drvector_init(constant_analysis, 6, false, ub_free_reg_constant_data);

    ub_constant_state_t *prev_state = NULL;

    instr_t *instr = instrlist_first_app(bb);

    int index = 0;

    while (instr) {

        // Allocate constant data for each reg.
        ub_constant_state_t *state = dr_global_alloc(
                sizeof(ub_constant_state_t));

        if (prev_state) {
            memcpy(state, prev_state, sizeof(ub_constant_state_t));
        } else {

            bool *empty_modified = dr_global_alloc(sizeof(ub_constant_state_t));

            // Before the bb, everything is constant and emulated disps are 0.
            memset(empty_modified, 0, sizeof(ub_constant_state_t));

            memset(state, 0, sizeof(ub_constant_state_t));
            drvector_set_entry(constant_analysis, index, empty_modified);
            index++;
        }

        ub_constant_analysis_update(state, instr);

        drvector_set_entry(constant_analysis, index, state);
        prev_state = state;

        instr = instr_get_next_app(instr);
        index++;
    }

    return constant_analysis;
}

void ub_constant_analysis_destroy_result(void* constant_analysis_opaque) {

    DR_ASSERT(constant_analysis_opaque);
    drvector_t *result = (drvector_t *) constant_analysis_opaque;

    drvector_delete(result);
    dr_global_free(result, sizeof(drvector_t));

}

/**************************************************************
 * Other
 */

/*
 *  Does not contain data for every instr at the bb, and therefore is faster.
 *  Avoid allocations.
 *
 *  Returns if true if an instr uses a modified reg for calculating an address.
 *
 */
bool ub_constant_analysis_get_index_at_modified(instrlist_t *bb, uint *index) {

    *index = 0;
    instr_t *instr = instrlist_first_app(bb);

    ub_constant_state_t state;
    ub_constant_analysis_init(&state);

    while (instr) {

        if (ub_constant_analysis_instr_uses_mod_addr_regs(&state, instr))
            return true;

        ub_constant_analysis_update(&state, instr);

        instr = instr_get_next_app(instr);
        (*index)++;
    }

    return false;
}

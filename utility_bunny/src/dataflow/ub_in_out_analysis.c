/*
 * tb_in_out_analysis.c
 *
 *      Author: john
 */

#include "ub_in_out_analysis.h"
#include "ub_instr_flows.h"
#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include  <stdint.h>
#include  "../datastructs/lists/ub_list.h"
#include "ub_constant_analysis.h"
#include "../location/ub_loc.h"
#include "../register/ub_register.h"

/****************************************************
 * Helper functions
 */

static opnd_t *copy_opnd(opnd_t opnd) {

    opnd_t *copy = dr_global_alloc(sizeof(opnd_t));
    *copy = opnd;
    return copy;
}

static reg_id_t normalise_reg(reg_id_t reg_id) {

    if (reg_is_gpr(reg_id)) {
        return reg_resize_to_opsz(reg_id, OPSZ_PTR);
    }

    return reg_id;
}

static bool examine_reg_opnd(opnd_t *stored_opnd, opnd_t *opnd, bool do_update) {

    reg_id_t stored_reg = opnd_get_reg(*stored_opnd);
    reg_id_t considered_reg = opnd_get_reg(*opnd);

    if (opnd_get_reg(*opnd) == opnd_get_reg(*stored_opnd)) {

        size_t existing_size2 = opnd_size_in_bytes(opnd_get_size(*stored_opnd));
        size_t considering_size = opnd_size_in_bytes(opnd_get_size(*opnd));

        /**
         * We store the largest access to the register, not smaller
         * partial accesses (e.g. for xmm).
         */
        if (do_update && considering_size > existing_size2)
            *stored_opnd = *opnd;

        return false;
    }

    /* Handle regs */
    if (reg_is_gpr(stored_reg) && reg_is_gpr(considered_reg)) {

        reg_id_t stored_ptr_reg = normalise_reg(stored_reg);
        reg_id_t considered_ptr_reg = normalise_reg(considered_reg);

        if (stored_ptr_reg != DR_REG_NULL
                && stored_ptr_reg == considered_ptr_reg) {
            return false;
        }
    }

    return true;
}

static bool examine_mem_opnd(opnd_t *in, opnd_t *opnd, bool do_update) {

    if (opnd_same_address(*in, *opnd)) {

        size_t existing_size2 = opnd_size_in_bytes(opnd_get_size(*in));
        size_t considering_size = opnd_size_in_bytes(opnd_get_size(*opnd));

        /* We store the largest opnd size accessing the address */
        if (do_update && considering_size > existing_size2) {
            *in = *opnd;
        }

        return false;
    }

    return true;
}

static bool examine_opnd_list(void *list, opnd_t *opnd, bool do_update) {

    DR_ASSERT(opnd_is_memory_reference(*opnd) || ub_opnd_is_reg(opnd));

    for (void * it = ub_list_get_start_it(list); it;
            it = ub_list_get_next_it(it)) {

        opnd_t *stored_opnd = ub_list_get_it_value(it);

        if (opnd_same(*opnd, *stored_opnd))
            return false;

        if (ub_opnd_is_reg(opnd) && ub_opnd_is_reg(stored_opnd)) {

            if (!examine_reg_opnd(stored_opnd, opnd, do_update))
                return false;
        } else {

            if (!examine_mem_opnd(stored_opnd, opnd, do_update))
                return false;
        }
    }

    return true;
}

bool ub_is_opnd_base_disp_no_index(opnd_t *ref_opnd) {

    bool are_regs_okay = (opnd_is_base_disp(*ref_opnd)
            && opnd_get_index(*ref_opnd) == DR_REG_NULL
            && opnd_get_base(*ref_opnd) != DR_REG_NULL);

    /**
     * TODO:
     * We need to set this range check because when sharing translation for fp,
     * we are skipping the redzone and a crash is occurring for extremely large
     * disps that span over a page!
     *
     * For disps that exceed the limit, we cannot share the translation,
     * but we need to do translate again.
     *
     * Further document this!
     *
     * Keep calm, it's just a prototype!
     */

    int disp = opnd_get_disp(*ref_opnd);
    bool is_disp_okay = -100 < disp && disp <= 100;

    return are_regs_okay && is_disp_okay;
}

static void ub_analyse_mem_base_opnd(opnd_t *opnd, ub_in_out_set_t *set) {

    DR_ASSERT(opnd_is_memory_reference(*opnd));

    reg_id_t base = opnd_get_base(*opnd);
    int disp = opnd_get_disp(*opnd);

    bool found_sublist = false;
    bool inserted = false;

    void *prev_it = NULL;

    for (void * it = ub_list_get_start_it(set->mem_base_list); it; it =
            ub_list_get_next_it(it)) {

        opnd_t *stored_opnd = ub_list_get_it_value(it);
        reg_id_t base2 = opnd_get_base(*stored_opnd);
        int disp2 = opnd_get_disp(*stored_opnd);

        if (base == base2)
            found_sublist = true;

        if (found_sublist) {

            if (base == base2) {

                /* If opnd is already in list, just return */

                if (!examine_mem_opnd(stored_opnd, opnd, true))
                    return;

                /* If disp is less than the current, place here so we have ascending order.*/
                if (disp < disp2) {
                    opnd_t *copy = copy_opnd(*opnd);
                    ub_list_insert_it_value(set->mem_base_list, prev_it, copy);
                    return;
                }

            } else {

                /**
                 *  We found a sequence of opnds that share the same base register with
                 *  the opnd to insert. This sequence has just ended and it's time
                 *  to append our opnd to the sequence. Note that uniqueness is checked.
                 */
                DR_ASSERT(prev_it);

                opnd_t *copy = copy_opnd(*opnd);
                ub_list_insert_it_value(set->mem_base_list, prev_it, copy);
                return;
            }
        }

        prev_it = it;
    }

    /* opnd was not inserted, insert it now */
    if (!inserted) {
        opnd_t *copy = copy_opnd(*opnd);
        ub_list_insert(set->mem_base_list, copy);
    }
}

static void ub_analyse_reg_opnd(opnd_t *opnd, ub_in_out_set_t *set) {

    DR_ASSERT(ub_opnd_is_reg(opnd));

    reg_id_t reg = opnd_get_reg(*opnd);
    reg_id_t norm_reg = normalise_reg(reg);

    void *prev_it = NULL;

    for (void * it = ub_list_get_start_it(set->reg_list); it; it =
            ub_list_get_next_it(it)) {

        opnd_t *stored_opnd = ub_list_get_it_value(it);
        reg_id_t reg2 = opnd_get_reg(*stored_opnd);
        reg_id_t norm_reg2 = normalise_reg(reg2);

        if (!examine_reg_opnd(stored_opnd, opnd, true)) {
            return;
        } else if (norm_reg < norm_reg2) {
            opnd_t *copy = copy_opnd(opnd_create_reg(norm_reg));
            ub_list_insert_it_value(set->reg_list, prev_it, copy);
            return;
        }

        prev_it = it;
    }

    opnd_t *copy = copy_opnd(opnd_create_reg(norm_reg));
    ub_list_insert(set->reg_list, copy);
}

static void ub_analyse_opnd(opnd_t *opnd, ub_loc_info_t *loc_info,
        ub_in_out_set_t *set) {

    if (loc_info->type == UB_REG_TYPE) {
        ub_analyse_reg_opnd(opnd, set);

    } else if (loc_info->type == UB_MEM_TYPE) {

        if (ub_is_opnd_base_disp_no_index(opnd)) {
            ub_analyse_mem_base_opnd(opnd, set);
        } else {

            if (examine_opnd_list(set->mem_list, opnd, true)) {
                opnd_t *copy = copy_opnd(*opnd);
                ub_list_insert(set->mem_list, copy);
            }
        }
    }
}

void ub_get_out_set_of_regs(ub_in_out_set_t *out_sets, instrlist_t *bb) {

    size_t num_flows;
    size_t num_srcs;

    ub_instr_dataflow_t instr_dataflow;

    instr_t *instr = instrlist_first_app(bb);
    while (instr) {

        ub_dataflow_get_info(instr, &instr_dataflow);

        // We need to get dataflow info.
        num_flows = ub_dataflow_num_flows(&instr_dataflow);

        // Now handle the outs
        for (size_t i = 0; i < num_flows; i++) {

            opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow, i);

            ub_loc_info_t loc_info;
            ub_get_loc_info(&loc_info, &dst_opnd);

            if (loc_info.type == UB_REG_TYPE){

                ub_analyse_reg_opnd(&dst_opnd, out_sets);
            }
        }

        instr = instr_get_next_app(instr);
    }
}

static void ub_analyse_bb(instrlist_t *bb, ub_in_out_set_t *in_set,
        ub_in_out_set_t *out_set, bool is_set) {

    size_t num_flows;
    size_t num_srcs;

    ub_instr_dataflow_t instr_dataflow;
    ub_constant_state_t constant_state;
    ub_constant_analysis_init(&constant_state);

    instr_t *instr = instrlist_first_app(bb);
    while (instr) {

        /*
         * Any writes to address generation registers changes the the ins and outs when
         * the address is read. We therefore need to ensure that registers are constant when
         * a memory read, where ref is in the form base + disp, occurs.
         */
        DR_ASSERT(
                !ub_constant_analysis_instr_uses_mod_addr_regs(&constant_state,
                        instr));

        ub_dataflow_get_info(instr, &instr_dataflow);

        // We need to get dataflow info.
        num_flows = ub_dataflow_num_flows(&instr_dataflow);

        // We first needs to consider the inputs.
        for (size_t i = 0; i < num_flows; i++) {

            num_srcs = ub_dataflow_flow_num_srcs(&instr_dataflow, i);

            for (size_t j = 0; j < num_srcs; j++) {
                opnd_t src_opnd = ub_dataflow_get_flow_src(instr, &instr_dataflow, i,
                        j);

                ub_loc_info_t loc_info;
                ub_get_loc_info(&loc_info, &src_opnd);

                // If it is a memory operand, we need to patch it with constant data.

                if (loc_info.type == UB_MEM_TYPE)
                    ub_constant_analysis_patch_addr(&constant_state, &src_opnd);

                /* If we are not generating a single in_out set, then check if output
                 * opnd is already in the out set
                 */
                if (is_set
                        || !ub_is_opnd_in_out_set(out_set, &src_opnd,
                                &loc_info))
                    ub_analyse_opnd(&src_opnd, &loc_info, in_set);
            }
        }

        // Now handle the outs
        for (size_t i = 0; i < num_flows; i++) {

            opnd_t dst_opnd = ub_dataflow_get_flow_dst(instr, &instr_dataflow, i);

            ub_loc_info_t loc_info;
            ub_get_loc_info(&loc_info, &dst_opnd);

            if (loc_info.type == UB_MEM_TYPE)
                ub_constant_analysis_patch_addr(&constant_state, &dst_opnd);

            ub_analyse_opnd(&dst_opnd, &loc_info, out_set);
        }

        ub_constant_analysis_update(&constant_state, instr);

        instr = instr_get_next_app(instr);
    }
}

bool ub_is_opnd_in_out_set(ub_in_out_set_t *set, opnd_t *opnd,
        ub_loc_info_t *loc_info) {

    if (loc_info->type == UB_REG_TYPE) {
        return !examine_opnd_list(set->reg_list, opnd, false /*Don't Update*/);

    } else if (loc_info->type == UB_MEM_TYPE) {

        if (ub_is_opnd_base_disp_no_index(opnd)) {
            return !examine_opnd_list(set->mem_base_list, opnd,
            false /*Don't Update*/);
        } else {

            return !examine_opnd_list(set->mem_list, opnd,
            false /*Don't Update*/);
        }
    }

    return false;
}



void ub_get_in_out_set(ub_in_out_set_t *set, instrlist_t *bb) {

    ub_analyse_bb(bb, set, set, true);
}

void ub_get_in_out_opnds(ub_in_out_opnds_t *in_out_opnds, instrlist_t *bb) {

    ub_analyse_bb(bb, &(in_out_opnds->in_set), &(in_out_opnds->out_set),
    false);
}

void ub_init_in_out_set(ub_in_out_set_t *set) {

    set->reg_list = ub_list_create();
    set->mem_list = ub_list_create();
    set->mem_base_list = ub_list_create();
}

void ub_init_in_out_opnds(ub_in_out_opnds_t *in_out_opnds) {

    ub_init_in_out_set(&(in_out_opnds->in_set));
    ub_init_in_out_set(&(in_out_opnds->out_set));
}

static void ub_destroy_opnd(void *opnd_opaque) {
    dr_global_free(opnd_opaque, sizeof(opnd_t));
}

void ub_delete_in_out_set(ub_in_out_set_t *set) {

    ub_list_destroy(set->reg_list, ub_destroy_opnd);
    ub_list_destroy(set->mem_list, ub_destroy_opnd);
    ub_list_destroy(set->mem_base_list, ub_destroy_opnd);
}

void ub_delete_in_out_opnds(ub_in_out_opnds_t *in_out_opnds) {

    ub_delete_in_out_set(&(in_out_opnds->in_set));
    ub_delete_in_out_set(&(in_out_opnds->out_set));
}

size_t ub_size_in_out_set(ub_in_out_set_t *set) {

    size_t total = 0;

    total += ub_list_get_size(set->reg_list);
    total += ub_list_get_size(set->mem_list);
    total += ub_list_get_size(set->mem_base_list);

    return total;
}

size_t ub_size_in_out_opnds(ub_in_out_opnds_t *in_out_opnds) {

    size_t total = 0;

    total = ub_size_in_out_set(&(in_out_opnds->in_set));
    total += ub_size_in_out_set(&(in_out_opnds->out_set));

    return total;
}

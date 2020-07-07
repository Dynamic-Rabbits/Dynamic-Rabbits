/*
 * tb_raw_umbra_fault_handlers.c
 *
 *      Author: john
 */

#include "tb_umbra_fault_handlers.h"

#include "../taint_maps/memory_maps/tb_cc_mem_maps/tb_cc_umbra_mem_maps/tb_cc_umbra_mem_map.h"
#include "../../../tls_access/tb_tls_access.h"
#include "umbra.h"
#include "instrumentation_bunny.h"
#include "utility_bunny.h"
#include <signal.h>
#include <limits.h>

/******************************************************************************************
 *  Functions for handling faults caused by special block access.
 *
 *  Responsible for converting special block to normal block.
 *
 *  Some of the following code is dependent on the great work carried out
 *  by the maintainers of Dr Memory (mainly the UMBRA library).
 *
 *****************************************************************************************/

/***********************************************************************************
 * Prototypes
 */
static int tb_calculate_app_translation_distance(umbra_map_t *mem_map,
        app_pc translation_addr, int memory_disp, app_pc addr_val);
static bool tb_handle_find_app_address_in_srcs(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc translation_addr,
        int mem_ref_disp, instr_t *app_inst, app_pc *best_addr_opnd,
        int *best_distance);
static bool tb_handle_find_app_address_in_dsts(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc translation_addr,
        int mem_ref_disp, instr_t *app_inst, app_pc *best_addr_opnd,
        int *best_distance);
static byte *tb_get_translation_addr(umbra_map_t *mem_map, app_pc addr);

/***********************************************************************************
 * Implementation (Helpers)
 */

/**
 * Performs translation from app address to shadow address.
 *
 * It calls umbra_get_shadow_memory.
 */
static byte *tb_get_translation_addr(umbra_map_t *mem_map, app_pc addr) {

    umbra_shadow_memory_info_t info;
    byte *shadow_addr;
    info.struct_size = sizeof(info);
    if (umbra_get_shadow_memory(mem_map, addr, &shadow_addr, &info)
            != DRMF_SUCCESS) {
        return NULL;
    }
    return shadow_addr;
}

static app_pc tb_update_app_address(void *drcontext, umbra_map_t *mem_map,
        app_pc translation_addr, int mem_ref_disp, app_pc app_addr) {

    DR_ASSERT(app_addr);

    int distance = tb_calculate_app_translation_distance(mem_map,
            translation_addr, mem_ref_disp, app_addr);

    return app_addr + distance;
}

static int tb_calculate_app_translation_distance(umbra_map_t *mem_map,
        app_pc translation_addr, int memory_disp, app_pc addr_val) {

    DR_ASSERT(mem_map != NULL);
    DR_ASSERT(translation_addr != NULL);

    // We employ a very simple (perhaps fragile) heuristic here.
    // The app address where its translation is the closest to that of the fault is chosen.
    // We calculate the distance and translation here. The comparison occurs higher up the function call stack.

    app_pc computed_translated_addr = tb_get_translation_addr(mem_map,
            (app_pc) addr_val);
    int distance = ((intptr_t) translation_addr
            - ((intptr_t) (computed_translated_addr + memory_disp)));

    int scale;
    bool is_scale_down;

    umbra_get_granularity(mem_map, &scale, &is_scale_down);

    if (is_scale_down) {
        distance = distance * scale;
    } else {
        distance = distance / scale;
    }

    return distance;
}

static bool tb_handle_find_app_address_in_srcs(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc translation_addr,
        int mem_ref_disp, instr_t *app_inst, app_pc *best_addr_opnd,
        int *best_distance) {

    DR_ASSERT(best_addr_opnd);
    DR_ASSERT(best_distance);

    bool res = false;

    *best_distance = INT_MAX;

    ub_instr_dataflow_t instr_dataflow;
    ub_dataflow_get_info(app_inst, &instr_dataflow);

    size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);
    for (size_t i = 0; i < num_flows; i++) {

        // Firstly, check srcs
        size_t num_srcs = ub_dataflow_flow_num_srcs(&instr_dataflow, i);
        for (size_t j = 0; j < num_srcs; j++) {

            ub_opnd_access_t opnd_access = ub_dataflow_get_flow_src_access(
                    &instr_dataflow, i, j);
            opnd_t src_opnd = ub_dataflow_get_flow_src(app_inst,
                    &instr_dataflow, i, j);

            if (opnd_is_memory_reference(src_opnd)) {

                // Fetch original app address and follow by checking if its translation caused the fault.
                app_pc addr_opnd;

                /* Rely on IB SPILLS. */
                addr_opnd = (app_pc) ib_get_comp_opnd(drcontext, &opnd_access);

                int distance = tb_calculate_app_translation_distance(mem_map,
                        translation_addr, mem_ref_disp, addr_opnd);

                // We take the minimum (best) score
                if (abs(distance) < abs(*best_distance)) {
                    *best_addr_opnd = addr_opnd;
                    *best_distance = distance;
                    res |= true;
                }
            }
        }
    }

    return res;
}

static bool tb_handle_find_app_address_in_dsts(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc translation_addr,
        int mem_ref_disp, instr_t *app_inst, app_pc *best_addr_opnd,
        int *best_distance) {

    DR_ASSERT(best_addr_opnd);
    DR_ASSERT(best_distance);

    bool res = false;

    *best_distance = INT_MAX;

    ub_instr_dataflow_t instr_dataflow;
    ub_dataflow_get_info(app_inst, &instr_dataflow);

    size_t num_flows = ub_dataflow_num_flows(&instr_dataflow);
    for (size_t i = 0; i < num_flows; i++) {

        ub_opnd_access_t opnd_access = ub_dataflow_get_flow_dst_access(
                &instr_dataflow, i);
        opnd_t dst_opnd = ub_dataflow_get_flow_dst(app_inst, &instr_dataflow,
                i);

        if (opnd_is_memory_reference(dst_opnd)) {

            /* DRREG conveniently restores the registers for us. */
            app_pc addr_opnd = (app_pc) ib_get_comp_opnd(drcontext,
                    &opnd_access);

            int distance = tb_calculate_app_translation_distance(mem_map,
                    translation_addr, mem_ref_disp, addr_opnd);

            if (abs(distance) < abs(*best_distance)) {
                *best_addr_opnd = addr_opnd;
                *best_distance = distance;
                res |= true;
            }
        }
    }

    return res;
}

static app_pc tb_get_address_info_from_instr(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc translation_addr,
        int mem_ref_disp, instr_t *app_inst) {

    app_pc src_best_addr = NULL;
    int src_best_distance;
    bool src_found = tb_handle_find_app_address_in_srcs(drcontext, mem_map,
            info, translation_addr, mem_ref_disp, app_inst, &src_best_addr,
            &src_best_distance);

    app_pc dst_best_addr = NULL;
    int dst_best_distance;
    bool dst_found = tb_handle_find_app_address_in_dsts(drcontext, mem_map,
            info, translation_addr, mem_ref_disp, app_inst, &dst_best_addr,
            &dst_best_distance);

    DR_ASSERT(dst_found || src_found);

    if (src_found && !dst_found) {
        DR_ASSERT(src_best_addr);
        return src_best_addr + src_best_distance;
    } else if (!src_found && dst_found) {
        DR_ASSERT(dst_best_addr);
        return dst_best_addr + dst_best_distance;
    } else if (src_found && dst_found
            && abs(src_best_distance) < abs(dst_best_distance)) {
        DR_ASSERT(src_best_addr);
        return src_best_addr + src_best_distance;
    } else if (src_found && dst_found
            && abs(src_best_distance) >= abs(dst_best_distance)) {
        DR_ASSERT(dst_best_addr);
        return dst_best_addr + dst_best_distance;
    }

    DR_ASSERT(false);
    return NULL;
}

static bool tb_fault_opnd_index_check(dr_mcontext_t *raw_mc, app_pc access,
        opnd_t *opnd, int *index, int i) {

    if (opnd_is_memory_reference(*opnd)) {

        // Compute the address and check if it matches with the access.
        app_pc computed_address = opnd_compute_address(*opnd, raw_mc);

        if (computed_address == access) {
            // Index found
            *index = i;
            return true;
        }
    }

    return false;
}

static bool tb_find_fault_index_opnd_in_srcs(dr_mcontext_t *raw_mc,
        app_pc access, instr_t *fault_inst, int *index) {

    DR_ASSERT(index != NULL);

    /* Begin searching for app address which caused the fault */
    for (int i = 0; i < instr_num_srcs(fault_inst); i++) {

        opnd_t opnd = instr_get_src(fault_inst, i);

        if (tb_fault_opnd_index_check(raw_mc, access, &opnd, index, i))
            return true;
    }

    return false;
}

static bool tb_find_fault_address_in_dsts(dr_mcontext_t *raw_mc, app_pc access,
        instr_t *fault_inst, int *index) {
    DR_ASSERT(index != NULL);

    /* Begin searching for app address which caused the fault */
    for (int i = 0; i < instr_num_dsts(fault_inst); i++) {

        opnd_t opnd = instr_get_dst(fault_inst, i);

        if (tb_fault_opnd_index_check(raw_mc, access, &opnd, index, i))
            return true;
    }

    return false;
}

/**
 *  Determines whether the addr is in redzone.
 */
bool tb_raw_umbra_is_in_redzone(umbra_map_t *map, app_pc pc) {

    umbra_shadow_memory_type_t shadow_type;

    drmf_status_t status = umbra_get_shadow_memory_type(map, pc, &shadow_type);
    DR_ASSERT(status == DRMF_SUCCESS);

    return shadow_type & UMBRA_SHADOW_MEMORY_TYPE_REDZONE;
}

/**
 *  Determines whether the addr is in a special shadow block of umbra.
 */
bool tb_raw_umbra_is_in_special_shadow_block(umbra_map_t *map, app_pc pc) {

    umbra_shadow_memory_type_t shadow_type;

    drmf_status_t status = umbra_shadow_memory_is_shared(map, pc, &shadow_type);
    DR_ASSERT(status == DRMF_SUCCESS);

    return shadow_type == UMBRA_SHADOW_MEMORY_TYPE_SHARED;
}

/**
 *  Replaces the mapping of the special block of the unmapped address with
 *  a normal one.
 */
static byte * tb_raw_replace_special_with_default(umbra_map_t *mem_map,
        app_pc addr) {

    byte *shadow_addr;

    drmf_status_t status = umbra_replace_shared_shadow_memory(mem_map, addr,
            &shadow_addr);
    DR_ASSERT(status == DRMF_SUCCESS);

    return shadow_addr;
}

static bool is_partial_redzone_access(umbra_map_t *mem_map, dr_siginfo_t *info,
        byte *shadow_addr, size_t size) {

    bool in_redzone = false;
    bool in_live = false;

    if (info->access_address != shadow_addr) {

        for (size_t i = 0; i < size; i++) {

            if (tb_raw_umbra_is_in_redzone(mem_map, shadow_addr + i))
                in_redzone = true;
            else
                in_live = true;
        }
    }

    return in_redzone && in_live;

}

static bool tb_raw_handle_redzone_get_fault_opnd(void *drcontext,
        dr_siginfo_t *info, instr_t * fault_inst, opnd_t* fault_opnd) {

    // We now need to find the operand of the meta-instruction that
    // caused the fault, so that we may change its address.
    bool found = false;

    // First search sources
    int index;
    found = tb_find_fault_index_opnd_in_srcs(info->raw_mcontext,
            info->access_address, fault_inst, &index);

    if (found) {
        // Get the found operand
        *fault_opnd = instr_get_src(fault_inst, index);
    } else {
        // If we failed to find in sources, search destinations.
        found = tb_find_fault_address_in_dsts(info->raw_mcontext,
                info->access_address, fault_inst, &index);

        if (found) {
            *fault_opnd = instr_get_dst(fault_inst, index);
        }
    }

    return found;
}

static void tb_raw_handle_redzone_full_access(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, int disp, app_pc app_addr,
        reg_id_t base_reg) {

    // We need to normalise back to app addr distance, and not that used for shadow mem.

    int scale;
    bool is_scale_down;
    umbra_get_granularity(mem_map, &scale, &is_scale_down);

    size_t app_disp;
    if (is_scale_down)
        app_disp = disp * scale;
    else
        app_disp = disp / scale;

    // We need to get the translated address with respect with the app_disp.
    app_pc translated_opnd = tb_get_translation_addr(mem_map,
            (app_pc) app_addr + app_disp);

    reg_set_value(base_reg, info->raw_mcontext,
            (reg_t) (translated_opnd - disp));
}

static void tb_raw_handle_redzone_partial_access(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, instr_t *fault_inst,
        app_pc app_addr, reg_id_t main_reg, size_t opnd_size) {

    int scale;
    bool is_scale_down;
    umbra_get_granularity(mem_map, &scale, &is_scale_down);

    size_t app_size;
    if (is_scale_down) {
        app_size = opnd_size * scale;

    } else {
        app_size = opnd_size / scale;
    }

    byte labels[opnd_size];
    memset(labels, 0, opnd_size);

    size_t shadow_size = opnd_size;

    if (instr_writes_memory(fault_inst)) {

        // Get reg value and store in shadow memory
        reg_get_value_ex(main_reg, info->raw_mcontext, (byte *) labels);

        tb_umbra_safe_write(mem_map, (uintptr_t) app_addr, app_size,
                shadow_size, (uintptr_t) labels);
    } else {

        tb_umbra_safe_read(mem_map, (uintptr_t) app_addr, app_size, shadow_size,
                (uintptr_t) labels);
        reg_set_value_ex(main_reg, info->raw_mcontext, (byte *) labels);
    }

    byte* next = decode_next_pc(drcontext, info->raw_mcontext->pc);
    DR_ASSERT(next != NULL);
    info->raw_mcontext->pc = next;
}

static void tb_raw_extract_partial_data(instr_t *fault_inst,
        opnd_t *mem_opnd_out, reg_id_t *main_reg_out) {

    if (instr_writes_memory(fault_inst)) {

        *mem_opnd_out = instr_get_dst(fault_inst, 0);

        opnd_t src = instr_get_src(fault_inst, 0);
        DR_ASSERT(opnd_is_reg(src));
        *main_reg_out = opnd_get_reg(src);

    } else {
        *mem_opnd_out = instr_get_src(fault_inst, 0);

        opnd_t dst = instr_get_dst(fault_inst, 0);
        DR_ASSERT(opnd_is_reg(dst));
        *main_reg_out = opnd_get_reg(dst);
    }
}

// Handles redzone fault by using the pc.
void tb_raw_handle_redzone_fault_from_pc(void *drcontext, umbra_map_t *mem_map,
        dr_siginfo_t *info, app_pc pc) {

    // Get the application instruction
    instr_t *app_inst = instr_create(drcontext);
    byte *valid = decode(drcontext, dr_app_pc_for_decoding(pc), app_inst);
    DR_ASSERT(valid);

    // Decode fault instr (i.e., the TB's instructions)
    instr_t * fault_inst = instr_create(drcontext);
    valid = decode(drcontext, info->raw_mcontext->pc, fault_inst);
    DR_ASSERT(valid);

    // We now need to find the operand of the meta-instruction that
    // caused the fault, so that we may change its address.
    bool found = false;
    opnd_t found_opnd;

    found = tb_raw_handle_redzone_get_fault_opnd(drcontext, info, fault_inst,
            &found_opnd);

    if (found) {

        DR_ASSERT(opnd_is_memory_reference(found_opnd));
        int disp = opnd_get_disp(found_opnd);

        app_pc app_addr = tb_get_address_info_from_instr(drcontext, mem_map,
                info, info->access_address, disp, app_inst);

        tb_raw_handle_redzone_full_access(drcontext, mem_map, info, disp,
                app_addr, opnd_get_base(found_opnd));

    } else {

        // We failed to find a direct access. This hints at a partial case.

        /*
         * This is called when we have accessed the redzone while in simd propagation mode
         * The issue is that labels in an oward operand may span across two different shadow regions
         * Therefore a fault is occurring as the bottom labels are accessing the redzone.
         *
         * For example, the first 3 labels are in the region where the translated address resides in esi.
         * The last label is in another shadow region for which we need to perform a translation. Since we
         * are trying to access the last label via translation stored in esi, we are accessing redzone.
         *
         * Note, this may also occur  when using the scaled down memory of the taint check optimisation.
         */

        // We ensure that the fault is caused by a str or load instruction.
        // Our instruction handlers takes care  of this assumption.
        DR_ASSERT(
                instr_get_opcode(fault_inst) == OP_movdqu
                        || instr_get_opcode(fault_inst) == OP_mov_ld
                        || instr_get_opcode(fault_inst) == OP_mov_st);

        opnd_t mem_opnd;
        reg_id_t main_reg;

        tb_raw_extract_partial_data(fault_inst, &mem_opnd, &main_reg);

        DR_ASSERT(opnd_is_base_disp(mem_opnd));
        int disp = opnd_get_disp(mem_opnd);

        size_t byte_size = opnd_size_in_bytes(opnd_get_size(mem_opnd));

        app_pc computed_address = opnd_compute_address(mem_opnd,
                info->raw_mcontext);
        DR_ASSERT(
                is_partial_redzone_access(mem_map, info, computed_address,
                        byte_size));

        app_pc app_addr = tb_get_address_info_from_instr(drcontext, mem_map,
                info, computed_address, disp, app_inst);

        tb_raw_handle_redzone_partial_access(drcontext, mem_map, info,
                fault_inst, app_addr, main_reg, byte_size);
    }

    instr_destroy(drcontext, fault_inst);
    instr_destroy(drcontext, app_inst);
}

// Handles redzone fault by using the pc.
static void tb_raw_handle_redzone_fault_from_app_address(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, void *app_addr) {

    // Decode fault instr (i.e., the TB's instructions)
    instr_t * fault_inst = instr_create(drcontext);
    byte *valid = decode(drcontext, info->raw_mcontext->pc, fault_inst);
    DR_ASSERT(valid);

    // We now need to find the operand of the meta-instruction that
    // caused the fault, so that we may change its address.
    bool found = false;
    opnd_t found_opnd;

    found = tb_raw_handle_redzone_get_fault_opnd(drcontext, info, fault_inst,
            &found_opnd);

    if (found) {

        DR_ASSERT(opnd_is_memory_reference(found_opnd));
        int disp = opnd_get_disp(found_opnd);

        app_pc updated_app_addr = tb_update_app_address(drcontext, mem_map,
                info->access_address, disp, app_addr);

        tb_raw_handle_redzone_full_access(drcontext, mem_map, info, disp,
                updated_app_addr, opnd_get_base(found_opnd));

    } else {

        // We failed to find a direct access. This hints at a partial case.

        /*
         * This is called when we have accessed the redzone while in simd propagation mode.
         * The issue is that labels in an oward operand may span across two different shadow regions
         * Therefore a fault is occurring as the bottom labels are accessing the redzone.
         *
         * For example, the first 3 labels are in the region where the translated address resides in esi.
         * The last label is in another shadow region for which we need to perform a translation. Since we
         * are trying to access the last label via translation stored in esi, we are accessing redzone.
         */

        // We ensure that the fault is caused by a movdqu instruction. Our instruction handlers takes care
        // of this assumption.
        DR_ASSERT(
                instr_get_opcode(fault_inst) == OP_movdqu
                        || instr_get_opcode(fault_inst) == OP_mov_ld
                        || instr_get_opcode(fault_inst) == OP_mov_st
                        || instr_get_opcode(fault_inst) == OP_movd
                        || instr_get_opcode(fault_inst) == OP_movq);

        opnd_t mem_opnd;
        reg_id_t main_reg;

        tb_raw_extract_partial_data(fault_inst, &mem_opnd, &main_reg);

        DR_ASSERT(opnd_is_base_disp(mem_opnd));
        int disp = opnd_get_disp(mem_opnd);
        size_t byte_size = opnd_size_in_bytes(opnd_get_size(mem_opnd));

        app_pc computed_address = opnd_compute_address(mem_opnd,
                info->raw_mcontext);
        DR_ASSERT(
                is_partial_redzone_access(mem_map, info, computed_address,
                        byte_size));

        app_pc updated_app_addr = tb_update_app_address(drcontext, mem_map,
                computed_address, disp, app_addr);

        tb_raw_handle_redzone_partial_access(drcontext, mem_map, info,
                fault_inst, updated_app_addr, main_reg, byte_size);
    }

    instr_destroy(drcontext, fault_inst);
}

static void tb_handle_shared_block_fault(void *drcontext, umbra_map_t *mem_map,
        dr_siginfo_t *info, app_pc ib_addr_opnd, reg_id_t base_reg) {

    // No longer use the special block.
    byte *new_shadow_addr = tb_raw_replace_special_with_default(mem_map,
            (app_pc) ib_addr_opnd);

    reg_set_value(base_reg, info->raw_mcontext, (reg_t) new_shadow_addr);

}

static void tb_handle_shared_block_fault_from_pc(void *drcontext,
        umbra_map_t *mem_map, dr_siginfo_t *info, app_pc pc) {

    // Decode fault instr (i.e., the TB's instructions)
    instr_t * fault_inst = instr_create(drcontext);
    byte *valid = decode(drcontext, info->raw_mcontext->pc, fault_inst);
    DR_ASSERT(valid);

    opnd_t shadow_opnd = instr_get_dst(fault_inst, 0);

    // We use a mov instruction to access shadow blocks. The faulting
    // instruction MUST therefore be a mov.
    DR_ASSERT(opnd_is_memory_reference(shadow_opnd));
    int disp = opnd_get_disp(shadow_opnd);
    reg_id_t base_reg = opnd_get_base(shadow_opnd);
    instr_destroy(drcontext, fault_inst);

    app_pc computed_address = opnd_compute_address(shadow_opnd,
            info->raw_mcontext);
    DR_ASSERT(computed_address == info->access_address);

    // Decode original app instr
    instr_t * app_inst = instr_create(drcontext);
    valid = decode(drcontext, dr_app_pc_for_decoding(pc), app_inst);
    DR_ASSERT(valid);

    // Retrieve address information.
    app_pc ib_addr_opnd = tb_get_address_info_from_instr(drcontext, mem_map,
            info, info->access_address, disp, app_inst);
    instr_destroy(drcontext, app_inst);

    tb_handle_shared_block_fault(drcontext, mem_map, info, ib_addr_opnd,
            base_reg);
}

dr_signal_action_t tb_umbra_event_signal_handler(void *drcontext,
        dr_siginfo_t *info, tb_context_t * tb_ctx, umbra_map_t *map) {

    if (info->sig == SIGSEGV || info->sig == SIGBUS) {
        byte *target = info->access_address;

        if (tb_raw_umbra_is_in_redzone(map, target)) {

            app_pc fp_addr = tb_get_fp_address_spill(tb_ctx);

            if (fp_addr) {

                tb_raw_handle_redzone_fault_from_app_address(drcontext, map,
                        info, fp_addr);

            } else if (tb_ctx->is_inline) {
                DR_ASSERT(info->mcontext->pc);
                tb_raw_handle_redzone_fault_from_pc(drcontext, map, info,
                        info->mcontext->pc);

            } else {
                // In this optimisation, we do not rely on translation being set,
                // but instead garner pc information by saving it via the IB.
                app_pc pc = ib_get_pc(drcontext);
                tb_raw_handle_redzone_fault_from_pc(drcontext, map, info, pc);
            }

            // Suppress the signal.
            return DR_SIGNAL_SUPPRESS;
        }

        if (tb_raw_umbra_is_in_special_shadow_block(map, target)) {

            if (tb_ctx->is_inline) {
                DR_ASSERT(info->mcontext->pc);
                tb_handle_shared_block_fault_from_pc(drcontext, map, info,
                        info->mcontext->pc);

            } else {

                // In this optimisation, we do not rely on translation being set,
                // but instead garner pc information by saving it via the IB.
                app_pc pc = ib_get_pc(drcontext);
                tb_handle_shared_block_fault_from_pc(drcontext, map, info, pc);
            }

            // Suppress the signal.
            return DR_SIGNAL_SUPPRESS;
        }
    }

    return DR_SIGNAL_DELIVER;
}

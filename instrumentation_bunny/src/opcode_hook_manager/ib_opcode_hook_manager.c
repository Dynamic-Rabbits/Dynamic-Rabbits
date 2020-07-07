/**
 *  @file ib_opcode_map.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "ib_opcode_hook_manager.h"
#include "../options/ib_option.h"
#include "ib_instrum_tool.h"
#include "ib_hook_summary.h"
#include "utility_bunny.h"
#include <string.h>

/********************************************************************
 * Structs and Definitions
 */

typedef struct {
    void *tool_list;
    void *tool_map;
} ib_opcode_hook_mngr_t;

extern ib_ctx_t *ib_ctx;

/********************************************************************
 * Prototypes
 */

static void *ib_opcode_hook_mngr_create_it(int opcode);
static void ib_opcode_hook_mngr_destroy_it(void *hook_mngr_it);
static bool ib_opcode_hook_mngr_get_start_it(void *hook_mngr_opaque,
        void *it_opaque);
static bool ib_opcode_hook_mngr_get_next_it(void *it_opaque);
static ib_hook_info_t *ib_instrument_get_considered_hook_info(
        void *hook_info_list, ib_hook_info_t *default_hook, instr_t *instr);

/********************************************************************
 * Implementation
 */

typedef struct {
    int opcode;
    void *instrum_tool_it;
} ib_opcode_hook_mngr_it_t;

void* ib_opcode_hook_mngr_create() {

    ib_opcode_hook_mngr_t *hook_mngr = dr_global_alloc(
            sizeof(ib_opcode_hook_mngr_t));

    hook_mngr->tool_list = ub_list_create();
    hook_mngr->tool_map = ub_intptr_hashmap_create_map();

    return (void *) hook_mngr;
}

void ib_opcode_hook_mngr_destroy(void *hook_mngr_opaque) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    ub_list_destroy(hook_mngr->tool_list, NULL);
    ub_intptr_hashmap_destroy_map(hook_mngr->tool_map, ib_instrum_tool_destroy);

    dr_global_free(hook_mngr, sizeof(ib_opcode_hook_mngr_t));
}

void ib_opcode_hook_mngr_register_instrum_tool(void *hook_mngr_opaque,
        unsigned int tool_id) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);
    DR_ASSERT(hook_mngr->tool_map);

    void *result = ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map, tool_id);

    DR_ASSERT(!result);

    void *instrum_tool = ib_instrum_tool_create(tool_id);
    ub_list_insert(hook_mngr->tool_list, (void *) (uintptr_t) tool_id);

    ub_key_value_pair_t key_val_pair;
    key_val_pair.key = tool_id;
    key_val_pair.value = instrum_tool;

    ub_intptr_hashmap_insert_entry(hook_mngr->tool_map, &key_val_pair);
}

void ib_opcode_hook_mngr_hook_opcode_for_tool(void *hook_mngr_opaque,
        unsigned int tool_id, int opcode, ib_hook_info_t *src_opcode_hook_info) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);

    void *instrum_tool = ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map,
            tool_id);
    DR_ASSERT(instrum_tool);

    ib_instrum_tool_register_opcode_hook(instrum_tool, opcode,
            src_opcode_hook_info);
}

void ib_opcode_hook_mngr_hook_default_for_tool(void *hook_mngr_opaque,
        unsigned int tool_id, ib_hook_info_t *src_default_hook_info) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);

    void *instrum_tool = ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map,
            tool_id);

    DR_ASSERT(instrum_tool);

    ib_instrum_tool_register_default_opcode_hook(instrum_tool,
            src_default_hook_info);
}

void ib_opcode_hook_mngr_unhook_opcode_for_tool(void *hook_mngr_opaque,
        unsigned int tool_id, int opcode) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);

    void *instrum_tool = ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map,
            tool_id);
    DR_ASSERT(instrum_tool);

    ib_instrum_tool_unregister_opcode_hook(instrum_tool, opcode);
}

bool ib_opcode_hook_mngr_unhook_default_for_tool(void *hook_mngr_opaque,
        unsigned int tool_id) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);

    void *instrum_tool = ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map,
            tool_id);
    DR_ASSERT(instrum_tool);

    return ib_instrum_tool_unregister_default_opcode_hook(instrum_tool);
}

static bool ib_opcode_compare_tool_ids(const void *tool_id1_opaque,
        const void *tool_id2_opaque) {

    unsigned int *tool_id1 = (unsigned int *) tool_id1_opaque;
    unsigned int *tool_id2 = (unsigned int *) tool_id2_opaque;

    return tool_id1 == tool_id2;
}

bool ib_opcode_hook_mngr_unregister_instrum_tool(void *hook_mngr_opaque,
        unsigned int tool_id) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;
    DR_ASSERT(hook_mngr);
    DR_ASSERT(hook_mngr->tool_list);
    DR_ASSERT(hook_mngr->tool_map);

    void *result = ub_intptr_hashmap_remove_entry(hook_mngr->tool_map,
            (uintptr_t) tool_id);

    ub_list_remove(hook_mngr->tool_list, (void *) (uintptr_t) tool_id,
            ib_opcode_compare_tool_ids);

    if (result) {
        ib_instrum_tool_destroy(result);
        return true;
    }

    return false;
}

/**
 *  Creates an interator to obtain all hook infos associated with
 *  an instruction's opcode.
 *
 *  Note that the order of the iteration is dependant on the order
 *  of instrum tool registration.
 *
 *  @param opcode The instruction's opcode to fetch its registered
 *  hook infos.
 *  @return Returns the newly created iterator.
 */
static void *ib_opcode_hook_mngr_create_it(int opcode) {

    ib_opcode_hook_mngr_it_t *it = (ib_opcode_hook_mngr_it_t *) dr_global_alloc(
            sizeof(ib_opcode_hook_mngr_it_t));
    it->opcode = opcode;

    return it;
}

/**
 *  Destroys the opcode hook iterator.
 *
 *  @param hook_mngr_it The iterator to destroy.
 */
static void ib_opcode_hook_mngr_destroy_it(void *hook_mngr_it) {

    DR_ASSERT(hook_mngr_it);
    dr_global_free(hook_mngr_it, sizeof(ib_opcode_hook_mngr_it_t));
}

/**
 *  Initialises the opcode hook iterator.
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param hook_mngr_it The opcode hook iterator. Must be created via
 *  ib_opcode_hook_mngr_create_it
 */
static bool ib_opcode_hook_mngr_get_start_it(void *hook_mngr_opaque,
        void *it_opaque) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    DR_ASSERT(hook_mngr);

    ib_opcode_hook_mngr_it_t *it = (ib_opcode_hook_mngr_it_t *) it_opaque;

    it->instrum_tool_it = ub_list_get_start_it(hook_mngr->tool_list);

    if (it->instrum_tool_it)
        return true;

    return false;
}

/**
 *  Fetches the instrum tool at the current iteration
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param hook_mngr_it The opcode hook iterator.
 */
static void *ib_opcode_hook_mngr_get_instrum_tool(void *hook_mngr_opaque,
        unsigned int tool_id) {

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    return ub_intptr_hashmap_lookup_entry(hook_mngr->tool_map, tool_id);
}

/**
 *  Fetches the tool id at the current iteration
 *
 *  @param opcode_hook_mngr The opcode hook manager.
 *  @param hook_mngr_it The opcode hook iterator.
 */
static unsigned int ib_opcode_hook_mngr_get_it_instrum_tool_id(void * it_opaque) {

    ib_opcode_hook_mngr_it_t *it = (ib_opcode_hook_mngr_it_t *) it_opaque;

    unsigned int tool_id = (uintptr_t) ub_list_get_it_value(
            it->instrum_tool_it);

    return tool_id;
}

/**
 *  Increments the opcode hook iterator.
 *
 *  @param hook_mngr_it The opcode hook iterator to increment.
 */
static bool ib_opcode_hook_mngr_get_next_it(void *it_opaque) {

    ib_opcode_hook_mngr_it_t *it = (ib_opcode_hook_mngr_it_t *) it_opaque;

    it->instrum_tool_it = ub_list_get_next_it(it->instrum_tool_it);

    if (it->instrum_tool_it)
        return true;

    return false;
}

bool ib_opcode_hook_mngr_get_hook_summary(void *hook_mngr_opaque,
        instr_t *instr, ib_hook_summary_t *summary,
        ib_instrum_analysis_data_t *analysis_data) {

    int opcode = instr_get_opcode(instr);

    ib_opcode_hook_mngr_t *hook_mngr =
            (ib_opcode_hook_mngr_t *) hook_mngr_opaque;

    void *it = ib_opcode_hook_mngr_create_it(opcode);

    bool is_skippable = true;

    ib_hook_summary_init(summary);

    int index = 0;

    for (bool present = ib_opcode_hook_mngr_get_start_it(hook_mngr, it);
            present; present = ib_opcode_hook_mngr_get_next_it(it)) {

        unsigned int tool_id = ib_opcode_hook_mngr_get_it_instrum_tool_id(it);

        if (analysis_data && analysis_data->id == tool_id
                && analysis_data->action == IB_INSTRUM_ACTION_SKIP) {

            // Removing due to analysis
            continue;
        }

        void *instrum_tool = ib_opcode_hook_mngr_get_instrum_tool(hook_mngr,
                tool_id);

        void *hook_info_list = ib_instrum_tool_get_hook_info(instrum_tool,
                instr_get_opcode(instr));

        ib_hook_info_t *default_hook = ib_instrum_tool_get_default_opcode_hook(
                instrum_tool);

        ib_hook_info_t *hook_info = ib_instrument_get_considered_hook_info(
                hook_info_list, default_hook, instr);

        if (hook_info) {

            DR_ASSERT_MSG(index < 8,
                    "Cannot register more than 8 instrum tools for now");

            ib_hook_summary_add(summary, hook_info, index);
            index++;

            is_skippable = false;
        }
    }

    ib_opcode_hook_mngr_destroy_it(it);

    return is_skippable;
}

/**
 *  Returns which hook to consider.
 *  Checks flags, nullness, and guards. The first non-skippable hook is considered.
 *
 *  @param hook_info The hook info list.
 *  @param hook_info The default hook info.
 *  @param instr The instruction being instrumented.
 *
 *  @return Returns the hook info to consider when hooking. Returns NULL if no hook should be placed.
 */
static ib_hook_info_t *ib_instrument_get_considered_hook_info(
        void *hook_info_list, ib_hook_info_t *default_hook, instr_t *instr) {

    if (hook_info_list) {

        bool found_default = false;

        for (void * it = ub_list_get_start_it(hook_info_list); it; it =
                ub_list_get_next_it(it)) {

            ib_hook_info_t *hook_info = ub_list_get_it_value(it);

            if (!hook_info->is_skip) {

                if (hook_info->check_hook_guard) {

                    ib_guard_result_t res = IB_GUARD_DEFAULT;

                    if (hook_info->check_hook_guard(instr))
                        res = hook_info->action_result;

                    if (res == IB_GUARD_HOOK)
                        return hook_info;
                    else if (res == IB_GUARD_DEFAULT && default_hook)
                        found_default = true;
                    else if (res == IB_GUARD_SKIP)
                        return NULL;

                } else {
                    return hook_info;
                }
            }

        }

        if (found_default)
            return default_hook;

    } else if (default_hook) {
        return default_hook;
    }

    return NULL;
}

/*********************************************************************************************
 * Flag Checks
 */

bool ib_is_pc_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_pc_enabled;

    return false;
}

bool ib_is_immed_opnd_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_immed_opnd_enabled;

    return false;
}

bool ib_is_reg_opnd_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_reg_opnd_enabled;

    return false;
}

bool ib_is_addr_opnd_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_addr_opnd_enabled;

    return false;
}

bool ib_is_full_addr_gen_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_full_addr_gen_enabled;

    return false;
}

bool ib_is_addr_gen_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_addr_gen_enabled;

    return false;
}

bool ib_is_loc_size_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_loc_size_enabled;

    return false;
}

bool ib_is_loc_type_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_loc_type_enabled;

    return false;
}

bool ib_is_conc_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_conc_enabled;

    return false;
}

bool ib_is_opnd_count_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_opnd_count_enabled;

    return false;
}

bool ib_is_flag_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_flag_enabled;

    return false;
}

bool ib_is_opcode_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_opcode_enabled;

    return false;
}

bool ib_is_full_opnd_storage_enabled_for_instr(instr_t *instr) {

    ib_hook_summary_t hook_summary;
    bool skip = ib_opcode_hook_mngr_get_hook_summary(ib_ctx->opcode_hook_mngr,
            instr, &hook_summary, NULL);

    if (!skip)
        return hook_summary.is_full_opnd_storage_enabled;

    return false;
}

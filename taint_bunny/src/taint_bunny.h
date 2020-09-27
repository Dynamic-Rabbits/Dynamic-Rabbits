/**
 *  @file taint_bunny.h
 *  @brief The Taint Bunny. Provides functionality for conducting
 *  dynamic taint analysis
 *  @author John F.X. Galea
 */

#ifndef _TAINT_BUNNY_H_
#define _TAINT_BUNNY_H_

#include "dr_defines.h"
#include <stdint.h>
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"

#include "taint_policies/raw_taint_policies/tb_raw_bitwise_policy.h"
#include "taint_policies/raw_taint_policies/tb_raw_dst_id_policy.h"
#include "taint_policies/raw_taint_policies/tb_raw_dummy_policy.h"
#include "taint_policies/raw_taint_policies/tb_raw_bitvect_policy.h"
#include "taint_policies/raw_taint_policies/tb_raw_bitvect_tree_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_bitwise_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_dummy_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_set_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_dst_id_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_bitvector_policy.h"
#include "taint_policies/cc_taint_policies/tb_cc_bitvect_tree_policy.h"

/***************************************************************************
 *  Definitions & Global Variables
 */

/**
 * Name of taint bunny instrumentation pass priorities for app2app
 */
#define DRMGR_PRIORITY_NAME_TBTAINT "TAINT_BUNNY"

enum {
    DRMGR_PRIORITY_INSERT_TAINT_BUNNY = 501,
};

/***************************************************************************
 * INIT/UNINIT Functions
 */

/**
 *	Initialises a taint bunny.  Must be called prior to any of the
 *	other routines. Each call must be paired with a corresponding call to
 *	tb_exit()
 */
DR_EXPORT void *tb_cc_init_default(client_id_t client_id,
        tb_cc_taint_policy_t *taint_policy);

DR_EXPORT void *tb_raw_init_default(client_id_t client_id,
        tb_raw_taint_policy_t *taint_policy);

DR_EXPORT void *tb_simd_init_default(client_id_t client_id,
        tb_raw_taint_policy_t *taint_policy);

DR_EXPORT void *tb_cc_init(client_id_t client_id, IB_INSTRUM_OPT options,
        tb_options_t *te_options, tb_fp_settings_t *fp_settings,
        tb_cc_taint_policy_t *taint_policy);

DR_EXPORT void *tb_raw_init(client_id_t client_id, IB_INSTRUM_OPT options,
        tb_options_t *te_options, tb_fp_settings_t *fp_settings,
        tb_raw_taint_policy_t *taint_policy);

DR_EXPORT void *tb_simd_init(client_id_t client_id, IB_INSTRUM_OPT options,
        tb_options_t *te_options, tb_fp_settings_t *fp_settings,
        tb_raw_taint_policy_t *taint_policy);

/**
 * Hooks taint propagation handlers.
 *
 * Instrumentation to be executed prior taint analysis needs to be registered
 * prior to the calling of this function.
 */
DR_EXPORT void tb_register_hooks(void *tb_ctx_opaque);

/**
 *	Like \p tb_init, but uses default optimisations and options.
 *
 *  @param taint_funcs A structs containing functions for managing taint.
 *  @return Returns the taint bunny context.
 */

/**
 * Cleans up the taint bunny extension
 */
DR_EXPORT void tb_cc_exit(void *taint_bunny_ctx);
DR_EXPORT void tb_raw_exit(void *taint_bunny_ctx);
DR_EXPORT void tb_simd_exit(void *tb_ctx_opaque);

#endif 

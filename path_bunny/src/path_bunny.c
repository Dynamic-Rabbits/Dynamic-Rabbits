/*
 * instrumentation_bunny.c
 *
 *      Author: john
 */

#include "path_bunny.h"
#include "pb_private.h"
#include "instrumentation_bunny.h"

#include "instrumentation/pb_instrum_register.h"

#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>

#include <string.h>
#include <stddef.h>

/********************************************************************
 * Implementation
 */

DR_EXPORT void *pb_init(void *taint_bunny, path_bunny_funcs_t *funcs,
        PB_EV_OPT_t pb_opts, void *user_data, IB_INSTRUM_OPT ib_options) {

    DR_ASSERT(funcs);
    DR_ASSERT(pb_opts != PB_EV_ERROR);

    pb_context_t *pb_context = (pb_context_t *) dr_global_alloc(
            sizeof(pb_context_t));
    pb_context->user_data = user_data;
    memcpy(&(pb_context->funcs), funcs, sizeof(path_bunny_funcs_t));

    pb_context->pb_opts = pb_opts;
    pb_context->ib_options = ib_options;
    pb_context->taint_bunny = taint_bunny;
    pb_context->tool_id = ib_register_instrum_tool();

    pb_live_regs_init();

    return pb_context;
}

DR_EXPORT void pb_exit(void *path_bunny_opaque) {

    DR_ASSERT(path_bunny_opaque);

    pb_context_t * pb_ctx = (pb_context_t *) path_bunny_opaque;

    pb_live_regs_destroy();

    ib_unregister_instrum_tool(pb_ctx->tool_id);

    dr_global_free(pb_ctx, sizeof(pb_context_t));
}

DR_EXPORT void pb_register_hooks(void *path_ctx_opaque) {

    pb_context_t * pb_ctx = (pb_context_t *) path_ctx_opaque;
    pb_register_cmp_hooks(pb_ctx);
}

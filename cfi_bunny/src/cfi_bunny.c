#include "cfi_bunny.h"
#include "instrumentation_bunny.h"
#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>

#include <string.h>
#include <stddef.h>

#include "cfib_private.h"
#include "instrumentation/cfib_instrum_register.h"

/********************************************************************
 * Implementation
 */

DR_EXPORT void *cfib_init(void *taint_bunny, cfib_handle_detection_func_t detection_func,
        CFIB_EV_DETECTION_OPT_t detection_options, IB_INSTRUM_OPT instrum_opts,
        void *user_data) {

    DR_ASSERT(detection_func);

    cfib_context_t *cfib_context = (cfib_context_t *) dr_global_alloc(
            sizeof(cfib_context_t));

    cfib_context->user_data = user_data;
    cfib_context->taint_bunny = taint_bunny;
    cfib_context->detection_func = detection_func;
    cfib_context->tool_id = ib_register_instrum_tool();
    cfib_context->detection_options = detection_options;
    cfib_context->instrum_opts = instrum_opts;

    return cfib_context;
}

DR_EXPORT void cfib_exit(void *cfib_bunny_opaque) {

    DR_ASSERT(cfib_bunny_opaque);

    cfib_context_t * cfib_ctx = (cfib_context_t *) cfib_bunny_opaque;
    ib_unregister_instrum_tool(cfib_ctx->tool_id);
    dr_global_free(cfib_ctx, sizeof(cfib_context_t));
}

DR_EXPORT void cfib_register_hooks(void *cfi_bunny_opaque) {

    cfib_context_t * cfi_ctx = (cfib_context_t *) cfi_bunny_opaque;
    cfib_register_detection_hooks(cfi_ctx);
}

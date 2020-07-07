#include "ib_tls_access.h"
#include "../ib_data.h"

extern ib_ctx_t *ib_ctx;

static void **ib_tls_get_addr(int slot_idx) {

#ifdef DEBUG
    DR_ASSERT(ib_ctx);
#endif

    byte *addr = dr_get_dr_segment_base(ib_ctx->tls_raw_reg)
            + ib_ctx->tls_raw_base + (slot_idx * (sizeof(void *)));

    return (void **) addr;
}

opnd_t ib_tls_get_raw_slot_opnd(int slot_idx) {

#ifdef DEBUG
    DR_ASSERT(ib_ctx);
#endif

    return opnd_create_far_base_disp_ex(ib_ctx->tls_raw_reg,
    REG_NULL, REG_NULL, 1, ib_ctx->tls_raw_base + (slot_idx * (sizeof(void *))),
            OPSZ_4, false, true, false);
}

void *ib_get_thread_data(void *drcontext) {

    return drmgr_get_tls_field(drcontext, ib_ctx->tls_data_idx);
}

uintptr_t ib_tls_get_opnd_data(int index) {

    DR_ASSERT(index >= IB_RAW_SLOT_SRC_OPND_DATA_1 && index <= IB_RAW_SLOT_DST_OPND_DATA_3);
    uintptr_t *data_addr =  (uintptr_t *) ib_tls_get_addr(index);

    return *data_addr;
}

app_pc ib_tls_get_pc_data() {

    uintptr_t *pc_addr =  (uintptr_t *) ib_tls_get_addr(IB_RAW_SLOT_PC_DATA);

    return (app_pc) *pc_addr;
}

void ib_tls_set_thread_data(void *thread_data) {

    void **thread_data_addr = ib_tls_get_addr(IB_RAW_SLOT_THRD_DATA);
    *thread_data_addr = thread_data;
}

void tb_tls_set_return_data(void *return_data) {

    void **return_data_addr = ib_tls_get_addr(IB_RAW_SLOT_RET_DATA);
    *return_data_addr = return_data;
}




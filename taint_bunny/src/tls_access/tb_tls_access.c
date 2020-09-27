#include "tb_tls_access.h"

opnd_t tb_raw_get_tls_raw_slot_opnd(tb_context_t *tb_ctx, int slot_idx) {

    return opnd_create_far_base_disp_ex(tb_ctx->tls_raw_reg,
    REG_NULL, REG_NULL, 1, tb_ctx->tls_raw_base + (slot_idx * (sizeof(void *))),
            OPSZ_4, false, true, false);
}

void *tb_get_reg_map(tb_context_t *tb_ctx) {

    void *drcontext = dr_get_current_drcontext();
    tb_per_thrd_t *per_thread = drmgr_get_tls_field(drcontext, tb_ctx->tls_id);
    return per_thread->reg_map;
}

void tb_set_reg_map(tb_context_t *tb_ctx, void *reg_map) {

    byte *addr = dr_get_dr_segment_base(tb_ctx->tls_raw_reg)
            + tb_ctx->tls_raw_base + (TB_RAW_SLOT_IDX_MAP * (sizeof(void *)));
    void **regmap_addr = (void **) addr;

    *regmap_addr = reg_map;
}

void tb_set_reg_analysis_switch(tb_context_t *tb_ctx, bool analysis_switch) {

    byte *addr = dr_get_dr_segment_base(tb_ctx->tls_raw_reg)
            + tb_ctx->tls_raw_base
            + (TB_RAW_SLOT_IDX_ANALYSIS_SWITCH * (sizeof(void *)));
    bool *analysis_switch_addr = (bool *) addr;
    *analysis_switch_addr = analysis_switch;
}

void *tb_get_fp_address_spill(tb_context_t *tb_ctx) {

    byte *addr = (dr_get_dr_segment_base(tb_ctx->tls_raw_reg)
            + tb_ctx->tls_raw_base + (TB_FP_SLOT_ADDR * (sizeof(void *))));

    void **fp_addr = (void **) addr;
    return *fp_addr;
}

uint32_t tb_get_fp_reg_state(tb_context_t *tb_ctx) {

    byte *addr = (dr_get_dr_segment_base(tb_ctx->tls_raw_reg)
            + tb_ctx->tls_raw_base + (TB_FP_SLOT_REG_STATE * (sizeof(void *))));

    uint32_t *fp_reg_state = (uint32_t *) addr;
    return *fp_reg_state;
}

void tb_set_fp_reg_state(tb_context_t *tb_ctx, uint32_t reg_state) {

    byte *addr = dr_get_dr_segment_base(tb_ctx->tls_raw_reg)
            + tb_ctx->tls_raw_base + (TB_FP_SLOT_REG_STATE * (sizeof(void *)));
    uint32_t *reg_state_addr = (uint32_t *) addr;
    *reg_state_addr = reg_state;
}


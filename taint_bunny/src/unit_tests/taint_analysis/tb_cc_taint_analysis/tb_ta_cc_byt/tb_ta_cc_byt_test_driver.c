/*
 * tb_ta_cc_byt_unsupport_test.c
 *
 *      Author: john
 */

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../../../../taint_bunny.h"
#include "tb_ta_cc_byt_untainted_test.h"
#include "tb_ta_cc_byt_src_dst_test.h"
#include "tb_ta_cc_byt_src_srcdst_test.h"
#include "tb_ta_cc_byt_untainted_test.h"
#include "tb_ta_cc_byt_p_src_srcdst_test.h"
#include "tb_ta_cc_byt_punpck_test.h"
#include "tb_ta_cc_byt_pack_test.h"
#include "tb_ta_cc_byt_xchg_test.h"
#include "tb_ta_cc_byt_src_srcdst_dst_test.h"

void *tb;

static void event_exit() {

    tb_cc_exit(tb);
    ib_exit();
}

static void thread_init(void *drcontext) {

    // Src Dst
//    tb_test_src_dst_dmem_smem(tb);
//    tb_test_src_dst_dmem_sreg(tb);
//    tb_test_src_dst_dreg_sreg(tb);
//    tb_test_src_dst_dreg_smem(tb);
//    tb_test_src_dst_reg_extension(tb);
//    tb_test_src_dst_mem_extension(tb);
//    tb_test_src_dst_whole_dreg_sreg(tb);
//    tb_test_src_dst_whole_dreg_smem(tb);
//    tb_test_src_dst_whole_dmem_sreg(tb);
//    tb_test_src_dst_whole_dreg_sreg(tb);
//    tb_test_src_dst_high_src_dst_mem(tb);
//    tb_test_src_dst_high_src_dst_reg(tb);

//    // Src SrcDst
//    tb_test_src_srcdst_whole_dreg_sreg_sreg(tb);
//    tb_test_src_srcdst_whole_dreg_smem_sreg(tb);
//    tb_test_src_srcdst_whole_dmem_sreg_smem(tb);
//    tb_test_src_srcdst_dreg_sreg_sreg(tb);
//    tb_test_src_srcdst_dreg_smem_sreg(tb);
//    tb_test_src_srcdst_dmem_sreg_smem(tb);
//
//    // Untainted
//    tb_test_untaint_mem(tb);
//    tb_test_untaint_reg(tb);
//
//    // P Src Dst
//    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_sreg_16_sreg_16_test(tb);
//    tb_cc_byt_handle_pd_src_srcdst_whole_dreg_16_smem_16_sreg_16_test(tb);
//    tb_cc_byt_handle_pmaddwd_dreg_16_sreg_16_sreg_16_test(tb);
//    tb_cc_byt_handle_pmaddwd_dreg_16_smem_16_sreg_16_test(tb);
//
//    // Punpck
//    tb_cc_byt_handle_low_punpcklwd_dreg_16_sreg_16_sreg_16_test(tb);
//    tb_cc_byt_handle_low_punpcklwd_dreg_16_smem_16_sreg_16_test(tb);
//    tb_cc_byt_handle_high_punpckhwd_dreg_16_sreg_16_sreg_16_test(tb);
//    tb_cc_byt_handle_high_punpckhwd_dreg_16_smem_16_sreg_16_test(tb);
//
//    // Pack
//    tb_cc_byt_handle_pack_dreg_16_sreg_16_sreg_16_test(tb);
//    tb_cc_byt_handle_pack_dreg_16_smem_16_sreg_16_test(tb);
//
//    // XCHG
//     tb_cc_byt_handle_xchg_reg_4_reg_4_test(tb);
//     tb_cc_byt_handle_xchg_mem_4_reg_4_test(tb);
//     tb_cc_byt_handle_xchg_reg_4_mem_4_test(tb);
//     tb_cc_handle_bswap_dsreg_4_test(tb);
//     tb_cc_handle_bswap_dsmem_4_test(tb);
//     tb_cc_byt_handle_xadd_reg_4_reg_4_test(tb);
//     tb_cc_byt_handle_xadd_mem_4_reg_4_test(tb);
//
//     // Src SrcDst Dst
//
//     tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_sreg_4_sreg_4_test(tb);
//     tb_cc_byt_handle_src_srcdst_dst_whole_dreg_4_dreg_4_smem_4_sreg_4_test(tb);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ib_init(NULL);

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_bitwise_taint_policy(&taint_policy);

    tb = tb_cc_init_default(id, &taint_policy);

    drmgr_register_thread_init_event(thread_init);
    dr_register_exit_event(event_exit);

}

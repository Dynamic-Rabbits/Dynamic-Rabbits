/*
 * spill.h
 *
 *  Created on: 20 Jun 2018
 *      Author: john
 */

#ifndef INSTR_HANDLERS_SPILL_H_
#define INSTR_HANDLERS_SPILL_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "drext.h"
#include <stdint.h>

typedef struct {

    int scaler_cnt;
    reg_id_t scaler_regs[6];
    int xmm_cnt;
    reg_id_t xmm_regs[5];
} tb_spill_info_t;

extern tb_spill_info_t tb_1_scaler;
extern tb_spill_info_t tb_2_scaler;
extern tb_spill_info_t tb_3_scaler;
extern tb_spill_info_t tb_4_scaler;
extern tb_spill_info_t tb_5_scaler;
extern tb_spill_info_t tb_6_scaler;

extern tb_spill_info_t tb_3_scaler_2_xmm;
extern tb_spill_info_t tb_3_scaler_3_xmm;
extern tb_spill_info_t tb_2_scaler_2_xmm;
extern tb_spill_info_t tb_4_scaler_2_xmm;
extern tb_spill_info_t tb_4_scaler_3_xmm;
extern tb_spill_info_t tb_4_scaler_4_xmm;
extern tb_spill_info_t tb_5_scaler_2_xmm;
extern tb_spill_info_t tb_5_scaler_4_xmm;

void tb_live_regs_init();
void tb_live_regs_destroy();

void tb_spill_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void **spilling_data_opaque);

void tb_restore_regs(void *drcontext, instrlist_t *ilist, instr_t *where,
        void *user_data, void *spilling_data_opaque);

#endif /* INSTR_HANDLERS_SPILL_H_ */

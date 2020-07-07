/*
 * ub_spin_lock.c
 *
 *      Author: john
 */

#include "ub_spin_lock.h"
#include "../instrumentation/ub_instrum_insert.h"

void ub_sl_try_and_lock(volatile int *spin_lock) {

    int set_lock = 1;
    int comperand = 0;

    while (__sync_bool_compare_and_swap(spin_lock, comperand, set_lock) == false)
        dr_sleep(1);
}

void ub_sl_unlock(volatile int *spin_lock) {

    *spin_lock = 0;
}

void ub_sl_insert_try_and_lock(void *drcontext, instrlist_t *ilist,
        instr_t *where, reg_id_t xax_scratch, reg_id_t reg_scratch, int *spin_lock) {

    DR_ASSERT(xax_scratch == DR_REG_XAX);

    instr_t *instr;
    opnd_t opnd, opnd2;

    instr_t* done_label = INSTR_CREATE_label(drcontext);
    instr_t* retry_label = INSTR_CREATE_label(drcontext);

    // Increment scratch.
    ub_instrum_mov_st_immed_to_reg(drcontext, ilist, where, 1, reg_scratch);

    // Place retry label.
    instrlist_meta_preinsert(ilist, where, retry_label);

    // Clear scratch.
    ub_instrum_clear_reg(drcontext, ilist, where, xax_scratch);

    opnd = opnd_create_abs_addr(spin_lock, OPSZ_4);
    opnd2 = opnd_create_reg(reg_scratch);
    instr = LOCK(INSTR_CREATE_cmpxchg_4(drcontext, opnd, opnd2));
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_instr(done_label);
    instr = INSTR_CREATE_jcc(drcontext, OP_jz, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    /** Insert a pause instr to notify that CPU that this is a spin-lock. **/
    instr = INSTR_CREATE_pause(drcontext);
    instrlist_meta_preinsert(ilist, where, instr);

    opnd = opnd_create_instr(retry_label);
    instr = INSTR_CREATE_jmp(drcontext, opnd);
    instrlist_meta_preinsert(ilist, where, instr);

    /** When lock is acquired, we jump to done label. **/
    instrlist_meta_preinsert(ilist, where, done_label);
}

void ub_sl_insert_unlock(void *drcontext, instrlist_t *ilist,
        instr_t *where, int *spin_lock) {

    instr_t *instr;
    opnd_t opnd, opnd2;

    opnd = OPND_CREATE_INTPTR(NULL);
    opnd2 = opnd_create_abs_addr(spin_lock, OPSZ_4);
    instr = INSTR_CREATE_mov_st(drcontext, opnd2, opnd);
    instrlist_meta_preinsert(ilist, where, instr);
}

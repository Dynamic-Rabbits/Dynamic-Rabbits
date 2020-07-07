/*
 * ub_eflags.h
 *
 *  Created on: 10 Jan 2018
 *      Author: john
 */

#ifndef SRC_REGISTER_UB_EFLAGS_H_
#define SRC_REGISTER_UB_EFLAGS_H_

#include "dr_api.h"
#include "stdint.h"

typedef unsigned int flagindex_t;

// TODO: Make use of DR corresponding flags. No need to maintain your own.
#define CF_FLAG_INDEX 0
#define PF_FLAG_INDEX 2
#define AF_FLAG_INDEX 4
#define ZF_FLAG_INDEX 6
#define SF_FLAG_INDEX 7
#define DF_FLAG_INDEX 10
#define OF_FLAG_INDEX 11

bool ub_eflag_check_direction(unsigned int flags);

bool ub_eflag_check_b(unsigned int flags);

bool ub_eflag_check_nb(unsigned int flags);

bool ub_eflag_check_be(unsigned int flags);

bool ub_eflag_check_nbe(unsigned int flags);

bool ub_eflag_check_o(unsigned int flags);

bool ub_eflag_check_no(unsigned int flags);

bool ub_eflag_check_p(unsigned int flags);

bool ub_eflag_check_np(unsigned int flags);

bool ub_eflag_check_s(unsigned int flags);

bool ub_eflag_check_ns(unsigned int flags);

bool ub_eflag_check_e(unsigned int flags);

bool ub_eflag_check_ne(unsigned int flags);

bool ub_eflag_check_g(unsigned int flags);

bool ub_eflag_check_ge(unsigned int flags);

bool ub_eflag_check_l(unsigned int flags);

bool ub_eflag_check_le(unsigned int flags);

/**
 * RAW INSTR Imp.
 */

void ub_eflag_insert_check_direction(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_b(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_nb(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_be(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_nbe(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_o(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_no(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_p(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_np(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
        reg_id_t scratch_reg);

void ub_eflag_insert_check_s(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_ns(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);


void ub_eflag_insert_check_e(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_ne(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg);

void ub_eflag_insert_check_g(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg);

void ub_eflag_insert_check_ge(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg);

void ub_eflag_insert_check_l(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg);

void ub_eflag_insert_check_le(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg);

#endif /* SRC_REGISTER_UB_EFLAGS_H_ */

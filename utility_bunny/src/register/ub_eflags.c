/*
 * ub_eflags.c
 *
 *      Author: john
 */

#include "ub_eflags.h"
#include "../byte/ub_bit_checker.h"

/**
 * CC Imp.
 */

bool ub_eflag_check_direction(unsigned int flags) {

	//We can't call DR's instr_cmovcc_triggered bc that takes instr_t as param.

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, DF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}


bool ub_eflag_check_b(unsigned int flags) {

	//We can't call DR's instr_cmovcc_triggered bc that takes instr_t as param.

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, CF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_nb(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, CF_FLAG_INDEX, false);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_be(unsigned int flags) {

	ub_bit_check_t cf_bit_check;
	ub_byte_populate_check(&cf_bit_check, CF_FLAG_INDEX, true);

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, true);

	return ub_byte_is_any_bit_set(flags, 2, cf_bit_check, zf_bit_check);
}

bool ub_eflag_check_nbe(unsigned int flags) {

	ub_bit_check_t cf_bit_check;
	ub_byte_populate_check(&cf_bit_check, CF_FLAG_INDEX, false);

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, false);

	return ub_byte_are_all_bit_set(flags, 2, cf_bit_check, zf_bit_check);
}

bool ub_eflag_check_o(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, OF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_no(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, OF_FLAG_INDEX, false);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_p(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_np(unsigned int flags) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, false);

    return ub_byte_are_all_bit_set(flags, 1, bit_check);
}


bool ub_eflag_check_s(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, SF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_ns(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, SF_FLAG_INDEX, false);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_e(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, ZF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_ne(unsigned int flags) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, ZF_FLAG_INDEX, false);

	return ub_byte_are_all_bit_set(flags, 1, bit_check);
}

bool ub_eflag_check_g(unsigned int flags) {

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, false);

	ub_bit_check_t neg_of_bit_check;
	ub_byte_populate_check(&neg_of_bit_check, OF_FLAG_INDEX, false);

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t neg_sf_bit_check;
	ub_byte_populate_check(&neg_sf_bit_check, SF_FLAG_INDEX, false);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 3, zf_bit_check, neg_of_bit_check,
			neg_sf_bit_check)
			|| ub_byte_are_all_bit_set(flags, 3, zf_bit_check, of_bit_check,
					sf_bit_check);
}

bool ub_eflag_check_ge(unsigned int flags) {

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, of_bit_check)
			== ub_byte_are_all_bit_set(flags, 1, sf_bit_check);
}

bool ub_eflag_check_l(unsigned int flags) {

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, of_bit_check)
			!= ub_byte_are_all_bit_set(flags, 1, sf_bit_check);
}

bool ub_eflag_check_le(unsigned int flags) {

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, false);

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	return ub_byte_are_all_bit_set(flags, 1, zf_bit_check)
			|| (ub_byte_are_all_bit_set(flags, 1, of_bit_check) !=
			ub_byte_are_all_bit_set(flags, 1, sf_bit_check));
}

/**
 * RAW INSTR Imp.
 */

void ub_eflag_insert_check_direction(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, DF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}


void ub_eflag_insert_check_b(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, CF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_nb(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, CF_FLAG_INDEX, false);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_be(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t cf_bit_check;
	ub_byte_populate_check(&cf_bit_check, CF_FLAG_INDEX, true);

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, true);

	ub_byte_insert_is_any_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, 2, cf_bit_check, zf_bit_check);
}

void ub_eflag_insert_check_nbe(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t cf_bit_check;
	ub_byte_populate_check(&cf_bit_check, CF_FLAG_INDEX, false);

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, false);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 2, cf_bit_check, zf_bit_check);
}

void ub_eflag_insert_check_o(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, OF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_no(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, OF_FLAG_INDEX, false);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_p(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_np(void *drcontext, instrlist_t *ilist,
        instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
        reg_id_t scratch_reg) {

    ub_bit_check_t bit_check;
    ub_byte_populate_check(&bit_check, PF_FLAG_INDEX, false);

    ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
            is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_s(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, SF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_ns(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, SF_FLAG_INDEX, false);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_e(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, ZF_FLAG_INDEX, true);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_ne(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg) {

	ub_bit_check_t bit_check;
	ub_byte_populate_check(&bit_check, ZF_FLAG_INDEX, false);

	ub_byte_insert_are_all_bit_set(drcontext, ilist, where, val_opnd,
			is_set_label, scratch_reg, 1, bit_check);
}

void ub_eflag_insert_check_g(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg) {

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, true);

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, of_bit_check);
	opnd_t opnd = opnd_create_reg(low_scratch_reg);
	instr_t *instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, sf_bit_check);

	opnd = opnd_create_reg(high_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(high_scratch_reg);
	opnd_t opnd2 = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, zf_bit_check);

	opnd = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setnz, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(high_scratch_reg);
	opnd2 = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_or(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	instr = INSTR_CREATE_jcc(drcontext, OP_jz, *is_set_label);
	instrlist_meta_preinsert(ilist, where, instr);
}

void ub_eflag_insert_check_ge(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg) {

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, of_bit_check);

	opnd_t opnd = opnd_create_reg(low_scratch_reg);
	instr_t *instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, sf_bit_check);

	opnd = opnd_create_reg(high_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(high_scratch_reg);
	opnd_t opnd2 = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	instr = INSTR_CREATE_jcc(drcontext, OP_jz, *is_set_label);
	instrlist_meta_preinsert(ilist, where, instr);

}

void ub_eflag_insert_check_l(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg) {

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, of_bit_check);

	opnd_t opnd = opnd_create_reg(low_scratch_reg);
	instr_t *instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, sf_bit_check);

	opnd = opnd_create_reg(high_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setne, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(high_scratch_reg);
	opnd_t opnd2 = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	instr = INSTR_CREATE_jcc(drcontext, OP_jnz, *is_set_label);
	instrlist_meta_preinsert(ilist, where, instr);
}

void ub_eflag_insert_check_le(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t low_scratch_reg, reg_id_t high_scratch_reg) {

	ub_bit_check_t zf_bit_check;
	ub_byte_populate_check(&zf_bit_check, ZF_FLAG_INDEX, true);

	ub_bit_check_t of_bit_check;
	ub_byte_populate_check(&of_bit_check, OF_FLAG_INDEX, true);

	ub_bit_check_t sf_bit_check;
	ub_byte_populate_check(&sf_bit_check, SF_FLAG_INDEX, true);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, zf_bit_check);

	instr_t *instr = INSTR_CREATE_jcc(drcontext, OP_jnz, *is_set_label);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, of_bit_check);

	opnd_t opnd = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setnz, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	ub_byte_insert_test_bit(drcontext, ilist, where, val_opnd, sf_bit_check);

	opnd = opnd_create_reg(high_scratch_reg);
	instr = INSTR_CREATE_setcc(drcontext, OP_setnz, opnd);
	instrlist_meta_preinsert(ilist, where, instr);

	opnd = opnd_create_reg(high_scratch_reg);
	opnd_t opnd2 = opnd_create_reg(low_scratch_reg);
	instr = INSTR_CREATE_xor(drcontext, opnd, opnd2);
	instrlist_meta_preinsert(ilist, where, instr);

	instr = INSTR_CREATE_jcc(drcontext, OP_jnz, *is_set_label);
	instrlist_meta_preinsert(ilist, where, instr);

}

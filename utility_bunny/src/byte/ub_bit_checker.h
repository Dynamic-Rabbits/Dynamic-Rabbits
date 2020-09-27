/**
 *  @file ub_bit_checker.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef BYTE_UB_BIT_CHECKER_H_
#define BYTE_UB_BIT_CHECKER_H_

#include "dr_defines.h"
#include "dr_api.h"

typedef struct {

	bool is_set;
	unsigned int check_index;

} ub_bit_check_t;

DR_EXPORT void ub_byte_populate_check(ub_bit_check_t *bit_check,
		unsigned int check_index, bool is_set);

DR_EXPORT void ub_byte_set_bit(unsigned int *value, int set_count, ...);


DR_EXPORT bool ub_byte_are_all_bit_set(unsigned int value, int set_count, ...);

DR_EXPORT bool ub_byte_is_any_bit_set(unsigned int value, int index_num, ...);

DR_EXPORT void ub_byte_insert_test_bit(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd,  ub_bit_check_t bit_check);

DR_EXPORT void ub_byte_insert_are_all_bit_set(void *drcontext, instrlist_t *ilist,
		instr_t *where, opnd_t *val_opnd, opnd_t *is_set_label,
		reg_id_t scratch_reg, int index_num, ...);

DR_EXPORT void ub_byte_insert_is_any_bit_set(void *drcontext,
		instrlist_t *ilist, instr_t *where, opnd_t *val_opnd,
		opnd_t *is_set_label, int index_num, ...);

#endif /* BYTE_UB_BIT_CHECKER_H_ */

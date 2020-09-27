/**
 *  @file ub_instrum_insert_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test1() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_mov_ld_mem_to_reg(drcontext, ilist, where, NULL,
	DR_REG_XBX, 2, DR_REG_XBX);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_is_mov(inserted_instr) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_srcs(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t source = instr_get_src(inserted_instr, 0);
	DR_ASSERT_MSG(opnd_is_memory_reference(source) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_base(source) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_disp(source) == 2,
					"ub_instrum_insert - test1 failed...");

	opnd_t dest = instr_get_dst(inserted_instr, 0);

	DR_ASSERT_MSG(	opnd_get_reg(dest) == DR_REG_XBX,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);
}

static void test2() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_mov_st_reg_to_mem(drcontext, ilist, where,
			DR_REG_XBX, DR_REG_XBX, 2);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_is_mov(inserted_instr) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_srcs(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t dst = instr_get_dst(inserted_instr, 0);
	DR_ASSERT_MSG(opnd_is_memory_reference(dst) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_base(dst) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_disp(dst) == 2,
					"ub_instrum_insert - test1 failed...");

	opnd_t source = instr_get_src(inserted_instr, 0);

	DR_ASSERT_MSG(	opnd_get_reg(source) == DR_REG_XBX,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);
}

static void test3() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_mov_st_reg_to_reg(drcontext, ilist, where,
			DR_REG_XBX, DR_REG_XBX);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_is_mov(inserted_instr) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_srcs(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t dst = instr_get_dst(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_reg(dst) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_reg(dst) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	opnd_t source = instr_get_src(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_reg(source) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(	opnd_get_reg(source) == DR_REG_XBX,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);
}

static void test4() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_clear_reg_no_eflag_corrupt(drcontext, ilist, where,
			DR_REG_XBX);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_is_mov(inserted_instr) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_srcs(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t dst = instr_get_dst(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_reg(dst) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_reg(dst) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	opnd_t source = instr_get_src(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_immed(source) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(	opnd_get_immed_int(source) == 0,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);
}
/*
static void test5() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_inc_mem_with_eflag(drcontext, ilist, where,
			DR_REG_XBX, 5, DR_REG_XSP);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_get_opcode(inserted_instr) == OP_lea,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t dst = instr_get_dst(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_memory_reference(dst) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_base(dst) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_disp(dst) != 2,
					"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_disp(dst) == 5,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);

}*/

static void test6() {

	void *drcontext = dr_get_current_drcontext();

	instrlist_t *ilist = instrlist_create(drcontext);

	instr_t *where = INSTR_CREATE_and(drcontext, opnd_create_reg(DR_REG_XBX), opnd_create_reg(DR_REG_XBX));
	instrlist_init(ilist);

	instrlist_append(ilist, where);

	ub_instrum_lea_base_disp(drcontext, ilist, where,
			DR_REG_XBX, 5, DR_REG_XSP);

	instr_t *inserted_instr = instr_get_prev(where);

	DR_ASSERT_MSG(instr_get_opcode(inserted_instr) == OP_lea,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(instr_num_dsts(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t dst = instr_get_dst(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_reg(dst) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_reg(dst) == DR_REG_XSP,
				"ub_instrum_insert - test1 failed...");


	DR_ASSERT_MSG(instr_num_srcs(inserted_instr) == 1,
			"ub_instrum_insert - test1 failed...");

	opnd_t src = instr_get_src(inserted_instr, 0);

	DR_ASSERT_MSG(opnd_is_memory_reference(src) == true,
			"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_base(src) == DR_REG_XBX,
				"ub_instrum_insert - test1 failed...");

	DR_ASSERT_MSG(opnd_get_disp(src) == 5,
					"ub_instrum_insert - test1 failed...");

	instrlist_clear_and_destroy(drcontext, ilist);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
//	test5();
	test6();
}


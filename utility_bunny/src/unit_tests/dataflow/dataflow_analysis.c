/*
 * dataflow_analysis.c
 *
 *      Author: john
 */

#include "../../dataflow/ub_in_out_analysis.h"
#include "../../dataflow/ub_dataflow_analysis.h"
#include "../../datastructs/lists/ub_list.h"
#include <string.h>

static void test1() {

	void *dataflow = ub_create_dataflow_analysis();
	ub_destroy_dataflow_analysis(dataflow);
}

static void test2() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);
	while (my_instr) {

		DR_ASSERT(!ub_dataflow_is_any_instr_src_tainted(instr, dataflow));
		DR_ASSERT(!ub_dataflow_is_any_instr_dst_tainted(instr, dataflow));
		DR_ASSERT(!ub_dataflow_is_instr_tainted(instr, dataflow));

		DR_ASSERT(!ub_dataflow_is_instr_tainted(instr, dataflow));

		ub_dataflow_propagate(instr, dataflow);
		my_instr = instr_get_next(my_instr);
	}

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test3() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, true);

	DR_ASSERT(!ub_dataflow_is_any_instr_src_tainted(instr, dataflow));
	DR_ASSERT(ub_dataflow_is_any_instr_dst_tainted(instr, dataflow));
	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(!ub_dataflow_is_any_instr_src_tainted(instr, dataflow));
	DR_ASSERT(!ub_dataflow_is_any_instr_dst_tainted(instr, dataflow));
	DR_ASSERT(!ub_dataflow_is_instr_tainted(instr, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test4() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);

	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test5() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);

	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test6() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);

	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test7() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);

	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test8() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	DR_ASSERT(!ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test9() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	DR_ASSERT(ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test10() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XSI),
			opnd_create_reg(DR_REG_XAX));
	instrlist_append(bb, instr);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test11() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XSI),
			opnd_create_reg(DR_REG_XAX));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xsi_opnd, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test12() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XSI),
			opnd_create_reg(DR_REG_XAX));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test13() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XAX),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, opnd_create_reg(DR_REG_XSI),
			opnd_create_reg(DR_REG_XAX));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test14() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XSI),
			mem_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test15() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XSI),
			mem_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test16() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XSI),
			mem_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test17() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XSI),
			mem_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&xsi_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test18() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xdx_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test19() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xdx_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test20() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xdx_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test21() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xdx_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test22() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xdx_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test23() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test24() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test25() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test26() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test27() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSI, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test28() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 70);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test29() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 6);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdx_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test30() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 6);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_imm(drcontext, mem_opnd2,
			opnd_create_immed_int(2, OPSZ_4));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test31() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 9);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_imm(drcontext, mem_opnd2,
			opnd_create_immed_int(2, OPSZ_4));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test32() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 18);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 20);
	opnd_t mem_opnd3 = OPND_CREATE_MEMPTR(DR_REG_XAX, 30);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xsi_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdi_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, xdi_opnd, mem_opnd3);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd3, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** Third STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test33() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 18);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 20);
	opnd_t mem_opnd3 = OPND_CREATE_MEMPTR(DR_REG_XAX, 30);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);
	opnd_t xsi_opnd = opnd_create_reg(DR_REG_XSI);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, xsi_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xdi_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, xdi_opnd, mem_opnd3);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd3, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	/** Third STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xsi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test34() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XAX, DR_REG_XDI, 1, 0,
			OPSZ_1);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSP, 40);
	opnd_t mem_opnd3 = OPND_CREATE_MEM_lea(DR_REG_XBP, DR_REG_XDI, 4, 0);
	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	instr_t *instr = INSTR_CREATE_movzx(drcontext, xax_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, xdi_opnd, mem_opnd2);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_lea(drcontext, xdi_opnd, mem_opnd3);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test35() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XAX, DR_REG_XDI, 1, 0,
			OPSZ_1);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XSP, 40);
	opnd_t mem_opnd3 = OPND_CREATE_MEM_lea(DR_REG_XBP, DR_REG_XDI, 4, 0);
	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	instr_t *instr = INSTR_CREATE_movzx(drcontext, xax_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_ld(drcontext, xdi_opnd, mem_opnd2);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_lea(drcontext, xdx_opnd, mem_opnd3);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test36() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	opnd_t push_opnd = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -1, OPSZ_VARSTACK);
	opnd_t push_opnd2 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -2, OPSZ_VARSTACK);
	opnd_t push_opnd3 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -3, OPSZ_VARSTACK);

	instr_t *instr = INSTR_CREATE_push(drcontext, xax_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_push(drcontext, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_push(drcontext, xdi_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&push_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&push_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&push_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test37() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	opnd_t push_opnd = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -1, OPSZ_VARSTACK);
	opnd_t push_opnd2 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -2, OPSZ_VARSTACK);
	opnd_t push_opnd3 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * -3, OPSZ_VARSTACK);

	instr_t *instr = INSTR_CREATE_push(drcontext, xax_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_push(drcontext, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_push(drcontext, xdi_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&push_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&push_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&push_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&push_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&push_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test38() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	opnd_t pop_opnd = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0, 0,
	OPSZ_VARSTACK);
	opnd_t pop_opnd2 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *), OPSZ_VARSTACK);
	opnd_t pop_opnd3 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * 2, OPSZ_VARSTACK);

	instr_t *instr = INSTR_CREATE_pop(drcontext, xax_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdi_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&pop_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&pop_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&pop_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test39() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	opnd_t pop_opnd = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0, 0,
	OPSZ_VARSTACK);
	opnd_t pop_opnd2 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *), OPSZ_VARSTACK);
	opnd_t pop_opnd3 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * 2, OPSZ_VARSTACK);

	instr_t *instr = INSTR_CREATE_pop(drcontext, xax_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdi_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&pop_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&pop_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&pop_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test40() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xdi_opnd = opnd_create_reg(DR_REG_XDI);

	opnd_t pop_opnd = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0, 0,
	OPSZ_VARSTACK);
	opnd_t pop_opnd2 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *), OPSZ_VARSTACK);
	opnd_t pop_opnd3 = opnd_create_base_disp(DR_REG_XSP, DR_REG_NULL, 0,
			sizeof(void *) * 2, OPSZ_VARSTACK);

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XSI, 90);

	instr_t *instr = INSTR_CREATE_pop(drcontext, xax_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pop(drcontext, xdi_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, xdi_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&pop_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&pop_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&pop_opnd3, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdi_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));

	/** THIRD STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));

	/** FOUR STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&pop_opnd3, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdi_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test41() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t abs_opnd = opnd_create_abs_addr((void *) 0x124446, OPSZ_4);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&abs_opnd, dataflow, true);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);

	instr_t *my_instr = instrlist_first_app(bb);

	DR_ASSERT(!ub_dataflow_is_instr_tainted(instr, dataflow));

	ub_dataflow_propagate(instr, dataflow);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test42() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t abs_opnd = opnd_create_abs_addr((void *) 0x124446, OPSZ_4);
	opnd_t mem_opnd2 = OPND_CREATE_MEMPTR(DR_REG_XAX, 5);
	opnd_t xdx_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t xax_opnd = opnd_create_reg(DR_REG_XAX);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, abs_opnd, xdx_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, xax_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&abs_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&xdx_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&xax_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&abs_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&abs_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xdx_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&xax_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test43() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 1, 0,
			OPSZ_16);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XAX, DR_REG_NULL, 1, 0,
			OPSZ_16);
	opnd_t mem_opnd3 = opnd_create_base_disp(DR_REG_XAX, DR_REG_XCX, 1, -8,
			OPSZ_16);

	instr_t *instr = INSTR_CREATE_movq(drcontext, opnd_create_reg(DR_REG_XMM0),
			mem_opnd2);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movq(drcontext, opnd_create_reg(DR_REG_XMM1),
			mem_opnd3);
	instrlist_append(bb, instr);

	instr = INSTR_CREATE_mov_ld(drcontext, mem_opnd,
			opnd_create_reg(DR_REG_XMM0));
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd3, dataflow, false);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** SECOND STEP **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** Third STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test44() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XDX, DR_REG_NULL, 1, 0,
			OPSZ_8);

	instr_t *instr = INSTR_CREATE_movlpd(drcontext,
			opnd_create_reg(DR_REG_XMM0), mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqa(drcontext, opnd_create_reg(DR_REG_XMM1),
			opnd_create_reg(DR_REG_XMM0));
	instrlist_append(bb, instr);

	opnd_t xmm_opnd1 = opnd_create_reg(DR_REG_XMM0);
	opnd_t xmm_opnd2 = opnd_create_reg(DR_REG_XMM1);

	ub_dataflow_mark_opnd_tainted(&xmm_opnd1, dataflow, true);

	/** FIRST STEP **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));

	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** SECOND STEP **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&xmm_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test45() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XDX),
			OPND_CREATE_MEMPTR(DR_REG_XBP, 4));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XAX, 4),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);

	ub_in_out_set_t in_out_set;
	ub_init_in_out_set(&in_out_set);
	ub_get_in_out_set(&in_out_set, bb);

	for (void * it = ub_list_get_start_it(in_out_set.reg_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *reg_opnd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(reg_opnd, dataflow, true);
	}

	for (void * it = ub_list_get_start_it(in_out_set.mem_base_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *mem_base_opmd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(mem_base_opmd, dataflow, true);
	}

	for (void * it = ub_list_get_start_it(in_out_set.mem_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *mem_opnd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(mem_opnd, dataflow, true);
	}

	int i = 0;
	instr = instrlist_first_app(bb);
	while (instr != NULL) {
		// If instr deals with tainted data, apply instrumentation.
		if (!ub_dataflow_is_instr_tainted(instr, dataflow)) {
			DR_ASSERT(false);
		}

		i++;
		ub_dataflow_propagate(instr, dataflow);

		instr = instr_get_next_app(instr);
	}

	ub_delete_in_out_set(&in_out_set);

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test46() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XBP, DR_REG_NULL, 1, 0,
			OPSZ_4);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XBP, DR_REG_NULL, 1, 4,
			OPSZ_4);
	opnd_t imm_opnd = opnd_create_immed_int(0, OPSZ_4);
	opnd_t reg_opnd = opnd_create_reg(DR_REG_XBX);

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, reg_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd, reg_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&reg_opnd, dataflow, false);

	/** STEP 1 **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 2 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 3 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 4 **/
	DR_ASSERT(!ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test47() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_8);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_1);
	opnd_t imm_opnd = opnd_create_immed_int(0, OPSZ_4);
	opnd_t reg_opnd = opnd_create_reg(DR_REG_XMM0);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqu(drcontext, reg_opnd, mem_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&reg_opnd, dataflow, false);

	/** STEP 1 **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 2 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test48() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_8);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_4);
	opnd_t imm_opnd = opnd_create_immed_int(0, OPSZ_4);
	opnd_t reg_opnd = opnd_create_reg(DR_REG_XMM0);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqu(drcontext, reg_opnd, mem_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_pxor(drcontext, reg_opnd, reg_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqu(drcontext, mem_opnd, reg_opnd);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&reg_opnd, dataflow, false);

	/** STEP 1 **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 2 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 3 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 4 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test49() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XBP, DR_REG_XBX, 1, 0,
			OPSZ_8);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_4);
	opnd_t imm_opnd = opnd_create_immed_int(0, OPSZ_4);
	opnd_t reg_opnd = opnd_create_reg(DR_REG_XAX);
	opnd_t reg_opnd2 = opnd_create_reg(DR_REG_XMM0);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, reg_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqu(drcontext, mem_opnd, reg_opnd2);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&reg_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&reg_opnd2, dataflow, true);

	/** STEP 1 **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 2 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 3 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test50() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	opnd_t mem_opnd = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_8);
	opnd_t mem_opnd2 = opnd_create_base_disp(DR_REG_XBP, DR_REG_XAX, 1, 0,
			OPSZ_4);
	opnd_t imm_opnd = opnd_create_immed_int(0, OPSZ_4);
	opnd_t reg_opnd = opnd_create_reg(DR_REG_XDX);
	opnd_t reg_opnd2 = opnd_create_reg(DR_REG_XMM0);

	instr_t *instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, reg_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, mem_opnd2, imm_opnd);
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_movdqu(drcontext, mem_opnd, reg_opnd2);
	instrlist_append(bb, instr);

	ub_dataflow_mark_opnd_tainted(&mem_opnd, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&mem_opnd2, dataflow, false);
	ub_dataflow_mark_opnd_tainted(&reg_opnd, dataflow, true);
	ub_dataflow_mark_opnd_tainted(&reg_opnd2, dataflow, true);

	/** STEP 1 **/
	instr_t *my_instr = instrlist_first_app(bb);
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(!ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 2 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	/** STEP 3 **/
	DR_ASSERT(ub_dataflow_is_instr_tainted(my_instr, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));
	ub_dataflow_propagate(my_instr, dataflow);
	my_instr = instr_get_next(my_instr);

	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&mem_opnd2, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd, dataflow));
	DR_ASSERT(ub_dataflow_is_opnd_tainted(&reg_opnd2, dataflow));

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

static void test51() {

	void *drcontext = dr_get_current_drcontext();
	instrlist_t *bb = instrlist_create(drcontext);
	instrlist_init(bb);

	void *dataflow = ub_create_dataflow_analysis();

	instr_t *instr = INSTR_CREATE_mov_ld(drcontext, opnd_create_reg(DR_REG_XDX),
			OPND_CREATE_MEMPTR(DR_REG_XBP, 4));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XAX, 4),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);

	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XAX, 4),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XAX, 4),
			opnd_create_reg(DR_REG_XDX));
	instrlist_append(bb, instr);
	instr = INSTR_CREATE_mov_st(drcontext, OPND_CREATE_MEMPTR(DR_REG_XBP, 4),
			opnd_create_immed_int(0, OPSZ_4));
	instrlist_append(bb, instr);

	ub_in_out_set_t in_out_set;
	ub_init_in_out_set(&in_out_set);
	ub_get_in_out_set(&in_out_set, bb);

	for (void * it = ub_list_get_start_it(in_out_set.reg_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *reg_opnd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(reg_opnd, dataflow, true);
	}

	for (void * it = ub_list_get_start_it(in_out_set.mem_base_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *mem_base_opmd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(mem_base_opmd, dataflow, true);
	}

	for (void * it = ub_list_get_start_it(in_out_set.mem_list); it; it =
			ub_list_get_next_it(it)) {

		// This opnd is therefore tainted. We need to update the taint state.
		opnd_t *mem_opnd = ub_list_get_it_value(it);
		ub_dataflow_mark_opnd_tainted(mem_opnd, dataflow, true);
	}

	int i = 0;
	instr = instrlist_first_app(bb);
	while (instr != NULL) {
		// If instr deals with tainted data, apply instrumentation.
		if (!ub_dataflow_is_instr_tainted(instr, dataflow)) {
			DR_ASSERT(false);
		}

		i++;
		ub_dataflow_propagate(instr, dataflow);

		instr = instr_get_next_app(instr);
	}

	ub_delete_in_out_set(&in_out_set);

	ub_destroy_dataflow_analysis(dataflow);
	instrlist_clear_and_destroy(drcontext, bb);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();
	test12();
	test13();
	test14();
	test15();
	test16();
	test17();
	test18();
	test19();
	test20();
	test21();
	test22();
	test23();
	test24();
	test25();
	test26();
	test27();
	test28();
	test29();
	test30();
	test31();
	test32();
	test33();
	test34();
	test35();
	test36();
	test37();
	test38();
	test39();
	test40();
	test41();
	test42();
	test43();
	test44();
	test45();
	test46();
	test47();
	test48();
	test49();
	test50();
	test51();
}


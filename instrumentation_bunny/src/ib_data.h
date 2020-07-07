/**
 *  @file ib_data.h
 *  @brief Important structure definitions and type defs for instrumentation
 *  @author: John F.X. Galea
 */

#ifndef IB_DATA_H_
#define IB_DATA_H_

#include "ib_defines.h"
#include "utility_bunny.h"
#include "drbbdup.h"


typedef struct {
    unsigned int id;
    ib_analysis_action_t action;
} ib_instrum_analysis_data_t;

typedef struct {

    size_t tool_id;
    ib_dup_opts_t dup_opts;
} ib_dup_tool_t;

typedef struct {

	reg_id_t tls_raw_reg;
	uint tls_raw_base;

	size_t tool_id_counter;
	void *slicer;
	void *opcode_hook_mngr;
	int ref_counter;

	int tls_data_idx;

	ib_dup_tool_t *dup_tool_info;
} ib_ctx_t;


/**
 *  @struct ib_opnd_extraction_data_t
 *
 *  Information extracted from an opnd.
 *
 *  @var ib_opnd_extraction_data_t::loc_data
 *  Information of the location.
 *
 *	@var ib_opnd_extraction_data_t::opnd_data
 *	The actual opnd struct provided by DynamoRIO. The rest of the info was extracted
 *	from this struct.
 */
typedef struct {
	ub_loc_info_t loc_data;
	opnd_t opnd_data;
} ib_opnd_extraction_data_t;

/**
 *  @struct ib_comp_data_t
 *
 *  An operand can deal with multiple inner operands. For instance, LEA
 *  deals with base register as well as index register.
 *
 *  This struct stores information about a single component, say the base
 *  register, or also the effective result.
 *
 *  @var ib_comp_data_t::opnd
 *	The value that represents the opnd. Could be a reg_id or an effective addr
 *
 *  @var ib_comp_data_t::size
 *	The size of the operand. E.g. EAX is of size 4 bytes
 *
 *  @var ib_comp_data_t::conc
 *	The concrete value of the operand.
 *
 *  @var ib_comp_data_t::map
 *  The appropriate map to use for tracking the operand described
 *
 *  @var ib_comp_data_t::type
 *  The type of component.
 */
typedef struct {

	uintptr_t opnd;
	uintptr_t type;
	uintptr_t size;
	byte conc[16];
} ib_comp_data_t;

/**
 * @struct ib_opnd_data_t
 *
 *  Stores operand information
 *
 *  @var ib_opnd_data_t::mode
 *	The mode used to determine which components are used by the operand
 *
 *  @var ib_opnd_data_t::components
 *	Information on the components that make up the opnd
 */
typedef struct {

	// Denotes how the struct has been populated.
	//ib_opnd_mode mode;

	ib_comp_data_t components[5];
} ib_opnd_data_t;

typedef struct {

    drvector_t instrum_vector;
    size_t index;
    size_t max;
    void *post_instrum_info;
} ib_analyse_instrum_info_t;

/**
 *  @struct ib_per_thread_t
 *
 *	Stores information pertaining to an instrumented instruction.
 *
 *  @var ib_per_thread_t::instr_opcode
 *  The opcode of the instrumented instruction.
 *
 *  @var ib_per_thread_t::flag_value
 *  The saved flag register.
 *
 *  @var ib_per_thread_t::instr_src_count
 *  The count of source operands of the instrumented instruction.
 *
 *  @var ib_per_thread_t::instr_dst_count
 *  The count of destination operands of the instrumented instruction.
 *
 *  @var ib_per_thread_t::saved_ret_addr
 *  The return address to jump to once code in a cache has finished
 *  executing.
 *
 *  @var ib_per_thread_t::opnd_slots slots for saving src and dst opnd data
 */
typedef struct {

	int instr_opcode;
	uintptr_t flag_value;
	uintptr_t instr_src_count;
	uintptr_t instr_dst_count;
	ib_comp_data_t components[12 * 5];
}
ib_per_thread_t;

#endif

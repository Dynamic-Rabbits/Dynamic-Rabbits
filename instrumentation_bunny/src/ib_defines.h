/**
 *  @file ib_defines.h
 *  @brief Several definitions related to instrumentation which
 *  are exposed.
 *  @author John F.X. Galea
 */

#ifndef IB_DEFINES_H_
#define IB_DEFINES_H_

#include "dr_api.h"
#include "dr_defines.h"
#include <stdint.h>
#include "drvector.h"
#include "drbbdup.h"

//#define DEBUG_CHECK_ASSESS 1

/**
 * Definitions for specifying the position of instrumentation code.
 */
typedef bool IB_INSTRUM_POS;
#define IB_INSTRUM_BEFORE true
#define IB_INSTRUM_AFTER false

typedef void (*ib_skip_check_t)(void *, void *);
extern ib_skip_check_t check;
extern void *check_data;

/**
 * Defines flags that specify what information to be available at runtime.
 */
typedef unsigned int IB_INSTRUM_OPT;
// No additional information
#define IB_OPT_BARE 0
// Include conc info
#define IB_OPT_CONC_INFO 1
// Include conc info
#define IB_OPT_OPCODE_INFO 2
// Include operand sizes info
#define IB_OPT_OPND_COUNT_INFO 4
/**
 *  The mode of storing and loading an operand during instrumentation
 *
 *  IB_OPND_ADDR_GENERATOR_MODE => This will store the effective address, along
 *  with the sub components used in address generation, such as the base reg.
 *
 *  IB_OPND_EFFECTIVE_MODE => This will store the effective address and not
 *
 * This flag includes address generator operands.
 */
#define IB_OPT_ADDR_GEN_INFO 8
// Include flag info
#define IB_OPT_FLAG_INFO 16
// Include PC info
#define IB_OPT_PC_INFO 32
// Include operand sizes info
#define IB_OPT_LOC_TYPE_INFO 64
// Include operand sizes info
#define IB_OPT_LOC_SIZE_INFO 128
// Include full opnd storage
#define IB_OPT_FULL_OPND_INFO 256
#define IB_OPT_FULL_ADDR_GEN_INFO 512

// Only include mem addr as operands. Other operands may be obtained from instr info.
#define IB_OPT_ADDR_OPND_INFO 1024
#define IB_OPT_REG_OPND_INFO 2048
#define IB_OPT_IMMED_OPND_INFO 4096

/**
 * A function pointer to the instrumentation code provided by the user. It has a similar
 * params to the clean-call.
 */
typedef void (*ib_insert_hndle_func_t)(void *, instrlist_t *, instr_t *,
		instr_t *, void *, void *);

/**
 *  Call-back function used for context switching when jumping to a code cache.
 *
 *  Spills registers so that they can be used in the code cache.
 *
 *  XAX needs to be spilled.
 *
 *  @param where The instruction where instrumentation will be placed before it
 *  @return Returns a register, which won't be used for anything else but to act as
 *  a return reg. Note return reg cannot be XAX.
 *
 *  It must be noted that the return reg must be the same recorded when initialising the code
 *  cache. It also cannot be used by the instrumentation code, as otherwise the Instrumentation
 *  Bunny would not be able to jump back if it is corrupted.
 *
 */
typedef void (*ib_spill_regs_func_t)(void *drcontext, instrlist_t *ilist,
		instr_t *where, void * user_data, void **spill_data);

/**
 *  Call-back function used for context switching
 *
 *  Restores the content of registers that have been spilled via spill_regs_func_t
 *
 *  @param where The instruction where instrumentation will be placed before it
 */
typedef void (*ib_restore_regs_func_t)(void *drcontext, instrlist_t *ilist,
		instr_t *where, void * user_data, void *spill_data);

/**
 *  @struct ib_insert_hndle_data_t
 *
 *  @var ib_code_cache_data_t::user_instrum_func The function to call when initialising
 *  the code cache.
 *  @var ib_code_cache_data_t::user_data The user data to pass to the function.
 *  @var ib_code_cache_data_t::clobbers_return_reg A flag denoting whether code in cache
 *  makes use, and therefore clobbers the return reg.
 */
typedef struct {
	ib_insert_hndle_func_t user_instrum_func;
	void *user_data;
	ib_spill_regs_func_t spill_reg_func;
	ib_restore_regs_func_t restore_reg_func;
	void *spilling_user_data;

} ib_insert_hndle_data_t;

/**
 * Enum of results provided by a guard.
 */
typedef enum {
	IB_GUARD_HOOK, IB_GUARD_SKIP, IB_GUARD_DEFAULT,
} ib_guard_result_t;

/**
 *  Call-back function.
 *
 *  Checks whether an instruction should be instrumented.
 *
 *  This enables more fine-grained control on whether a certain instruction should be
 *  instrumented, rather than just solely checking their opcode.
 *
 *  For instance, one might want to instrument mov instructions where the destination
 *  register is strictly EAX.
 *
 *  @param instr The instruction to check.
 *  @return Returns the result of the check.
 */
typedef bool (*ib_check_hook_guard_func_t)(instr_t *instr);

/**********************************************************
 * DUP FUNCTIONS
 */

typedef enum {
	IB_INSTRUM_ACTION_SKIP,
	IB_INSTRUM_ACTION_APPLY,

} ib_analysis_action_t;

typedef bool (*ib_create_default_manager_t)(void *drbbdup_ctx, void *drcontext,
		void *tag, instrlist_t *bb, bool *enable_dynamic_fp,
		uint *default_case_value, void *user_data);

typedef void* (*ib_get_pre_analysis_data_t)(void *drcontext, instrlist_t *bb,
		void *user_data);

typedef void (*ib_destroy_pre_analysis_t)(void *drcontext, void *user_data,
		void *pre_analysis_data);

typedef size_t (*ib_analyse_bb_t)(void *drcontext, instrlist_t *bb,
		uint case_val, void *user_data, drvector_t *action,
		void *pre_analysis_data, void **post_data);

typedef void (*ib_get_comparator_t)(void *drcontext, instrlist_t *bb,
		instr_t *where, void *user_data, void *pre_analysis_data);

typedef bool (*ib_allow_fp_t)(void *drbbdup_ctx, void *drcontext,
		void *tag, instrlist_t *ilist, uint dynamic_case,
		bool *enable_dynamic_fp, void *user_data);

typedef void (*ib_post_handling_t)(void *drcontext, instrlist_t *bb,
		instr_t *where, uint case_val, void *user_data, void *pre_analysis_data,
		void *post_data);

typedef struct {

	ib_create_default_manager_t create_default_manager;
	ib_get_pre_analysis_data_t get_pre_analysis_data;
	ib_destroy_pre_analysis_t destroy_pre_analysis_data;
	ib_analyse_bb_t analyse_bb;
	ib_get_comparator_t get_comparator;
	ib_allow_fp_t allow_fp;
	ib_post_handling_t post_handling;
	void *user_data;
} ib_dup_opts_t;

typedef drbbdup_fp_settings_t ib_dup_fp_settings_t;

DR_EXPORT bool ib_register_case_value(void *drbbdup_ctx, uint case_val);

#endif

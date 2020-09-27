/*
 * tb_umbra_fault_handlers.h
 *
 *  Created on: 28 May 2019
 *      Author: john
 */

#ifndef TAINT_ENGINES_TAINT_ANALYSIS_SHDW_FAULT_HANDLERS_TB_UMBRA_FAULT_HANDLERS_H_
#define TAINT_ENGINES_TAINT_ANALYSIS_SHDW_FAULT_HANDLERS_TB_UMBRA_FAULT_HANDLERS_H_

#include "../../../tb_bunny_private.h"
#include "instrumentation_bunny.h"
#include "umbra.h"

dr_signal_action_t tb_umbra_event_signal_handler(void *drcontext,
        dr_siginfo_t *info, tb_context_t * tb_ctx, umbra_map_t *map);


#endif /* TAINT_ENGINES_TAINT_ANALYSIS_SHDW_FAULT_HANDLERS_TB_UMBRA_FAULT_HANDLERS_H_ */

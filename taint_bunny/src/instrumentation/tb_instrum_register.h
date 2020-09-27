/**
 *  @file tb_dispatcher.h
 *  @brief The dispatcher instruments the appropriate taint handles
 *  for instructions
 *  with taint analysis code.
 *  @author John F.X. Galea
 */

#ifndef INSTRUMENTATION_TB_DISPATCHER_H_
#define INSTRUMENTATION_TB_DISPATCHER_H_

#include "../taint_bunny.h"
#include "dr_api.h"
#include "drmgr.h"
#include "../tb_bunny_private.h"
#include "tb_instrum_register_helper.h"

/**
 *  Responsible for weaving hooks prior to concrete instructions so that
 *  taint can be propagated.
 */
void tb_register_instrumentation_hooks(tb_context_t *tb_cxt);

#endif /* INSTRUMENTATION_TB_DISPATCHER_H_ */

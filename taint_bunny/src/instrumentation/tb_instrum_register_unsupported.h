/*
 * tb_instrum_register_unsupported.h
 *
 *  Created on: 7 May 2018
 *      Author: john
 */

#ifndef INSTRUMENTATION_TB_INSTRUM_REGISTER_UNSUPPORTED_H_
#define INSTRUMENTATION_TB_INSTRUM_REGISTER_UNSUPPORTED_H_

#include "dr_api.h"
#include "dr_defines.h"
#include "../tb_defines.h"
#include "../tb_bunny_private.h"
#include "drext.h"
#include <stdint.h>

void tb_register_default_hooks(tb_context_t *tb_ctx);

#endif /* INSTRUMENTATION_TB_INSTRUM_REGISTER_UNSUPPORTED_H_ */

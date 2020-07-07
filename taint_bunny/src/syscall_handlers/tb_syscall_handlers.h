/*
 * tb_syscall_handlers.h
 *
 *  Created on: 17 Sep 2018
 *      Author: john
 */

#ifndef TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_HANDLERS_H_
#define TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_HANDLERS_H_

#include "utility_bunny.h"

void tb_syscall_handlers_init(client_id_t client_id, void *tb_ctx);
void tb_syscall_handlers_destroy();

#endif /* TAINT_ENGINES_SYSCALL_HANDLERS_TB_SYSCALL_HANDLERS_H_ */

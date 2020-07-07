/*
 * ub_syscall_helper.h
 *
 *  Created on: 17 Sep 2018
 *      Author: john
 */

#ifndef SYSCALLS_UB_SYSCALL_HELPER_H_
#define SYSCALLS_UB_SYSCALL_HELPER_H_

#include "dr_api.h"
#include "drmgr.h"

#include <linux/net.h>
#include <string.h>
#include <sys/uio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <asm/unistd.h>

DR_EXPORT bool ub_get_syscall_result(void *drcontext, uint64 *res_value);
DR_EXPORT void ub_get_syscall_arg(void *drcontext, uint argnum, ptr_uint_t *value);

DR_EXPORT void *ub_create_single_buf_input_list(void * buf, ssize_t read_size);
DR_EXPORT void *ub_create_input_list_from_iov(ssize_t total_read,
		struct iovec *iov, int iovcnt);

#endif /* SYSCALLS_UB_SYSCALL_HELPER_H_ */

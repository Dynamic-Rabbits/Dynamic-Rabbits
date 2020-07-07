/*
 * ub_syscall_helper.c
 *
 *      Author: john
 */

#include "ub_syscall_helper.h"
#include "drsyscall.h"
#include "../datastructs/lists/ub_list.h"
#include "../events/input/input_buf/input_buf.h"

DR_EXPORT bool ub_get_syscall_result(void *drcontext, uint64 *res_value) {

	bool success = false;

	if (drsys_cur_syscall_result(drcontext, &success, res_value, NULL)
			!= DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "drsys_cur_syscall_result failed");

	return success;
}

DR_EXPORT void ub_get_syscall_arg(void *drcontext, uint argnum, ptr_uint_t *value) {

	if (drsys_pre_syscall_arg(drcontext, argnum, value) != DRMF_SUCCESS)
		DR_ASSERT_MSG(false, "drsys_pre_syscall_arg failed");
}


DR_EXPORT void *ub_create_single_buf_input_list(void * buf, ssize_t read_size) {

	void *buf_list = ub_list_create();

	ub_list_insert(buf_list, ub_create_input_buf(buf, read_size));

	return buf_list;
}

DR_EXPORT void *ub_create_input_list_from_iov(ssize_t total_read,
		struct iovec *iov, int iovcnt) {

	void *buf_list = ub_list_create();

	int counter = 0;

	// Check if we got any reads and bufs
	if (total_read <= 0 && iovcnt <= 0)
		return buf_list;

	while (counter < iovcnt) {

		if (total_read <= iov[counter].iov_len) {

			// Base case. Reached total read.
			ub_list_insert(buf_list,
					ub_create_input_buf(iov[counter].iov_base,
							(int64_t) total_read));
			break;
		} else {

			ub_list_insert(buf_list,
					ub_create_input_buf(iov[counter].iov_base,
							(int64_t) iov[counter].iov_len));

			total_read -= iov[counter].iov_len;
		}
		counter++;
	}

	return buf_list;
}

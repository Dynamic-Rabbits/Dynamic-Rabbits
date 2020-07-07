/*
 * pb_private.h
 *
 *  Created on: 5 Aug 2018
 *      Author: john
 */

#ifndef SRC_CFI_PRIVATE_H_
#define SRC_CFI_PRIVATE_H_

#include "cfi_bunny.h"

typedef struct {

    void *taint_bunny;
	void *user_data;
	cfib_handle_detection_func_t detection_func;
	void *tool_id;
	CFIB_EV_DETECTION_OPT_t detection_options;
	IB_INSTRUM_OPT instrum_opts;
} cfib_context_t;


#endif /* SRC_CFI_PRIVATE_H_ */

/*
 * pb_private.h
 *
 *  Created on: 5 Aug 2018
 *      Author: john
 */

#ifndef SRC_PB_PRIVATE_H_
#define SRC_PB_PRIVATE_H_

#include "path_bunny.h"

typedef struct {
    void *taint_bunny;
    IB_INSTRUM_OPT ib_options;
    PB_EV_OPT_t pb_opts;
    path_bunny_funcs_t funcs;
    void *user_data;
    void *tool_id;
} pb_context_t;

#endif /* SRC_PB_PRIVATE_H_ */

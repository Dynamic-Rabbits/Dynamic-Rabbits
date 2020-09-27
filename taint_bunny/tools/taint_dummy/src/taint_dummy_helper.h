/*
 * taint_dummy_helper.h
 *
 *  Created on: 15 Mar 2019
 *      Author: john
 */

#ifndef TAINT_DUMMY_HELPER_H_
#define TAINT_DUMMY_HELPER_H_

#include "dr_defines.h"
#include "taint_bunny.h"

void taint_dummy_intro_init(client_id_t client_id, tb_cc_get_default_label_t get_default_label, bool is_random_samp);

void taint_dummy_exit();

#endif /* TAINT_DUMMY_HELPER_H_ */

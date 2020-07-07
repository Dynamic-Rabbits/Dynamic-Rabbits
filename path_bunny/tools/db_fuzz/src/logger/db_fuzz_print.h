/*
 * db_fuzz_print.h
 *
 *  Created on: 11 Apr 2019
 *      Author: john
 */

#ifndef LOGGER_DB_FUZZ_PRINT_H_
#define LOGGER_DB_FUZZ_PRINT_H_

#include "taint_bunny.h"

void db_fuzz_store_pc(void *drcontext, char *buf_pc, size_t size);

void db_fuzz_store_conc_val(uintptr_t src_conc, char *buf_conc, size_t size);

bool db_fuzz_store_offsets_in_robdd(ub_bdd_node_t node, char *buf_offset,
        size_t buf_size);

#endif /* LOGGER_DB_FUZZ_PRINT_H_ */

/*
 * tb_fp_stat.h
 *
 *  Created on: 24 Jul 2019
 *      Author: john
 */

#ifndef OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_STAT_H_
#define OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_STAT_H_

#include "utility_bunny.h"

//#define ENABLE_STATS 1

extern unsigned long inc_false_fp;
extern unsigned long total_default;
extern unsigned long total_elided;
extern unsigned long total_gen_fp_count;

void tb_fp_stat_init();
void tb_fp_stat_exit();

size_t tb_fp_analyse_count_instrumented(void *drcontext, instrlist_t *bb,
        uint case_val, ub_in_out_set_t *in_out_set);

void tb_fp_stat_inc_false_fp();
void tb_fp_stat_add_total(uint default_count);
void tb_fp_stat_add_elided(uint elide_count);
void tb_fp_stat_inc_fp_gen();
void tb_fp_stat_inc_static_fp_gen();
void tb_fp_stat_print_stats();
void tb_fp_stat_inc_conventional_exec_count();
void tb_fp_stat_inc_revert_exec_count();

#endif /* OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_STAT_H_ */

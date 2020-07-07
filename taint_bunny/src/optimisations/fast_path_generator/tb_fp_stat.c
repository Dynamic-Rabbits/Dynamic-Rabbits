/*
 * tb_fp_stat.c
 *
 *      Author: john
 */

#include "tb_fp_stat.h"
#include "tb_fp_helper.h"

static void *tb_stat_mutex;

unsigned long inc_false_fp = 0;
unsigned long total_default = 0;
unsigned long total_elided = 0;
unsigned long total_gen_fp_count = 0;
unsigned long total_static_fp_count = 0;
unsigned long conventional_exec_count = 0;
unsigned long revert_exec_count = 0;

void tb_fp_stat_init(){

    tb_stat_mutex = dr_mutex_create();
}

void tb_fp_stat_exit(){

    tb_fp_stat_print_stats();
    dr_mutex_destroy(tb_stat_mutex);
}

size_t tb_fp_analyse_count_instrumented(void *drcontext, instrlist_t *bb,
        uint case_val, ub_in_out_set_t *in_out_set) {

    size_t instrum_count = 0;

    /* Reconstruct the initial taint state. */
    void *taint_state = tb_fp_analyse_set_up_taint_state(case_val, in_out_set);

    size_t index = 0;
    /* Instrument according to analysis */
    instr_t *instr = instrlist_first_app(bb);
    while (instr != NULL) {

        // If instr deals with tainted data, apply instrumentation.
        if (ub_dataflow_is_instr_tainted(instr, taint_state)) {
            instrum_count++;
        }

        ub_dataflow_propagate(instr, taint_state);

        index++;
        instr = instr_get_next_app(instr);
    }

    ub_destroy_dataflow_analysis(taint_state);

    return instrum_count;
}

void tb_fp_stat_inc_false_fp() {

    dr_mutex_lock(tb_stat_mutex);
    inc_false_fp++;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_add_total(uint default_count) {

    dr_mutex_lock(tb_stat_mutex);
    total_default += default_count;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_add_elided(uint elide_count) {

    dr_mutex_lock(tb_stat_mutex);
    total_elided += elide_count;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_inc_fp_gen() {

    dr_mutex_lock(tb_stat_mutex);
    total_gen_fp_count++;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_inc_static_fp_gen() {

    dr_mutex_lock(tb_stat_mutex);
    total_static_fp_count++;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_inc_conventional_exec_count() {

    dr_mutex_lock(tb_stat_mutex);
    conventional_exec_count++;
    dr_mutex_unlock(tb_stat_mutex);
}

void tb_fp_stat_inc_revert_exec_count() {

    dr_mutex_lock(tb_stat_mutex);
    revert_exec_count++;
    dr_mutex_unlock(tb_stat_mutex);
}


void tb_fp_stat_print_stats() {

    dr_fprintf(STDERR, "---------------------------\n");

    dr_fprintf(STDERR, "Total False FP: %lu/%lu\n", inc_false_fp, total_gen_fp_count);
    dr_fprintf(STDERR, "Total ELIDED: %lu/%lu\n", total_elided, total_default);

    if (total_default)
    	dr_fprintf(STDERR, "Elision factor: %f\n\n", ((float)total_elided)/total_default);

    if (total_gen_fp_count)
    dr_fprintf(STDERR, "Avg ELIDED: %f\n\n",
            ((float) total_elided) / total_gen_fp_count);

    dr_fprintf(STDERR, "---------------------------\n");
}



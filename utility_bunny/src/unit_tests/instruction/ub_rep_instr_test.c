/*
 * ub_rep_instr_test.c
 *
 *      Author: john
 */

#include "../../instruction/ub_rep_instr.h"

static void ub_is_rep_movs_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_movs_1(drcontext);
    DR_ASSERT(ub_is_rep_movs_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_movs_4(drcontext);
    DR_ASSERT(ub_is_rep_movs_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_rep_movsb_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_movs_1(drcontext);
    DR_ASSERT(ub_is_rep_movsb_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_movs_4(drcontext);
    DR_ASSERT(!ub_is_rep_movsb_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);
}

static void ub_is_rep_movsd_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_movs_1(drcontext);
    DR_ASSERT(!ub_is_rep_movsd_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_movs_4(drcontext);
    DR_ASSERT(ub_is_rep_movsd_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_rep_stos_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_stos_1(drcontext);
    DR_ASSERT(ub_is_rep_stos_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_stos_4(drcontext);
    DR_ASSERT(ub_is_rep_stos_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_rep_stosb_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_stos_1(drcontext);
    DR_ASSERT(ub_is_rep_stosb_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_stos_4(drcontext);
    DR_ASSERT(!ub_is_rep_stosb_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

static void ub_is_rep_stosd_instr_test() {

    void *drcontext = dr_get_current_drcontext();

    instr_t *instr1 = INSTR_CREATE_rep_stos_1(drcontext);
    DR_ASSERT(!ub_is_rep_stosd_instr(instr1));

    instr_t *instr2 = INSTR_CREATE_rep_stos_4(drcontext);
    DR_ASSERT(ub_is_rep_stosd_instr(instr2));

    instr_destroy(drcontext, instr1);
    instr_destroy(drcontext, instr2);

}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ub_is_rep_movs_instr_test();
    ub_is_rep_movsb_instr_test();
    ub_is_rep_movsd_instr_test();
    ub_is_rep_stos_instr_test();
    ub_is_rep_stosb_instr_test();
    ub_is_rep_stosd_instr_test();
}


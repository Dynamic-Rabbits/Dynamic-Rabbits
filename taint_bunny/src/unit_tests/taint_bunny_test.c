/*
 * taint_bunny_test.c
 *
 *      Author: john
 */

#include "dr_defines.h"
#include <stdint.h>
#include "dr_defines.h"
#include "tb_defines.h"
#include "utility_bunny.h"
#include "drext.h"
#include "dr_api.h"
#include "../taint_bunny.h"

void *tb;

static void event_exit() {

    tb_cc_exit(tb);
    ib_exit();
}

static void taint_spec_mem_test() {

    tb_taint_mem(tb, (uintptr_t) 7, (void *) 1);

    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 7));

    bool is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 1, 8);
    DR_ASSERT(!is_all);

    is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 7, 1);
    DR_ASSERT(is_all);

    bool is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 7, 1);
    DR_ASSERT(is_some);

    is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 8);
    DR_ASSERT(is_some);

    is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 7);
    DR_ASSERT(is_some);

    is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 6);
    DR_ASSERT(!is_some);

    void* tl = tb_mem_get_taint_label(tb, (uintptr_t) 1);
    DR_ASSERT(tl == NULL);

    tl = tb_mem_get_taint_label(tb, (uintptr_t) 7);
    DR_ASSERT(tl == (void * ) 1);

    tb_untaint_mem(tb, (uintptr_t) 7);

    is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 8);
    DR_ASSERT(!is_some);

    is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 7, 1);
    DR_ASSERT(!is_all);

    tl = tb_mem_get_taint_label(tb, (uintptr_t) 7);
    DR_ASSERT(tl == NULL);
}

static void taint_block_mem_test() {

    tb_taint_mem_block(tb, (uintptr_t) 1, 3, (void *) 1);

    void *tl;
    tl = tb_mem_get_taint_label(tb, (uintptr_t) 1);
    DR_ASSERT(tl == (void * ) 1);
    tl = tb_mem_get_taint_label(tb, (uintptr_t) 2);
    DR_ASSERT(tl == (void * ) 1);
    tl = tb_mem_get_taint_label(tb, (uintptr_t) 3);
    DR_ASSERT(tl == (void * ) 1);
    tl = tb_mem_get_taint_label(tb, (uintptr_t) 4);
    DR_ASSERT(tl == NULL);

    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 1));
    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 2));
    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 3));
    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 4));

    bool is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 1, 3);
    DR_ASSERT(is_all);
    is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 1, 4);
    DR_ASSERT(!is_all);

    bool is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 8);
    DR_ASSERT(is_some);

    tb_untaint_mem(tb, (uintptr_t) 1);
    is_all = tb_is_mem_all_tainted(tb, (uintptr_t) 1, 3);
    DR_ASSERT(!is_all);

    is_some = tb_is_some_mem_tainted(tb, (uintptr_t) 1, 8);
    DR_ASSERT(is_some);

    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 2));
    DR_ASSERT(tb_is_mem_tainted(tb, (uintptr_t ) 3));
    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 4));

    tb_untaint_mem_block(tb, (uintptr_t) 2, 2);

    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 1));
    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 2));
    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 3));
    DR_ASSERT(!tb_is_mem_tainted(tb, (uintptr_t ) 4));

}

static void taint_spec_reg_test() {

    void *drcontext = dr_get_current_drcontext();

    bool tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(!tainted);

    void *tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == NULL);

    tb_taint_reg_byte(tb, drcontext, DR_REG_XAX, 0, (void *) 1);

    tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tainted);

    tainted = tb_is_reg_byte_tainted_via_byte_id(tb,
            drcontext, ub_get_byte_id(DR_REG_XAX, 0));
    DR_ASSERT(tainted);

    tainted = tb_is_all_reg_block_tainted_via_byte_id(tb,
            drcontext,  ub_get_byte_id(DR_REG_XAX, 0), 2);
    DR_ASSERT(!tainted);

    tainted = tb_is_all_reg_block_tainted_via_byte_id(tb,
            drcontext,  ub_get_byte_id(DR_REG_XAX, 0), 1);
    DR_ASSERT(tainted);

    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == (void *) 1);

    tb_untaint_reg_byte(tb, drcontext, DR_REG_XAX, 0);
    tb_untaint_reg_byte(tb, drcontext, DR_REG_XAX, 0);

    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == NULL);

    tb_taint_reg_byte(tb, drcontext, DR_REG_XAX, 0, (void *) 1);

    tainted = tb_is_reg_byte_tainted_via_byte_id(tb,
            drcontext, ub_get_byte_id(DR_REG_XAX, 0));
    DR_ASSERT(tainted);

    tb_untaint_reg(tb, drcontext, DR_REG_XAX);

    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == NULL);


}

static void taint_block_reg_test() {

    void *drcontext = dr_get_current_drcontext();

    bool tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(!tainted);

    void *tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == NULL);

    tb_taint_reg(tb, drcontext, DR_REG_XAX, (void *) 1);

    tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tainted);
    tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 1);
    DR_ASSERT(tainted);
    tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 2);
    DR_ASSERT(tainted);
     tainted = tb_is_reg_byte_tainted(tb, drcontext, DR_REG_XAX, 3);
    DR_ASSERT(tainted);

    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 0);
    DR_ASSERT(tl == (void *) 1);
    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 1);
    DR_ASSERT(tl == (void *) 1);
    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 2);
    DR_ASSERT(tl == (void *) 1);
    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 3);
    DR_ASSERT(tl == (void *) 1);

    tainted = tb_is_all_reg_block_tainted_via_byte_id(tb,
            drcontext,  ub_get_byte_id(DR_REG_XAX, 0), 4);
    DR_ASSERT(tainted);

    tainted = tb_is_some_reg_byte_tainted(tb, drcontext, DR_REG_XAX);
    DR_ASSERT(tainted);

    tb_untaint_reg_byte(tb, drcontext, DR_REG_XAX, 0);

    tainted = tb_is_all_reg_block_tainted_via_byte_id(tb,
            drcontext,  ub_get_byte_id(DR_REG_XAX, 0), 4);
    DR_ASSERT(!tainted);

    tainted = tb_is_some_reg_byte_tainted(tb, drcontext, DR_REG_XAX);
    DR_ASSERT(tainted);

    tb_untaint_reg(tb, drcontext, DR_REG_XAX);

    tl = tb_get_reg_byte_taint_label(tb, drcontext, DR_REG_XAX, 1);
    DR_ASSERT(tl == NULL);
}

static void thread_init(void *drcontext) {

    // Mem tests
    taint_spec_mem_test();
    taint_block_mem_test();

    // Reg tests
    taint_spec_reg_test();
    taint_block_reg_test();
}


DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    ib_init(NULL);

    tb_cc_taint_policy_t taint_policy;
    tb_cc_initialise_bitwise_taint_policy(&taint_policy);

    tb = tb_cc_init_default(id, &taint_policy);


    drmgr_register_thread_init_event(thread_init);
    dr_register_exit_event(event_exit);
}

/*
 * allocator_test2.c
 *
 *      Author: john
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include "../../utility_bunny.h"

typedef struct {

    int its;
    int just;
    int a;
    int prototype;
} prototype_t;

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

    drmgr_init();
    drutil_init();

    void *allocation_ctx = ub_create_fixed_allocator(1, sizeof(prototype_t));

    for (int i = 0; i < 5; i++) {

        prototype_t *prototype = (prototype_t *) ub_allocate(allocation_ctx);
        ub_deallocate(allocation_ctx, prototype);
    }

    for (int i = 0; i < 5; i++) {

        prototype_t *prototype = (prototype_t *) ub_allocate(allocation_ctx);
        prototype_t *prototype2 = (prototype_t *) ub_allocate(allocation_ctx);

        ub_deallocate(allocation_ctx, prototype);
        ub_deallocate(allocation_ctx, prototype2);
    }

    ub_destroy_fixed_allocator(allocation_ctx);

    drutil_exit();
    drmgr_exit();
}

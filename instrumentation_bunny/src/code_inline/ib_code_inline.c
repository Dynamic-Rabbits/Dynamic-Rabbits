/*
 * ib_code_inline.c
 *
 *      Author: john
 */

#include "ib_code_inline.h"
#include "../ib_data.h"
#include "utility_bunny.h"
#include <stddef.h>

typedef struct {

    void *user_data;
    ib_insert_hndle_func_t insert_code;

    void *spilling_user_data;
    ib_spill_regs_func_t spill_reg_func;
    ib_restore_regs_func_t restore_reg_func;

} ib_code_inline_t;

void *ib_code_inline_init(ib_insert_hndle_data_t *insert_hndle_data) {

    ib_code_inline_t *code_inline = (ib_code_inline_t *) dr_global_alloc(
            sizeof(ib_code_inline_t));

    code_inline->insert_code = insert_hndle_data->user_instrum_func;
    code_inline->user_data = insert_hndle_data->user_data;

    code_inline->spill_reg_func = insert_hndle_data->spill_reg_func;
    code_inline->spilling_user_data = insert_hndle_data->spilling_user_data;
    code_inline->restore_reg_func = insert_hndle_data->restore_reg_func;

    return (void *) code_inline;
}

void ib_code_inline_exit(void *code_inline_opaque) {

    ib_code_inline_t *code_inline = (ib_code_inline_t *) code_inline_opaque;

    DR_ASSERT(code_inline->insert_code);

    dr_global_free(code_inline, sizeof(ib_code_inline_t));
}

void ib_insert_code_inline(void *drcontext, instrlist_t *ilist, instr_t *where,
        instr_t *app_instr, void *code_inline_opaque) {

    ib_code_inline_t *code_inline = (ib_code_inline_t *) code_inline_opaque;

    void *spill_data = code_inline->spilling_user_data;

    if (code_inline->spill_reg_func)
        code_inline->spill_reg_func(drcontext, ilist, where, code_inline->user_data, &spill_data);

    code_inline->insert_code(drcontext, ilist, where, app_instr,
            code_inline->user_data, spill_data);

    if (code_inline->restore_reg_func)
        code_inline->restore_reg_func(drcontext, ilist, where, code_inline->user_data, spill_data);

}

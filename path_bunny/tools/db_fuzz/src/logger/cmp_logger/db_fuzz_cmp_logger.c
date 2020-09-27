/*
 * db_fuzz_cmp_logger.c
 *
 *      Author: john
 */

#include "db_fuzz_cmp_logger.h"
#include "../db_fuzz_print.h"

#include "dr_defines.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"
#include "string.h"
#include <stdio.h>
#include "path_bunny.h"

/***
 *
 * Keep calm it is a prototype.
 *
 * TODO:
 * 1) Reduce code repetition
 * 2) Document
 * 3) Rather than performing clean calls, use drx and perform clean call
 *    when a buffer is full. This is not really the main bottleneck as we
 *    only perform a clean-call upon tainted operands but nice to have in the
 *    future.
 */

FILE *cmp_log_file;


static void cmp_m_i_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    DR_ASSERT(num_bytes <= sizeof(intptr_t));

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "mem imm", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);

    const int start_index_disp = 3;

    for (int data_index = start_index_disp;
            data_index < num_bytes + start_index_disp;
            data_index++, src1_opnd++) {

        void *tb_label = tb_mem_get_taint_label(taint_bunny, src1_opnd);

        if (tb_label) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }
    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            /*
             * We use fprint because it is buffered. it *should* be okay to use
             * as opposed to dr_fprintf ... hopefully.
             */

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_mem_1_imm_1_log(void *taint_bunny) {

    cmp_m_i_log(taint_bunny, "8", 1);
}

static void insert_cmp_mem_1_imm_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_1_imm_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_2_imm_2_log(void *taint_bunny) {

    cmp_m_i_log(taint_bunny, "16", 2);
}

static void insert_cmp_mem_2_imm_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_2_imm_2_log,
    false, 1, OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_4_imm_4_log(void *taint_bunny) {

    cmp_m_i_log(taint_bunny, "32", 4);
}

static void insert_cmp_mem_4_imm_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_4_imm_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_r_i_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    DR_ASSERT(num_bytes <= sizeof(intptr_t));

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "reg imm", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);

    const int start_index_disp = 3;


    for (int data_index = start_index_disp;
            data_index < num_bytes + start_index_disp;
            data_index++, src1_opnd++) {

        void *tb_label = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, src1_opnd);

        if (tb_label) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }
    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            /*
             * We use fprint because it is buffered. it *should* be okay to use
             * as opposed to dr_fprintf ... hopefully.
             */

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_reg_1_imm_1_log(void *taint_bunny) {

    cmp_r_i_log(taint_bunny, "8", 1);
}

static void insert_cmp_reg_1_imm_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_1_imm_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_2_imm_2_log(void *taint_bunny) {

    cmp_r_i_log(taint_bunny, "16", 2);
}

static void insert_cmp_reg_2_imm_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_2_imm_2_log,
    false, 1, OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_4_imm_4_log(void *taint_bunny) {

    cmp_r_i_log(taint_bunny, "32", 4);
}

static void insert_cmp_reg_4_imm_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_4_imm_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_r_r_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    DR_ASSERT(num_bytes <= sizeof(intptr_t));

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "reg reg", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot2);

    for (int data_index = 3; data_index < num_bytes + 3;
            data_index++, src1_opnd++, src2_opnd++) {

        void *tb_label = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, src1_opnd);

        if (tb_label) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }

        void *tb_label2 = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, src2_opnd);

        if (tb_label2) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label2;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }
    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            // We use fprint because it is buffered. it *should* be okay to use
            // as opposed to dr_fprintf ... hopefully.

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_reg_1_reg_1_log(void *taint_bunny) {

    cmp_r_r_log(taint_bunny, "8", 1);
}

static void insert_cmp_reg_1_reg_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_1_reg_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_2_reg_2_log(void *taint_bunny) {

    cmp_r_r_log(taint_bunny, "16", 2);
}

static void insert_cmp_reg_2_reg_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_2_reg_2_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_4_reg_4_log(void *taint_bunny) {

    cmp_r_r_log(taint_bunny, "32", 4);
}

static void insert_cmp_reg_4_reg_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_4_reg_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_m_m_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    DR_ASSERT(num_bytes <= sizeof(intptr_t));

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "mem mem", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot2);

    for (int data_index = 3; data_index < num_bytes + 3;
            data_index++, src1_opnd++, src2_opnd++) {

        void *tb_label1 = tb_mem_get_taint_label(taint_bunny, src1_opnd);

        if (tb_label1) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label1;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }

        void *tb_label2 = tb_mem_get_taint_label(taint_bunny, src2_opnd);

        if (tb_label2) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label2;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }
    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            // We use fprint because it is buffered. it *should* be okay to use
            // as opposed to dr_fprintf ... hopefully.

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_mem_1_mem_1_log(void *taint_bunny) {

    cmp_m_m_log(taint_bunny, "8", 1);
}

static void insert_cmp_mem_1_mem_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_1_mem_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_2_mem_2_log(void *taint_bunny) {

    cmp_m_m_log(taint_bunny, "16", 2);
}

static void insert_cmp_mem_2_mem_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_2_mem_2_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_4_mem_4_log(void *taint_bunny) {

    cmp_m_m_log(taint_bunny, "32", 4);
}

static void insert_cmp_mem_4_mem_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_4_mem_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_m_r_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    DR_ASSERT(num_bytes <= sizeof(intptr_t));

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "mem reg", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot2);

    for (int data_index = 3; data_index < num_bytes + 3;
            data_index++, src1_opnd++, src2_opnd++) {

        void *tb_label1 = tb_mem_get_taint_label(taint_bunny, src1_opnd);

        if (tb_label1) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label1;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }

        void *tb_label2 = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, src2_opnd);

        if (tb_label2) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label2;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }

    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            // We use fprint because it is buffered. it *should* be okay to use
            // as opposed to dr_fprintf ... hopefully.

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_mem_1_reg_1_log(void *taint_bunny) {

    cmp_m_r_log(taint_bunny, "8", 1);
}

static void insert_cmp_mem_1_reg_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_1_reg_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_2_reg_2_log(void *taint_bunny) {

    cmp_m_r_log(taint_bunny, "16", 2);
}

static void insert_cmp_mem_2_reg_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_2_reg_2_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_mem_4_reg_4_log(void *taint_bunny) {

    cmp_m_r_log(taint_bunny, "32", 4);
}

static void insert_cmp_mem_4_reg_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_mem_4_reg_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_r_m_log(void *taint_bunny, char *size_in_str, size_t num_bytes) {

    bool is_tainted = false;

    void *drcontext = dr_get_current_drcontext();

    ub_opnd_access_t comp_access_slot;
    comp_access_slot.opnd_field = UB_SRC_OPND_1;
    comp_access_slot.comp_field = UB_COMP_1;

    ub_opnd_access_t comp_access_slot2;
    comp_access_slot2.opnd_field = UB_SRC_OPND_2;
    comp_access_slot2.comp_field = UB_COMP_1;

    // A data record is composed of 13 entries.
    char data[13][200];

    for (size_t i = 0; i < 13; i++) {
        strncpy(data[i], "{}", 200);
    }

    strncpy(data[0], size_in_str, 200);
    strncpy(data[1], "reg mem", 200);

    db_fuzz_store_pc(drcontext, data[2], 200);

    uintptr_t src1_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot);
    uintptr_t src2_opnd = ib_get_comp_opnd(drcontext, &comp_access_slot2);

    for (int data_index = 3; data_index < num_bytes + 3;
            data_index++, src1_opnd++, src2_opnd++) {

        void *tb_label = tb_get_reg_byte_taint_label_via_byte_id(taint_bunny,
                drcontext, src1_opnd);

        if (tb_label) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }

        void *tb_label2 = tb_mem_get_taint_label(taint_bunny, src2_opnd);

        if (tb_label2) {

            ub_bdd_node_t node = (ub_bdd_node_t) tb_label2;
            bool succ = db_fuzz_store_offsets_in_robdd(node, data[data_index], 200);

            is_tainted = is_tainted | succ;
        }
    }

    byte * array;
    array = ib_get_comp_conc(drcontext, &comp_access_slot);
    intptr_t conv_val1 = 0;
    memcpy(&conv_val1, array, num_bytes);
    db_fuzz_store_conc_val(conv_val1, data[11], 200);

    array = ib_get_comp_conc(drcontext, &comp_access_slot2);
    intptr_t conv_val2 = 0;
    memcpy(&conv_val2, array, num_bytes);
    db_fuzz_store_conc_val(conv_val2, data[12], 200);

    if (is_tainted) {

        for (int i = 0; i < 12; i++) {

            // We use fprint because it is buffered. it *should* be okay to use
            // as opposed to dr_fprintf ... hopefully.

            fprintf(cmp_log_file, "%s ", data[i]);
        }

        fprintf(cmp_log_file, "%s\n", data[12]);
    }
}

static void cmp_reg_1_mem_1_log(void *taint_bunny) {

    cmp_r_m_log(taint_bunny, "8", 1);
}

static void insert_cmp_reg_1_mem_1_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_1_mem_1_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_2_mem_2_log(void *taint_bunny) {

    cmp_r_m_log(taint_bunny, "16", 2);
}

static void insert_cmp_reg_2_mem_2_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_2_mem_2_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

static void cmp_reg_4_mem_4_log(void *taint_bunny) {

    cmp_r_m_log(taint_bunny, "32", 4);
}

static void insert_cmp_reg_4_mem_4_log(void *drcontext, instrlist_t *ilist,
        instr_t *where, void *user_data) {

    dr_insert_clean_call(drcontext, ilist, where, cmp_reg_4_mem_4_log, false, 1,
            OPND_CREATE_INTPTR(user_data));
}

void db_fuzz_init_pb_callbacks(path_bunny_funcs_t *funcs) {

    /**
     * We share routines.... we can be a bit more precise for better perf
     *  but not worth it for maintainability.
     */

    funcs->pb_cmp_tainted_reg_1_mem_1_func = insert_cmp_reg_1_mem_1_log;
    funcs->pb_cmp_reg_1_tainted_mem_1_func = insert_cmp_reg_1_mem_1_log;
    funcs->pb_cmp_tainted_reg_1_tainted_mem_1_func = insert_cmp_reg_1_mem_1_log;

    funcs->pb_cmp_tainted_reg_2_mem_2_func = insert_cmp_reg_2_mem_2_log;
    funcs->pb_cmp_reg_2_tainted_mem_2_func = insert_cmp_reg_2_mem_2_log;
    funcs->pb_cmp_tainted_reg_2_tainted_mem_2_func = insert_cmp_reg_2_mem_2_log;

    funcs->pb_cmp_tainted_reg_4_mem_4_func = insert_cmp_reg_4_mem_4_log;
    funcs->pb_cmp_reg_4_tainted_mem_4_func = insert_cmp_reg_4_mem_4_log;
    funcs->pb_cmp_tainted_reg_4_tainted_mem_4_func = insert_cmp_reg_4_mem_4_log;

    funcs->pb_cmp_tainted_reg_8_mem_8_func = NULL;
    funcs->pb_cmp_reg_8_tainted_mem_8_func = NULL;
    funcs->pb_cmp_tainted_reg_8_tainted_mem_8_func = NULL;

    funcs->pb_cmp_tainted_reg_16_mem_16_func = NULL;
    funcs->pb_cmp_reg_16_tainted_mem_16_func = NULL;
    funcs->pb_cmp_tainted_reg_16_tainted_mem_16_func = NULL;

    funcs->pb_cmp_tainted_mem_1_reg_1_func = insert_cmp_mem_1_reg_1_log;
    funcs->pb_cmp_mem_1_tainted_reg_1_func = insert_cmp_mem_1_reg_1_log;
    funcs->pb_cmp_tainted_mem_1_tainted_reg_1_func = insert_cmp_mem_1_reg_1_log;

    funcs->pb_cmp_tainted_mem_2_reg_2_func = insert_cmp_mem_2_reg_2_log;
    funcs->pb_cmp_mem_2_tainted_reg_2_func = insert_cmp_mem_2_reg_2_log;
    funcs->pb_cmp_tainted_mem_2_tainted_reg_2_func = insert_cmp_mem_2_reg_2_log;

    funcs->pb_cmp_tainted_mem_4_reg_4_func = insert_cmp_mem_4_reg_4_log;
    funcs->pb_cmp_mem_4_tainted_reg_4_func = insert_cmp_mem_4_reg_4_log;
    funcs->pb_cmp_tainted_mem_4_tainted_reg_4_func = insert_cmp_mem_4_reg_4_log;

    funcs->pb_cmp_tainted_mem_8_reg_8_func = NULL;
    funcs->pb_cmp_mem_8_tainted_reg_8_func = NULL;
    funcs->pb_cmp_tainted_mem_8_tainted_reg_8_func = NULL;

    funcs->pb_cmp_tainted_mem_16_reg_16_func = NULL;
    funcs->pb_cmp_mem_16_tainted_reg_16_func = NULL;
    funcs->pb_cmp_tainted_mem_16_tainted_reg_16_func = NULL;

    funcs->pb_cmp_tainted_reg_1_reg_1_func = insert_cmp_reg_1_reg_1_log;
    funcs->pb_cmp_reg_1_tainted_reg_1_func = insert_cmp_reg_1_reg_1_log;
    funcs->pb_cmp_tainted_reg_1_tainted_reg_1_func = insert_cmp_reg_1_reg_1_log;

    funcs->pb_cmp_tainted_reg_2_reg_2_func = insert_cmp_reg_2_reg_2_log;
    funcs->pb_cmp_reg_2_tainted_reg_2_func = insert_cmp_reg_2_reg_2_log;
    funcs->pb_cmp_tainted_reg_2_tainted_reg_2_func = insert_cmp_reg_2_reg_2_log;

    funcs->pb_cmp_tainted_reg_4_reg_4_func = insert_cmp_reg_4_reg_4_log;
    funcs->pb_cmp_reg_4_tainted_reg_4_func = insert_cmp_reg_4_reg_4_log;
    funcs->pb_cmp_tainted_reg_4_tainted_reg_4_func = insert_cmp_reg_4_reg_4_log;

    funcs->pb_cmp_tainted_reg_8_reg_8_func = NULL;
    funcs->pb_cmp_reg_8_tainted_reg_8_func = NULL;
    funcs->pb_cmp_tainted_reg_8_tainted_reg_8_func = NULL;

    funcs->pb_cmp_tainted_reg_16_reg_16_func = NULL;
    funcs->pb_cmp_reg_16_tainted_reg_16_func = NULL;
    funcs->pb_cmp_tainted_reg_16_tainted_reg_16_func = NULL;

    funcs->pb_cmp_tainted_reg_1_imm_1_func = insert_cmp_reg_1_imm_1_log;
    funcs->pb_cmp_tainted_reg_2_imm_2_func = insert_cmp_reg_2_imm_2_log;
    funcs->pb_cmp_tainted_reg_4_imm_4_func = insert_cmp_reg_4_imm_4_log;
    funcs->pb_cmp_tainted_reg_8_imm_8_func = NULL;

    funcs->pb_cmp_tainted_mem_1_imm_1_func = insert_cmp_mem_1_imm_1_log;
    funcs->pb_cmp_tainted_mem_2_imm_2_func = insert_cmp_mem_2_imm_2_log;
    funcs->pb_cmp_tainted_mem_4_imm_4_func = insert_cmp_mem_4_imm_4_log;
    funcs->pb_cmp_tainted_mem_8_imm_8_func = NULL;

    funcs->pb_cmp_tainted_mem_1_mem_1_func = insert_cmp_mem_1_mem_1_log;
    funcs->pb_cmp_mem_1_tainted_mem_1_func = insert_cmp_mem_1_mem_1_log;
    funcs->pb_cmp_tainted_mem_1_tainted_mem_1_func = insert_cmp_mem_1_mem_1_log;

    funcs->pb_cmp_tainted_mem_2_mem_2_func = insert_cmp_mem_2_mem_2_log;
    funcs->pb_cmp_mem_2_tainted_mem_2_func = insert_cmp_mem_2_mem_2_log;
    funcs->pb_cmp_tainted_mem_2_tainted_mem_2_func = insert_cmp_mem_2_mem_2_log;

    funcs->pb_cmp_tainted_mem_4_mem_4_func = insert_cmp_mem_4_mem_4_log;
    funcs->pb_cmp_mem_4_tainted_mem_4_func = insert_cmp_mem_4_mem_4_log;
    funcs->pb_cmp_tainted_mem_4_tainted_mem_4_func = insert_cmp_mem_4_mem_4_log;

    funcs->pb_cmp_tainted_mem_8_mem_8_func = NULL;
    funcs->pb_cmp_mem_8_tainted_mem_8_func = NULL;
    funcs->pb_cmp_tainted_mem_8_tainted_mem_8_func = NULL;
}


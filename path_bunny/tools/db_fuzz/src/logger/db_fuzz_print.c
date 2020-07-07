/*
 * db_fuzz_print.c
 *
 *      Author: john
 */

#include "instrumentation_bunny.h"
#include "string.h"

// VUzzer limits the number of offsets considered to 4
static const int offset_limit = 4;

typedef struct {

    void *buf;
    size_t size;
} offset_buff_t;

void db_fuzz_store_pc(void *drcontext, char *buf_pc, size_t size) {

    dr_snprintf(buf_pc, size, "%p", ib_get_pc(drcontext));
}

void db_fuzz_store_conc_val(uintptr_t src_conc, char *buf_conc, size_t size) {

    dr_snprintf(buf_conc, size, "%p", src_conc);
}

static void add_elem(void *elem, void *buf_opaque) {

    int val = (int) (intptr_t) elem;

    offset_buff_t *offset_buf = (offset_buff_t *) buf_opaque;

    char int_buf[100];
    size_t partial_size = dr_snprintf(int_buf, 100, "%d,", val);
    strncat(offset_buf->buf, int_buf, offset_buf->size);

    offset_buf->size -= partial_size;
}

bool db_fuzz_store_offsets_in_robdd(ub_bdd_node_t node, char *buf_offset,
        size_t buf_size) {

    bool succ = false;

    strncpy(buf_offset, "{", buf_size);
    buf_size--;

    ub_bitvect_t *vect = ub_bdd_get_bit_vect(node);

    size_t num_bit_sets = ub_bitvect_get_num_of_bit_sets(vect);

    if (num_bit_sets <= offset_limit) {

        size_t size = ub_bitvect_get_size(vect);

        offset_buff_t offset_buf;
        offset_buf.buf = buf_offset;
        offset_buf.size = buf_size;

        for (size_t i = 0; i < size; i++) {

            if (ub_bitvect_get_bit(vect, i))
                add_elem((void *) (intptr_t) i, (void *) &offset_buf);
        }

        int length = strlen(buf_offset);
        // We need to delete the last comma
        buf_offset[length - 1] = '\0';
        offset_buf.size++;

        buf_size = offset_buf.size;

        succ = true;
    }

    strncat(buf_offset, "}", buf_size);

    ub_bitvect_destroy(vect);

    return succ;
}


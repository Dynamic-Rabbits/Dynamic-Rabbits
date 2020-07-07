/*
 * instr_parser.c
 *
 *      Author: john
 */

#include "ub_instr_parser.h"
#include "../instruction/ub_instruction_checker.h"
#include "../register/ub_register.h"

static ub_opnd_access_t ub_create_opnd_access(ub_opnd_field_t opnd_field,
        ub_comp_field_t comp_field);

void ub_dataflow_parse_cpuid(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 4;
    dataflow->num_opnds = 4;

    for (size_t i = 0; i < dataflow->num_flows; i++) {

        dataflow->opnd_access[i] = ub_create_opnd_access(UB_DST_OPND_1 + i,
                UB_COMP_1);
        dataflow->dataflow[i].dst = i;
        dataflow->dataflow[i].num_srcs = 0;
    }
}

void ub_dataflow_parse_untaint_1dst(instr_t *instr,
        ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 1;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 0;
}

void ub_dataflow_parse_imul(instr_t *instr, ub_instr_dataflow_t *dataflow) {


    dataflow->supported = true;

    if (instr_num_dsts(instr) == 2) {

        dataflow->num_flows = 2;

        dataflow->num_opnds = 3;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_2,
                UB_COMP_1);
        dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 0;
        dataflow->dataflow[0].num_srcs = 2;
        dataflow->dataflow[0].srcs[0] = 2;
        dataflow->dataflow[0].srcs[1] = 1;

        dataflow->dataflow[1].dst = 1;
        dataflow->dataflow[1].num_srcs = 2;
        dataflow->dataflow[1].srcs[0] = 2;
        dataflow->dataflow[1].srcs[1] = 1;

    } else if (instr_num_dsts(instr) == 1) {

        dataflow->num_flows = 1;

        if (opnd_is_immed(instr_get_src(instr, 0))) {
            dataflow->num_opnds = 1;
            dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1,
                    UB_COMP_1);

            dataflow->dataflow[0].dst = 0;
            dataflow->dataflow[0].num_srcs = 1;
            dataflow->dataflow[0].srcs[0] = 0;

        } else {

            dataflow->num_opnds = 3;
            dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1,
                    UB_COMP_1);
            dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_1,
                    UB_COMP_1);
            dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_2,
                    UB_COMP_1);

            dataflow->dataflow[0].dst = 0;
            dataflow->dataflow[0].num_srcs = 2;
            dataflow->dataflow[0].srcs[0] = 1;
            dataflow->dataflow[0].srcs[1] = 2;
        }
    }
}

void ub_dataflow_parse_div(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 3;
    dataflow->dataflow[0].srcs[0] = 0;
    dataflow->dataflow[0].srcs[1] = 1;
    dataflow->dataflow[0].srcs[2] = 2;

    dataflow->dataflow[1].dst = 2;
    dataflow->dataflow[1].num_srcs = 3;
    dataflow->dataflow[1].srcs[0] = 0;
    dataflow->dataflow[1].srcs[1] = 1;
    dataflow->dataflow[1].srcs[2] = 2;

}

void ub_dataflow_parse_cmpxchg(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;

    dataflow->dataflow[1].dst = 2;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 1;
}

void ub_dataflow_parse_2src_2dst(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    opnd_t src = instr_get_src(instr, 0);

    if (opnd_is_immed(src)) {

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_2,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 0;
        dataflow->dataflow[0].num_srcs = 1;
        dataflow->dataflow[0].srcs[0] = 0;

        dataflow->dataflow[1].dst = 1;
        dataflow->dataflow[1].num_srcs = 1;
        dataflow->dataflow[1].srcs[0] = 0;

    } else {

        dataflow->num_opnds = 3;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_2,
                UB_COMP_1);
        dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 2;
        dataflow->dataflow[0].srcs[0] = 0;
        dataflow->dataflow[0].srcs[1] = 1;

        dataflow->dataflow[1].dst = 2;
        dataflow->dataflow[1].num_srcs = 2;
        dataflow->dataflow[1].srcs[0] = 0;
        dataflow->dataflow[1].srcs[1] = 1;
    }
}

void ub_dataflow_parse_shiftd(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;

    dataflow->num_flows = 1;

    if (opnd_is_immed(instr_get_src(instr, 1))) {

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 2;
        dataflow->dataflow[0].srcs[0] = 0;
        dataflow->dataflow[0].srcs[1] = 1;

    } else {

        dataflow->num_opnds = 3;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_2,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 3;
        dataflow->dataflow[0].srcs[0] = 0;
        dataflow->dataflow[0].srcs[1] = 1;
        dataflow->dataflow[0].srcs[2] = 2;
    }

}

void ub_dataflow_parse_rdtsc(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;

    dataflow->num_flows = 2;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 0;

    dataflow->dataflow[1].dst = 1;
    dataflow->dataflow[1].num_srcs = 0;

}

void ub_dataflow_parse_enter(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;

    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_3, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 2;

    dataflow->dataflow[1].dst = 2;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 0;
}

void ub_dataflow_parse_leave(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;

    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_3, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;

    dataflow->dataflow[1].dst = 0;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 2;
}

void ub_dataflow_parse_none(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 0;
    dataflow->num_opnds = 0;
}

void ub_dataflow_parse_xgetbv(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    // TODO For now I untaint the destinations, but should I taint based on ecx?

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 0;

    dataflow->dataflow[1].dst = 1;
    dataflow->dataflow[1].num_srcs = 0;
}

void ub_dataflow_parse_srcdst(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    opnd_t src = instr_get_src(instr, 0);
    if (opnd_is_immed(src)) {

        dataflow->num_opnds = 1;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 0;
        dataflow->dataflow[0].num_srcs = 1;
        dataflow->dataflow[0].srcs[0] = 0;

    } else {

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 2;
        dataflow->dataflow[0].srcs[0] = 0;
        dataflow->dataflow[0].srcs[1] = 1;
    }
}

void ub_dataflow_parse_xor(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    // e.g., xor eax, eax
    dataflow->supported = true;
    dataflow->num_flows = 1;

    if (opnd_same(instr_get_src(instr, 0), instr_get_dst(instr, 0))) {
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
    } else {
        ub_dataflow_parse_srcdst(instr, dataflow);
    }
}

void ub_dataflow_parse_pushf(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 1;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 0;
}

void ub_dataflow_parse_pusha(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 9;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_4, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_5, UB_COMP_1);
    dataflow->opnd_access[3] = ub_create_opnd_access(UB_SRC_OPND_3, UB_COMP_1);
    dataflow->opnd_access[4] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[5] = ub_create_opnd_access(UB_SRC_OPND_6, UB_COMP_1);
    dataflow->opnd_access[6] = ub_create_opnd_access(UB_SRC_OPND_7, UB_COMP_1);
    dataflow->opnd_access[7] = ub_create_opnd_access(UB_SRC_OPND_8, UB_COMP_1);
    dataflow->opnd_access[8] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 8;
    dataflow->dataflow[0].num_srcs = 8;
    dataflow->dataflow[0].srcs[0] = 0;
    dataflow->dataflow[0].srcs[1] = 1;
    dataflow->dataflow[0].srcs[2] = 2;
    dataflow->dataflow[0].srcs[3] = 3;
    dataflow->dataflow[0].srcs[4] = 4;
    dataflow->dataflow[0].srcs[5] = 5;
    dataflow->dataflow[0].srcs[6] = 6;
    dataflow->dataflow[0].srcs[7] = 7;
}

void ub_dataflow_parse_popa(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 8;

    dataflow->num_opnds = 9;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_4, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_5, UB_COMP_1);
    dataflow->opnd_access[3] = ub_create_opnd_access(UB_DST_OPND_3, UB_COMP_1);
    dataflow->opnd_access[4] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[5] = ub_create_opnd_access(UB_DST_OPND_6, UB_COMP_1);
    dataflow->opnd_access[6] = ub_create_opnd_access(UB_DST_OPND_7, UB_COMP_1);
    dataflow->opnd_access[7] = ub_create_opnd_access(UB_DST_OPND_8, UB_COMP_1);
    dataflow->opnd_access[8] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 8;

    dataflow->dataflow[1].dst = 0;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 8;

    dataflow->dataflow[2].dst = 0;
    dataflow->dataflow[2].num_srcs = 1;
    dataflow->dataflow[2].srcs[0] = 8;

    dataflow->dataflow[3].dst = 0;
    dataflow->dataflow[3].num_srcs = 1;
    dataflow->dataflow[3].srcs[0] = 8;

    dataflow->dataflow[4].dst = 0;
    dataflow->dataflow[4].num_srcs = 1;
    dataflow->dataflow[4].srcs[0] = 8;

    dataflow->dataflow[5].dst = 0;
    dataflow->dataflow[5].num_srcs = 1;
    dataflow->dataflow[5].srcs[0] = 8;

    dataflow->dataflow[6].dst = 0;
    dataflow->dataflow[6].num_srcs = 1;
    dataflow->dataflow[6].srcs[0] = 8;

    dataflow->dataflow[7].dst = 0;
    dataflow->dataflow[7].num_srcs = 1;
    dataflow->dataflow[7].srcs[0] = 8;
}

void ub_dataflow_parse_mov_st(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    if (opnd_is_immed(instr_get_src(instr, 0))) {
        ub_dataflow_parse_untaint_1dst(instr, dataflow);
    } else {

        ub_dataflow_parse_src_dst(instr, dataflow);
    }
}

void ub_dataflow_parse_loop(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 1;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;
}

void ub_dataflow_parse_xadd(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);

    // SRC + DST Flow
    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 2;
    dataflow->dataflow[0].srcs[0] = 0;
    dataflow->dataflow[0].srcs[1] = 1;

    // DST -> SRC
    dataflow->dataflow[1].dst = 1;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 0;
}

void ub_dataflow_parse_conditional_src_dst(instr_t *instr,
        ub_instr_dataflow_t *dataflow) {

    /* We over approximate here as we are not sure whether the conditional move will take place. */

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 2;
    dataflow->dataflow[0].srcs[0] = 0;
    dataflow->dataflow[0].srcs[1] = 1;

}

void ub_dataflow_parse_src_dst(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;
}

void ub_dataflow_parse_rep_movs(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_4, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;

    dataflow->dataflow[1].dst = 2;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 2;
}

void ub_dataflow_parse_rep_stos(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 2;

    dataflow->num_opnds = 3;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[2] = ub_create_opnd_access(UB_SRC_OPND_3, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;

    dataflow->dataflow[1].dst = 2;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 2;
}

void ub_dataflow_parse_same_src(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;
    dataflow->num_opnds = 1;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;
}

void ub_dataflow_parse_pop(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);

    dataflow->dataflow[0].dst = 1;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 0;
}

void ub_dataflow_parse_push(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    opnd_t src = instr_get_src(instr, 0);

    dataflow->supported = true;
    dataflow->num_flows = 1;

    if (opnd_is_immed(src)) {

        dataflow->num_opnds = 1;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_2,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 0;
        dataflow->dataflow[0].num_srcs = 0;

    } else {

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_1);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_2,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 1;
        dataflow->dataflow[0].srcs[0] = 0;
    }
}

void ub_dataflow_parse_call(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    dataflow->num_opnds = 1;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 0;
}

void ub_dataflow_parse_lea(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;
    dataflow->num_flows = 1;

    opnd_t lea_opnd = instr_get_src(instr, 0);

    reg_id_t base = opnd_get_base(lea_opnd);
    reg_id_t index = opnd_get_index(lea_opnd);

    if (base == DR_REG_NULL && index == DR_REG_NULL) {

        ub_dataflow_parse_untaint_1dst(instr, dataflow);

    } else if (base != DR_REG_NULL && index == DR_REG_NULL) {

        dataflow->num_flows = 1;

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_2);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 1;
        dataflow->dataflow[0].srcs[0] = 0;

    } else if (base == DR_REG_NULL && index != DR_REG_NULL) {

        dataflow->num_flows = 1;

        dataflow->num_opnds = 2;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_3);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 1;
        dataflow->dataflow[0].num_srcs = 1;
        dataflow->dataflow[0].srcs[0] = 0;

    } else {

        dataflow->num_flows = 1;

        dataflow->num_opnds = 3;
        dataflow->opnd_access[0] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_2);
        dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_1,
                UB_COMP_3);
        dataflow->opnd_access[2] = ub_create_opnd_access(UB_DST_OPND_1,
                UB_COMP_1);

        dataflow->dataflow[0].dst = 2;
        dataflow->dataflow[0].num_srcs = 2;
        dataflow->dataflow[0].srcs[0] = 0;
        dataflow->dataflow[0].srcs[1] = 1;
    }
}

void ub_dataflow_parse_xchg(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    dataflow->supported = true;

    dataflow->num_flows = 2;

    dataflow->num_opnds = 2;
    dataflow->opnd_access[0] = ub_create_opnd_access(UB_DST_OPND_1, UB_COMP_1);
    dataflow->opnd_access[1] = ub_create_opnd_access(UB_SRC_OPND_2, UB_COMP_1);

    dataflow->dataflow[0].dst = 0;
    dataflow->dataflow[0].num_srcs = 1;
    dataflow->dataflow[0].srcs[0] = 1;

    dataflow->dataflow[1].dst = 1;
    dataflow->dataflow[1].num_srcs = 1;
    dataflow->dataflow[1].srcs[0] = 0;
}

void ub_dataflow_parse_undefined(instr_t *instr, ub_instr_dataflow_t *dataflow) {

    /* For undefined, we consider all source operands for  each destination operand. */
    size_t num_srcs = 0;
    size_t num_dsts = instr_num_dsts(instr);

    dataflow->supported = false;

    // We need to exclude immeds and pcs.
    for (int i = 0; i < instr_num_srcs(instr); i++) {

        opnd_t src_opnd = instr_get_src(instr, i);

        if (ub_opnd_is_reg(&src_opnd) || opnd_is_memory_reference(src_opnd)) {

            dataflow->opnd_access[num_srcs] = ub_create_opnd_access(
                    UB_SRC_OPND_1 + i, UB_COMP_1);
            num_srcs++;
        }
    }

    dataflow->num_flows = num_dsts;
    dataflow->num_opnds = num_srcs + num_dsts;

    DR_ASSERT(dataflow->num_flows <= 12);

    size_t opnd_cntr = num_srcs;

    for (size_t i = 0; i < dataflow->num_flows; i++) {

        dataflow->opnd_access[opnd_cntr] = ub_create_opnd_access(
                UB_DST_OPND_1 + i, UB_COMP_1);

        dataflow->dataflow[i].dst = opnd_cntr;
        dataflow->dataflow[i].num_srcs = num_srcs;

        for (size_t j = 0; j < num_srcs; j++) {
            dataflow->dataflow[i].srcs[j] = j;
        }

        opnd_cntr++;
    }

    DR_ASSERT(opnd_cntr <= 12);
}

static ub_opnd_access_t ub_create_opnd_access(ub_opnd_field_t opnd_field,
        ub_comp_field_t comp_field) {

    ub_opnd_access_t opnd_access;

    opnd_access.opnd_field = opnd_field;
    opnd_access.comp_field = comp_field;

    return opnd_access;

}


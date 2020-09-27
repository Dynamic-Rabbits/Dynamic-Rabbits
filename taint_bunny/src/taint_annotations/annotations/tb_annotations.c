/*
 * tb_annotations.c
 *
 *      Author: john
 */

#include "annotations/dr_annotations.h"

DR_DEFINE_ANNOTATION(void, tr_annotate_taint,
		(void *start, size_t size), )

DR_DEFINE_ANNOTATION(void, tr_annotate_untaint,
        (void *start, size_t size), )

/*
 * tb_annotations.h
 *
 *  Created on: 22 Aug 2019
 *      Author: john
 */

#ifndef TAINT_ANNOTATIONS_TB_ANNOTATIONS_H_
#define TAINT_ANNOTATIONS_TB_ANNOTATIONS_H_

#include "annotations/dr_annotations.h"

/* To simplify project configuration, this pragma excludes the file from GCC warnings. */
#ifdef __GNUC__
#    pragma GCC system_header
#endif

#define TR_TAINT(start, size) \
   DR_ANNOTATION(tr_annotate_taint, start, size)

#define TR_UNTAINT(start, size) \
   DR_ANNOTATION(tr_annotate_untaint, start, size)

#ifdef __cplusplus
extern "C" {
#endif

DR_DECLARE_ANNOTATION(void, tr_annotate_taint,
                      (void *start, size_t size));

DR_DECLARE_ANNOTATION(void, tr_annotate_untaint,
                      (void *start, size_t size));

#ifdef __cplusplus
}
#endif

#endif /* TAINT_ANNOTATIONS_TB_ANNOTATIONS_H_ */

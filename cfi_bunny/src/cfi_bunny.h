#ifndef CFI_BUNNY_H_
#define CFI_BUNNY_H_

#include "dr_defines.h"
#include "dr_api.h"

#include "utility_bunny.h"
#include "instrumentation_bunny.h"
#include "taint_bunny.h"

/**
 * Defines flags that specify what types of hijacking methods to
 * detect.
 */
typedef unsigned int CFIB_EV_DETECTION_OPT_t;
#define CFIB_EV_ERROR 0 /** This is an invalid definition. **/
#define CFIB_EV_DETECT_CALL 1
#define CFIB_EV_DETECT_RET 2
#define CFIB_EV_DETECT_JMP 4

typedef enum {
    CFIB_CALL_ATTACK, CFIB_JMP_ATTACK, CFIB_RET_ATTACK
} cfib_attack_type_t;

typedef void (*cfib_handle_detection_func_t)(cfib_attack_type_t type,
        ub_opnd_access_t *corrupt_slot, void *user_data);

DR_EXPORT void * cfib_init(void *taint_bunny, cfib_handle_detection_func_t detection_func,
        CFIB_EV_DETECTION_OPT_t detection_options, IB_INSTRUM_OPT instrum_opts,
        void *user_data);

DR_EXPORT void cfib_exit(void *cfi_bunny);

DR_EXPORT void cfib_register_hooks(void *cfi_ctx);

#endif /* CFI_BUNNY_H_ */

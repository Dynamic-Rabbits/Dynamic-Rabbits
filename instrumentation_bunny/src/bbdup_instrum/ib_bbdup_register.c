/*
 * ib_bbdup_register.c
 *
 *      Author: john
 */

#include "../ib_defines.h"
#include "dr_api.h"
#include <drmgr.h>
#include <drutil.h>
#include "../ib_data.h"

DR_EXPORT bool ib_register_case_value(void *drbbdup_ctx,
        uint case_val){

	drbbdup_status_t status = drbbdup_register_case_value(drbbdup_ctx, case_val);

	return status == DRBBDUP_SUCCESS;
}

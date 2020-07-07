/*
 * tb_fast_path_optimisation.h
 *
 *  Created on: 25 Nov 2018
 *      Author: john
 */

#ifndef OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_OPTIMISATION_H_
#define OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_OPTIMISATION_H_

#include "../../tb_bunny_private.h"

uint32_t tb_fast_path_get_reg_mask(reg_id_t reg_id);

void *tb_fast_path_init(client_id_t client_id, tb_context_t *tb_ctx, tb_fp_settings_t *fp_settings);

void tb_fast_path_exit();

#endif /* OPTIMISATIONS_FAST_PATH_GENERATOR_TB_FP_OPTIMISATION_H_ */

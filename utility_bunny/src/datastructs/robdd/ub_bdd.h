/*
 * bdd.h
 *
 *  Created on: 1 Jul 2018
 *      Author: john
 */

#ifndef DATASTRUCTS_ROBDD_BDD_H_
#define DATASTRUCTS_ROBDD_BDD_H_

#include "dr_defines.h"
#include "dr_api.h"
#include "drmgr.h"
#include "drutil.h"
#include "../vectors/ub_bitvector.h"

typedef void * ub_bdd_node_t;

DR_EXPORT ub_bdd_node_t ub_bdd_create();

DR_EXPORT void ub_bdd_destroy(ub_bdd_node_t root_node_opaque);

DR_EXPORT ub_bitvect_t* ub_bdd_get_bit_vect(ub_bdd_node_t node_opaque);

DR_EXPORT ub_bdd_node_t ub_bdd_insert(ub_bdd_node_t root_node, ub_bitvect_t *bit_vect);

DR_EXPORT ub_bdd_node_t ub_bdd_node_union(ub_bdd_node_t root_node_opaque,
        ub_bdd_node_t node_opaque, ub_bdd_node_t node2_opaque);

#endif /* DATASTRUCTS_ROBDD_BDD_H_ */

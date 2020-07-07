/**
 * ub_dr_hashmap.c
 *
 *      Author: john
 */

#include "ub_hashmap.h"
#include "../lists/ub_list.h"
#include "hashtable.h"

void ub_hashmap_destroy_map(void *map_opaque,
        ub_destroy_value_func_t detroy_val_func) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;

    if (detroy_val_func) {
        hashtable_apply_to_all_payloads(hashtable, detroy_val_func);
    }

    hashtable_delete(hashtable);
    dr_global_free(hashtable, sizeof(hashtable_t));
}

void ub_hashmap_apply_all_values(void *map_opaque,
        void (*apply_func)(void *value)) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    hashtable_apply_to_all_payloads(hashtable, apply_func);

}

void ub_hashmap_apply_all_values_ex(void *map_opaque,
        void (*apply_func)(void *value, void *user_data), void *user_data) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;

    hashtable_apply_to_all_payloads_user_data(hashtable, apply_func, user_data);
}

void *ub_hashmap_insert_entry(void *map_opaque,
        ub_key_value_pair_t *key_val_pair) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    DR_ASSERT(hashtable);

    void *val = NULL;

    val = hashtable_add_replace(hashtable, (void *) key_val_pair->key,
            key_val_pair->value);

    return val;
}

void *ub_hashmap_lookup_entry(void *map_opaque, uintptr_t key) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    DR_ASSERT(hashtable);

    void *val = NULL;

    val = hashtable_lookup(hashtable, (void *) key);

    return val;
}

void *ub_hashmap_remove_entry(void *map_opaque, uintptr_t key) {

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    DR_ASSERT(hashtable);

    void *val = hashtable_lookup(hashtable, (void *) key);

    if (val) {
        bool is_removed = hashtable_remove(hashtable, (void *) key);
        DR_ASSERT(is_removed);
        return val;
    }

    return NULL;
}


void ub_hashmap_lock(void *map_opaque){

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    DR_ASSERT(hashtable);


    hashtable_lock(hashtable);
}

void ub_hashmap_unlock(void *map_opaque){

    hashtable_t *hashtable = (hashtable_t *) map_opaque;
    DR_ASSERT(hashtable);


    hashtable_unlock(hashtable);
}



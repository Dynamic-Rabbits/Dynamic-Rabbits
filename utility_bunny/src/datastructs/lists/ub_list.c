/**
 *  @author John F.X Galea
 */

/*TODO: Optimise linked list with more efficient lookups*/

#include "ub_list.h"

#include "dr_api.h"
#include <stddef.h>

/**
 *  @struct list_node_t
 *
 *  @var list_t::value
 *  A function pointer that safely destroys an element in the list
 *
 *  @var list_t::next
 *  Keep track of the number of elements in the list
 */
typedef struct list_node {

	void *value;
	struct list_node *next;
	struct list_node *prev;

} ub_list_node_t;

/**
 *  @struct list_t
 *
 *  @var list_t::destroy_value_func
 *  A function pointer that safely destroys an element in the list
 *
 *  @var list_t::count
 *  Keep track of the number of elements in the list
 *
 *  @var list_t::head
 *  Refers to the start node of the list
 */
typedef struct {

	size_t count;
	ub_list_node_t *head;
	ub_list_node_t *tail;
} ub_list_t;

DR_EXPORT void *ub_list_create() {

	ub_list_t *list = dr_global_alloc(sizeof(ub_list_t));

	list->count = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

DR_EXPORT void ub_list_destroy(void *list_opaque,
		ub_destroy_value_func_t destroy_val) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t *node = list->head;

	while (node != NULL) {

		// Iterate through list and clear.
		ub_list_node_t *freed_node = node;
		node = node->next;

		// Destroy value
		if (destroy_val)
			destroy_val(freed_node->value);

		// Destroy the struct
		dr_global_free(freed_node, sizeof(ub_list_node_t));
	}

	dr_global_free(list, sizeof(ub_list_t));
}

DR_EXPORT void ub_list_insert(void *list_opaque, void *value) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t *new_node = dr_global_alloc(sizeof(ub_list_node_t));
	new_node->value = value;
	new_node->next = NULL;

	if (list->tail != NULL) {

		DR_ASSERT(list->tail->next == NULL);
		list->tail->next = new_node;
		new_node->prev = list->tail;

	} else {
		DR_ASSERT(list->head == NULL);
		list->head = new_node;
		new_node->prev = NULL;
	}

	list->count++;
	list->tail = new_node;
}

/* Implement a block search */
DR_EXPORT void *ub_list_search(void *list_opaque, const void *value,
		ub_compare_func_t compare_func) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t *node = list->head;

	while (node != NULL) {

		if (compare_func(node->value, value))
			return node->value;

		node = node->next;
	}

	return NULL;
}

DR_EXPORT void* ub_list_get_head(void *list_opaque) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	if (list->head == NULL)
		return NULL;

	return list->head->value;
}

DR_EXPORT void ub_list_insert_at_ith(void *list_opaque, void *value,
		unsigned int index) {

	DR_ASSERT(index <= ub_list_get_size(list_opaque));

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t **next = &(list->head);
	ub_list_node_t *prev = NULL;

	/* Get to the point of insertion */
	while (index > 0) {
		DR_ASSERT(*next != NULL);
		index--;
		prev = *next;
		next = &((*next)->next);
	}

	ub_list_node_t *new_node = dr_global_alloc(sizeof(ub_list_node_t));
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;

	/* Next is at the head. */
	if (&(list->head) == next) {

		if (list->head == NULL) {
			list->tail = new_node;
		} else {
			new_node->next = list->head;
			list->head->prev = new_node;
		}

		list->head = new_node;

	} else if (*next != NULL) {

		new_node->next = *next;
		(*next)->prev = new_node;
		prev->next = new_node;

		DR_ASSERT(new_node->next != NULL);

	} else {
		DR_ASSERT(prev->next == NULL);

		prev->next = new_node;
		new_node->prev = prev;
		list->tail = new_node;
	}

	list->count++;
}

static void * ub_list_remove_helper(ub_list_t *list, ub_list_node_t **next,
		ub_list_node_t *prev) {

	ub_list_node_t *old_node = *next;
	*next = old_node->next;

	if (&(list->head) == next && *next == NULL) {
		/* List is empty now. */
		list->tail = NULL;
	} else if (list->tail == old_node) {
		DR_ASSERT(*next == NULL);
		/* Last node was deleted */
		list->tail = prev;
	} else {
		DR_ASSERT(*next != NULL);
		(*next)->prev = prev;
	}

	void *value = old_node->value;
	dr_global_free(old_node, sizeof(ub_list_node_t));

	list->count--;

	return value;
}

DR_EXPORT void * ub_list_remove_at_ith(void *list_opaque, unsigned int index) {

	DR_ASSERT(index < ub_list_get_size(list_opaque));

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t **next = &(list->head);
	ub_list_node_t *prev = NULL;

	while (index > 0) {
		DR_ASSERT(*next != NULL);
		index--;
		prev = *next;
		next = &((*next)->next);
	}

	return ub_list_remove_helper(list, next, prev);
}

DR_EXPORT void * ub_list_remove(void *list_opaque, const void *value,
		ub_compare_func_t compare_func) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t **next = &(list->head);
	ub_list_node_t *prev = NULL;

	while (*next != NULL) {

		if (compare_func((*next)->value, value))
			return ub_list_remove_helper(list, next, prev);

		prev = *next;
		next = &((*next)->next);
	}

	return NULL;
}

DR_EXPORT size_t ub_list_get_size(void *list_opaque) {

	DR_ASSERT(list_opaque);

	ub_list_t *list = (ub_list_t *) list_opaque;
	return list->count;
}

DR_EXPORT void *ub_list_get_ith_value(void *list_opaque, unsigned int index) {

	DR_ASSERT(list_opaque);
	DR_ASSERT(index < ub_list_get_size(list_opaque));

	//TODO This implementation is really stupid. Improve it in the future.
	void *it = ub_list_get_start_it(list_opaque);

	unsigned int count = 0;
	while (it != NULL) {

		if (count == index)
			return ub_list_get_it_value(it);

		count++;
		it = ub_list_get_next_it(it);
	}

	DR_ASSERT(false);

	return NULL;
}

DR_EXPORT void* ub_list_pop(void *list_opaque) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	ub_list_node_t *node = list->head;

	if (node) {

		list->head = node->next;

		if (list->head == NULL)
			list->tail = NULL;
		else
			list->head->prev = NULL;

		void *value = node->value;
		dr_global_free(node, sizeof(ub_list_node_t));

		list->count--;

		return value;
	}

	return NULL;
}

DR_EXPORT void *ub_list_get_start_it(void *list_opaque) {

	ub_list_t *list = (ub_list_t *) list_opaque;
	return list->head;
}

DR_EXPORT void *ub_list_get_end_it(void *list_opaque) {

	ub_list_t *list = (ub_list_t *) list_opaque;
	return list->tail;
}

DR_EXPORT void *ub_list_get_it_value(void * it_opaque) {

	if (it_opaque) {
		ub_list_node_t * it = (ub_list_node_t *) it_opaque;
		return it->value;
	}

	return NULL;
}

DR_EXPORT void *ub_list_insert_it_value(void *list_opaque, void * it_opaque,
		void *value) {

	ub_list_t *list = (ub_list_t *) list_opaque;

	if (it_opaque != NULL) {
		ub_list_node_t * it = (ub_list_node_t *) it_opaque;

		ub_list_node_t *new_node = dr_global_alloc(sizeof(ub_list_node_t));
		new_node->value = value;
		new_node->next = it->next;
		new_node->prev = it;
		it->next = new_node;

		if (new_node->next == NULL)
			list->tail = new_node;

		list->count++;
		return new_node;
	} else {
		ub_list_insert_at_ith(list, value, 0);
		return list->head;
	}
}

DR_EXPORT void *ub_list_get_next_it(void * it_opaque) {

	if (it_opaque != NULL) {
		ub_list_node_t * it = (ub_list_node_t *) it_opaque;
		return it->next;
	}

	return NULL;
}

DR_EXPORT void *ub_list_get_prev_it(void * it_opaque) {

	if (it_opaque != NULL) {
		ub_list_node_t * it = (ub_list_node_t *) it_opaque;
		return it->prev;
	}

	return NULL;
}


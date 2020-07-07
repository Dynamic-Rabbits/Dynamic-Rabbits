/**
 *  @file list.h
 *  @brief A list data structure
 *  @author John F.X. Galea
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include "../ub_datastruct.h"
#include "dr_defines.h"
#include "dr_api.h"

/**
 *  Creates and initialises a list.
 *
 *	@return A pointer to the created list or null if unsuccessful.
 */
DR_EXPORT void *ub_list_create();

/**
 *  Safely destroys a list.
 *
 *  @param destroy_value_func Pointer to function that cleanly destroys
 *  the value stored on the list
 */
DR_EXPORT void ub_list_destroy(void *list, ub_destroy_value_func_t destroy_val);

/**
 *  Inserts value to the list.
 *
 *  @param map The list to insert the new value
 *  @param value The value to insert
 */
DR_EXPORT void ub_list_insert(void *list, void *value);
/**
 *  Searches for the first value in the list that results in compare_func in
 *  returning true when compared with the passed value
 *
 *  @param list The list to perform search operation on
 *  @param value The value to search in the list
 *  @param compare_func A pointer to the comparison function
 *  @return The found value, or NULL if search fails
 */
DR_EXPORT void *ub_list_search(void *list, const void *value, ub_compare_func_t compare_func);



/**
 *  Removes entry from list.
 *
 *  @param list The list to perform search operation on
 *  @param value The value to remove in the list
 *  @param compare_func A pointer to a compare function that determines whether
 *  the value in the list to remove matches with the value passed as param
 *  @return Returns true on successful removal. False if no matching entry
 *  was found in the list.
 */
DR_EXPORT void * ub_list_remove(void *list, const void *value,
		ub_compare_func_t compare_func);

/**
 *  Retrieves the number of elements in the list
 *  @return Returns the number of elements
 */
DR_EXPORT size_t ub_list_get_size(void *list);

DR_EXPORT void* ub_list_get_head(void *list_opaque);

DR_EXPORT void ub_list_insert_at_ith(void *list_opaque, void *value, unsigned int index);

/**
 *  @return Removes the ith element in the list
 */
DR_EXPORT void * ub_list_remove_at_ith(void *list_opaque, unsigned int index);

/**
 * Returns the ith element in the list.
 */
DR_EXPORT void *ub_list_get_ith_value(void *list, unsigned int index);

/**
 *  Removes and returns the head of the list
 *  @return Returns NULL if the list is empty
 */
DR_EXPORT void* ub_list_pop(void *list);

/**
 *  @return Returns the starting iterator of the list, or NULL if the list
 *  is empty.
 */
DR_EXPORT void *ub_list_get_start_it(void *list);

/**
 *  @return Returns the end iterator of the list, or NULL if the list
 *  is empty.
 */
DR_EXPORT void *ub_list_get_end_it(void *list_opaque);

/**
 *  @return Returns the value at the given iterator
 */
DR_EXPORT void *ub_list_get_it_value(void * it);


/**
 *  @return Inserts and return the iterator at position of new node.
 */
DR_EXPORT void *ub_list_insert_it_value(void *list, void * it,
        void *value);

/**
 *  @return Returns the incremented iterator. Null if end is reached.
 */
DR_EXPORT void *ub_list_get_next_it(void * it);


/**
 *  @return Returns the decremented iterator. Null if end is reached.
 */
DR_EXPORT void *ub_list_get_prev_it(void * it_opaque);

#endif /* LIST_LIST_H_ */

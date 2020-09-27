/**
 *  @file ub_string.h
 *  @brief 
 *  @author John F.X. Galea
 */

#ifndef STRING_UB_STRING_H_
#define STRING_UB_STRING_H_

/**
 *  Copies string to the heap.
 *
 *  @param string The string to copy.
 *  @return Returns the new string copy.
 */
char *ub_string_create_copy(const char *string);

/**
 *  Deallocates a string stored on the heap created via
 *  \p ub_string_create_copy.
 *
 *  @param string The string to destroy.
 */
void ub_string_destroy(char *string);

#endif /* STRING_UB_STRING_H_ */

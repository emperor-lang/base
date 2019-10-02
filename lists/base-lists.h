#ifndef BASE_LISTS_H_
#define BASE_LISTS_H_

/**
 * @file base-lists.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Provides prototypes for functions on lists
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "../generics/base-generics.h"
#include "../unused/base-unused.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Stores a single value in a doubly linked list
 *
 */
typedef struct base_emperorListNode
{
	base_Any_t value;
	base_Any_t succ;
	base_Any_t prev;
} base_EmperorListNode_t;

/**
 * @brief Represents a doubly linked list
 *
 * This list is accessible from both ends, and a length is maintained.
 *
 */
typedef struct base_emperorList
{
	base_Any_t length;
	base_Any_t first;
	base_Any_t last;
} base_EmperorList_t;

/**
 * @brief Create an empty list
 *
 * @return base_Any_t
 */
base_Any_t base_initEmperorList(void);

/**
 * @brief Free the memory occupied by an emperor list, possibly also destroying its contents
 *
 * @param lst List to destroy
 * @param elementDestructor A function applied to each element
 */
void base_destroyEmperorList(base_Any_t lst, void (*elementDestructor)(base_Any_t));

/**
 * @brief Copy the top-level of a list
 * Any ints, chars, doubles or chars are copied literally, but referenced values have their references copied (i.e. both
 * the old and new lists refer to the same value.)
 *
 * @param lst The list to copy
 * @return base_Any_t The copied list
 */
base_Any_t base_shallowCopyList(base_Any_t lst);

/**
 * @brief Return whether the list is empty
 *
 * @param lst The list to check
 * @return true The list is empty
 * @return false The list is not empty
 */
bool base_isEmpty(base_Any_t lst);

/**
 * @brief Get the list element found at a given position
 *
 * @param lst The list to search
 * @param idx The index of the item to find
 * @return base_Any_t The value found
 */
base_Any_t base_get(base_Any_t lst, base_Any_t idx);

/**
 * @brief Remove an element from a list
 *
 * Note: this does not free the memory used by that element!
 *
 * @param lst The list to search
 * @param idx The index of the element
 * @param elementDestructor Function to apply to the deleted value
 * @return base_Any_t THe new list
 */
base_Any_t base_del(base_Any_t lst, base_Any_t idx, void (*elementDestructor)(base_Any_t));

/**
 * @brief Add a value to the _end_ of a list
 *
 * @param lst The list to be appended
 * @param value The value to append
 * @return base_Any_t The new list
 */
base_Any_t base_append(base_Any_t lst, base_Any_t value);

/**
 * @brief Add a value to the _front_ of a list
 *
 * @param lst The list to be prepended
 * @param value The value to prepend
 * @return base_Any_t The new list
 */
base_Any_t base_prepend(base_Any_t lst, base_Any_t value);

/**
 * @brief Concatenate two lists
 *
 * @param lst1 List to go at the start of the new list
 * @param lst2 List to go at the end of the new list
 * @return base_Any_t The new list: `lst1 ++ lst2`
 */
base_Any_t base_unite(base_Any_t lst1, base_Any_t lst2);

/**
 * @brief Convert create a list from an array
 *
 * @return base_Any_t The created list
 */
base_Any_t base_listFromArray(base_Any_t*, int);

/**
 * @brief Create an array from a list
 *
 * @return base_Any_t* Pointer to the start of the array
 */
base_Any_t* base_arrayFromList(base_Any_t);

/**
 * @brief Convert a C string to a list of characters
 *
 * @param str The string to convert
 * @return base_EmperorList_t* A list of characters
 */
base_Any_t base_stringToCharList(char* str);

/**
 * @brief Convert a string to a character list with a given length
 *
 * @param str String to convert
 * @param length Length of the string
 * @return base_Any_t A char list containing the string
 */
base_Any_t base_stringToCharListL(char* str, size_t length);

/**
 * @brief Convert a list of characters in to a C string
 *
 * @param lst A list of characters
 * @return char* A C string
 */
char* base_charListToString(base_Any_t lst);

#endif /* BASE_LISTS_H_ */

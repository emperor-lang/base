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
	struct base_emperorListNode* succ;
	struct base_emperorListNode* prev;
} base_EmperorListNode_t;

/**
 * @brief Represents a doubly linked list
 *
 * This list is accessible from both ends, and a length is maintained.
 *
 */
typedef struct base_emperorList
{
	int length;
	base_EmperorListNode_t* first;
	base_EmperorListNode_t* last;
} base_EmperorList_t;

/**
 * @brief Create an empty list
 *
 * @return base_EmperorList_t*
 */
base_EmperorList_t* base_initEmperorList(void);

/**
 * @brief Free the memory occupied by an emperor list, possibly also destroying its contents
 *
 * @param lst List to destroy
 * @param valueDestructor A function applied to each element
 */
void base_destroyEmperorList(base_EmperorList_t* lst, void (*elementDestructor)(base_Any_t));

/**
 * @brief Return whether the list is empty
 *
 * @param lst The list to check
 * @return true The list is empty
 * @return false The list is not empty
 */
bool base_isEmpty(base_EmperorList_t* lst);

/**
 * @brief Get the list element found at a given position
 *
 * @param lst The list to search
 * @param idx The index of the item to find
 * @return base_Any_t The value found
 */
base_Any_t base_get(base_EmperorList_t* lst, int idx);

/**
 * @brief Get the node in a list at a given position
 *
 * @param lst The list to search
 * @param idx The index of the node
 * @return base_EmperorListNode_t* A pointer to the node
 */
base_EmperorListNode_t* getNode(base_EmperorList_t* lst, int idx);

/**
 * @brief Get the node in a specified position, searching from the front of the list
 *
 * @param lst The list to search
 * @param idx The index of the node
 * @return base_EmperorListNode_t* A pointer to the node
 */
base_EmperorListNode_t* getFromFront(base_EmperorList_t* lst, int idx);

/**
 * @brief Get the node in a specified position, searching from the back of the list
 *
 * @param lst The list to search
 * @param idx The index of the node
 * @return base_EmperorListNode_t* A pointer to the node
 */
base_EmperorListNode_t* getFromBack(base_EmperorList_t* lst, int idx);

/**
 * @brief Remove an element from a list
 *
 * Note: this does not free the memory used by that element!
 *
 * @param lst The list to search
 * @param idx The index of the element
 * @return base_EmperorList_t* THe new list
 */
base_EmperorList_t* base_del(base_EmperorList_t* lst, int idx);

/**
 * @brief Add a value to the _end_ of a list
 *
 * @param lst The list to be appended
 * @param value The value to append
 * @return base_EmperorList_t* The new list
 */
base_EmperorList_t* base_append(base_EmperorList_t* lst, base_Any_t value);

/**
 * @brief Add a value to the _front_ of a list
 *
 * @param lst The list to be prepended
 * @param value The value to prepend
 * @return base_EmperorList_t* The new list
 */
base_EmperorList_t* base_prepend(base_EmperorList_t* lst, base_Any_t value);

/**
 * @brief Concatenate two lists
 *
 * @param lst1 List to go at the start of the new list
 * @param lst2 List to go at the end of the new list
 * @return base_EmperorList_t* The new list: `lst1 ++ lst2`
 */
base_EmperorList_t* base_unite(base_EmperorList_t* lst1, base_EmperorList_t* lst2);

/**
 * @brief Convert a C string to a list of characters
 *
 * @param str The string to convert
 * @return base_EmperorList_t* A list of characters
 */
base_EmperorList_t* base_stringToCharList(char* str);

/**
 * @brief Convert a list of characters in to a C string
 *
 * @param lst A list of characters
 * @return char* A C string
 */
char* base_charListToString(base_EmperorList_t* lst);

#endif /* BASE_LISTS_H_ */
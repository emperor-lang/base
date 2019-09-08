#ifndef BASE_REFERENCES_H_
#define BASE_REFERENCES_H_

/**
 * @file base-references.h
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines references (values with versions) and functions to handle them
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "../generics/base-generics.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief An identifier for a context
 *
 * This need not be globally unique but it must be unique in any reference tree
 * in which it appears.
 *
 */
typedef long int base_ReferenceIndex_t;

/**
 * @brief Represents a value in a given context
 */
typedef struct base_value
{
	/**
	 * @brief The value of the reference in the context given by idx
	 */
	base_Any_t value;
	/**
	 * @brief Index of this content
	 */
	base_ReferenceIndex_t idx;
	/**
	 * @brief The sub-tree of contexts with an index less than `idx`
	 */
	struct base_reference* leftChild;
	/**
	 * @brief The sub-tree of contexts with an index greater than `idx`
	 */
	struct base_reference* rightChild;
	/**
	 * @brief Flag indicates whether this reference may be freed (it is no longer required but is still necessary for
	 *        searching this unbalanced binary tree)
	 */
	bool canBeFreed;
} base_Value_t;

/**
 * @brief Stores context parent and identifier
 */
typedef struct base_referenceContext
{
	/**
	 * @brief The index of the current context
	 */
	base_ReferenceIndex_t idx;
	/**
	 * @brief The parent context
	 */
	const struct base_referenceContext* parent;
} base_ReferenceContext_t;

/**
 * @brief Represents a reference in a specified context
 */
typedef struct base_reference
{
	/**
	 * @brief The root value of the reference
	 */
	base_Value_t val;
	/**
	 * @brief The context of the reference
	 */
	base_ReferenceContext_t* ctx;
} base_Reference_t;

/**
 * @brief Obtain the value of a reference in the given context or its closest parent which has an associated value
 * 		  change
 *
 * @param ref The root of the reference tree to handle
 * @param ctx The required context
 * @return base_Any_t The value of the reference in the given context
 */
base_Any_t base_dereference(const base_Reference_t ref);

/**
 * @brief Make new reference in a specified context with a given value
 *
 * @param value The value of the new reference
 * @return base_Reference_t The new reference
 */
base_Reference_t* base_makeNewReference(base_Any_t value);

/**
 * @brief Create a change to a given reference in a given context
 *
 * @param ref The reference to change
 * @param ctx The context of the new change
 * @param value The value of the new change
 */
base_Reference_t base_authorReferenceChange(const base_Reference_t ref, base_Any_t value);

#endif /* BASE_REFERENCES_H_ */
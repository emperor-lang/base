#ifndef BASE_GENERICS_H_
#define BASE_GENERICS_H_

#include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
#include "../unused/base-unused.h"

// /**
//  * @brief An identifier for a context
//  *
//  * This need not be globally unique but it must be unique in any reference tree
//  * in which it appears.
//  *
//  */
// typedef long int base_ReferenceIndex_t;

// /**
//  * @brief Stores context parent and identifier
//  */
// typedef struct base_referenceContext
// {
// 	/**
// 	 * @brief The index of the current context
// 	 */
// 	base_ReferenceIndex_t idx;
// 	/**
// 	 * @brief The parent context
// 	 */
// 	const struct base_referenceContext* parent;
// } base_ReferenceContext_t;

// /**
//  * @brief Represents a value in a given context
//  */
// typedef struct base_pointerValue
// {
// 	/**
// 	 * @brief The value of the reference in the context given by idx
// 	 */
// 	void* value;
// 	/**
// 	 * @brief Index of this content
// 	 */
// 	base_ReferenceContext_t* ctx;
// 	/**
// 	 * @brief The sub-tree of contexts with an index less than `idx`
// 	 */
// 	struct base_reference* leftChild;
// 	/**
// 	 * @brief The sub-tree of contexts with an index greater than `idx`
// 	 */
// 	struct base_reference* rightChild;
// 	/**
// 	 * @brief Flag indicates whether this reference may be freed (it is no longer required but is still necessary for
// 	 *        searching this unbalanced binary tree)
// 	 */
// 	bool canBeFreed;
// } base_PointerValue_t;

// /**
//  * @brief Represents a reference in a specified context
//  */
// typedef struct base_reference
// {
// 	/**
// 	 * @brief The root value of the reference
// 	 */
// 	base_PointerValue_t val;
// 	/**
// 	 * @brief The context of the reference
// 	 */
// 	base_ReferenceContext_t* ctx;
// } base_Reference_t;

typedef struct base_any
{
	int intV;
	char charV;
	bool boolV;
	double doubleV;
	void* voidV;
} base_Any_t;

void base_noDestroy(base_Any_t _);

// /**
//  * @brief Obtain the value of a reference in the given context or its closest parent which has an associated value
//  * 		  change
//  *
//  * @param ref The root of the reference tree to handle
//  * @param ctx The required context
//  * @return base_Any_t The value of the reference in the given context
//  */
// void* base_dereference(const base_Reference_t* ref);

// /**
//  * @brief Make new reference in a specified context with a given value
//  *
//  * @param value The value of the new reference
//  * @param ctx The context of the reference
//  * @return base_Reference_t The new reference
//  */
// base_Any_t base_reference(void* obj, const base_ReferenceContext_t* ctx);

// /**
//  * @brief Create a change to a given reference in a given context
//  *
//  * @param ref The reference to change
//  * @param ctx The context of the new change
//  * @param value The value of the new change
//  */
// void base_authorReferenceChange(const base_Reference_t* ref, const base_ReferenceContext_t* ctx, void* value);

// /**
//  * @brief Make a new context as a child of a specified one
//  *
//  * @param ctx The parent of the new context
//  * @return const base_ReferenceContext_t* Pointer to the new context
//  */
// base_ReferenceContext_t* base_makeNewContext(const base_ReferenceContext_t* ctx);

#endif /* BASE_GENERICS_H_ */

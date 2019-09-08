/**
 * @file base-references.c
 * @author Ed Jones (ed@kcza.net)
 * @brief Defines functions to handle references
 * @version 0.1
 * @date 2019-09-06
 *
 * @copyright Copyright (c) 2019
 *
 */
#include "base-references.h"

/**
 * @brief Search a reference for a value in the context exactly specified by idx
 *
 * @param ref Pointer to the root of the reference tree to search
 * @param idx The context to search for
 * @return base_Any_t* A pointer to the value, or *NULL* if the required context is absent from the context tree (i.e.
 * 		   			   it makes no change)
 */
static base_Any_t* getReferenceValueByIndex(const base_Reference_t* ref, base_ReferenceIndex_t idx);

base_Any_t base_dereference(const base_Reference_t rootRef, const base_ReferenceContext_t ctx)
{
	base_Any_t* toReturn             = NULL;
	base_ReferenceContext_t* currCtx = (base_ReferenceContext_t*)&ctx;

	// Walk up the contexts until a change is seen
	while (true)
	{
		// Search down the reference tree to find whether a change has been made
		toReturn = getReferenceValueByIndex(&rootRef, currCtx->idx);
		if (toReturn != NULL)
		{
			return *toReturn;
		}
		else
		{
			currCtx = (base_ReferenceContext_t*)currCtx->parent;
		}
	}

	return *toReturn;
}

static base_Any_t* getReferenceValueByIndex(const base_Reference_t* ref, const base_ReferenceIndex_t idx)
{
	// Walk down the reference tree
	while (ref != NULL)
	{
		if (ref->idx < idx)
		{
			ref = ref->leftChild;
		}
		else if (ref->idx > idx)
		{
			ref = ref->rightChild;
		}
		else // ref.idxNode == idx
		{
			return (base_Any_t*)&ref->value;
		}
	}
	return NULL;
}

base_ReferenceContext_t base_makeNewContext(const base_ReferenceContext_t parent)
{
	// Generate the index of the new context;
	// Thanks, Uli Schlachter! https://stackoverflow.com/questions/3665257/generate-random-long-number
	base_ReferenceIndex_t idx = 0x0;
	for (long unsigned int i = 0; i < sizeof(base_ReferenceIndex_t) / sizeof(int); i++)
	{
		idx = (idx << (sizeof(int) * 8)) | rand();
	}

	return (base_ReferenceContext_t){ .parent = &parent, .idx = idx };
}

base_Reference_t base_makeNewReference(const base_ReferenceContext_t ctx, const base_Any_t value)
{
	return (
	    base_Reference_t){ .canBeFreed = false, .leftChild = NULL, .rightChild = NULL, .value = value, .idx = ctx.idx };
}

void base_authorReferenceChange(const base_Reference_t ref, const base_ReferenceContext_t ctx, const base_Any_t value)
{
	base_ReferenceIndex_t idx = ctx.idx;
	base_Reference_t* currRef = (base_Reference_t*)&ref;
	base_Reference_t* nextRef = NULL;

	while (true)
	{
		if (currRef->idx < idx)
		{
			nextRef = (base_Reference_t*)currRef->leftChild;
			if (nextRef == NULL)
			{
				base_Reference_t newRef = base_makeNewReference(ctx, value);
				currRef->leftChild      = &newRef;
				return;
			}
			currRef = nextRef;
		}
		else if (currRef->idx > idx)
		{
			nextRef = (base_Reference_t*)currRef->rightChild;
			if (nextRef == NULL)
			{
				base_Reference_t newRef = base_makeNewReference(ctx, value);
				currRef->rightChild     = &newRef;
				return;
			}
		}
		else
		{
			currRef->value = value;
		}
	}
}

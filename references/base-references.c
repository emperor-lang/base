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

base_Any_t base_dereference(base_Reference_t rootRef, base_ReferenceContext_t ctx)
{
	base_Any_t* toReturn             = NULL;
	base_ReferenceContext_t* currCtx = &ctx;

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
			currCtx = currCtx->parent;
		}
	}

	return *toReturn;
}

base_Any_t* getReferenceValueByIndex(base_Reference_t* ref, base_ReferenceIndex_t idx)
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
			return &ref->value;
		}
	}
	return NULL;
}

base_ReferenceContext_t* base_makeNewContext(base_ReferenceContext_t* parent)
{
	base_ReferenceContext_t* toReturn = (base_ReferenceContext_t*)malloc(sizeof(base_ReferenceContext_t));
	toReturn->parent                  = parent;

	// Generate the index of the new context;
	// Thanks, Uli Schlachter! https://stackoverflow.com/questions/3665257/generate-random-long-number
	base_ReferenceIndex_t idx = 0x0;
	for (long unsigned int i = 0; i < sizeof(base_ReferenceIndex_t) / sizeof(int); i++)
	{
		idx = (idx << (sizeof(int) * 8)) | rand();
	}

	toReturn->idx = idx;

	return toReturn;
}

base_Reference_t base_makeNewReference(base_ReferenceContext_t ctx, base_Any_t value)
{
	base_Reference_t ref;
	ref.canBeFreed = false;
	ref.leftChild  = NULL;
	ref.rightChild = NULL;
	ref.value      = value;
	ref.idx        = ctx.idx;
	return ref;
}

void base_authorReferenceChange(base_Reference_t ref, base_ReferenceContext_t ctx, base_Any_t value)
{
	base_ReferenceIndex_t idx = ctx.idx;
	base_Reference_t* currRef = &ref;
	base_Reference_t* nextRef = NULL;

	while (true)
	{
		if (currRef->idx < idx)
		{
			nextRef = currRef->leftChild;
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
			nextRef = currRef->rightChild;
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

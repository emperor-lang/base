#include "base-generics.h"

/**
 * @brief Search a reference for a value in the context exactly specified by idx
 *
 * @param ref Pointer to the root of the reference tree to search
 * @param idx The context to search for
 * @return base_Any_t* A pointer to the value, or *NULL* if the required context is absent from the context tree (i.e.
 * 		   			   it makes no change)
 */
static base_Any_t* getReferenceValueByIndex(const base_Reference_t* ref, base_ReferenceIndex_t idx);

/**
 * @brief Make a new context as a child of a specified one
 *
 * @param ctx The parent of the new context
 * @return const base_ReferenceContext_t* Pointer to the new context
 */
static base_ReferenceContext_t* makeNewContext(const base_ReferenceContext_t* ctx);

/**
 * @brief Make a new value in the context with a given index
 *
 * @param value The value to hold
 * @param idx The index of the context
 * @return base_Value_t* The stored value struct
 */
static base_Value_t* makeNewValue(const base_Any_t value, base_ReferenceIndex_t idx);

base_Any_t base_dereference(const base_Reference_t ref)
{
	base_Any_t* toReturn             = NULL;
	base_ReferenceContext_t* currCtx = (base_ReferenceContext_t*)ref.ctx;

	// Walk up the contexts until a change is seen
	while (true)
	{
		// Search down the reference tree to find whether a change has been made
		toReturn = getReferenceValueByIndex(&ref, currCtx->idx);
		if (toReturn != NULL)
		{
			return *toReturn;
		}
		else
		{
			if (currCtx != NULL)
			{
				currCtx = (base_ReferenceContext_t*)currCtx->parent;
			}
			else
			{
				printf("Failed to dereference pointer in context %ld, unable to find parent which defines a change",
				    ref.ctx->idx);
				exit(EXIT_FAILURE);
			}
		}
	}
}

static base_Any_t* getReferenceValueByIndex(const base_Reference_t* ref, const base_ReferenceIndex_t idx)
{
	// Walk down the reference tree
	base_Value_t* val;
	while (ref != NULL)
	{
		val = (base_Value_t*)&ref->val;
		if (ref->ctx->idx < idx)
		{
			ref = (base_Reference_t*)val->leftChild;
		}
		else if (ref->ctx->idx > idx)
		{
			ref = (base_Reference_t*)val->rightChild;
		}
		else // ref.idxNode == idx
		{
			return (base_Any_t*)&val->value;
		}
	}
	return NULL;
}

base_Reference_t* base_makeNewReference(const base_Any_t value)
{
	base_Reference_t* ref = (base_Reference_t*)malloc(sizeof(base_Reference_t));
	if (ref == NULL)
	{
		fprintf(stderr, "Failed to allocate space for new reference");
		exit(EXIT_FAILURE);
	}

	ref->ctx = makeNewContext(NULL);
	ref->val = *makeNewValue(value, ref->ctx->idx);

	return ref;
}

static base_Value_t* makeNewValue(const base_Any_t value, base_ReferenceIndex_t idx)
{
	base_Value_t* val = (base_Value_t*)malloc(sizeof(base_Value_t));
	val->leftChild    = NULL;
	val->rightChild   = NULL;
	val->value        = value;
	val->idx          = idx;
	val->canBeFreed   = false;

	return val;
}

base_Reference_t base_authorReferenceChange(const base_Reference_t ref, const base_Any_t value)
{
	base_ReferenceContext_t* ctx     = makeNewContext(ref.ctx);
	base_Reference_t* newRefTreeNode = (base_Reference_t*)malloc(sizeof(base_Reference_t));
	if (newRefTreeNode == NULL)
	{
		fprintf(stderr, "Failed to allocate space while authoring reference change\n");
		exit(EXIT_FAILURE);
	}
	// newRef->ctx                           = ctx;
	// (base_ReferenceContext_t*)newRef->val = &ref.val;

	base_Reference_t* currRef = (base_Reference_t*)&ref;
	base_Reference_t* nextRef;

	// Update the value tree here
	while (true)
	{
		if (currRef->ctx->idx < ctx->idx)
		{
			nextRef = (base_Reference_t*)currRef->val.leftChild;
			if (nextRef == NULL)
			{
				currRef->val.leftChild    = newRefTreeNode;
				base_Reference_t toReturn = (base_Reference_t){ .ctx = ctx, .val = value };
				return toReturn;
			}
			currRef = nextRef;
		}
		else if (currRef->ctx->idx > ctx->idx)
		{
			nextRef = (base_Reference_t*)currRef->val.rightChild;
			if (nextRef == NULL)
			{
				currRef->val.rightChild   = newRefTreeNode;
				base_Reference_t toReturn = (base_Reference_t){ .ctx = ctx, .val = value };
				return toReturn;
			}
			currRef = nextRef;
		}
		else // currRef->ctx->idx == ctx.idx
		{
			// Context by this index already exists, so get a new one and restart the search. (It is assumed that the
			// probability of many such collisions is extremely low.)
			free(ctx);
			ctx                 = makeNewContext(ref.ctx);
			currRef             = (base_Reference_t*)&ref;
			newRefTreeNode->ctx = ctx;
		}
	}
}

static base_ReferenceContext_t* makeNewContext(const base_ReferenceContext_t* parent)
{
	// Generate the index of the new context;
	// Thanks, Uli Schlachter! https://stackoverflow.com/questions/3665257/generate-random-long-number
	base_ReferenceIndex_t idx = 0x0;
	for (long unsigned int i = 0; i < sizeof(base_ReferenceIndex_t) / sizeof(int); i++)
	{
		idx = (idx << (sizeof(int) * 8)) | rand();
	}

	base_ReferenceContext_t* newCtx = (base_ReferenceContext_t*)malloc(sizeof(base_ReferenceContext_t));
	newCtx->parent                  = parent;
	newCtx->idx                     = idx;

	return newCtx;
}
#ifndef BASE_REFERENCES_H_
#define BASE_REFERENCES_H_

#include "../generics/base-generics.h"
#include <stdio.h>
#include <stdlib.h>

typedef const long int base_ReferenceIndex_t;

typedef struct base_referenceContext
{
	base_ReferenceIndex_t idx;
	struct base_referenceContext* parent;
} base_ReferenceContext_t;

typedef struct base_reference
{
	base_Any_t value;
	base_ReferenceIndex_t idx;
	struct base_reference* leftChild;
	struct base_reference* rightChild;
	bool canBeFreed;
} base_Reference_t;

base_Any_t base_dereference(base_Reference_t, base_ReferenceContext_t);
static base_Any_t* getReferenceValueByIndex(base_Reference_t*, base_ReferenceIndex_t);

base_ReferenceContext_t* base_makeNewContext(base_ReferenceContext_t*);
base_Reference_t base_makeNewReference(base_ReferenceContext_t, base_Any_t);
void base_authorReferenceChange(base_Reference_t, base_ReferenceContext_t, base_Any_t);

#endif /* BASE_REFERENCES_H_ */
#ifndef REFERENCES_H_
#define REFERENCES_H_

#include "../generics/base-generics.h"

typedef struct base_reference
{
	base_Any_t value;
	long int idx;
} base_Reference_t;

void* base_getValue(base_Reference_t, int);

#endif /* REFERENCES_H_ */
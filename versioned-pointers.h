#ifndef VERSIONED_POINTERS_H_
#define VERSIONED_POINTERS_H_

#include "generics.h"

typedef struct versionedPointer
{
	any_t value;
	long int idx;
} versionedPointer_t;

void* getValue(versionedPointer_t, int);

#endif /* VERSIONED_POINTERS_H_ */
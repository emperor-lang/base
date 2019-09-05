#ifndef VERSIONED_POINTERS_H_
#define VERSIONED_POINTERS_H_

#include "generics.h"

typedef struct base_versionedPointer
{
	base_Any_t value;
	long int idx;
} base_VersionedPointer_t;

void* base_getValue(base_VersionedPointer_t, int);

#endif /* VERSIONED_POINTERS_H_ */